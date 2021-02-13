/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/net/Internal.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketHandle.hpp"
#include "og/net/SocketAddr.hpp"
#include "og/net/generic/ISource.hpp"

namespace og {

namespace net {

class Socket : public ISource<SocketHandle> {
public:
	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	Socket(SocketHandle handle);
	virtual ~Socket();

	SocketHandle handle() const { return m_handle; };
	void handle(SocketHandle handle);

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open(int domain, int type, int protocol);
	virtual int close();

	SocketHandle m_handle = intl::bad_socket;
}; // class Socket

} // namespace net

} // namespace og
