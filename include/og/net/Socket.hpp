/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/net/Ipv4.hpp"
#include "og/net/SocketHandle.hpp"
#include "og/net/SocketAddr.hpp"
#include "og/net/generic/ISource.hpp"

#if defined(OG_SYSTEM_LINUX)
	#include <errno.h>
#elif defined(OG_SYSTEM_FREEBSD) || defined(OG_SYSTEM_MACOS)
	#include <sys/errno.h>
#endif

namespace og {

namespace net {

class Socket : public ISource<SocketHandle> {
public:
	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	virtual ~Socket();

	SocketHandle handle() const { return m_handle; };

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open();
	virtual int close();

	SocketHandle m_handle;
	int m_domain;
	int m_type;
	int m_protocol;
}; // class Socket

} // namespace net

} // namespace og
