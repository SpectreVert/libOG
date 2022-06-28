/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
*/

#include <iostream>
#include <cstring>
#include <string_view>

#include "og/Poll.hpp"
#include "og/TcpStream.hpp"
#include "og/Error.hpp"

#define SOCKET 1

int main()
{
	og::SocketAddr addr(og::Ipv4(127, 0, 0, 1), 6970);
	og::Poll poll;
	og::Poll::Events events;
	og::RawBuffer data;

	auto res = og::TcpStream::try_connect(addr);

	if (!res) {
		std::cerr << "could not connect" << std::endl;
		return 1;
	}
	
	auto tcpstream = res.get();

	if (poll.add(*tcpstream, SOCKET, og::Poll::e_read|og::Poll::e_write) < 0)
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
					res = tcpstream->recv(data, recvd);

					if (res == og::e_success)
					{
						std::string_view str(reinterpret_cast<char*>(data.data));
						std::cout << "received message: " << str.substr(0, recvd);
					}
					else if (res == og::e_closed)
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
