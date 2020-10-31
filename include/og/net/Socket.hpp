/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/io/SourceHandle.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#if defined(OG_SYSTEM_LINUX)
	#include <errno.h>
#elif defined(OG_SYSTEM_FREEBSD) || defined(OG_SYSTEM_MACOS)
	#include <sys/errno.h>
#endif

namespace og {

namespace net {

// for unix systems
#if defined(OG_SYSTEM_UNIX)
typedef int SocketHandle;
#endif

// Note: this class and subsequently all socket classes
// will return int values as error codes.
// Each socket type will have its own error codes in addition
// to Socket::Success, Socket::Error
class Socket : public io::Source<SocketHandle> {
public:
	enum
	{
		Error = -1,
		Success,
		Connecting,
		Retry,
		PartialSend,
	};

	Socket() = delete;
	Socket(int domain, int type, int protocol = 0);
	virtual ~Socket();

	SocketHandle handle() const { return m_socket; };

	virtual int bind(const SocketAddr& address);

protected:
	virtual int open();
	virtual int open(SocketHandle handle);
	virtual int close();

	// think about defining this as private
	SocketHandle m_socket;
	int m_domain;
	int m_type;
	int m_protocol;
}; // class Socket

} // namespace net

} // namespace og
