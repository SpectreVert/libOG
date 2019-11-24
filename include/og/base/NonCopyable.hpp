/*
 * libOG, 2019
 *
 * Name: NonCopyable.hpp
 *
 * Description:
 * 
*/

#pragma once

namespace og {

class NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}

private:
	NonCopyable (const NonCopyable&);
	NonCopyable& operator=(const NonCopyable&);
}; // class NonCopyable

} // namespace og
