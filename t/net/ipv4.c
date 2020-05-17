/*
 * libOG, 2020
 *
 * Name: net_ipv4.c
 *
*/

#include "net/ipv4.h"
#include "ctap.h"

#include <arpa/inet.h> /* htonl */

TESTS {
	plan(4);

	/* IPv4 -> 44.78.78.23 */
	static const uint32_t adr = 743329303;
	const uint32_t nadr = htonl(adr);

	ok(og_ipv4_from_dec(adr) == nadr, "from decimal");
	ok(og_ipv4_from_oct(44, 78, 78, 23) == nadr, "from 4 octets");
	ok(og_ipv4_from_str("44.78.78.23") == nadr, "from string");
	ok(og_ipv4_to_dec(og_ipv4_from_dec(adr)) == adr, "to host");
}
