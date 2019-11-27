/*
 * libOG, 2019
 *
 * Name: UdpSocket.cxx
 *
 * Description:
 * Socket using the connectionless UDP protocol.
*/

#include <og/network/UdpSocket.hpp>
#include <og/network/SocketImplementation.hpp>
#include <og/base/SystemException.hpp>

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

const int maximum_datagram_size = 65507;

/* Therefore maximum size of UDP payload is 65535 - 28 = 65507 octets. */

UdpSocket::UdpSocket() :
	Socket(UDP)
{
	
}

Socket::Status UdpSocket::bind(const Ipv4& address, uint16_t port)
{
	sockaddr_in addr = impl::SocketHelper::fill_ipv4_sockaddr(address, port);
	// Reset the socket
	close();
	open();

	if ((::bind(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1))
		throw SystemException("bind");
	return Socket::Status::SUCCESS;
}

} // namespace og
