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
	Ipv4();
	Ipv4(const char* address);
	Ipv4(const std::string& address);
	Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	Ipv4(uint32_t address);

} // class v4

} // namespace og
