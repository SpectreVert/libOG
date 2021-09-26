/*
 * libOG, 2020
 *
 * Name: Ipv4.cc
 *
*/

#include "og/Ipv4.hpp"

#include <cstring>

using namespace og;

Ipv4::Ipv4()
	: m_address(0)
{
}

Ipv4::Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
	: m_address(htonl(b1 << 24 | b2 << 16 | b3 << 8 | b4))
{
}

Ipv4::Ipv4(uint32_t address)
	: m_address(htonl(address))
{
}

Ipv4::Ipv4(const char* address)
	: m_address(0)
{
	struct in_addr buf;

	inet_pton(AF_INET, address, &buf);
	m_address = buf.s_addr;
}

std::string Ipv4::to_string() const
{
	char addr[INET_ADDRSTRLEN];
	struct in_addr buf{};

	buf.s_addr = m_address;
	inet_ntop(AF_INET, &buf, addr, INET_ADDRSTRLEN);
	return addr;
}

uint32_t Ipv4::host_order() const
{
	return ntohl(m_address);
}

uint32_t Ipv4::net_order() const
{
	return m_address;
}
