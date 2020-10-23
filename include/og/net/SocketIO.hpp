/*
 * libOG, 2020
 *
 * Name: SocketIO.hpp
 *
*/

#pragma once

#include "og/core/config.hpp"

#if defined(OG_SYSTEM_UNIX)
	#include "og/net/unix/SocketIO.hpp"

#elif defined(OG_SYSTEM_WINDOWS)
	#include "og/net/win/SocketIO.hpp"

#endif
