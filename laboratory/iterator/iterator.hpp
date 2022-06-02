#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
class iterator
{
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef Category iterator_category;
};

} // namespace ft
#endif