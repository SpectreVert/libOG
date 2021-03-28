/*
 * Created by Costa Bushnaq
 *
 * 12-02-2021 @ 19:20:55
*/

#include <cstring>
#include <iostream>
#include <string_view>

#include "og/net/Poll.hpp"
#include "og/net/TcpListener.hpp"

/* TODO: include Error.hpp in headers
 * that use the return codes
*/
#include "og/core/Error.hpp"

#define SOCKET 1

int main(int ac, char* av[])
{
	og::net::TcpListener tcplistener;
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::net::Events events = og::net::ev::with_capacity(1024);
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	if (tcplistener.bind(addr) < 0)
		goto error;

	if (tcplistener.listen(128) < 0)
		goto error;
	
	//tcplistener.monitor(poll, SOCKET, og::core::Writable | og::core::Readable);
	//! Alternate syntax:
	if (poll.monitor(tcplistener, SOCKET, og::core::e_write | og::core::e_read) == -1)
		goto error;

	for (;;) {
		poll.poll(events, -1); // not timeout -> wait infinite
		og::net::TcpStream new_stream;

		std::cerr << "just got " << events.size() << " events\n";
		auto event = events[0];
		{
			if (og::net::ev::is_readable(event))
			{
				int res = tcplistener.accept(new_stream);

				if (res < 0)
					goto error;

				std::cerr << "Accepted socket" << std::endl;
			}
		}
	}

error:
	std::cerr << av[0] << ": " << strerror(errno) << std::endl;
	return 1;
}
