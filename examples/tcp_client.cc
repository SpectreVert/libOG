/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
*/

#include <iostream>
#include <cstring>
#include <string_view>

#include "og/net/Poll.hpp"
#include "og/net/TcpStream.hpp"
#include "og/net/Error.hpp"

#define SOCKET 1

int main()
{
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::net::Poll::Events events;
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	auto res = og::net::TcpStream::try_connect(addr);

	if (!res)
	{
		std::cerr << "could not connect" << std::endl;
		return 1;
	}
	
	auto tcpstream = res.value();

	if (poll.monitor(tcpstream, SOCKET, og::core::e_read|og::core::e_write) < 0)
	{
		std::cerr << "could not monitor" << std::endl;
		return 1;
	}

	for (;;)
	{
		poll.poll(events, -1);

		for (auto event : events)
		{
			if (event.is_error())
			{
				goto closed;
			}

			if (event.is_read_closed())
			{
				goto closed;
			}

			if (event.is_readable())
			{
				int res;
				std::size_t recvd;

				for (;;)
				{
					res = tcpstream.recv(data, recvd);

					if (res == og::net::e_success)
					{
						std::string_view str(reinterpret_cast<char*>(data.first));
						std::cout << "received message: " << str.substr(0, recvd);
					}
					else if (res == og::net::e_closed)
					{
						goto closed;
					}
					else if (res < 0)
					{
					std::cerr << "error on socket: " << strerror(errno) << '\n';
					return 1;
					}
				}
			}
		}
	}
closed:
	std::cerr << "Connection closed" << std::endl;
	return 0;
}
