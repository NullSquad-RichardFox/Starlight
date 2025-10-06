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

void InputSubsystem::OnUpdate_Int(float deltaTime)
{
    for (const auto& key : ActiveKeys)
    {
        for (uint32 i = 0; i < BoundKeysPressed.size(); i++)
        {
            if (BoundKeysPressed[i].Key == key.Key && BoundKeysPressed[i].InputAction == key.InputAction && (BoundKeysPressed[i].ModKeys & key.ModKeys) == key.ModKeys)
            {
                BoundCallbacksPressed[i]();
            }
        }
    }
}

void InputSubsystem::BindKey_Int(EKeyType key, std::function<void()> callback, EInputAction inputAction, uint32 modKeys)
{
    InputBinding action;
    action.Key = key;
    action.InputAction = inputAction;
    action.ModKeys = modKeys;

    if (inputAction == EInputAction::Pressed)
    {
        BoundKeysPressed.push_back(action);
        BoundCallbacksPressed.push_back(callback);
    }
    else
    {
        BoundKeys.push_back(action);
        BoundCallbacks.push_back(callback);
    }
}

void InputSubsystem::BindMouse_Int(std::function<void(glm::vec2)> callback)
{
    MouseCallbacks.push_back(callback);
}

void InputSubsystem::ProcessKey_Int(EKeyType key, EInputAction inputAction, uint32 modKeys)
{
    ASSERT(BoundKeys.size() == BoundCallbacks.size(), "Array size mismatch!");

    LOG("{}", int(inputAction));

    for (uint32 i = 0; i < BoundKeys.size(); i++)
    {
        if (BoundKeys[i].Key == key && BoundKeys[i].InputAction == inputAction && (BoundKeys[i].ModKeys & modKeys) == modKeys)
        {
            BoundCallbacks[i]();
        }
    }

    for (uint32 i = 0; i < BoundKeysPressed.size(); i++)
    {
        if (BoundKeysPressed[i].Key == key && (BoundKeysPressed[i].ModKeys & modKeys) == modKeys)
        {
            if (inputAction == EInputAction::Triggered)
            {
                InputBinding action;
                action.Key = key;
                action.InputAction = EInputAction::Pressed;
                action.ModKeys = modKeys;
                ActiveKeys.push_back(action);
            }
            else if (inputAction == EInputAction::Released)
            {
                InputBinding action;
                action.Key = key;
                action.InputAction = EInputAction::Pressed;
                action.ModKeys = modKeys;

                if (auto it = std::find(ActiveKeys.begin(), ActiveKeys.end(), action); it != ActiveKeys.end())
                {
                    ActiveKeys.erase(it);
                }
                else
                {
                    LOG("Key was released without beeing pressed and recorded first!");
                }
            }
        }
    }
}

void InputSubsystem::ProcessMouse_Int(float xpos, float ypos)
{
    MousePosition += glm::vec2(xpos, ypos);

    for (const auto& callback : MouseCallbacks)
        callback(glm::vec2(xpos, ypos));
}
