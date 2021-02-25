/*
 * Created by Costa Bushnaq
 *
 * 24-02-2021 @ 19:04:07
*/

#include "og/async/Driver.hpp"

using namespace og::async;

int Driver::dispatch(core::Tag id, net::Events& events)
{
	(void) id;
	(void) events;

	return 0;
}

int Driver::monitor(net::SocketHandle source, core::Tag id, core::Concern concern)
{
	(void) source;
	(void) id;
	(void) concern;

	return 0;
}

int Driver::step(int timeout)
{
	return timeout;
}
