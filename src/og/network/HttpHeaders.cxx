/*
 * libOG, 2020
 *
 * Name: Header.cxx
 *
 * Description:
 * Encapsulation of HTTP-style headers.
*/

#include "og/network/HttpHeaders.hpp"

using namespace og::Http;

Headers::Headers()
{}

Headers::Headers(const Headers& t_other)
{
	m_headers = t_other.m_headers;
}

bool Headers::has(const std::string& t_name) const
{
	auto it = m_headers.find(t_name);

	if (it != m_headers.end())
		return true;
	
	return false;
}

void Headers::insert(const std::string& t_name, const std::string& t_value)
{
	m_headers.insert(HeadersUmap::ValueType(t_name, t_value));
}

const std::string& Headers::operator[] (const std::string& t_name) const
{
	return m_headers[t_name];
}

std::string& Headers::operator[] (const std::string& t_name)
{
	return m_headers[t_name];
}
