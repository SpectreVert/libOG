/*
 * Created by Costa Bushnaq
 *
 * 12-02-2021 @ 19:20:55
*/

#include <cstring>
#include <iostream>
#include <string_view>

#include "og/Poll.hpp"
#include "og/TcpListener.hpp"

/* TODO: include Error.hpp in headers
 * that use the return codes
*/
#include "og/Error.hpp"

#define L 1

int main(int ac, char* av[])
{
	(void) ac;

	og::TcpListener listener;
	og::SocketAddr addr(og::Ipv4(127, 0, 0, 1), 6970);
	og::Poll poll;
	og::Poll::Events events;
	og::RawBuffer data; (void) data;

	if (listener.bind(addr) < 0)
		goto error;

	if (listener.listen(128) < 0)
		goto error;
	
	if (poll.add(listener, L, og::Poll::e_write | og::Poll::e_read) == -1)
		goto error;

	for (;;) {
		poll.poll(events, -1); // not timeout -> wait infinite

		auto event = events[0];
		{
			if (event.is_readable())
			{
				auto new_stream = listener.try_accept();

				if (!new_stream)
					goto error;

				std::cerr << "Accepted socket" << std::endl;
			}
		}
	}

error:
	std::cerr << av[0] << ": " << strerror(errno) << std::endl;
	return 1;
}
