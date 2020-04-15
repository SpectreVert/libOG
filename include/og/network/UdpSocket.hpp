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

	//! \brief Transmit raw data message to another socket
	//!
	//! \param data The contents of the message
	//!
	//! \param length The length of the message
	//!
	//! \param address Address of the target
	//!
	//! \param port Port of the target
	//!
	//! \return The Status code
	//!
	//! \see receive_from
	//!
	virtual Status send_to(const void* data,
						   std::size_t length,
                           const Ipv4& address,
						   Port port);

	//! \brief Receive a raw data message from a socket
	//!
	//! \param data An buffer to fill with the received data
	//!
	//! \param length Maximum number of bytes that can be received
	//!
	//! \param address Provides the address of the source socket
	//!
	//! \param port Provides the port of the source socket
	//!
	//! \return The Status code
	//!
	//! \see send_to
	//!
	virtual Status receive_from(void* buffer,
							    std::size_t length,
								Ipv4& address,
								Port& port
								);

	//! \brief Receive a raw data message from a sockets
	//!
	//! The received argument is filled with the number of
	//! received bytes.
	//!
	//! \param data An buffer to fill with the received data
	//!
	//! \param length Maximum number of bytes that can be received
	//!
	//! \param address Provides the address of the source socket
	//!
	//! \param port Provides the port of the source socket
	//!
	//! \param received The number of received bytes
	//!
	//! \return The Status code
	//!
	//! \see send_to
	//!
	virtual Status receive_from(void* buffer,
							    std::size_t length,
								Ipv4& address,
								Port& port,
                                ssize_t& received
								);

}; // class UdpSocket

} // namespace og
