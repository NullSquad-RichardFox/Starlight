#pragma once


enum class EInputAction
{
    Pressed,
    Triggered,
    Released
};

enum EModifierKeys : uint32
{
    MK_Shift  =     0b0000000000000001,
    MK_Control =    0b0000000000000010,
    MK_Alt =        0b0000000000000100,
    MK_Super =      0b0000000000001000,
};

enum class EKeyType
{

};

struct InputAction
{
    EKeyType Key; 
    EInputAction InputAction; 
    uint32 ModKeys;
};

class InputHandler
{
public:
    void BindKey(EKeyType key, std::function<void()> callback, EInputAction InputAction = EInputAction::Triggered, uint32 modKeys = 0);
    void ProcessKey(EKeyType key, EInputAction inputAction, uint32 modKeys);

private:
    std::unordered_map<InputAction, std::function<void()>> BoundKeys;
};