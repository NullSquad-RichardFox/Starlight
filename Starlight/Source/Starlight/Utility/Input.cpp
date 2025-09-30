#include "pcch.h"
#include "Input.h"


void InputHandler::BindKey(EKeyType key, std::function<void()> callback, EInputAction InputAction = EInputAction::Triggered, uint32 modKeys = 0)
{
    InputAction action;
    action.Key = key;
    action.InputAction = inputAction;
    action.ModKeys = modKeys;

    BoundKeys[action] = callback;
}

void InputHandler::ProcessKey(EKeyType key, EInputAction inputAction, uint32 modKeys)
{
    for (const auto& [action, callback] : BoundKeys)
    {
        if (action.Key == key && 
            action.InputAction == inputAction && 
            ((action.ModKeys & modKeys) == modKeys)) 
        {
            callback();
        }  
    }
}