/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:42:41
 *
 * see LICENSE
*/

#ifndef _POLL_HPP
#define _POLL_HPP

#include "og/epoll/Event.hpp"
#include "og/generic/IPoll.hpp"
#include "og/generic/ISource.hpp"
#include "og/Socket.hpp"

#include <sys/epoll.h>

namespace og {

class Poll : public IPoll<Socket, Event> {
public:
	virtual ~Poll();
	Poll();

	virtual int poll(Events& events, int timeout);

	virtual int monitor(Source& socket, Tag id, Concern concern);
	virtual int re_monitor(Source& socket, Tag id, Concern concern);
	virtual int forget(Source& socket);

private:
	int m_epoll_fd;

}; // class Poll

} // namespace og

#endif /* _POLL_HPP */
