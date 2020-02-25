/*
 * libOG, 2020
 *
 * Name: Headers.hpp
 *
 * Description:
 * Encapsulation of HTTP-style headers.
*/

#pragma once

#include "og/base/Umap.hpp"

#include <string>

namespace og {

namespace Http {

class Headers {
public:
	typedef Umap<std::string, std::string> HeadersUmap;
	
	Headers();
	Headers(HeadersUmap t_headers);

	const std::string& operator[] (const std::string& t_name) const;
	std::string& operator[] (const std::string& t_name);

	bool has(const std::string& t_name) const;
	void insert(const std::string& t_name, const std::string& t_value);
	void erase(const std::string& t_name);
	void clear();

private:
	HeadersUmap m_headers;

};

} // namespace Http

} // namespace og
