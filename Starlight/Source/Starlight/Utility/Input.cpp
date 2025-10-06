#include "Input.h"

void InputSubsystem::Initialize()
{
    ASSERT(sInputSubsystem == nullptr, "Input subsystem was already initialized!");
    sInputSubsystem = new InputSubsystem();
}

void InputSubsystem::Shutdown()
{
    delete sInputSubsystem;
    sInputSubsystem = nullptr;
}

void InputSubsystem::BindKey_Int(EKeyType key, std::function<void()> callback, EInputAction inputAction, uint32 modKeys)
{
    InputBinding action;
    action.Key = key;
    action.InputAction = inputAction;
    action.ModKeys = modKeys;

    BoundKeys.push_back(action);
    BoundCallbacks.push_back(callback);
}

void InputSubsystem::BindMouse_Int(std::function<void(glm::vec2)> callback)
{
    MouseCallbacks.push_back(callback);
}

void InputSubsystem::ProcessKey_Int(EKeyType key, EInputAction inputAction, uint32 modKeys)
{
    ASSERT(BoundKeys.size() == BoundCallbacks.size(), "Array size mismatch!");

    for (uint32 i = 0; i < BoundKeys.size(); i++)
    {
        if (BoundKeys[i].Key == key && BoundKeys[i].InputAction == inputAction && (BoundKeys[i].ModKeys & modKeys) == modKeys)
        {
            BoundCallbacks[i]();
        }
    }
}

void InputSubsystem::ProcessMouse_Int(float xpos, float ypos)
{
    MousePosition += glm::vec2(xpos, ypos);

    for (const auto& callback : MouseCallbacks)
        callback(glm::vec2(xpos, ypos));
}
