#ifndef INCLUDE_ITERATOR_HPP_
#define INCLUDE_ITERATOR_HPP_
#include <cstddef>

namespace ft {
// tag를 상속관계로 설정함으로써(구조체) tag끼리 상관관계를 이해하기 쉽게 구성함
// STL라이브러리 중 iterator를 매개변수로 받을 떄 tag를 확인하는 부분이 있음
// tag따라 iterator의 연산이 달라지기 때문에, 현 구현에서는 random만 사용하고 있음
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// iterator의 특성정보를 저장하는 부분
// 특정 함수를 진행할 때 특성정보를 확인하는 부분에서 아래와 같이 탬플릿 특수화를 시켜놓으면
// 들어온 iterator  혹은 포인터형 변수가 들어왔을 떄 아래와 같이 typedef된 특성정보를 확인할 수 있다.
// 포인터의 경우 random tag의 기능을 모두 사용 가능함으로 카테고리를 random tag로 지정한다.
// 아래의 중첩 의존타입은 typename이 없을 경우 컴파일러가 변수로 착각 하기 때문에
// 변수가 아닌 타입임을 알려준다.
template<class Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef random_access_iterator_tag iterator_category;
};

// const 포인터 대응
template<class T>
struct iterator_traits<const T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef random_access_iterator_tag iterator_category;
};

// 카테고리와 타입을 제외하고는 디폴트 값으로 해당 타입을 설정해놓는다.
// cplusplus.com 참조
template<class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T *, class Reference = T &>
struct iterator {
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};
}
#endif // INCLUDE_ITERATOR_HPP_
