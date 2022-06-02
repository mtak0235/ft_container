#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_

#include <iostream>
#include "../iterator/iterator.hpp"
namespace ft {
// 기본적으로 enable_if는 bool, type이 들어가야 한다.
// type이 없을경우 void로 초기화
// 그리고 구조체는 비어 있다.
template<bool Cond, class T = void>
struct enable_if {};

// 만약 enable_if를 true와 type을 넣어주면 구조체 안에 type이 존재한다.
// 이부분을 이용해 type이 있을 때만 해당 함수로 오버로딩 할 수 있도록 처리
// true부분은 is_integral구조체의 변수 value를 이용해서 처리한다.
// 즉  is_integral의 탬플릿 특수화를 통해 해당 구조체가 상속하고 있는
// 구조체의 value를 확인해서 그  value가 true면 아래와 같이 type이라는 변수가 존재하고
// 그 존재 유무에 따라 탬플릿함수의 오버라이딩을 할지 말지를 결정하는 것
template<class T>
struct enable_if<true, T> {
  typedef T type;
};

// 두 iter의 거리 구하기 (random tag만 가능)
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(InputIterator first,
                                                                  InputIterator last,
                                                                  random_access_iterator_tag) {
  return (last - first);
}

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
  typedef typename iterator_traits<InputIterator>::difference_type difference_type;
  difference_type cnt = 0;
  while (first != last) {
    cnt++;
    first++;
  }
  return (cnt);
}

// 두 iter의 집합이 같은지 확인(vector에서 사용중)
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
  while (first1 != last1) {
    if (!(*first1 == *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

// 특정 조건을 넣어서 같은지 확인(pred)
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
  while (first1 != last1) {
    if (!pred(*first1, *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

// 두 iter의 집합의 크기 비교 | 왼쪽 값이 작으면 true | 왼쪽 데이터 수가 적어도 ture (vector 에서 사용중)
template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1)
      return false;
    else if (*first1 < *first2)
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

// comp라는 비교 조건을 넣어서 함수 실행
template<class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2, Compare comp) {
  while (first1 != last1) {
    if (first2 == last2 || comp(*first2, *first1))
      return false;
    else if (comp(*first1, *first2))
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

// 이항 함수 개체를 제공하느 파생 클래스에 상속 될 수 있는 형식을 정의하는 빈 구조체
template<class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

// 위에 3개의 타입을 받아서 아래와 같이 비교 하는 함수 작성
template<class T>
struct less : ft::binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const {
    return x < y;
  }
};

// pair 기본 구조체
template<class T1, class T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;

  pair() : first(), second() {};

  template<class U, class V>
  pair(const pair<U, V> &copy) : first(copy.first), second(copy.second) {};

  pair(const first_type &a, const second_type &b) : first(a), second(b) {};

  ~pair() {};

  pair &operator=(const pair &other) {
    if (this != &other) {
      first = other.first;
      second = other.second;
    }
    return (*this);
  }
};

//구조체 pair을 만들어주는 함수
template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 x, T2 y) {
  return (ft::pair<T1, T2>(x, y));
}
}
#endif //INCLUDE_UTILS_HPP_
