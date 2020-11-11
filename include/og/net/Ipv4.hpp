/*
 * libOG, 2020
 *
 * Name: Ipv4.hpp
 *
*/

#pragma once

#include <string>

#include <arpa/inet.h>

namespace og {

namespace net {

struct Ipv4 {
	static const Ipv4 Broadcast;
	static const Ipv4 Any;
	static const Ipv4 Loopback;

	static Ipv4 get_local_address();

	Ipv4() = delete;
	Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	Ipv4(uint32_t address);
	explicit Ipv4(const char* address);

	std::string to_string() const;
	uint32_t to_decimal() const;

	uint32_t address;

}; // struct Ipv4

} // namespace net

} // namespace og
