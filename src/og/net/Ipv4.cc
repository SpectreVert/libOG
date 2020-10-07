/*
 * libOG, 2020
 *
 * Name: Ipv4.cc
 *
*/

#include "og/net/Ipv4.hpp"

#include <cstring>

using namespace og;

Ipv4 Ipv4::get_local_address()
{
	return 0;
}

Ipv4::Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
	: address(htonl(b1 << 24 | b2 << 16 | b3 << 8 | b4))
{
}

Ipv4::Ipv4(uint32_t t_address)
	: address(htonl(t_address))
{
}

Ipv4::Ipv4(const char* t_address)
	: address(0)
{
	struct in_addr buf;

	inet_pton(AF_INET, t_address, &buf);
	address = buf.s_addr;
}

std::string Ipv4::to_string() const
{
	char addr[INET_ADDRSTRLEN];
	struct in_addr buf = { 0 };

	buf.s_addr = address;
	inet_ntop(AF_INET, &buf, addr, INET_ADDRSTRLEN);
	return addr;
}

uint32_t Ipv4::to_decimal() const
{
	return ntohl(address);
}
