/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/net/SocketHandle.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

namespace og {

// Note: this class and subsequently all socket classes
// will return int values as error codes.
// Each socket type will have its own error codes in addition
// to Socket::Success, Socket::Error
class Socket {
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

} // namespace og