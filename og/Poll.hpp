/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#include "og/System.hpp"

#if defined(OG_SYSTEM_LINUX) || defined(OG_SYSTEM_ANDROID)
#include "og/epoll/Poll.hpp"
#include "og/epoll/Event.hpp"
#else
#warning "Your distribution does not support a Poll implementation"
#endif
