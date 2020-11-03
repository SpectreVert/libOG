/*
 * libOG, 2020
 *
 * Name: SocketPoll.hpp
 *
*/

#pragma once

#include "og/io/IPoll.hpp"
#include "og/net/Socket.hpp"

namespace og {

namespace net {

template<std::size_t N = 32>
class Poll : public io::IPoll<Socket, N> {
public:
	Poll();
	virtual ~Poll() = default;

	virtual int poll(io::Events<N> events, int timeout);
	virtual int add(Socket source, io::Tag id, io::Concern concern);
	virtual int remove(Socket source);

private:
	io::Events<N> m_events;

}; // class Poll

} // namespace net

} // namespace og
