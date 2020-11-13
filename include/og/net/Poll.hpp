/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#include "og/core/System.hpp"

# if defined(OG_SYSTEM_LINUX) \
  || defined(OG_SYSTEM_ANDROID)
  #include "og/net/epoll/Poll.hpp"
  #include "og/net/epoll/Event.hpp"
# else
#   warning "Your distribution does not support a Poll implementation"
# endif
