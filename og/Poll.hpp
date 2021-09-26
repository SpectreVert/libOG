/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#include "og/System.hpp"

// TODO compile the appropriate files from Makefile
// rather than doing this dirty hack

#if defined(OG_SYSTEM_LINUX) || defined(OG_SYSTEM_ANDROID)
#  include "og/epoll/Poll.hpp"
#  include "og/poll/Event.hpp"
#else
#  warning "Your distribution does not support a Poll implementation"
#endif
