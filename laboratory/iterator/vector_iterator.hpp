#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"
namespace ft
{
	/**
	 * @brief __wrap_iter 을 이해하기 어려워서 vector_iterator로 만들어 이용
	 *
	 * @tparam Iterator
	 * @version 0.1
	 * @author your name (you@domain.com)
	 * @date 2022-06-15
	 * @copyright Copyright (c) 2022
	 */
	template <class Iterator>
	class vector_iterator : public iterator<ft::random_access_iterator_tag, Iterator>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::iterator_category iterator_category;
		typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::value_type value_type;
		typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::difference_type difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::pointer pointer;
		typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::reference reference;

		//기본 생성자
		vector_iterator() : current_value(0) {};
		//주소값을 받는 생성자
		explicit vector_iterator(iterator_type *x): current_value(x){};
		// explicit vector_iterator(iterator_type x): current_value(x) {};
		//복사 생성자
		vector_iterator(const vector_iterator<Iterator> &copy) {
			this->current_value = copy.current_value;
		}
		//대입 연산자
		vector_iterator& operator=(const vector_iterator &other) {
			if (this != &other) {
				this->current_value = other.current_value;
			}
			return *this;
		}
		//소멸자
		virtual ~vector_iterator(){};
		/**
		 * @brief 현재의 주소값 리턴
		 * 
		 * @return pointer 
		 * @version 0.1
		 * @author your name (you@domain.com)
		 * @date 2022-06-15
		 * @copyright Copyright (c) 2022
		 */
		pointer base() { return current_value;}
		reference operator*() const {return *current_value;};
		pointer operator->() const { return &(operator*())}
		vector_iterator &operator++(){
			++current_value;
			return *this;
		}
		vector_iterator &operator--(){
			--current_value;
			return *this;
		}
		vector_iterator operator++(){
			vector_iterator t(*this);
			this->current_value++;
			return t;
		}
		vector_iterator operator--() {
			vector_iterator t(*this);
			this->current_value--;
			return t;
		}
		vector_iterator operator+(difference_type n) const{
			return vector_iterator(current_value + n);
		}
		vector_iterator operator-(difference_type n) const {
			return vector_iterator(current_value - n);
		}
		//iterator끼리 minus도 지원
		difference_type operator-(vector_iterator const &other) {return this->current_value - other.current_value;}
		vector_iterator& operator+=(difference_type n) {
			this->current_value += n;
			return *this;
		}
		vector_iterator& operator-=(difference_type n) {
			this->current_value -= n;
			return *this;
		}
		reference operator[](difference_type n) const { return *(current_value + n);}
		
		private :
		iterator_type *current_value;
	};

}

#endif