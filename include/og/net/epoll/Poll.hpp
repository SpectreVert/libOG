/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 *
*/

#pragma once

#include "og/net/Socket.hpp"
#include "og/net/epoll/Event.hpp"
#include "og/net/generic/IPoll.hpp"

#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Poll implementation for epoll
//!
class Poll : IPoll<SocketHandle, Events> {
public:
	//! \brief Initialize the internal resource for event
	//!        polling.
	//!
	//! \see   is_valid
	//!
	Poll();
    virtual ~Poll();

	//! \brief Indicates if the object has been properly
	//!        initialized and can be used safely.
	//!
	virtual bool is_valid() const;

    virtual int poll(Events& events, int timeout);
    virtual int add(SocketHandle source, core::Tag id, core::Concern concern);
    virtual int remove(SocketHandle source);

private:
    int m_epoll_fd;

}; // class Poll

} // namespace net

} // namespace og
