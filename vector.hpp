#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>

namespace ft
{
	template<typename T, class Allocator = std::allocator<T>>
	class random_access_iterator {

	};
	
	template<typename T, class Allocator = std::allocator<T>>
	class reverse_iterator {

	};


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

			// allocator
			// 	이 개체에 사용할 할당자 클래스입니다.get_allocator 개체에 대 한 할당자 클래스를 반환 합니다.

			// 	count
			// 		생성된 벡터에 있는 요소의 수입니다.

			// 	value
			// 		생성된 벡터에 있는 요소의 값입니다.

			// 	source
			// 		해당 복사본으로 벡터를 생성할 벡터입니다.

			// 	first
			// 		복사할 요소의 범위에서 첫 번째 요소의 위치입니다.

			// 	last
			// 		복사할 요소의 범위를 벗어난 첫 번째 요소의 위치입니다.

			// 	init_list
			// 		initializer_list복사할 요소를 포함 하는입니다.
			vector(const allocator_type &alloc = allocator_type())
			{}
			explicit vector(const Allocator &allocator)
			{}
			explicit vector(size_type count, const value_type &val = value_type(), const allocator_type &alloc= allocator_type())
			{}
			vector(const vector &source)
			{}
			vector(vector &&source)
			{}
			vector(initializer_list<T> init_list, const Allocator &allocator)
			{}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last)
			{}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &allocator)
			{}
		private:
			_allo
	};

}
#endif