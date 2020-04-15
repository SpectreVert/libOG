/*
 * libOG, 2020
 *
 * Name:
 *
 * Description:
 * Asynchronous I/O example
*/

#include <og/network.hpp>
#include <og/base/SystemException.hpp>

#include <string>
#include <iostream>

#include <memory>
#include <vector>

#define WRITE_BUFFER 24
#define READ_BUFFER 48

int main()
{
	try
	{


	og::TcpListener listener;
	og::Poll poll;
	int sid;






	}
	catch (og::SystemException& e)
	{
		std::cerr << e.who() << ": " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

/*

int main()
{
	try {
	og::TcpListener listener;
	og::Poll poll;
	int sid = 1;

	listener.listen(6970, og::Ipv4::Loopback);

	poll.add(listener.handle(), 0, og::Concern::Readable);

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

				poll.add(sock->handle(), sid, og::Concern::Both);

				sid++;

			} else
			{
				if (event.is_read_closed())
				{
					std::cerr << "CLOSED";
				
					auto sock = sockets[event.token() - 1];
					poll.remove(sock->handle());

					(void) event;
				}

				if (event.is_write_closed())
				{
					(void) event;
				}

				if (event.is_writable())
				{
					std::shared_ptr<og::TcpStream> sock = sockets[event.token() - 1];
					char buffer[WRITE_BUFFER];
					ssize_t sent = 0;

					std::memset(buffer, 0, sizeof(buffer));
					std::memcpy(buffer, "yo mec", 6);

					sock->send(buffer, sizeof(buffer), sent);
				}

				if (event.is_readable()) 
				{
					std::shared_ptr<og::TcpStream> sock = sockets[event.token() - 1];

					char buffer[READ_BUFFER];
					ssize_t recvd = 0;

					sock->receive(buffer, sizeof(buffer), recvd);

					buffer[recvd < READ_BUFFER ? recvd : READ_BUFFER] = '\0';
					std::cout << "bytes: " << recvd << " ; text: " << buffer;
					std::cerr << std::endl;
				}
			}
		}
	}
	} catch (og::SystemException& e)
 	{
		std::cerr << e.who() << ": " << e.what() << std::endl;
 	}
}

*/
