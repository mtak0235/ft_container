#ifndef IS_ITERATOR_HPP
# define IS_ITERATOR_HPP

namespace ft {
	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant type;
	}

	template<class T>
	struct is_integral {};
}

integral_constant vs intedsjafhjc<T, v>
# endif