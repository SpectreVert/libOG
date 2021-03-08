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

class Socket : public ISource<SocketFd> {
public:
	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	Socket(SocketFd handle);
	virtual ~Socket();

	SocketFd handle() const { return m_socket; };
	void handle(SocketFd handle);

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open(int domain, int type, int protocol);
	virtual int close();

	SocketFd m_socket = intl::bad_socket;
}; // class Socket

} // namespace net

} // namespace og
