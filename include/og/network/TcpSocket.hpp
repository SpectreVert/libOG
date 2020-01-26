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
#include <og/network/ip/Ipv4.hpp>

namespace og {

class TcpSocket : public Socket {
public:
	TcpSocket();

	Status connect(const Ipv4& raddress, uint16_t rport);
	void disconnect();

	Status send(const void* data, std::size_t len);
	Status send(const void* data, std::size_t len, std::size_t& sent);
	Status receive(void* data, std::size_t len);
	Status receive(void* data, std::size_t len, std::size_t& received);

private:
	// So we can access open/close of the Socket class from TcpListener methods.
	friend class TcpListener;

}; // class TcpSocket

} // namespace og
