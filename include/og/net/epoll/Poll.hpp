/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#pragma once

#include "og/io/IPoll.hpp"
#include "og/net/epoll/Event.hpp"
#include "og/net/Socket.hpp"

#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Poll implementation for epoll
//!
class Poll : io::IPoll<io::SocketHandle, Events> {
public:
    Poll();
    virtual ~Poll() = default;

    virtual int poll(Events& events, int timeout);
    virtual int add(io::SocketHandle source, io::Tag id, io::Concern concern);
    virtual int remove(io::SocketHandle source);

private:
    int m_epoll_fd;

}; // class Poll

} // namespace net

} // namespace og
