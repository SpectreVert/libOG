/*
 * libOG, 2020
 *
 * Name: Config.hpp
 *
*/

#pragma once

#if defined(__unix__)
	#define OG_SYSTEM_UNIX

	#if defined(__ANDROID__)
		#define OG_SYSTEM_ANDROID
	
	#elif defined(__linux__)
		#define OG_SYSTEM_LINUX

	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define OG_SYSTEM_FREEBSD

	#else
		#error unix distribution not supported
	
	#endif

#elif defined(__APPLE__) && defined(__MACH__)
	#include "TargetConditionals.h"

	#if TARGET_OS_MAC
		#define OG_SYSTEM_MACOS

	#else
		#error operating system not supported

#elif defined(_WIN32)
	#define OG_SYSTEM_WINDOWS

#else
	#error operating system not supported

#endif
