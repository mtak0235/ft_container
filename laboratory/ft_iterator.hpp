#ifndef FT_ITERATOR
# define FT_ITERATOR

#include "ft_utility.hpp"

namespace ft {

	struct output_iterator_tag
	{};
	struct input_iterator_tag
	{};
	struct forward_iterator_tag: public input_iterator_tag, public output_iterator_tag
	{};
	struct bidirectional_iterator_tag : forward_iterator_tag
	{};
	struct random_access_iterator_tag : bidirectional_iterator_tag
	{};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};
	
	template <class Iterator>
	class iterator_traits {
		typedef Iterator::difference_type difference_type;
		typedef Iterator::value_type value_type;
		typedef Iterator::pointer pointer;
		typedef Iterator::reference reference;
		typedef Iterator::iterator_category iterator_category;

	};
	template <class T>
	class iterator_traits<T *> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T *> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	

	template<typename T>
	class Random_access_iterator : ft::iterator<Random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;

		Random_access_iterator(void) : _ele(_ele) {}
		Random_access_iterator(pointer ele) : _ele(ele) {}
		Random_access_iterator(const Random_access_iterator& op) : _ele(op._ele) {}
		Random_access_iterator &operator=(const Random_access_iterator& op) {
			if (this != op) 
				this->_ele = op._ele;
			return *this;
		}
		virtual ~Random_access_iterator (){}
		bool operator!=(const pointer rhs) const {return _ele != rhs._ele;}
		bool operator==(const pointer rhs) const {return _ele == rhs._ele;}
		reference operator*(void) {return *_ele;}
		pointer operator->(void) {return &(this->operator*())}
		Random_access_iterator& operator==(const pointer rhs) const {return _ele == rhs._ele;}

		private:
			pointer _ele;
	};

	class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

	
	template<typename T, class Allocator = std::allocator<T> >
	class reverse_iterator {

	};
}
#endif