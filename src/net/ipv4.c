/*
 * libOG, 2020
 *
 * Name: ipv4.c
 *
*/

#include "net/ipv4.h"

#include <arpa/inet.h> // htonl, ntop, etc.

og_ipv4
og_ipv4_from_dec(uint32_t adr)
{
	return htonl(adr);
}

og_ipv4
og_ipv4_from_oct(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4)
{
	return htonl(o1 << 24 | o2 << 16 | o3 << 8 | o4);
}


og_ipv4
og_ipv4_from_str(const char *str)
{
	static struct in_addr buf;
	
	inet_pton(AF_INET, str, &buf);
	return buf.s_addr;
}

og_ipv4
og_ipv4_to_dec(og_ipv4 adr)
{
	return ntohl(adr);
}
