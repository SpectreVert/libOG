/*
 * libOG, 2020
 *
 * Name: Message.hpp
 *
 * Description:
 * Base class for any HTTP message.
*/

#pragma once

#include "og/network/Http/Headers.hpp"

namespace og {

namespace Http {

class Message {
public:

private:
	Headers m_headers;

}; // class Message

}; // namespace Http

} // namespace og
