// Simple MATH library
#ifndef SMATH_H_
#define SMATH_H

#include <math.h>

typedef struct {
    int x;
    int y;
} Vec2i;

typedef struct {
    float x;
    float y;
} Vec2f;

static inline Vec2i vec2i(int x, int y);
static inline Vec2i vec2ii(int a);
static inline Vec2i vec2i_sub(Vec2i a, Vec2i b);
static inline Vec2i vec2i_add(Vec2i a, Vec2i b);
static inline Vec2i vec2i_mul(Vec2i a, Vec2i b);
static inline Vec2i vec2i_div(Vec2i a, Vec2i b);
static inline Vec2i vec2i_floor(Vec2i a);
static inline Vec2i vec2i_ceil(Vec2i a);
static inline Vec2f vec2f2i(Vec2i a);
static inline int   vec2i_sqrlen(Vec2i a);

static inline Vec2f vec2f(float x, float y);
static inline Vec2f vec2ff(float a);
static inline Vec2f vec2f_sub(Vec2f a, Vec2f b);
static inline Vec2f vec2f_add(Vec2f a, Vec2f b);
static inline Vec2f vec2f_mul(Vec2f a, Vec2f b);
static inline Vec2f vec2f_div(Vec2f a, Vec2f b);
static inline Vec2f vec2f_floor(Vec2f a);
static inline Vec2f vec2f_ceil(Vec2f a);
static inline Vec2i vec2i2f(Vec2f a);
static inline float vec2f_sqrlen(Vec2f a);

#define vec2i_sum(a, b) vec2i_add(a, b)
#define vec2f_sum(a, b) vec2f_add(a, b)

#ifdef SMATH_IMPLEMENTATION

static inline Vec2i vec2i(int x, int y)
{
    return (Vec2i) {x, y};
}

static inline Vec2i vec2ii(int a)
{
    return vec2i(a, a);
}

static inline Vec2i vec2i_add(Vec2i a, Vec2i b)
{
    return vec2i(a.x + b.x, a.y + b.y);
}

static inline Vec2i vec2i_sub(Vec2i a, Vec2i b)
{
    return vec2i(a.x - b.x, a.y - b.y);
}

static inline Vec2i vec2i_mul(Vec2i a, Vec2i b)
{
    return vec2i(a.x * b.x, a.y * b.y);
}

static inline Vec2i vec2i_div(Vec2i a, Vec2i b)
{
    return vec2i(a.x / b.x, a.y / b.y);
}

static inline Vec2i vec2i_floor(Vec2i a)
{
    a.x = floor(a.x);
    a.y = floor(a.y);
    
    return a;
}

static inline Vec2i vec2i_ceil(Vec2i a)
{
    a.x = ceil(a.x);
    a.y = ceil(a.y);

    return a;
}

static inline int vec2i_sqrlen(Vec2i a)
{
    return a.x*a.x + a.y*a.y;
}

static inline Vec2f vec2f2i(Vec2i a)
{
    Vec2f result;

    result.x = (float) a.x;
    result.y = (float) a.y;

    return result;
}

static inline Vec2f vec2f(float x, float y)
{
    return (Vec2f) {x, y};
}

static inline Vec2f vec2ff(float a)
{
    return vec2f(a, a);
}

static inline Vec2f vec2f_add(Vec2f a, Vec2f b)
{
    return vec2f(a.x + b.x, a.y + b.y);
}

static inline Vec2f vec2f_sub(Vec2f a, Vec2f b)
{
    return vec2f(a.x - b.x, a.y - b.y);
}

static inline Vec2f vec2f_mul(Vec2f a, Vec2f b)
{
    return vec2f(a.x * b.x, a.y * b.y);
}

static inline Vec2f vec2f_div(Vec2f a, Vec2f b)
{
    return vec2f(a.x / b.x, a.y / b.y);
}

static inline Vec2f vec2f_floor(Vec2f a)
{
    a.x = floorf(a.x);
    a.y = floorf(a.y);

    return a;
}

static inline Vec2f vec2f_ceil(Vec2f a)
{
    a.x = ceilf(a.x);
    a.y = ceilf(a.y);

    return a;
}

static inline Vec2i vec2i2f(Vec2f a)
{
    Vec2i result;

    result.x = (int) a.x;
    result.y = (int) a.y;

    return result;
}

static inline float vec2f_sqrlen(Vec2f a)
{
    return a.x*a.x + a.y*a.y;
}

#endif // SMATH_IMPLEMENTATION
#endif // SMATH_H
