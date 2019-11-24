/*
 * libOG, 2019
 *
 * Name: SocketHandle
 *
 * Description:
 * Socket handles specific to each platform.
*/

#pragma once

#ifdef _WIN_32
	#include <basetsd.h>
#endif

namespace og {

#ifdef _WIN_32

	typedef UINT_PTR SocketHandle;

#else // Assuming UNIX platform

	typedef int SocketHandle;

#endif

} // namespace og
