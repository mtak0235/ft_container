#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator : public iterator<ft::random_access_iterator_tag, Iterator>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traitsM<Iterator>::reference reference;
		reverse_iterator() : _current(){};
		explicit reverse_iterator(iterator_type it) : _current(it){};
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iterator> &rev_it) : _current(rev_it.base()){};
		~reverse_iterator();
		reverse_iterator &operator=(const reverse_iterator &source)
		{
			if (this != &source)
			{
				this->_current = source._current;
			}
			return *this;
		}
		iterator_type base() const { return _current; };
		reference operator*() const
		{
			iterator_type t = _current;
			return *(--t);
		};
		pointer operator->() const
		{
			return &(operator*());
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); };
		reverse_iterator &operator++()
		{
			_current--;
			return *this;
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator t(*this);
			_current--;
			return t;
		};
		reverse_iterator &operator+=(difference_type n)
		{
			_current -= n;
			return *this;
		};
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); };
		reverse_iterator &operator--()
		{
			_current++;
			return *this;
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator t(*this);
			_current++;
			return t;
		};
		reverse_iterator &operator-=(difference_type n)
		{
			_current += n;
			return *this;
		};
		reference operator[](difference_type n) const {return *(_current - n - 1)};

	private:
		iterator_type _current;
	};
	/** no member functions**/
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() == rhs.base(); };
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() != rhs.base(); };
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
				   const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() > rhs.base(); };
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() <= rhs.base(); };
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
				   const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() < rhs.base(); };
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() <= rhs.base(); };

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
									 const reverse_iterator<Iter> &it) { return it.base() - n; };
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs,
			  const reverse_iterator<Iterator> &rhs) {return rhs.base() - lhs.base();};
}
#endif