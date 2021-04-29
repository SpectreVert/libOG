/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:42:41
 *
 * see LICENSE
*/

#ifndef _POLL_HPP
#define _POLL_HPP


#include "og/net/epoll/Event2.hpp"
#include "og/net/generic/IPoll2.hpp"
#include "og/net/generic/ISource2.hpp"
#include "og/net/Socket2.hpp"

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

	virtual int monitor(Source&, core::Tag, core::Concern);
	virtual int re_monitor(Source&, core::Tag, core::Concern);
	virtual int forget(Source&);

private:
	core::RawFd m_epoll_fd;

}; // class Poll

} // namespace net

} // namespace og

#endif /* _POLL_HPP */
