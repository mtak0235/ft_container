#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator/iterator.hpp"
#include "iterator/vector_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "utils/utils.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T>>
	class vector
	{

	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::vector_iterator<value_type> iterator;
		typedef ft::vector_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		/* constructor */

		/**
		 * @brief default 생성자
		 *
		 * @param allocator
		 */
		explicit vector(const allocator_type &allocator = allocator_type())
			: _allocator(allocator), _size(0), _begin(NULL), _capacity(0)
		{
		}
		/**
		 * @brief fill 생성자
		 *
		 * @param count : 초기 컨테이너 크기
		 * @param val : 컨테이너를 초기화 할 값
		 * @param allocator
		 */
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &allocator = allocator_type())
			: _allocator(allocator)
		{
			if (n > 0)
			{
				if (n > _allocator.max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
				_size = n;
				_capacity = n;
				_begin = _allocator.allocate(n);
				for (pointer i = _begin; i < _begin + size; i++)
					_allocator.construct(i, val);
			}
		}
		/**
		 * @brief range 생성자
		 * point! : template meta programming에서 if문은 템플릿 특수화를 통해 구현됨
		 * @param InputIterator
		 * @param first 첫 element를 가리키는 iterator
		 * @param last  마지막 다음을 가리키는 iterator
		 * @param allocator
		 */
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &allocator = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
			: _size(0), _allocator(allocator)
		{
			difference_type d = ft::distance(first, last);
			if (d < 0 || d > static_cast<difference_type>(_allocator.max_size()))
				throw std::length_error("vector");
			_begin = _allocator.allocate(d);
			while (first != last) {
				this->push_back(*first);
				first++;
			}
		}
		/**
		 * @brief 복사 생성자
		 *
		 * @param source
		 * @version 0.1
		 * @author your name (you@domain.com)
		 * @date 2022-06-16
		 * @copyright Copyright (c) 2022
		 */
		vector(const vector &source)
			: _size(0), _capacity(source._size)
		{
			_begin = _allocator.allocate(_capacity)
			for (size_type i = 0; i < x.size(); i++)
				push_back(source[i]);
		}
		~vector()
		{
			clear();
			_allocator.deallocate(_begin, _capacity);
		}
		/**
		 * @brief 대입 연산자
		 *
		 * @param x
		 * @return vector&
		 * @version 0.1
		 * @author your name (you@domain.com)
		 * @date 2022-06-16
		 * @copyright Copyright (c) 2022
		 */
		vector &operator=(const vector &source)
		{
			if (this != &source)
			{
				clear();
				this->assign(x.begin(), x.end());
				_capacity = source._capacity;
				_begin = _allocator.allocate(_capacity);
				for (size_type i = 0; i < source.size(); i++) {
					_allocator.construct(_begin + i, source._begin + i);
				}
				_size = source.size();
			}
			return *this;
		}

		/* Iterator */
		iterator begin() { return iterator(_begin); }
		const_iterator begin() const { return const_iterator(_begin); }
		iterator end() { return iterator(_begin + _size); }
		const_iterator end() const { return const_iterator(_begin + _size); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* capacity */
		size_type size() const { return _size; }
		size_type max_size() const
		{
			const size_t nmax = std::numeric_limits<size_type>::max();
			const size_t amax = _allocator.max_size();
			return nmax > amax ? amax : nmax;
		}
		bool empty() const { return begin() == end() }
		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				while (_size > n)
					pop_back();
			else
				while (_size < n)
					push_back(val);

		}
		size_type capacity() const {return _capacity;}
		void reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				pointer tmp = _allocator.allocate(new_cap);
				// size_type tmpSize = size();
				// size_type tmpCap = capacity();
				for (size_type i = 0; i < size(); i++) {
					_allocator.construct(tmp + i, _begin[i]);
					_allocator.destroy(_begin[i]);
				}
				if (_capacity != 0)
					_allocator.deallocate(_begin, _capacity);
				_begin = tmp;
				_capacity = new_cap;
			}
		}

		/* element access */
		reference operator[](size_type n) {}
		const_reference operator[](size_type n) const {}
		reference at(size_type n) {}
		const_reference at(size_type n) const {}
		reference front() {}
		const_reference front() const {}
		reference back() {};
		const_reference back() const {};

		/* modifier */
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			for (; first != last; first++)
				push_back(first);
		}
		void assign(size_type n, const value_type &val)
		{
			clear();
			if (n <= capacity())
			{
				while (n--)
					_allocator.construct(_finish++, val);
			}
			else
			{
				_allocator.deallocate(_begin, capacity());
				_begin = _finish = _allocator.allocate(n);
				_end_of_cap = _begin + n;
				while (n--)
				{
					_allocator.construct(_finish++, val);
				}
			}
		}
		void push_back(const value_type &val)
		{
			if (max_size() > size() + 1)
				throw std::length_error("vector::push_back() can't push back more than vector::max_size()");
			if (this->_finish != this->_end_of_cap)
				_allocator.construct(_finish++, val);
			else
			{
				reserve(size() > 0 ? 3 / 2 * size() : 1);
				_allocator.construct(_finish++, val);
			}
		}
		void pop_back() {}
		iterator insert(iterator position, const value_type &val)
		{
			vector<value_type> newV;
			size_type d = 0;
			iterator it = begin();
			while (it != end())
			{
				newV.push_back(*it);
				it < position ? ++d : 0;
				it++;
				if (it == position)
					newV.push_back(val);
			}
			clear();
			for (iterator it2 = newV.begin(); it2 != newV.end(); it2++)
			{
				push_back(*it2);
			}
			return begin() + d;
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			vector<value_type> newV;
			iterator it = begin();
			while (it != position)
			{
				newV.push_back(*it);
				it++;
			}
			for (size_t i = 0; i < n; i++)
				newV.push_back(val);
			while (it != end())
			{
				newV.push_back(*it);
				it++;
			}
			clear();
			for (iterator it2 = newV.begin(); it2 != newV.end(); it2++)
				push_back(*it2);
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			vector<value_type> newV;
			iterator it = begin();
			while (it != position)
			{
				newV.push_back(*it);
				it++;
			}
			for (iterator it3 = first; it3 != last; it3++)
				newV.push_back(*it3);
			while (it != end())
			{
				newV.push_back(*it);
				it++;
			}
			clear();
			for (iterator it2 = newV.begin(); it2 != newV.end(); it2++)
				push_back(*it2);
		}
		iterator erase(iterator position) {}
		iterator erase(iterator first, iterator last) {}
		void swap(vector &x)
		{
			if (x == *this)
				return;
			pointer tmpStart = _begin;
			pointer tmpFinish = _finish;
			size_type tmpEndOfCap = _end_of_cap;
			allocator_type tmpAlloc = _allocator;
			_begin = x._begin;
			_finish = x._finish;
			_end_of_cap = x._end_of_cap;
			_allocator = x._allocator;
			x._begin = tmpStart;
			x._finish = tmpFinish;
			x._end_of_cap = tmpEndOfCap;
			x._allocator = tmpAlloc;
		}
		void clear()
		{
			if (_begin) {
				for (size_type i = 0; i < _size; i++)
					this->allocator.destroy(_begin + i);
			}
			_begin = 0;
			_size = 0;
		}
		
		/* allocator */
		allocator_type get_allocator() const {}

		/**
		 * @brief 멤버 변수
		 * _begin :  벡터 내부에 할당된 메모리의 시작 주소
		 * _allocator : 할당자 클래스 변수
		 * _size: 벡터 요소 수
		 * _capacity: 벡터에 넣을 수 있는 요소 수
		 */
	private:
		pointer _begin;
		// pointer _end;
		// pointer _end_cap;
		allocator_type _allocator;
		size_type _size;
		size_type _capacity;
	};

/*** non member functions overloads ***/
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector::const_iterator lhst = lhs.begin();
		typename ft::vector::const_iterator rhst = rhst.begin();
		for (; lhst != lhst.end(); lhst++, rhst++)
		{
			if (*rhst != *lhst)
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
	}
} // namespace ft

#endif