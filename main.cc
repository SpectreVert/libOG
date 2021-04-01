/*
 * Created by Costa Bushnaq
 *
 * 08-03-2021 @ 14:30:02
*/

#include "og/net/TcpStream.hpp"
#include "og/async/Driver.hpp"

#include <future>
#include <iostream>
#include <cmath>

#define SOCKET 1

int do_stuff(og::net::TcpStream& tcp)
{
	std::size_t recvd;
	char buffer[48];
	og::core::RawBuffer data{reinterpret_cast<void*>(buffer), 48};

	int res = tcp.recv(data, recvd);

	return static_cast<int>(recvd);
}

int main()
{
	og::net::TcpStream tcp;
	og::net::SocketAddr addr(og::net::Ipv4(127, 0, 0, 1), 6970);
	og::net::Poll poll;
	og::async::Driver driver(poll);
	std::packaged_task<int(og::net::TcpStream&)> task(do_stuff);

	tcp.connect(addr);

	auto res = driver.monitor_for(
		tcp,
		1,
		og::core::Writable | og::core::Readable,
		task
	);

	std::cerr << res.get() << std::endl;
}
