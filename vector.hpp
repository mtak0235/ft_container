#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>

namespace ft
{
	template<typename T, class Allocator = std::allocator<T>>
	class random_access_iterator<T> {

	}
	
	template<typename T, class Allocator = std::allocator<T>>
	class reverse_iterator<T> {

	}


	template<typename T, class Allocator = std::allocator<T>>
	class vector {
		public:
			typedef Allocator allocator_type;
			typedef T value_type;
			typedef value_type &reference;
			typedef const value_type &const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef const typename allocator_type::const_pointer const_pointer;
			typedef ft::random_access_iterator<value_type> iterator;
			typedef ft::random_access_iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename allocator_traits<allocator_type>::difference_type difference_type;
			typedef typename allocator_traits<allocator_type>::size_type size_type;

	}
}
#endif