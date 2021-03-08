/*
 * Created by Costa Bushnaq
 *
 * 24-02-2021 @ 19:21:08
*/

#include "og/async/Driver.hpp"

int add(int a)
{
	return 1;
}

int main()
{
	og::async::Driver driver;
	std::function<int(int)> func = add;

	std::cerr << driver.monitor_then(12, 54, og::core::Writable, func);
}
