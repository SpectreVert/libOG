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

/* Maximum possible datagram length is coded in a 16 bits section.
2^16-1 = 65535 octets max size for an entire IPv4 packet.
(including IPv4 header and payload, which would be the UDP
header and UDP payload).

IHL (Internet Header Length) field of IPv4 packet specifies
the number of 32-bit words in the header. Its min value is 5.
So min value for header is 160 bits or 20 octets.

An UDP header consists of four 16 bits fields; so a total
length of 8 octets. */

const int UdpSocket::maximum_datagram_size = 65507;

/* Therefore maximum size of UDP payload is 65535 - 28 = 65507 octets. */

UdpSocket::UdpSocket() :
	Socket(PF_INET, SOCK_DGRAM, 0)
{
	
}

Socket::Status UdpSocket::send(const void* data, std::size_t len, const Ipv4& address, uint16_t port)
{
	open();

	if (len > maximum_datagram_size)
		return Error;

	sockaddr_in addr = impl::SocketHelper::buildIpv4Sockaddr(address, port);

	if (sendto(getHandle(), static_cast<const char*>(data), len, 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;

	return Success;
}

Socket::Status UdpSocket::receive(void* buffer, std::size_t len, std::size_t& recvd, Ipv4& address, uint16_t& port)
{
	if (!buffer)
		return Error;

	sockaddr_in src_addr = impl::SocketHelper::buildIpv4Sockaddr(INADDR_ANY, 0);
	impl::Addrlen addrlen = sizeof(src_addr);

	int received = recvfrom(getHandle(), buffer, len, 0, reinterpret_cast<sockaddr*>(&src_addr), &addrlen);
	if (received < 0)
		return Error;

	recvd = static_cast<std::size_t>(received);
	address = ntohl(src_addr.sin_addr.s_addr);
	port = src_addr.sin_port;

	return Success;
}

} // namespace og
