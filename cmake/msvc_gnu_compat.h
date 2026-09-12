#ifndef EMULOCKE_MSVC_GNU_COMPAT_H
#define EMULOCKE_MSVC_GNU_COMPAT_H

#if defined(_MSC_VER) && !defined(__clang__)

#include <intrin.h>

#define __attribute(...)
#define __attribute__(...)

#define __builtin_unreachable() __assume(0)
#define __builtin_expect(x, v) (x)
#define __builtin_trap() __debugbreak()

static __forceinline int emulocke_msvc_popcount(unsigned v)
{
    return (int)__popcnt(v);
}

static __forceinline int emulocke_msvc_popcountll(unsigned long long v)
{
    return (int)__popcnt64(v);
}

static __forceinline int emulocke_msvc_ctz(unsigned v)
{
    unsigned long i;
    _BitScanForward(&i, v);
    return (int)i;
}

static __forceinline int emulocke_msvc_ctzll(unsigned long long v)
{
    unsigned long i;
    _BitScanForward64(&i, v);
    return (int)i;
}

static __forceinline int emulocke_msvc_clz(unsigned v)
{
    unsigned long i;
    _BitScanReverse(&i, v);
    return 31 - (int)i;
}

static __forceinline int emulocke_msvc_clzll(unsigned long long v)
{
    unsigned long i;
    _BitScanReverse64(&i, v);
    return 63 - (int)i;
}

#define __builtin_popcount(x) emulocke_msvc_popcount((unsigned)(x))
#define __builtin_popcountll(x) emulocke_msvc_popcountll((unsigned long long)(x))
#define __builtin_ctz(x) emulocke_msvc_ctz((unsigned)(x))
#define __builtin_ctzll(x) emulocke_msvc_ctzll((unsigned long long)(x))
#define __builtin_clz(x) emulocke_msvc_clz((unsigned)(x))
#define __builtin_clzll(x) emulocke_msvc_clzll((unsigned long long)(x))

#endif

#endif
