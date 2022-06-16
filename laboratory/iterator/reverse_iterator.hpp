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
		reverse_iterator() : _curr(){};
		explicit reverse_iterator(iterator_type it) : _curr(it){};
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iterator> &rev_it) : _curr(rev_it.base()){};
		~reverse_iterator();
		reverse_iterator &operator=(const reverse_iterator &source)
		{
			if (this != &source)
			{
				this->_curr = source._curr;
			}
			return *this;
		}
		iterator_type base() const { return _curr; };
		reference operator*() const
		{
			iterator_type t = _curr;
			return *(--t);
		};
		pointer operator->() const
		{
			return &(operator*());
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_curr - n); };
		reverse_iterator &operator++()
		{
			_curr--;
			return *this;
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator t(*this);
			_curr--;
			return t;
		};
		reverse_iterator &operator+=(difference_type n)
		{
			_curr -= n;
			return *this;
		};
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_curr + n); };
		reverse_iterator &operator--()
		{
			_curr++;
			return *this;
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator t(*this);
			_curr++;
			return t;
		};
		reverse_iterator &operator-=(difference_type n)
		{
			_curr += n;
			return *this;
		};
		reference operator[](difference_type n) const {return *(_curr - n - 1)};

	private:
		iterator_type _curr;
	};
	/** no member functions**/
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) { return (this->_curr == )};
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs);
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs);
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs);
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs);
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs);
}
#endif