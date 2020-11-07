/*
 * libOG, 2020
 *
 * Name: Config.hpp
 *
*/

#pragma once

// sorry but this "unix" definition is ballz
// actually I need to redo this whole file
#if defined(__unix__)
	#define OG_SYSTEM_UNIX

	#if defined(__ANDROID__)
		#define OG_SYSTEM_ANDROID
	
	#elif defined(__linux__)
		#define OG_SYSTEM_LINUX

	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define OG_SYSTEM_FREEBSD

	#else
		#error distribution not supported
	#endif

#elif defined(__APPLE__) && defined(__MACH__)
	#include "TargetConditionals.h"

	#if TARGET_OS_MAC
		#define OG_SYSTEM_MACOS
	
	#else
		#error distribution not supported
	#endif

#else
	#error distribution not supported
#endif
