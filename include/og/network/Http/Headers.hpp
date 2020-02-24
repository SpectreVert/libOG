/*
 * libOG, 2020
 *
 * Name: Headers.hpp
 *
 * Description:
 * Encapsulation of HTTP-style headers.
*/

#pragma once

#include <map>
#include <string>

namespace og {

namespace Http {

/*
	As per RFC2616 describing HTTP1.1 there can be more than
	one HTTP header with same name. This implementation offers
	only a single name-value pair.

	TODO: Implement aforementioned behaviour.

	See: https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html
*/

class Headers {
public:
	typedef std::map<std::string, std::string> HeaderMap;
	
	Headers();
	Headers(HeaderMap t_map);

	const std::string& operator[] (const std::string& t_name);

	bool has(const std::string& t_name) const;
	void add(const std::string& t_name, const std::string& t_value);
	void erase(const std::string& t_name);
	void clear();

private:
	HeaderMap m_headers;

};

} /// namespace Http

} // namespace og
