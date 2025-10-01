#include "Font.h"
#include "Texture.h"


#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8


Font::Font(const std::filesystem::path& path)
{
    msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
    ASSERT(ft, "FreeType failed to load!");

    msdfgen::FontHandle* font = msdfgen::loadFont(ft, path.string().c_str());
    ASSERT(font, "Font file failed to load!");

    double fontScale = 1.0;

    FontGeometry = std::make_shared<msdf_atlas::FontGeometry>(&Glyphs);
    int32 glyphsLoaded = FontGeometry->loadCharset(font, fontScale, msdf_atlas::Charset::ASCII);
    LOG("Loaded glyphs {0} out of {1}", glyphsLoaded, msdf_atlas::Charset::ASCII.size());

    double emSize = 32;
    msdf_atlas::TightAtlasPacker atlasPacker;
    atlasPacker.setPixelRange(2.0);
    atlasPacker.setMiterLimit(1.0);
    atlasPacker.setPadding(0);
    atlasPacker.setScale(emSize);
    int32 remaining = atlasPacker.pack(Glyphs.data(), (int32)Glyphs.size());

    int32 atlasWidth, atlasHeight;
    atlasPacker.getDimensions(atlasWidth, atlasHeight);
    emSize = atlasPacker.getScale();

    uint64_t coloringSeed = 0;
    msdf_atlas::Workload([&glyphs = Glyphs, &coloringSeed](int32 i, int32 threadNo) -> bool {
        unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
        glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
        return true;
        }, (int32)Glyphs.size()).finish(THREAD_COUNT);

    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = true;
    //attributes.config.errorCorrection.mode = msdfgen::ErrorCorrectionConfig::DISABLED;
    attributes.scanlinePass = true;

    msdf_atlas::ImmediateAtlasGenerator<float, 3, msdf_atlas::msdfGenerator, msdf_atlas::BitmapAtlasStorage<uint8_t, 3>> generator(atlasWidth, atlasHeight);
    generator.setAttributes(attributes);
    generator.setThreadCount(8);
    generator.generate(Glyphs.data(), (int32)Glyphs.size());

    msdfgen::BitmapConstRef<uint8_t, 3> bitmap = (msdfgen::BitmapConstRef<uint8_t, 3>)generator.atlasStorage();
    FontTexture = std::make_shared<Texture>((void*)bitmap.pixels, bitmap.width, bitmap.height, 3);

    msdfgen::destroyFont(font);
    msdfgen::deinitializeFreetype(ft);
}

void Font::GetCharTextCoords(char c, glm::vec2& outTextCoordMin, glm::vec2& outTextCoordMax) const
{
    if (FontGeometry && FontTexture)
    {
        double l, b, r, t;
        FontGeometry->getGlyph(c)->getQuadAtlasBounds(l, b, r, t);
        outTextCoordMin = glm::vec2(l / FontTexture->GetWidth(), b / FontTexture->GetHeight());
        outTextCoordMax = glm::vec2(r / FontTexture->GetWidth(), t / FontTexture->GetHeight());
    }
}

void Font::GetCharSize(char c, float scale, glm::vec2& outSizeMin, glm::vec2& outSizeMax) const
{
    if (FontGeometry)
    {
        double l, b, r, t;
        FontGeometry->getGlyph(c)->getQuadPlaneBounds(l, b, r, t);

        double diff = (FontGeometry->getMetrics().ascenderY - FontGeometry->getMetrics().descenderY);
        double fsScale = (double)scale / diff;

        outSizeMin = glm::vec2(l * fsScale, b * fsScale);
        outSizeMax = glm::vec2(r * fsScale, t * fsScale);
    }
}

float Font::GetAdvance(char char1, char char2, float scale) const
{
    if (FontGeometry)
    {
        double adv;
        double diff = (FontGeometry->getMetrics().ascenderY - FontGeometry->getMetrics().descenderY);
        double fsScale = (double)scale / diff;
        FontGeometry->getAdvance(adv, char1, char2);
        return (float)adv * (float)fsScale;
    }

    return 0.0f;
}

float Font::GetAscenderY() const
{
    if (FontGeometry)
    {
        return (float)FontGeometry->getMetrics().ascenderY;
    }

    return 0.0f;
}

float Font::GetDescenderY() const
{
    if (FontGeometry)
    {
        return (float)FontGeometry->getMetrics().descenderY;
    }

    return 0.0f;
}

float Font::GetLineHeight() const
{
    if (FontGeometry)
    {
        return (float)FontGeometry->getMetrics().lineHeight;
    }

    return 0.0f;
}

glm::vec2 Font::GetTextSize(float renderScale, const std::string& text) const
{
    glm::vec2 outSize = glm::vec2();
    float totalWidth = 0;
    for (int32 i = 1; i < text.size(); i++)
    {
        totalWidth += GetAdvance(text[i - 1], text[i], 0.05f * renderScale);

    }

    glm::vec2 minSize, maxSize;
    GetCharSize(text[text.size() - 1], 0.05f * renderScale, minSize, maxSize);
    totalWidth += maxSize.x;
    outSize.x += totalWidth;

    outSize *= 540.f;

    return outSize;
}
