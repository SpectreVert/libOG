/*
 * libOG, 2020
 *
 * Name: socket.hpp
 *
*/

#pragma once

#include "og/net/sockethandle.hpp"
#include "og/net/ipv4.hpp"

namespace og {

// Note: this class and subsequently all socket classes
// will return int values as error codes.
// Each socket type will have its own error codes in addition
// to Socket::Success, Socket::Error
class Socket {
public:
	enum
	{
		Success = 0,
		Error = -1
	};

	virtual ~Socket();

	SocketHandle handle() const { return m_socket; };
	
	virtual int bind(const Ipv4& address, Ipv4::Port port);

protected:
	Socket(int domain, int type, int protocol = 0);
	
	virtual int open();
	virtual int open(SocketHandle handle);
	virtual int close();

private:
	SocketHandle m_socket;
	int m_domain;
	int m_type;
	int m_protocol;
}; // class Socket

} // namespace og
