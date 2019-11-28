/*
 * libOG, 2019
 *
 * Name: Ipv4.hpp
 *
 * Description:
 * Class for manipulating IPv4 addresses.
*/

#pragma once

#include <string>

namespace og {

class Ipv4 {
public:
	static const Ipv4 Localhost; // 127.0.0.1
	static const Ipv4 Broadcast; // 255.255.255.255
	static const Ipv4 Any;       // 0.0.0.0

	Ipv4();
	Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	Ipv4(uint32_t address);
	Ipv4(const char* address);
	Ipv4(const std::string& address);

	std::string to_string() const;
	uint32_t to_int() const;

	static Ipv4 get_local_address();
	
private:
	bool m_good;
	uint32_t m_address;
}; // class Ipv4

} // namespace og
