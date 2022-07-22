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
			while (first != last)
			{
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
			_begin = _allocator.allocate(_capacity) for (size_type i = 0; i < x.size(); i++)
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
				for (size_type i = 0; i < source.size(); i++)
				{
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
		size_type capacity() const { return _capacity; }
		void reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				pointer tmp = _allocator.allocate(new_cap);
				for (size_type i = 0; i < size(); i++)
				{
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
		reference operator[](size_type n){return _begin[n]} const_reference operator[](size_type n) const {return _begin[n]} reference at(size_type n)
		{
			if (n < 0 || n > _size)
				throw std::out_of_range("vector");
			return _begin[n];
		}
		const_reference at(size_type n) const
		{
			if (n < 0 || n > _size)
				throw std::out_of_range("vector");
			return _begin[n];
		}
		reference front() { return _begin[0]; }
		const_reference front() const { return _begin[0]; }
		reference back() { return _begin[_size - 1]; };
		const_reference back() const { return _begin[_size - 1]; };

		/* modifier */
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
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
				for (int i = 0; i < n; i++)
					_allocator.construct(_begin + i, val);
				_size = n;
			}
			else
			{
				_allocator.deallocate(_begin, capacity());
				_begin = _allocator.allocate(n);
				for (int i = 0; i < n; i++)
					_allocator.construct(_begin + i, val);
				_size = n;
				_capacity = n;
			}
		}
		void push_back(const value_type &val)
		{
			if (max_size() > size() + 1)
				throw std::length_error("vector::push_back() can't push back more than vector::max_size()");
			if (this->_size == this->_capacity)
				reserve(capacity() > 0 ? 3 / 2 * capacity() : 1);
			_allocator.construct(_begin + _size, val);
			_size++;
		}
		void pop_back()
		{
			_allocator.destroy(_begin + _size - 1);
			_size--;
		}
		iterator insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
			return position;
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			iterator iter = begin();
			size_type pos = position.base() - begin().base();
			// 원래 SegFault 나옴.
			if (pos > size_ || pos < 0)
				throw std::length_error("vector");
			if (capacity_ == 0)
			{
				address_ = allocator_.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					allocator_.construct(address_ + i, val);
				}
				size_ = n;
				capacity_ = n;
			}
			// 다시 할당 해야 하는 경우
			else if (size_ + n > capacity_)
			{
				size_type j = 0;
				if (size_ + n <= capacity_ * 2)
					capacity_ *= 2;
				else
					capacity_ = size_ + n;
				value_type *tmp = allocator_.allocate(capacity_);
				for (size_type i = 0; i < size_; i++)
				{
					if (i == pos)
					{
						while (j < n)
						{
							allocator_.construct(tmp + i + j, val);
							j++;
						}
					}
					allocator_.construct(tmp + i + j, address_[i]);
					allocator_.destroy(address_ + i);
				}
				allocator_.deallocate(address_, capacity_);
				address_ = tmp;
				size_ += j;
			}
			// capacity가 충분한 경우
			else
			{
				for (size_type i = 1; i < size_ - pos + n; i++)
				{
					allocator_.construct(address_ + size_ - i + n, address_[size_ - i - 1 + n]);
					allocator_.destroy(address_ + size_ - i - 1 + n);
				}
				for (size_type i = 0; i < n; i++)
				{
					allocator_.construct(address_ + pos + i, val);
				}
				size_ += n;
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			iterator iter = begin();
			size_type pos = position.base() - begin().base();
			size_type count = ft::distance(first, last);
			// std::vector는 세폴이 나오는데, 세폴을 만들 방법이 없어 throw로 처리 함
			if (pos > size_ || pos < 0)
				throw std::length_error("vecor");
			// InputIterator가 잘못된 주소값이 들어오는 경우 std::vector는 그냥 무시함
			if (count > 100000 || count <= 0)
			{
			}
			// 벡터가 비어있는 경우
			else if (capacity_ == 0)
			{
				address_ = allocator_.allocate(count);
				for (size_type i = 0; i < count; i++)
				{
					allocator_.construct(address_ + i, *first);
					first++;
				}
				size_ = count;
				capacity_ = count;
			}
			// 다시 할당 해야 하는 경우
			else if (size_ + count > capacity_)
			{
				size_type j = 0;
				if (size_ + count <= capacity_ * 2)
					capacity_ *= 2;
				else
					capacity_ = size_ + count;
				value_type *tmp = allocator_.allocate(capacity_);
				for (size_type i = 0; i <= size_; i++)
				{
					if (i == pos)
					{
						while (j < count)
						{
							allocator_.construct(tmp + i + j, *first);
							j++;
							first++;
						}
					}
					allocator_.construct(tmp + i + j, address_[i]);
					allocator_.destroy(address_ + i);
				}
				allocator_.deallocate(address_, capacity_);
				address_ = tmp;
				size_ += j;
			}
			// capacity가 충분한 경우
			else
			{
				for (size_type i = 1; i <= count; i++)
				{
					allocator_.construct(address_ + size_ + count - i, address_[size_ - i]);
				}
				size_ += count;
				for (size_type i = 0; i < count; i++)
				{
					allocator_.destroy(address_ + pos + i);
					allocator_.construct(address_ + pos + i, *first);
					first++;
				}
			}
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
			if (_begin)
			{
				for (size_type i = 0; i < _size; i++)
					this->allocator.destroy(_begin + i);
			}
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