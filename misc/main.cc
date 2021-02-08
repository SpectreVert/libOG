/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
*/

#include <iostream>
#include <string_view>
#include <cstring>

#include "og/net/Poll.hpp"
#include "og/net/TcpStream.hpp"
#include "og/core/Error.hpp"

#define SOCKET 1

int main()
{
	og::net::TcpStream tcpstream;
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::net::Events events;
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	if (!poll.is_valid())
		return 1;

	tcpstream.connect(addr);

	poll.add(tcpstream.handle(), SOCKET, og::core::Writable | og::core::Readable);

	for (;;)
	{
		poll.poll(events, -1);

		for (auto event : events)
		{
			if (event.is_write_closed())
				goto closed;

			if (event.is_read_closed())
				goto closed;

			if (event.is_readable())
			{
				int res;
				std::size_t recvd;

				for (;;)
				{
					res = tcpstream.recv(data, recvd);

					if (res == og::net::Success)
					{
						std::string_view str(reinterpret_cast<char*>(data.first));
						std::cout << "received message: " << str.substr(0, recvd);
					}
					else if (res == og::net::Closed)
					{
						goto closed;
					}
					else if (res < 0)
					{
						std::cerr << "error on the socket: " << strerror(errno) << '\n';
						return 1;
					}
				}
			}
		}
	}
closed:
	std::cerr << "Connection closed\n";
	return 0;
}
