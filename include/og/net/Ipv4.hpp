/*
 * libOG, 2020
 *
 * Name: Ipv4.hpp
 *
*/

#pragma once

#include <string>

namespace og {

class Ipv4 {
public:
	typedef uint16_t Port;

	static const Ipv4 Broadcast;
	static const Ipv4 Any;
	static const Ipv4 Loopback;

	static Ipv4 get_local_address();

	Ipv4();
	Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	Ipv4(uint32_t address);
	Ipv4(const char* address);
	Ipv4(const std::string& address);

	std::string to_string() const;
	uint32_t to_decimal() const;

private:
	bool m_good;
	uint32_t m_address;

}; // class Ipv4

} // namespace og
