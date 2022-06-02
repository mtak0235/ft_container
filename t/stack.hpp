#ifndef FT_CONTAINERS__STACK_HPP_
#define FT_CONTAINERS__STACK_HPP_

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {
 public:
  typedef T value_type;
  typedef Container container_type;
//  typedef size_t size_type;
  typedef typename container_type::size_type size_type;

  explicit stack(const container_type& ct = container_type()) : c(ct) {}
  stack(const stack& x) : c(x.container_) {}
  stack &operator=(const stack &other) {
    if (*this != other) {
      this->c = other.c;
    }
    return (*this);
  }
  ~stack() {}

  bool empty() const { return (c.empty()); }
  size_type size() const { return (c.size()); }
  value_type& top() { return (c.back()); }
  const value_type& top() const { return (c.back()); }
  void push (const value_type& val) { c.push_back(val); }
  void pop () { c.pop_back(); }

//  friend bool operator==(const stack& lhs, const stack& rhs)  { return lhs.container_ == rhs.container_; }
//  friend bool operator!=(const stack& lhs, const stack& rhs)  { return lhs.container_ != rhs.container_; }
//  friend bool operator<(const stack& lhs, const stack& rhs)   { return lhs.container_ < rhs.container_; }
//  friend bool operator<=(const stack& lhs, const stack& rhs)  { return lhs.container_ <= rhs.container_; }
//  friend bool operator>(const stack& lhs, const stack& rhs)   { return lhs.container_ > rhs.container_; }
//  friend bool operator>=(const stack& lhs, const stack& rhs)  { return lhs.container_ >= rhs.container_; }
  // 탬플릿 매개변수 이름이 같으면 안되기 때문에 임시적으로 T1, C1으로 작성
  // 아래의 두 friend 함수가 있으면 나머지 관계연산자는 friend 키워드 없이 작동 가능
  // 기본적으로 컨테이너가 어떤 컨테이너가 들어올지 모르고, public함수로 비교를 할 수 없기(iterator없음) 때문에
  // (vector, map은 size()나 begin(), end() 와 같이 iterator 함수로 요소 확인가능)
  // protected 변수인 container_를 이용해야 하며, 그로 인해 friend 키워드 사용해야 함
  // 유지 보수를 위해 선언만 진행 후 정의는 아래에서 나머지 연산자와 함께 정의
  template <class T1, class C1>
  friend bool operator==(const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
  template <class T1, class C1>
  friend bool operator<(const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);

 protected:
  container_type c;
};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
  return (lhs.c == rhs.c);
}
template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  return !(lhs == rhs);
}
template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
  return (lhs.c < rhs.c);
}
template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  return !(rhs < lhs);
}
template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  return (rhs < lhs);
}
template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  return !(lhs < rhs);
}
}


#endif //FT_CONTAINERS__STACK_HPP_
