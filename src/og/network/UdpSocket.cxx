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

Socket::Status UdpSocket::sendTo(const void* data, std::size_t len, const Ipv4& address, uint16_t port)
{
	open();

	if (len > MAX_DATAGRAM_SIZE)
		return Error;

	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(address, port);

	if (sendto(handle(), static_cast<const char*>(data), len, 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;

	return Success;
}

Socket::Status UdpSocket::receiveFrom(void* buffer, std::size_t len, std::size_t& recvd, Ipv4& address, uint16_t& port)
{
	if (!buffer)
		return Error;

	sockaddr_in src_addr = impl::SocketHelper::build_ipv4_sockaddr(INADDR_ANY, 0);
	impl::Addrlen addrlen = sizeof(src_addr);

	int received = recvfrom(handle(), buffer, len, 0, reinterpret_cast<sockaddr*>(&src_addr), &addrlen);
	if (received < 0)
		return Error;

	recvd = static_cast<std::size_t>(received);
	address = ntohl(src_addr.sin_addr.s_addr);
	port = src_addr.sin_port;

	return Success;
}

} // namespace og
