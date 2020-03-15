/*
 * libOG, 2020
 *
 * Name: Selector.hpp
 *
*/

#pragma once

#if defined (__unix__)
	#include "og/network/unix/Selector.hpp"
#elif defined (_WIN_32)
	#include "og/network/windows/Selector.hpp"
#endif
