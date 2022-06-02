
#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "vector_iterator.hpp"

namespace ft {
// 이 부분은 테스트와 함께 다시 확인
template<class Iterator>
class reverse_iterator {
 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  // 기본 생성자
  reverse_iterator() : current_() {};
  explicit reverse_iterator(iterator_type x) : current_(x) {};
  // const_iter로 const_reverse_iterator를 만들기 위함
  template<class const_iter>
  reverse_iterator(reverse_iterator<const_iter> rev_it) : current_(rev_it.base()) {}
  reverse_iterator(const reverse_iterator<Iterator> &copy) : current_(copy.current_) {};
  reverse_iterator &operator=(const reverse_iterator &other) {
    if (this != &other) {
      this->current_ = other.current_;
    }
    return *this;
  };
  ~reverse_iterator() {
  }
  // 가지고 있는 iterator를 반납
  iterator_type base() { return current_; }
  reference operator*() const {
    iterator_type tmp = current_;
    return *(--tmp);
  }
  pointer operator->() const { return &(operator*()); }
  // iterator를 반대로 작동 시킨다.
  reverse_iterator &operator++() {
    current_--;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator tmp(*this);
    current_--;
    return tmp;
  }
  reverse_iterator &operator--() {
    current_++;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp(*this);
    current_++;
    return tmp;
  }
  reverse_iterator operator+(difference_type n) const { return reverse_iterator(current_ - n); }
  reverse_iterator &operator+=(difference_type n) {
    current_ -= n;
    return (*this);
  }
  reverse_iterator operator-(difference_type n) const { return reverse_iterator(current_ + n); }
  difference_type operator-(reverse_iterator const &other) const { return (other.current_ - current_); }
  reverse_iterator &operator-=(difference_type n) {
    current_ += n;
    return (*this);
  }
  reference operator[](difference_type n) const { return *(current_ - n - 1); }
  bool operator==(reverse_iterator const &other) const { return (this->current_ == other.current_); }
  bool operator!=(reverse_iterator const &other) const { return (this->current_ != other.current_); }
  bool operator<(reverse_iterator const &other) const { return (this->current_ > other.current_); }
  bool operator>(reverse_iterator const &other) const { return (this->current_ < other.current_); }
  bool operator<=(reverse_iterator const &other) const { return (this->current_ >= other.current_); }
  bool operator>=(reverse_iterator const &other) const { return (this->current_ <= other.current_); }
  operator reverse_iterator<const Iterator>() const { return (reverse_iterator<const Iterator>(this->current_)); }

  // 기본 iter와 다르게 주소값을 받는게 아니라 iter를 current로 받음
 private:
  iterator_type current_;
};

// 정수 + iterator연산을 위해 전역함수로 오버로딩
// private 부분을 참조하지 않기 때문에 friend 키워드 필요 없음
template<class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &i) {
  reverse_iterator<Iterator> new_iter(i);
  return (new_iter + n);
}

template<class Iterator>
reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &i) {
  reverse_iterator<Iterator> new_iter(i);
  return (new_iter - n);
}

// iter != const_iter, iter >= const_iter 등 처리
template<class Iterator, class Const_iterator>
bool operator!=(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() != rhs.base());
}

template<class Iterator, class Const_iterator>
bool operator==(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() == rhs.base());
}

template<class Iterator, class Const_iterator>
bool operator>(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() < rhs.base());
}

template<class Iterator, class Const_iterator>
bool operator>=(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() <= rhs.base());
}

template<class Iterator, class Const_iterator>
bool operator<(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() > rhs.base());
}

template<class Iterator, class Const_iterator>
bool operator<=(ft::reverse_iterator<Iterator> lhs, ft::reverse_iterator<Const_iterator> rhs) {
  return (lhs.base() >= rhs.base());
}
}
#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
