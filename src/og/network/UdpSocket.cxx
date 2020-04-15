/*
 * libOG, 2019
 *
 * Name: UdpSocket.cxx
 *
*/

#include "og/base/SystemException.hpp"
#include "og/network/UdpSocket.hpp"
#include "og/network/SocketImplementation.hpp"

#include <netinet/ip.h>

namespace og {

UdpSocket::UdpSocket() :
	Socket(PF_INET, SOCK_DGRAM, 0)
{
	
}

Socket::Status UdpSocket::send_to(
		const void* data,
		std::size_t len,
		const Ipv4& address,
		Port port)
{
	open();

	if (len > MAX_DATAGRAM_SIZE)
	{
		errno = EMSGSIZE;
		return Socket::Status::Error;
	}

	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(address, port);

	if (::sendto(handle(),
		static_cast<const char*>(data),
		len,
		impl::SocketHelper::MSG_FLAG,
		reinterpret_cast<sockaddr*>(&addr),
		sizeof(addr)) == -1)
		
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return Socket::Status::RetryReceive;

		return Socket::Status::Error;

	return Socket::Status::Success;
}

Socket::Status UdpSocket::receive_from(
		void* buffer,
		std::size_t len,
		Ipv4& address,
		Port& port)
{
	ssize_t received;

	return receive_from(buffer, len, address, port, received);
}

Socket::Status UdpSocket::receive_from(
		void* buffer,
		std::size_t len,
		Ipv4& address,
		Port& port,
		ssize_t& received)
{
	sockaddr_in src_addr = impl::SocketHelper::build_ipv4_sockaddr(INADDR_ANY, 0);
	impl::Addrlen addrlen = sizeof(src_addr);

	received = recvfrom(handle(),
							buffer,
							len,
							impl::SocketHelper::MSG_FLAG,
							reinterpret_cast<sockaddr*>(&src_addr),
							&addrlen);
	
	if (received < 0)
	{
		received = 0;

		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return Socket::Status::RetryReceive;
		
		return Socket::Status::Error;
	}

	address = ntohl(src_addr.sin_addr.s_addr);
	port = ntohs(src_addr.sin_port);

	return Socket::Status::Success;
}

} // namespace og
