#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "ft_utility.hpp"

namespace ft {
	
	template <class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key, T>>>
	class map {
		typedef pair<const Key, T>			valuetype;
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef 

	};

}

#endif