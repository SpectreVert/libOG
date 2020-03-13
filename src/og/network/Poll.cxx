/*
 * libOG, 2020
 *
 * Name: Poll.cxx
 *
*/

#include "og/network/Poll.hpp"

using namespace og;

Poll::Poll()
{
	
}

int Poll::poll(Events& events, int timeout)
{
	return m_registry.selector().select(events, timeout);
}

int Poll::add(SocketHandle socket, Token token, Concern concern)
{
	return m_registry.selector().add(socket, token, concern);
}
