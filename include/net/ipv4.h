/*
 * libOG, 2020
 *
 * Name: ipv4.h
 *
*/

#pragma once

#include <stdint.h> // uint32_t

/* Wrapper around a 32-bit int.
   Don't initialize it by hand as it stores the address in network byte order.
*/
typedef uint32_t og_ipv4;

/* Constructors */
og_ipv4 og_ipv4_from_dec(uint32_t adr);
og_ipv4 og_ipv4_from_oct(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
og_ipv4 og_ipv4_from_str(const char *str);

/* Conversions */
uint32_t og_ipv4_to_dec(og_ipv4 adr);
