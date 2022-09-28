/*
 * Created by Costa Bushnaq
 *
 * 29-04-2021 @ 00:55:28
 *
 * see LICENSE
*/

#ifndef OG_IPV4_HPP_
#define OG_IPV4_HPP_

#include <string>

#include <arpa/inet.h>

namespace og {

struct Ipv4 {
    /// static const Ipv4 k_loopback = "127.0.0.1";

    virtual ~Ipv4() = default;
    Ipv4();
    Ipv4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    Ipv4(uint32_t address);
    Ipv4(char const *address);

    // @Todo: write this function
    static Ipv4 get_local_address();

    std::string to_string() const;
    uint32_t host_order() const; //! host order
    uint32_t net_order() const;  //! network order (recommended)

private:
    uint32_t m_address;

}; // struct Ipv4

} // namespace og

#endif /* OG_IPV4_HPP_ */
