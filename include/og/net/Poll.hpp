/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#include "og/Config.hpp"

#if defined(OG_SYSTEM_LINUX)
    #include "og/net/epoll/Poll.hpp"
    #include "og/net/epoll/Event.hpp"
#endif