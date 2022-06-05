#ifndef FT_CONTAINERS_VECTOR_ITERATOR_HPP
#define FT_CONTAINERS_VECTOR_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
  // 실제 std::vector의 iterator를 typeid로 찍어 보면 NSt3__111__wrap_iterIPiEE와 같이 나온다.
  // 현재 wrap_iter를 이해하거나 구현하기에는 어렵기 때문에 아래와 같이
  // Vector_iterator로 만들어서 사용할 계획 (단 tag는 random을 넣어준다.)
  // 아래의 탬플릿의 type은 vector를 만들떄 넣는 변수 형으로 생각하면 된다.
  // vector<int>라면 iterator == int
  template <class Iterator>
  class vector_iterator
      : public iterator<ft::random_access_iterator_tag, Iterator>
  {
  public:
    typedef Iterator iterator_type;
    typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::iterator_category iterator_category;
    typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::value_type value_type;
    typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::difference_type difference_type;
    typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::pointer pointer;
    typedef typename ft::iterator<random_access_iterator_tag, iterator_type>::reference reference;

    // 기본 생성자
    vector_iterator() : current_value(0){};
    // type의 주소값을 받는 경우의 생성자
    explicit vector_iterator(iterator_type *x) : current_value(x){};
    // 복사 생성자
    vector_iterator(const vector_iterator<Iterator> &copy)
    {
      this->current_value = copy.current_value;
    };
    // 대입연산자
    vector_iterator &operator=(const vector_iterator &other)
    {
      if (this != &other)
      {
        this->current_value = other.current_value;
      }
      return *this;
    };
    // 소멸자
    virtual ~vector_iterator()
    {
    }
    //  현재의 주소값 리턴
    pointer base() { return current_value; }
    // *연산을 할경우 주소가 가리키는 값 리턴
    reference operator*() const { return *current_value; }
    // 아래는 아직 이해 못하겠음, cplusplus.com참고, 포인터 연산
    pointer operator->() const { return &(operator*()); }
    // 전위 증감
    vector_iterator &operator++()
    {
      current_value++;
      return *this;
    }
    // 후위 증감
    vector_iterator operator++(int)
    {
      vector_iterator tmp(*this);
      current_value++;
      return tmp;
    }
    // 전위 감소
    vector_iterator &operator--()
    {
      current_value--;
      return *this;
    }
    // 후위 감소
    vector_iterator operator--(int)
    {
      vector_iterator tmp(*this);
      current_value--;
      return tmp;
    }
    // 산술 및 축약형 연산자
    vector_iterator operator+(difference_type n) const { return vector_iterator(current_value + n); }
    vector_iterator &operator+=(difference_type n)
    {
      current_value += n;
      return (*this);
    }
    vector_iterator operator-(difference_type n) const { return vector_iterator(current_value - n); }
    // 빼기의 경우 iterator끼리 연산도 지원
    difference_type operator-(vector_iterator const &other) const { return (current_value - other.current_value); }
    vector_iterator &operator-=(difference_type n)
    {
      current_value -= n;
      return (*this);
    }
    // 배열연산자
    reference operator[](difference_type n) const { return *(current_value + n); }
    // 비교 연산자
    //  bool operator==(vector_iterator const &other) const { return (this->current_value == other.current_value); }
    //  bool operator!=(vector_iterator const &other) const { return (this->current_value != other.current_value); }
    //  bool operator<(vector_iterator const &other) const { return (this->current_value < other.current_value); }
    //  bool operator>(vector_iterator const &other) const { return (this->current_value > other.current_value); }
    //  bool operator<=(vector_iterator const &other) const { return (this->current_value <= other.current_value); }
    //  bool operator>=(vector_iterator const &other) const { return (this->current_value >= other.current_value); }
    // 아래의 형변환 operator 추가 이유 (변환 연산자) -> 일반 Vector_iterator의 값을 const Vector_iterator로 대입하는 경우 형변환 후 연산
    // vector의 begin함수의 경우 리턴값은 무조건 const가 아닌 일반 함수로 리턴 (오버로드 안됨, 컴파일에러)
    // const유무에 따른 오버로딩은 지원이 안되는것으로 판단 -> 기존 값을 const로 변환하여 대입할 수 있도록 처리
    operator vector_iterator<const Iterator>() const
    {
      return (vector_iterator<const Iterator>(this->current_value));
    }
    // 변수형의 포인터 변수, int면 int*
  private:
    iterator_type *current_value;
  };

  // 정수 + iterator연산을 위해 전역함수로 오버로딩
  // private 부분을 참조하지 않기 때문에 friend 키워드 필요 없음
  template <class Iterator>
  vector_iterator<Iterator>
  operator+(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &i)
  {
    vector_iterator<Iterator> new_iter(i);
    return (new_iter + n);
  }

  template <class Iterator>
  vector_iterator<Iterator>
  operator-(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &i)
  {
    vector_iterator<Iterator> new_iter(i);
    return (new_iter - n);
  }

  // iter != const_iter, iter >= const_iter 등 처리
  template <class Iterator, class Const_iterator>
  bool operator!=(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() != rhs.base());
  }

  template <class Iterator, class Const_iterator>
  bool operator==(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() == rhs.base());
  }

  template <class Iterator, class Const_iterator>
  bool operator>(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() > rhs.base());
  }

  template <class Iterator, class Const_iterator>
  bool operator>=(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() >= rhs.base());
  }

  template <class Iterator, class Const_iterator>
  bool operator<(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() < rhs.base());
  }

  template <class Iterator, class Const_iterator>
  bool operator<=(ft::vector_iterator<Iterator> lhs, ft::vector_iterator<Const_iterator> rhs)
  {
    return (lhs.base() <= rhs.base());
  }
}
#endif // FT_CONTAINERS_VECTOR_ITERATOR_HPP