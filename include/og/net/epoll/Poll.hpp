/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#pragma once

#include "og/core/RawFd.hpp"
#include "og/net/Socket.hpp"
#include "og/net/epoll/Event.hpp"
#include "og/net/generic/IPoll.hpp"

#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Poll implementation for epoll
//!
class Poll : public IPoll {
	core::RawFd m_epoll_fd;

public:
	Poll();
	virtual ~Poll();

	int poll(Events& events, int timeout);
	int monitor(SocketFd socket, core::Tag id, core::Concern concern);
	int forget(SocketFd socket);

}; // class Poll

} // namespace net

} // namespace og
