/*
 * libOG, 2019
 *
 * Name: Ipv4.cxx
 *
 * Description:
 * Class for manipulating IPv4 addresses.
*/

#include <og/network/ip/Ipv4.hpp>
#include <og/network/Socket.hpp>

#include <arpa/inet.h>

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
	SocketHandle 
}

} // namespace og
