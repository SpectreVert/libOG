/*
 * Created by Costa Bushnaq
 *
 * 29-04-2021 @ 00:55:28
 *
 * see LICENSE
*/

#ifndef _IPV4_HPP
#define _IPV4_HPP

#include <string>

#include <arpa/inet.h>

namespace og {

namespace net {

struct Ipv4 {
	// static const Ipv4 k_loopback = "127.0.0.1";

	virtual ~Ipv4() = default;
	Ipv4();
	Ipv4(uint8_t, uint8_t, uint8_t, uint8_t);
	Ipv4(uint32_t);
	Ipv4(char const*);

	static Ipv4 get_local_address();

	std::string to_string() const;
	uint32_t host_order() const; //! host order
	uint32_t net_order() const; //! network order (recommended)

private:
	uint32_t m_address;

}; // struct Ipv4

} // namespace net

} // namespace og

#endif /* _IPV4_HPP */
