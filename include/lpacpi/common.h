#pragma once
#include <cstddef>
#include <cstdint>

template <typename T>
auto unused_value(T) -> void {}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isz = ptrdiff_t;

using c8 = char;
using c16 = wchar_t;
