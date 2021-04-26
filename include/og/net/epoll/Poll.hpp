/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#pragma once

#include "og/net/Error.hpp"
#include "og/core/RawFd.hpp"
#include "og/net/Internal.hpp"
#include "og/net/Socket.hpp"
#include "og/net/epoll/Event.hpp"
#include "og/net/generic/IPoll.hpp"

#include <array>

#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Poll implementation for epoll
//!
class Poll : public IPoll<Socket, Events> {
	core::RawFd m_epoll_fd;

public:
	virtual ~Poll();
	Poll();

	int poll(Events& events, int timeout);
	
	int monitor(Socket& source, core::Tag id, core::Concern concern);
	int forget(Socket& source);

}; // class Poll

} // namespace net

} // namespace og
