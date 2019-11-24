/*
 * SGE, 2019
 *
 * Name: NonCopyable.hpp
 *
 * Description:
 * 
*/

#pragma once

namespace sge {

class non_copyable {
private:
	non_copyable();
	non_copyable(const non_copyable&) = delete;
	non_copyable&operator=(const non_copyable&) = delete;
}; // class non_copyable

} // namespace sge
