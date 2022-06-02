#ifndef INCLUDE_IS_INTEGRAL_HPP_
#define INCLUDE_IS_INTEGRAL_HPP_
namespace ft {
// 인자로 받는 탬플릿에 대한 정보를 담는 구조체
// T는 bool 타입으로 고정(구현 시점에서는)
//  value에는 bool변수로 true or false로 초기화 되고 값을 리턴할 수 있도록 하지만
// 아래의 주석 부분처럼 c++11버전이상에서 사용되는것으로 판단.
template<class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
//    const operator value_type () { return v; }
};

// 위의 구조체를 이용해서 아래와 같이 2개의 구조체를 typedef
typedef integral_constant<bool, true> true_type;

typedef integral_constant<bool, false> false_type;

// 탬플릿이 특수화에 해당하지 않는경우 false_type 구조체를 상속한다.
// 즉 디폴트로 false_type 구조체를 상속
template<class T>
struct is_integral : public false_type {};

// 탬플릿 특수화를 이용해서 특정 타입이 왔을때 true_type 구조체를 상속한다.
// char16_t, chat32_t는 c++ 11 버전부터 사용 가능(제외)
template<>
struct is_integral<bool> : public true_type {};

template<>
struct is_integral<char> : public true_type {};

template<>
struct is_integral<wchar_t> : public true_type {};

template<>
struct is_integral<signed char> : public true_type {};

template<>
struct is_integral<short int> : public true_type {};

template<>
struct is_integral<int> : public true_type {};

template<>
struct is_integral<long int> : public true_type {};

template<>
struct is_integral<long long int> : public true_type {};

template<>
struct is_integral<unsigned char> : public true_type {};

template<>
struct is_integral<unsigned short int> : public true_type {};

template<>
struct is_integral<unsigned int> : public true_type {};

template<>
struct is_integral<unsigned long int> : public true_type {};

template<>
struct is_integral<unsigned long long int> : public true_type {};

// std::is_integral 확인결과 cosnt도 처리가 되어 있음
template<>
struct is_integral<const bool> : public true_type {};

template<>
struct is_integral<const char> : public true_type {};

template<>
struct is_integral<const wchar_t> : public true_type {};

template<>
struct is_integral<const signed char> : public true_type {};

template<>
struct is_integral<const short int> : public true_type {};

template<>
struct is_integral<const int> : public true_type {};

template<>
struct is_integral<const long int> : public true_type {};

template<>
struct is_integral<const long long int> : public true_type {};

template<>
struct is_integral<const unsigned char> : public true_type {};

template<>
struct is_integral<const unsigned short int> : public true_type {};

template<>
struct is_integral<const unsigned int> : public true_type {};

template<>
struct is_integral<const unsigned long int> : public true_type {};

template<>
struct is_integral<const unsigned long long int> : public true_type {};
}

#endif //INCLUDE_IS_INTEGRAL_HPP_
