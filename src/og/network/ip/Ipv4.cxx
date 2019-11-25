/*
 * libOG, 2019
 *
 * Name: Ipv4.cxx
 *
 * Description:
 * Class for manipulating IPv4 addresses.
*/

#include <og/network/ip/Ipv4.hpp>
#include <og/network/SocketHandle.hpp>
#include <og/network/SocketImplementation.hpp>
#include <og/base/SystemException.hpp>

#include <arpa/inet.h>
#include <cstring>

namespace og {

const Ipv4 localhost = Ipv4(127, 0, 0, 1);
const Ipv4 broadcast = Ipv4(255, 255, 255, 255);
const Ipv4 any       = Ipv4(0, 0, 0, 0);

Ipv4::Ipv4() :
	m_good(false),
	m_address(0)
{

}

Ipv4::Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) :
	m_good(true),
	m_address(htonl(b1 << 24 | b2 << 16 | b3 << 8 | b4))
{
	
}

Ipv4::Ipv4(uint32_t address) :
	m_good(true),
	m_address(htonl(address))
{

}

std::string Ipv4::to_string() const
{
	char str[INET_ADDRSTRLEN];
	in_addr address;

	address.s_addr = m_address;
	return inet_ntop(AF_INET, reinterpret_cast<void*>(&address), str, INET_ADDRSTRLEN);
}

uint32_t Ipv4::to_int() const
{
	return m_address;
}

Ipv4 Ipv4::get_local_address()
{
	Ipv4 local;
	SocketHandle sock = ::socket(PF_INET, SOCK_DGRAM, 0);
	sockaddr_in loopback;

	if (sock == impl::SocketHelper::bad_socket)
		throw SystemException("socket");

	std::memset(&loopback, 0, sizeof(loopback));
	loopback.sin_family = AF_INET;
	loopback.sin_addr.s_addr = INADDR_LOOPBACK;
	loopback.sin_port = htons(9);

	/* Not sure if connect returns -1 on failure on Windows... */
	if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
		SystemException e("connect");
		impl::SocketHelper::close(sock);
		throw e;
	}

	socklen_t addrlen = sizeof(loopback);
	if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
		SystemException e("getsockname");
		impl::SocketHelper::close(sock);
		throw e;
	}

	impl::SocketHelper::close(sock);
	
	local = Ipv4(ntohl(loopback.sin_addr.s_addr));

	return local;
}

} // namespace og
