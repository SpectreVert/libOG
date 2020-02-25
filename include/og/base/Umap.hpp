/*
 * libOG, 2020
 *
 * Name: Umap.hpp
 *
 * Description:
 * Unordered, associative multimap-based container.
 * 
 * Not recommended for use with large datasets.
*/

#pragma once

#include <vector>
#include <utility>

namespace og {

template <class Key, class T, class Container = std::vector<std::pair<Key, T>>>

class Umap {
public:
	using KeyType = Key;
	using MappedType = T;
	using ValueType = typename Container::value_type;

	using Iterator = typename Container::iterator;
	using ConstIterator = typename Container::const_iterator;
	using SizeType = typename Container::size_type;

	Umap()
	{
	}

	Umap(const Umap& t_other) :
		m_container(t_other.m_container)
	{
	}

	MappedType& operator[] (const KeyType& t_key)
	{
		Iterator it = find(t_key);

		// If value is not found, insert a default contructed one
		// for the given key.
		if (it == m_container.end()) {
			ValueType v(t_key, MappedType());
			it = insert(v);
		}
		return it->second;
	}

	const MappedType& operator[] (const KeyType& t_key) const
	{
		ConstIterator it = find(t_key);

		if (it == m_container.end())
			throw "Not found"; // TODO: Replace with an exception
		else
			return it->second;
	}

	Iterator begin()
	{
		return m_container.begin();
	}
	
	ConstIterator begin() const
	{
		return m_container.begin();
	}

	Iterator end()
	{
		return m_container.end();
	}

	ConstIterator end() const
	{
		return m_container.end();
	}

	void clear()
	{
		m_container.clear();
	}

	void erase(Iterator it)
	{
		m_container.erase(it);
	}

	// Remove all corresponding.
	SizeType erase(const KeyType& t_key)
	{
		Iterator it = find(t_key);
		SizeType count = 0;
		bool done = false;

		while (it != m_container.end()) {
			if (it->first == t_key) {
				done = true;
				it = m_container.erase(it);
				++count;
			} else {
				if (done)
					return count;
				++it;
			}
		}

		return count;
	}

	Iterator find(const KeyType& t_key)
	{
		Iterator begin = m_container.begin();
		Iterator end = m_container.end();

		for (; begin != end; begin++) {
			if (begin->first == t_key)
				return begin;
		}

		return end;
	}

	ConstIterator find(const KeyType& t_key) const
	{

		ConstIterator begin = m_container.begin();
		ConstIterator end = m_container.end();

		for (; begin != end; begin++) {
			if (begin->first == t_key)
				return begin;
		}

		return end;
	}

	Iterator insert(const ValueType& t_value)
	{
		Iterator it = find(t_value.first);
		
		while (it != m_container.end() && it->first == t_value.first)
			++it;
		return m_container.insert(it, t_value);
	}
	
	void size() const
	{
		return m_container.size();
	}

	void swap(Umap& t_other)
	{
		m_container.swap(t_other.m_container);
	}
	
private:
	Container m_container;	

}; // class Umap

} // namespace og
