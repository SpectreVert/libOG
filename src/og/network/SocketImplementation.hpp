/*
 * libOG, 2019
 *
 * Name: SocketImplementation.hpp
 *
 * Description:
 * 
*/

#pragma once

#if defined (__unix__)
	#include <og/network/unix/SocketImplementation.hpp>
#elif defined (_WIN_32)
	#include <og/network/windows/SocketImplementation.hpp>
#endif
