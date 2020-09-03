/*
 * libOG, 2020
 *
 * Name: sockethandle.hpp
 *
*/

#pragma once

#include "og/core/config.hpp"

#if defined(OG_SYSTEM_WINDOWS)
	#include <basetsd.h>

#endif

namespace og {

#if defined(OG_SYSTEM_WINDOWS)

typedef UNIT_PTR SocketHandle;

#else

typedef int SocketHandle;

#endif

} // namespace og
