#include "keytype.h"

using namespace keyboard;

KeyZone KeyboardUtils::vkCodeType(DWORD key_code)
{
    if (key_code >= 0x41 && key_code <= 0x5A)
    {
        return KeyZone::AlphaZone;
    }
    if (key_code >= 0x30 && key_code <= 0x39)
    {
        return KeyZone::NumericZone;
    }
    if (key_code >= 0x6A && key_code <= 0x6F)
    {
        return KeyZone::SymbolZone;
    }
    if (key_code >= 0x70 && key_code <= 0x87)
    {
        return KeyZone::FuncZone;
    }
    if (key_code >= 0x22 && key_code <= 0x28)
    {
        return KeyZone::NavigationZone;
    }
    if (key_code == VK_ESCAPE || key_code == VK_CONTROL || key_code == VK_LCONTROL || key_code == VK_RCONTROL ||
        key_code == VK_LMENU || key_code == VK_RMENU)
    {
        return KeyZone::ControlZone;
    }
    if (key_code >= 0x5B && key_code <= 0x5F)
    {
        return KeyZone::SystemZone;
    }
    if (key_code == VK_TAB || key_code == VK_RETURN || key_code == VK_CAPITAL || key_code == VK_SHIFT ||
        key_code == VK_SPACE || key_code == VK_INSERT || key_code == VK_DELETE || key_code == VK_BACK)
    {
        return KeyZone::EditZone;
    }
    if ((key_code >= 0x60 && key_code <= 0x69) || key_code == VK_NUMLOCK || key_code == VK_SCROLL ||
        key_code == VK_PAUSE)
    {
        return KeyZone::keyPadZone;
    }
    return KeyZone::Other;
}

QString KeyboardUtils::vkCode2String(DWORD key, bool remove_prefix)
{
    LONG lParam = MapVirtualKeyA(key, MAPVK_VK_TO_VSC) << 16;
    char key_name[128];
    int result = GetKeyNameTextA(lParam, key_name, sizeof(key_name));

    if (!result)
    {
        return {};
    }

    QString key_str{key_name};
    if (remove_prefix)
    {
        key_str.remove(0, 3);
    }
    return key_str;
}