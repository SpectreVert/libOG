/*
 * libOG, 2020
 *
 * Name: System.hpp
 *
*/

#pragma once

/* Distribution verification
*/
# if defined(__linux__)
#   define OG_SYSTEM_LINUX

# elif defined(__ANDROID__)
#   define OG_SYSTEM_ANDROID

# elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#   define OG_SYSTEM_FREEBSD

# elif defined(__APPLE__) && defined(__MACH__)
#   include "TargetConditionals.h"

#   if TARGET_OS_MAC
#     define OG_SYSTEM_MACOS

#   else
#     error "Distribution not supported"
#   endif

/* Additional OSes go here
*/

# else
#   error "Distribution not supported"
# endif
