/*
 * libOG, 2019
 *
 * Name: UdpSocket.hpp
 *
*/

#pragma once

#include "og/network/Socket.hpp"

namespace og {

class Ipv4;

//! \brief Socket using the UDP protocol
//!
class UdpSocket : public Socket {
public:

//! Maximum possible datagram length is coded in a 16 bits section.
//! 2^16-1 = 65535 octets max size for an entire IPv4 packet.
//! (including IPv4 header and payload, which would be the UDP
//! header and UDP payload).
//!
//! IHL (Internet Header Length) field of IPv4 packet specifies
//! the number of 32-bit words in the header. Its min value is 5.
//! So min value for header is 160 bits or 20 octets.
//!
//! An UDP header consists of four 16 bits fields; so a total
//! length of 8 octets. 
//!
//! Therefore maximum size of UDP payload is 65535 - 20 - 8 = 65507 octets.
#define MAX_DATAGRAM_SIZE 65507 //<! Maximum payload size

	//! \brief Constructor
	//!
	UdpSocket();

	//! \brief Send raw data to a remote peer
	//!
	//! \param data Pointer to an array of bytes to send
	//!
	//! \param length Number of bytes to send
	//!
	//! \param address Address of the remote peer
	//!
	//! \param port Port of the remote peer
	//!
	//! \see receive_from
	//!
	virtual Status sendTo(const void* data, std::size_t length,
                          const Ipv4& address, uint16_t port);

	//! \brief Receive raw data from a remote peer
	//!
	//! \param data Pointer to an array of bytes to fill
	//!
	//! \param length Maximum number of bytes that can be received
	//!
	//! \param address Address of the remote peer
	//!
	//! \param port Port of the remote peer
	//!
	//! \see send_to
	//!
	virtual Status receiveFrom(void* buffer, std::size_t length,
                               std::size_t& recveived, Ipv4& address, uint16_t& port);

}; // class UdpSocket

} // namespace og
