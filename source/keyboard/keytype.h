#ifndef _SUMMARY_KEY_COUNTER_KEYTYPE_H_
#define _SUMMARY_KEY_COUNTER_KEYTYPE_H_

#include <minwindef.h>
#include <windows.h>
#include <QString>

namespace keyboard
{
enum class KeyZone
{
    AlphaZone,
    NumericZone,
    SymbolZone,
    FuncZone,
    NavigationZone,
    ControlZone,
    SystemZone,
    EditZone,
    keyPadZone,
    Other
};

class KeyboardUtils
{
public:
    static KeyZone vkCodeType(DWORD key_code);
    static QString vkCode2String(DWORD key, bool remove_prefix = true);
};
} // namespace keyboard

#endif