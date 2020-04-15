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

int Poll::remove(SocketHandle socket)
{
	return m_registry.selector().remove(socket);
}

int Poll::add(SocketHandle socket, Token token, Concern concern)
{
	return m_registry.selector().add(socket, token, concern);
}

int Poll::poll(Events& events, int64_t timeout)
{
	return m_registry.selector().select(events, timeout);
}

