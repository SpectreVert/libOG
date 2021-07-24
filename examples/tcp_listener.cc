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
#include "og/net/Error.hpp"

#define L 1

int main(int ac, char* av[])
{
	(void) ac;

	og::net::TcpListener listener;
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::net::Poll::Events events;
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	if (listener.bind(addr) < 0)
		goto error;

	if (listener.listen(128) < 0)
		goto error;
	
	if (poll.monitor(listener, L, og::core::e_write | og::core::e_read) == -1)
		goto error;

	for (;;) {
		poll.poll(events, -1); // not timeout -> wait infinite

		auto event = events[0];
		{
			if (event.is_readable())
			{
				auto new_str = listener.try_accept();

				if (!new_str)
					goto error;

				std::cerr << "Accepted socket" << std::endl;
			}
		}
	}

error:
	std::cerr << av[0] << ": " << strerror(errno) << std::endl;
	return 1;
}
