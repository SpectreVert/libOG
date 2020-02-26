/*
 * libOG, 2019
 *
 * Name: TcpSocket.hpp
 *
 * Description:
 * Socket using the stream TCP protocol.
*/

#pragma once

#include <og/network/Socket.hpp>
#include <og/network/Ipv4.hpp>

namespace og {

class TcpSocket : public Socket {
public:
	TcpSocket();

	virtual Status connect(const Ipv4& raddress, uint16_t rport);
	virtual void disconnect();

	virtual Status send(const void* data, std::size_t len);
	virtual Status send(const void* data, std::size_t len, std::size_t& sent);
	virtual Status receive(void* data, std::size_t len);
	virtual Status receive(void* data, std::size_t len, std::size_t& received);

private:

	// So we can access open/close of the Socket class from TcpListener methods.
	friend class TcpListener;

}; // class TcpSocket

} // namespace og
