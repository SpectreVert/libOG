/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
 * Description:
 * 
*/

#pragma once

#if defined (__unix__)
	#include "og/network/unix/Selector.hpp"
#elif defined (_WIN_32)
	#include "og/network/windows/Selector.hpp"
#endif
