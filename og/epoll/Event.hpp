/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 14:38:49
 *
 * see LICENSE
*/

#ifndef _EVENT_HPP
#define _EVENT_HPP

#include "og/generic/IEvent.hpp"

#include <sys/epoll.h>

namespace og {

struct Event : public epoll_event, public IEvent {
	virtual ~Event() = default;
	Event() = default;
	explicit Event(epoll_event);

	Tag id() const;

	bool is_error() const;
	bool is_readable() const;
	bool is_read_closed() const;
	bool is_writable() const;
	bool is_write_closed() const;

}; // class Event

} // namespace og

#endif /* _EVENT_HPP */
