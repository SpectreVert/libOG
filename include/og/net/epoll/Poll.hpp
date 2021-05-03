/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:42:41
 *
 * see LICENSE
*/

#ifndef _POLL_HPP
#define _POLL_HPP

#include "og/net/epoll/Event.hpp"
#include "og/net/generic/IPoll.hpp"
#include "og/net/generic/ISource.hpp"
#include "og/net/Socket.hpp"

#include <sys/epoll.h>

namespace og {

namespace net {

class Poll : public IPoll<Socket, Event> {
public:
	using Source = IPoll::Source;
	using Event  = IPoll::Event;
	using Events = IPoll::Events;

	virtual ~Poll();
	Poll();

	virtual int poll(Events& events, int timeout);

	virtual int monitor(Source&, core::Tag, short);
	virtual int re_monitor(Source&, core::Tag, short);
	virtual int forget(Source&);

private:
	core::RawFd m_epoll_fd;

}; // class Poll

} // namespace net

} // namespace og

#endif /* _POLL_HPP */
