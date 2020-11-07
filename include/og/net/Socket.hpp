/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/io/ISource.hpp"
#include "og/io/SocketHandle.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#if defined(OG_SYSTEM_LINUX)
	#include <errno.h>
#elif defined(OG_SYSTEM_FREEBSD) || defined(OG_SYSTEM_MACOS)
	#include <sys/errno.h>
#endif

namespace og {

namespace net {

// Note: this class and subsequently all socket classes
// will return int values as error codes.
// Each socket type will have its own error codes in addition
// to Socket::Success, Socket::Error
class Socket : public io::ISource<io::SocketHandle> {
public:
	enum // actually gon need to add all error codes
	{
		Error = -1,
		Success = 0,
		Connecting,
		Retry,
		PartialSend,
	};

	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	virtual ~Socket();

	io::SocketHandle handle() const { return m_handle; };

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open();
	virtual int close();

	io::SocketHandle m_handle;
	int m_domain;
	int m_type;
	int m_protocol;
}; // class Socket

} // namespace net

} // namespace og
