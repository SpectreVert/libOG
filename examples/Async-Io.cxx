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
	og::TcpListener listener;
	og::Poll poll;
	int sid = 1;

	listener.listen(6970, og::Ipv4(127, 0, 0, 1));

	poll.add(listener.handle(), 0, og::Concern::READABLE);

	og::Events events(1024);
	std::vector<std::shared_ptr<og::TcpStream>> sockets;

	while (1) {

		poll.poll(events, og::Poll::Timeout::None);

		for (auto event : events.events())
		{
			if (event.token() == 0)
			{
				std::shared_ptr<og::TcpStream> sock(new og::TcpStream);

				listener.accept(*sock);

				sockets.push_back(sock);

				poll.add(sock->handle(), sid, og::Concern::READABLE);

				sid++;

			} else
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
					std::shared_ptr<og::TcpStream> sock = sockets[event.token() - 1];

					char buffer[1024];
					std::size_t recvd = 0;

					sock->receive(buffer, sizeof(buffer), recvd);

					buffer[recvd < 1023 ? recvd : 1023] = '\0';
					std::cout << "bytes: " << recvd << " ; text: " << buffer;
				}
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
