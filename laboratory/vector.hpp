#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator/iterator.hpp"
#include "iterator/vector_iterator.hpp"

namespace ft
{
template <typename T, class Allocator = std::allocator<T>>
class vector
{
public:
	//member type
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef ft::Random_access_iterator<value_type> iterator;
	typedef ft::Random_access_iterator<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

	explicit vector(const allocator_type &allocator = allocator_type())
		: _start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(allocator)
	{
	}
	explicit vector(size_type count, const value_type &val = value_type(), const allocator_type &allocator = allocator_type())
		: _start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(allocator)
	{
		if (count > _alloc.max_size())
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &allocator = allocator_type())
	{
	}
	vector(const vector &source)
	{
	}
	~vector()
	{
	}
	vector &operator=(const vector &x)
	{
	}

	iterator begin() { return iterator(_start); }
	const_iterator begin() const { return const_iterator(_start); }
	iterator end() { return iterator(_finish); }
	const_iterator end() const { return const_iterator(_finish); }
	reverse_iterator rbegin() { return reverse_iterator(end();) }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(end()); }
	size_type size() const { return size_type(_finish - _start); }
	size_type max_size() const
	{

		return
	}
	bool empty() const { return begin() == end() }
	void resize(size_type n, value_type val = value_type())
	{
	}
	size_type capacity() const {}
	void reserve(size_type n) {}
	reference front() {}
	const_reference front() const {}
	reference operator[](size_type n) {}
	const_reference operator[](size_type n) const {}
	reference at(size_type n) {}
	const_reference at(size_type n) const {}
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
	}
	void assign(size_type n, const value_type &val) {}
	iterator insert(iterator position, const value_type &val) {}
	void insert(iterator position, size_type n, const value_type &val) {}
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {}
	iterator erase(iterator position) {}
	iterator erase(iterator first, iterator last) {}
	void push_back(const value_type &val) {}
	void pop_back() {}
	void clear() {}
	void swap(vector &x) {}
	allocator_type get_allocator() const {}

private:
	pointer _start;
	pointer _finish;
	pointer _end_of_storage;
	allocator_type _alloc;
};

} // namespace ft
#endif