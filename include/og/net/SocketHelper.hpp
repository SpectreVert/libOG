/*
 * libOG, 2020
 *
 * Name: SocketImplementation.hpp
 *
*/

#pragma once

#include "og/core/config.hpp"

#if defined(OG_SYSTEM_UNIX)
	#include "og/net/unix/SocketHelper.hpp"

#elif defined(OG_SYSTEM_WINDOWS)
	#include "og/net/win/SocketHelper.hpp"

#endif
