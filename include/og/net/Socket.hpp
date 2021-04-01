/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/net/generic/ISource.hpp"
#include "og/net/Internal.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"
#include "og/net/SocketFd.hpp"

namespace og {

namespace net {

// TODO: add copy, move and other
// constructors.
class Socket : public ISource {
public:
	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	Socket(SocketFd handle);
	virtual ~Socket();

	SocketFd handle() const { return m_socket; };
	void handle(SocketFd handle);

	template<typename P>
	int monitor(P& poll, core::Tag id, core::Concern concern)
	{
		return poll.monitor(*this, id, concern);
	}

	template<typename P>
	int forget(P& poll)
	{
		return poll.forget(*this);
	}

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open(int domain, int type, int protocol);
	virtual int close() final;

	SocketFd m_socket = intl::bad_socket;

}; // class Socket

} // namespace net

} // namespace og
