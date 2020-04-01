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

int main()
{
	og::UdpSocket listener;
	og::Poll poll;
	int sid = 1;

	listener.bind(6970, og::Ipv4(127, 0, 0, 1));

	poll.add(listener.handle(), 0, og::Concern::Readable);

	og::Events events(1024);

	while (1) {

		poll.poll(events, og::PollTimeout::None);

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

			if (event.is_readable()) 
			{
				char buffer[1024];
				ssize_t recvd = 0;
				og::Ipv4 addr;
				og::Socket::Port port;  

				listener.receive_from(buffer, sizeof(buffer), addr, port, recvd);

				buffer[recvd < 1023 ? recvd : 1023] = '\0';
				std::cout << "bytes: " << recvd << " ; text: " << buffer;
			}
			std::cerr << std::endl;
		}
	}
}

/*
const og::Token SERVER(0);
const og::Token CLIENT(1);

int main()
{
	og::TcpListener listener;
	og::TcpStream stream;
	og::Poll poll;

	listener.listen(6970);

	poll.add(listener.handle(), SERVER, og::Concern::READABLE);

	stream.connect(og::Ipv4(127, 0, 0, 1), 6970);

	poll.add(stream.handle(), CLIENT, og::Concern::WRITABLE);

	og::Events events(1024);

	while (1) {
		poll.poll(events, og::Poll::Timeout::None);

		for (auto event : events.events())
		{
			og::TcpSocket t;
			
			switch (event.token())
			{
				case SERVER:
					
					listener.accept(t);
					
					break;

				case CLIENT:

					break;
			}
		}
	}
}

*/
