#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include "ft_utils.hpp"
namespace ft {
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>>>
	class map
	{
	private:
		/* data */
	public:
		map(/* args */){}
		~map(){}
	};	
};

#endif