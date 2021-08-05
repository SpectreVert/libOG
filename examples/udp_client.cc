/*
 * Created by Costa Bushnaq
 *
 * 05-08-2021 @ 14:23:58
*/

#include <iostream>
#include <cstring>
#include <string_view>

#include "og/net/Poll.hpp"
#include "og/net/UdpSocket.hpp"
#include "og/net/Error.hpp"

#define SOCKET 1

int main()
{
	og::net::UdpSocket udp;
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::net::Poll::Events events;
	
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	if (udp.bind(addr) < 0)
	{
		std::cerr << "Could not bind" << std::endl;
		return 1;
	}

	if (poll.monitor(udp, SOCKET, og::core::e_read|og::core::e_write) < 0)
	{
		std::cerr << "Could not monitor" << std::endl;
		return 1;
	}

	for (;;)
	{
		poll.poll(events, -1);

		for (auto event : events)
		{
			int res;
			std::size_t recvd;

			if (event.is_readable())
			{
				res = udp.recv_from(addr, data, recvd);

				if (res == og::net::e_success)
				{
					std::string_view str{reinterpret_cast<char*>(data.first)};
					std::cout << "received datagram: " << str.substr(0, recvd);
				}
				else
				{
					std::cerr << "error on socket: " << strerror(errno) << '\n';
					return 1;
				}
			}
		}
	}
}
