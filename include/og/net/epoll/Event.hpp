/*
 * Created by Costa Bushnaq
 *
 * 27-03-2021 @ 21:04:45
 *
*/

#pragma once

#include "og/core/Tag.hpp"

#include <vector>
#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Events implementation for epoll
//!
using Event = epoll_event;
using Events = std::vector<Event>;

// TODO: bruh this looks nastyyyyy

namespace ev {

//! \brief Create and return an Events object with
//!        at least cap capacity
//!
Events with_capacity(std::size_t cap);

core::Tag id(Event event);

bool is_readable(Event event);
bool is_writable(Event event);
bool is_read_closed(Event event);
bool is_write_closed(Event event);
bool is_error(Event event);

} // namespace ev

} // namespace net

} // namespace og
