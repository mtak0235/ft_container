#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator/iterator.hpp"
#include "iterator/vector_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "utils/utils.hpp"
#include "utils/is_integral.hpp"
#include <memory>
#include <iostream>

namespace ft
{
template <class T, class Allocator = std::allocator<T>>
class vector
{
public:
	// member type
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

	// 기본 생성자
	explicit vector(const allocator_type &alloc = allocator_type())
			: allocator_(alloc), size_(0), address_(0), capacity_(0)
	{
	}
	// fill
	// std::vectot확인결과 length_error exception으로 vector라고만 출력됨 (맞춤)
	explicit vector(size_type n, const value_type &val = value_type(),
									const allocator_type &alloc = allocator_type()) : allocator_(alloc)
	{
		if (n > allocator_.max_size() || n < 0)
			throw std::length_error("vecor");
		size_ = n;
		capacity_ = n;
		address_ = allocator_.allocate(n);
		for (size_type i = 0; i < n; i++)
		{
			address_[i] = val;
		}
	}
	// range
	// std::vectot확인결과 length_error exception으로 vector라고만 출력됨 (맞춤)
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
			: allocator_(alloc), size_(0)
	{
		difference_type n = ft::distance(first, last);
		if (n > static_cast<difference_type>(allocator_.max_size()) || n < 0)
			throw std::length_error("vector");
		address_ = allocator_.allocate(n);
		capacity_ = n;
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}
	// 복사 생성자
	vector(const vector &x) : size_(0), capacity_(x.size_)
	{
		address_ = allocator_.allocate(capacity_);
		for (size_type i = 0; i < x.size(); i++)
			push_back(x[i]);
	}
	// 대입연산자
	vector &operator=(vector const &other)
	{
		if (this != &other)
		{
			// clear()에서  destroy실행 함
			clear();
			allocator_.deallocate(address_, capacity_);
			capacity_ = other.capacity_;
			address_ = allocator_.allocate(capacity_);
			for (size_type i = 0; i < other.size_; i++)
				push_back(other[i]);
		}
		return *this;
	}
	~vector()
	{
		if (capacity_ > 0)
		{
			clear();
			allocator_.deallocate(address_, capacity_);
		}
	}
	// vector의 시작 주소값 리턴
	iterator begin() { return iterator(address_); }
	// vector의 시작 주소값을 const로 리턴
	const_iterator begin() const { return const_iterator(address_); }
	// vector의 끝 주소값 리턴
	iterator end() { return iterator(address_ + size_); }
	// vector의 끝 주소값을 const로 리턴
	const_iterator end() const { return const_iterator(address_ + size_); }
	// vector의 끝 주소값을 reverse_iterator로 리턴
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	// vector의 시작 주소값을 reverse_iterator로 리턴
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }
	// vector의 size를 리턴
	size_type size() const { return size_; }
	// vector의 최대 사이즈를 리턴 (allocator함수 이용)
	size_type max_size() const { return allocator_.max_size(); }
	// vector의 새 크기를 지정한다.
	// value_type val이 있고, 현 size보다 큰 경우 val(val이 없으면 0으로)로 push_back
	// 만약 size보다 n이 작으면 pop_back
	void resize(size_type n, value_type val = value_type(0))
	{
		if (n < size_)
		{
			while (size_ > n)
				pop_back();
		}
		else
		{
			while (size_ < n)
				push_back(val);
		}
	}
	// vector의 capacity확인
	size_type capacity() const { return capacity_; }
	// vector가 비어 있는지 확인
	bool empty() const { return (size_ == 0); }
	// vector의 공간을 확보한다.
	// 만약 기존 capacity보다 작은 값을 넣으면 작동하지 않는다.
	// 새로운 n크기의 새로운 백터를 만들어 데이터를 복사해준다.
	// exception은 allocator에서 throw함(std::vector참조)
	void reserve(size_type n)
	{
		if (n > capacity_)
		{
			value_type *tmp = allocator_.allocate(n);
			for (size_type i = 0; i < size_; i++)
			{
				allocator_.construct(tmp + i, address_[i]);
				allocator_.destroy(address_ + i);
			}
			if (capacity_ != 0)
				allocator_.deallocate(address_, capacity_);
			address_ = tmp;
			capacity_ = n;
		}
	}
	// vector의 배열연산자 오버로딩
	reference operator[](size_type n) { return address_[n]; }
	const_reference operator[](size_type n) const { return address_[n]; }
	// vector에 지정된 위치에 있는 요소에 대한 참조를 반환한다.
	// std::vectot확인결과 length_error exception으로 vector라고만 출력됨 (맞춤)
	reference at(size_type n)
	{
		if (n < 0 || n >= size_)
			throw std::out_of_range("vector");
		return address_[n];
	}
	const_reference at(size_type n) const
	{
		if (n < 0 || n >= size_)
			throw std::out_of_range("vector");
		return address_[n];
	}
	// vector의 첫번째 요소의 참조를 반환
	reference front() { return address_[0]; }
	const_reference front() const { return address_[0]; }
	// vector의 마지막 요소에 참조를 반환
	reference back() { return address_[size_ - 1]; }
	const_reference back() const { return address_[size_ - 1]; }
	// 백터를 지우고 지정된 요소를 빈 백터에 복사한다.
	// fill
	void assign(size_type n, const value_type &val)
	{
		if (n < 0 || n > allocator_.max_size())
			throw std::length_error("vector");
		clear();
		while (size_ != n)
			push_back(val);
	}
	//range
	template <class InputIterator>
	void assign(InputIterator first,
							InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
	{
		clear();
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}
	// vector의 끝에 요소를 추가한다.
	// 비어있는 vector의 경우 1개의 공간을, 이후로 공간이 부족할 때 2배씩 공간을 할당한다.
	// 아래의 경우도 결국은 allocator로 다시 할당을 하기 떄문에 allocator에서 exception을 던질 듯
	void push_back(value_type val)
	{
		if (capacity_ == 0)
			reserve(1);
		if (size_ == capacity_)
			reserve(capacity_ * 2);
		allocator_.construct(address_ + size_, val);
		size_++;
	}
	// vector의 끝의 요소를 삭제한다.
	void pop_back()
	{
		allocator_.destroy(address_ + size_ - 1);
		size_--;
	}
	// vector 의 지정된 위치에 요소 또는 많은 요소를 삽입한다.
	// single element
	iterator insert(iterator position, const value_type &val)
	{
		insert(position, 1, val);
		return position;
	}
	// fill
	void insert(iterator position, size_type n, const value_type &val)
	{
		iterator iter = begin();
		size_type pos = position.base() - begin().base();
		// std::vector는 세폴이 나오는데, 세폴을 만들 방법이 없어 throw로 처리 함
		if (pos > size_ || pos < 0)
			throw std::length_error("vector");
		// 벡터가 비어있는 경우
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
	// range
	//insert(position, int, int)가 들어올 때 range함수로 오버로딩 되는 오류가 있다.
	//template <class InputIterator,
	//          typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value,
	//          InputIterator>::type>
	// 위에는 c++ 11버전 문법으로 다른 방법 필요
	// slack참고, 마지막 인자로 enable_if 이용
	// 만약 정수가 들어오면, type이 생성되지 않고, 정수가 아닌 값이 들어오면 4번째 매개변수가 만들어지면서 오버로딩
	// type은 아무의미없는 값으로 초기화
	template <class InputIterator>
	void insert(iterator position,
							InputIterator first,
							InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
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
	// erase
	// 인자로 받을 수 있는  iterator는 vector_iterator이며, 이미  random tag이기 때문에 따로 확인 안함
	// 백터에 지정된 위치에서 요소 또는 요소 범위를 제거 한다.
	iterator erase(iterator position)
	{
		pointer pos = position.base();
		if (position + 1 == end())
		{
			pop_back();
		}
		// std::vector의 경우 세폴, 세폴을 만들이 어려워 throw로 결정
		else if (end() - position <= 0)
		{
			throw std::length_error("vector");
		}
		else
		{
			allocator_.destroy(pos);
			for (int i = 0; i < end() - position; i++)
			{
				allocator_.construct(pos + i, *(position + i + 1));
				allocator_.destroy(pos + i + 1);
			}
			size_--;
		}
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		iterator tmp = first;
		while (first != last)
		{
			allocator_.destroy(first.base());
			first++;
		}
		for (int i = 0; i < end() - last; i++)
		{
			allocator_.construct((tmp + i).base(), *(last + i));
			allocator_.destroy(last.base());
		}
		size_ -= ft::distance(tmp, last, typename ft::iterator_traits<iterator>::iterator_category());
		return tmp;
	}
	// 두 vector의 요소를 교환한다.
	// 대입연산 등을 이용할 수 있지만, 해제 하고 다시 할당하기 때문에 효율을 올리기 위해
	// 아래 처럼 주소와 각 인자의 값만 복사할 수 있도록 구현 -> 평가표에 있었음..
	void swap(vector &x)
	{
		allocator_type tmp_allocator = x.allocator_;
		size_type tmp_size = x.size_;
		value_type *tmp_address = x.address_;
		size_type tmp_capacity = x.capacity_;

		x.allocator_ = this->allocator_;
		x.size_ = this->size_;
		x.address_ = this->address_;
		x.capacity_ = this->capacity_;

		this->allocator_ = tmp_allocator;
		this->size_ = tmp_size;
		this->address_ = tmp_address;
		this->capacity_ = tmp_capacity;
	}
	// vector의 요소를 지운다.
	void clear()
	{
		for (size_type i = 0; i < size_; i++)
		{
			allocator_.destroy(address_ + i);
		}
		size_ = 0;
	}
	// vector에서 사용하는 allocator의 클래스 개체를 반환한다.
	allocator_type get_allocator() const { return allocator_; }

	// 멤버 변수
private:
	allocator_type allocator_;
	size_type size_;
	value_type *address_;
	size_type capacity_;
};

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (!(lhs == rhs));
}

// 아래와 같이 하나를 정의하면 나머지는 논리로 가능함
// a < b 는 a < b
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

// a < b 의 반대는 a >= b
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (!(lhs < rhs));
}

// a > b는 b < a
template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (rhs < lhs);
}

// a > b의 반대는 a <= b 는 !(a > b) 는 !(b < a)
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
{
	x.swap(y);
}
} // namespace ft
#endif //FT_CONTAINERS_VECTOR_HPP
