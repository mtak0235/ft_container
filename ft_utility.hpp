#ifndef FT_UTILITY
#define FT_UTILITY

#include <cstddef>

namespace ft {

	template <class Iterator>
	class iterator_traits;
	template <class T>
	class iterator_traits<T *>;
	template <class T>
	class iterator_traits<const T *>;

	struct random_access_iterator_tag{};
	struct bidirectional_iterator_tag {};
	struct forward_iterator_tag {};
	struct output_iterator_tag {};
	struct input_iterator_tag {};

	
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <class T1, class T2>
	struct pair {
		public:
			typedef T1 first_type;
			typedef T2 second_type;
			first_type first;
			second_type second;
			pair(): T1(), T2() {}
			template<class U, class V> 
			pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}
			pair (const first_type& a, const second_type& b): first(a), second(b){}
			pair& operator= (const pair& pr){
				if (this != &pr) {
					this.first = pr.first;
					this.second = pr.second;
				}
				return *this;
			}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}
	
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const { return x < y; }
	};
}
#endif