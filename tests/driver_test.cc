/*
 * Created by Costa Bushnaq
 *
 * 28-03-2021 @ 15:12:11
*/

#include "og/async/Driver.hpp"
#include "og/net/TcpStream.hpp"

#include <iostream>

int test(og::net::TcpStream& st, int flag)
{
	(void) st;
	(void) flag;

	return flag + 20;
}

int main()
{
	og::async::Driver d;
	og::net::TcpStream st;
	std::function<int()> fn1 = std::bind(&test, st, 0);
	std::function<int()> fn2 = std::bind(&test, st, 1);

	// do not use binded fn after call to monitor_then
	auto fut1 = d.monitor_then(st, 0, fn1);
	auto fut2 = d.monitor_then(st, 1, fn2);

	d.run_all();

	std::cerr << "got: " << fut1.get() << '\n';
	std::cerr << "got: " << fut2.get() << '\n';
}
