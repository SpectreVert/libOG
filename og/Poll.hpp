/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#ifndef OG_POLL_HPP_
#define OG_POLL_HPP_

#include "og/defs.hpp"
#include "og/Socket.hpp"

#if defined(OG_SYSTEM_LINUX) or defined(OG_SYSTEM_ANDROID)
    #include "og/epoll/Event.hpp"
#else
    #warning "Your distribution does not support a Poll implementation"
#endif

namespace og {

typedef std::array<Event, OG_MAX_POLL_EVENTS> Events;

struct Poll {
    enum {
        e_read   = 1,
        e_write  = 2,
        e_shared = 4
    };

    s32 m_pollfd;

    ~Poll();
    Poll();

    s32 poll(Events& events, int timeout);

    s32 add(Socket& socket, u64 id, u16 concern);
    s32 refresh(Socket& socket, u64 id, u16 concern);
    s32 forget(Socket& socket);

}; // struct Poll

} // namespace og

#endif /* OG_POLL_HPP_ */
