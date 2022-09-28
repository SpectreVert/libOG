/*
 * Created by Costa Bushnaq
 *
 * 28-09-2022 @ 12:03:33
 *
 * see LICENSE
*/

#ifndef OG_DEFS_HPP_
#define OG_DEFS_HPP_

#include <cstdint>

#if defined(__linux__)
    #define OG_SYSTEM_LINUX

#elif defined(__ANDROID__)
    #define OG_SYSTEM_ANDROID

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    #define OG_SYSTEM_FREEBSD

#elif defined(__APPLE__) && defined(__MACH__)
    #include "TargetConditionals.h"

#if TARGET_OS_MAC
    #define OG_SYSTEM_MACOS

#else
    #error "Distribution not supported"
#endif

/* Additional OSes go here
*/

#else
    #error "Distribution not supported"
#endif

namespace og {

enum {
    e_failure = -1,
    e_success = 0,
    e_again,
    e_closed,
    e_in_progress
};

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

constexpr s32 k_bad_socketfd{ -1 };

} // namespace og

#endif /* OG_DEFS_HPP_ */
