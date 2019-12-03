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
#include <og/network/SocketHandle.hpp>

namespace og {

class Socket : NonCopyable {
public:
	enum Status {
		Success = 0,
		Again = 1,
		Disconnect = 2,
		Error = 42,
	};

	virtual ~Socket();

	bool blocking() const;
	void blocking(bool blocking);

	SocketHandle handle() const;
protected:
	void open();
	void open(SocketHandle t_socket);
	void close();

	enum Type {
		TCP = 1,
		UDP
	};
	
	Socket(Type t_type);

private:
	SocketHandle m_socket;
	bool m_blocking;
	Type m_type;

}; // class Socket

} // namespace og
