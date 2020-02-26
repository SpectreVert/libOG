/*
 * libOG, 2019
 *
 * Name: Socket.hpp
 *
 * Description:
 * Base class for all socket types.
*/

#pragma once

#include <og/base/NonCopyable.hpp>
#include <og/network/IBaseSocket.hpp>
#include <og/network/SocketHandle.hpp>

namespace og {

//! \brief User-oriented base class for all the socket types.
//!
class Socket : public IBaseSocket, private NonCopyable {
public:
	enum Status {
		Success = 0,
		Again = 1,
		Disconnect = 2,
		Error = 42,
	};

	virtual ~Socket();

	bool isBlocking() const;
	void setBlocking(bool blocking);

	SocketHandle getHandle() const;

protected:
	void open();
	void open(SocketHandle t_socket);
	void close();
	
	Socket(int t_domain, int t_type, int t_protocol);

private:
	SocketHandle m_socket;
	bool m_blocking;
	int m_domain;
	int m_type;
	int m_protocol;

}; // class Socket

} // namespace og
