/*
 * libOG, 2020
 *
 * Name: Registry.hpp
 * 
*/

#pragma once

#include "og/base/NonCopyable.hpp"
#include "og/network/Selector.hpp"
#include "og/network/SocketHandle.hpp"
#include "og/network/Token.hpp"

namespace og {

//! \brief Register a I/O source for events on the Poll instance
//!
class Registry : public NonCopyable {
public:

	//! \brief Default constructor
	//!
	Registry()
	{

	}

	//! \brief Access the selector
	//!
	//! \return The selector
	//!
	Selector& selector()
	{
		return m_selector;
	}

private:

	Selector m_selector; //!< OS-based selector implementation

}; // class Poll

} // namespace og
