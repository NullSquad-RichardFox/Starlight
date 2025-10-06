#include "Font.h"
#include "Texture.h"

#undef INFINITE
#include "msdf-atlas-gen/msdf-atlas-gen.h"


#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8


Font::Font(const std::filesystem::path& path)
{
    // Creating font resources
    msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
    ASSERT(ft, "FreeType failed to load!");

    msdfgen::FontHandle* font = msdfgen::loadFont(ft, path.string().c_str());
    ASSERT(font, "Font file failed to load!");

    // Font creation 
    double fontScale = 1.0;
    std::vector<msdf_atlas::GlyphGeometry> glyphs;
    auto fontGeometry = std::make_shared<msdf_atlas::FontGeometry>(&glyphs);
    int32 glyphsLoaded = fontGeometry->loadCharset(font, fontScale, msdf_atlas::Charset::ASCII);
    LOG("Loaded glyphs {0} out of {1}", glyphsLoaded, msdf_atlas::Charset::ASCII.size());

    double emSize = 32;
    msdf_atlas::TightAtlasPacker atlasPacker;
    atlasPacker.setPixelRange(2.0);
    atlasPacker.setMiterLimit(1.0);
    atlasPacker.setPadding(0);
    atlasPacker.setScale(emSize);
    int32 remaining = atlasPacker.pack(glyphs.data(), (int32)glyphs.size());

    int32 atlasWidth, atlasHeight;
    atlasPacker.getDimensions(atlasWidth, atlasHeight);
    emSize = atlasPacker.getScale();

    uint64_t coloringSeed = 0;
    msdf_atlas::Workload([&glyphs = glyphs, &coloringSeed](int32 i, int32 threadNo) -> bool {
        unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
        glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
        return true;
        }, (int32)glyphs.size()).finish(THREAD_COUNT);

    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = true;
    attributes.scanlinePass = true;

    msdf_atlas::ImmediateAtlasGenerator<float, 3, msdf_atlas::msdfGenerator, msdf_atlas::BitmapAtlasStorage<uint8_t, 3>> generator(atlasWidth, atlasHeight);
    generator.setAttributes(attributes);
    generator.setThreadCount(8);
    generator.generate(glyphs.data(), (int32)glyphs.size());

    msdfgen::BitmapConstRef<uint8_t, 3> bitmap = (msdfgen::BitmapConstRef<uint8_t, 3>)generator.atlasStorage();
    
    // Storing font data in custom data types
    FontTexture = std::make_shared<Texture>((void*)bitmap.pixels, bitmap.width, bitmap.height, 3);
    Kerning = fontGeometry->getKerning();

    LineHeight = (float)fontGeometry->getMetrics().lineHeight;
    AscenderY = (float)fontGeometry->getMetrics().ascenderY;
    DescenderY = (float)fontGeometry->getMetrics().descenderY;

    for (const auto& glyph : glyphs)
    {
        char c = glyph.getCodepoint();

        double lc, bc, rc, tc, ls, bs, rs, ts;
        glyph.getQuadAtlasBounds(lc, bc, rc, tc);
        glyph.getQuadPlaneBounds(ls, bs, rs, ts);

        CharTextCoords[c] = glm::vec4(lc / FontTexture->GetWidth(), bc / FontTexture->GetHeight(), rc / FontTexture->GetWidth(), tc / FontTexture->GetHeight());
        CharSizes[c] = glm::vec4(ls, bs, rs, ts);
        CharAdvance[c] = (float)glyph.getAdvance();
    }

    // Freeing font resources
    msdfgen::destroyFont(font);
    msdfgen::deinitializeFreetype(ft);
}

void Font::GetCharTextCoords(char c, glm::vec2& outTextCoordMin, glm::vec2& outTextCoordMax) const
{
    if (CharTextCoords.find(c) == CharTextCoords.end()) return;

    glm::vec4 charTextCoord = CharTextCoords.at(c);
    outTextCoordMin = glm::vec2(charTextCoord.x, charTextCoord.y);
    outTextCoordMax = glm::vec2(charTextCoord.z, charTextCoord.w);
}

void Font::GetCharSize(char c, float scale, glm::vec2& outSizeMin, glm::vec2& outSizeMax) const
{
    if (CharSizes.find(c) == CharSizes.end()) return;
    
    glm::vec4 charSize = CharSizes.at(c);
    float fsScale = scale / (AscenderY - DescenderY);
    outSizeMin = glm::vec2(charSize.x, charSize.y) * fsScale;
    outSizeMax = glm::vec2(charSize.z, charSize.w) * fsScale;
}

float Font::GetAdvance(char char1, char char2, float scale) const
{
    if (CharAdvance.find(char1) == CharAdvance.end()) return 0.0f;

    float advance = CharAdvance.at(char1);
    if (auto it = Kerning.find(std::make_pair<int, int>(char1, char2)); it != Kerning.end())
    {
        advance += (float)it->second;
    }

    float fsScale = scale / (AscenderY - DescenderY);
    return advance * fsScale;
}
