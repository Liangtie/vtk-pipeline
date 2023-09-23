#ifndef __BETTER_ENUM_H__
#define __BETTER_ENUM_H__

#include "enum.h"

#define Enum(name, ...) BETTER_ENUM(name, int, __VA_ARGS__);

template<typename T>
inline constexpr auto betterEnumToString(T&& v)
{
    return (+v)._to_string();
}

#endif  // __BETTER_ENUM_H__