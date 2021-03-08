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

class Socket : public ISource {
public:
	using Handle = SocketFd;

	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	Socket(Handle handle);
	virtual ~Socket();

	Handle handle() const { return m_socket; };
	void handle(Handle handle);

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open(int domain, int type, int protocol);
	virtual int close();

	Handle m_socket = intl::bad_socket;
}; // class Socket

} // namespace net

} // namespace og
