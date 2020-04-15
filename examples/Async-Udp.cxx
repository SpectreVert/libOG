/*
 * libOG, 2020
 *
 * Name:
 *
 * Description:
 * Asynchronous I/O example
*/

#include <og/network.hpp>

#include <string>
#include <iostream>

#include <memory>
#include <vector>

#define WRITE_BUFFER 24
#define READ_BUFFER 48

int main()
{
	og::UdpSocket listener;
	og::Poll poll;
	int sid = 1;

	listener.bind(og::Ipv4::Loopback, 6970);

	//poll.add(listener.handle(), 0, og::Concern::Both);

	og::Events events(1024);

	while (1) {

		poll.poll(events, og::Poll::Timeout::None);

		for (auto event : events.events())
		{
			if (event.is_read_closed())
			{
				(void) event;
			}

			if (event.is_write_closed())
			{
				(void) event;
			}

			if (event.is_writable())
			{
				
			}

			if (event.is_readable()) 
			{
				char buffer[READ_BUFFER];
				ssize_t recvd = 0;
				og::Ipv4 addr;
				og::Socket::Port port;  

				listener.receive_from(buffer, sizeof(buffer), addr, port, recvd);

				buffer[recvd < READ_BUFFER ? recvd : READ_BUFFER] = '\0';
				std::cout << "bytes: " << recvd << " ; text: " << buffer;
				std::cerr << std::endl;
			}
		}
	}
}
