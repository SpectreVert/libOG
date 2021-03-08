/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#pragma once

#include "og/net/Socket.hpp"
#include "og/net/epoll/Event.hpp"
#include "og/net/generic/IPoll.hpp"

#include <sys/epoll.h>

namespace og {

namespace net {

// FIXME: rather than asking for SocketFd, this
// should work for derivates of ISource

//! \brief Poll implementation for epoll
//!
class Poll : public IPoll<SocketFd, Events> {
	int m_epoll_fd;

public:
	Poll();
    virtual ~Poll();

    virtual int poll(Events& events, int timeout);
    virtual int monitor(SocketFd socket, core::Tag id, core::Concern concern);
    virtual int forget(SocketFd socket);
}; // class Poll

} // namespace net

} // namespace og
