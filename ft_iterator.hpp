#ifndef FT_ITERATOR
# define FT_ITERATOR

#include "ft_utility.hpp"

namespace ft {
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
		Random_access_iterator& operator!=(const pointer rhs) const {return _ele != rhs._ele;}
		Random_access_iterator& operator==(const pointer rhs) const {return _ele == rhs._ele;}
		reference operator*(void) {return *_ele;}
		reference operator
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