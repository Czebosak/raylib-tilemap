#pragma once
#include <raylib.h>

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

struct Vector2i {
    i32 x;
    i32 y;

    Vector2i(i32 x, i32 y);
    
    static Vector2i zero();

    Vector2i operator+(const Vector2i rhs) const;
    Vector2i operator*(const Vector2i rhs) const;
    Vector2i operator*(const int rhs) const;
};

Vector2 v2itov2(Vector2i x);
Vector2i v2tov2i(Vector2 x);

struct Rectanglei {
    Vector2i pos, size;
};

