#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
/**
	 * @brief 특정한 타입들에게만 작동하는 템플릿을 작성하고 싶으면 함수의 선언부에 올바르지 않은 타입을 넣어서 타입 치환 오류가 나게 한다. 
	 * 그래야 컴파일러는 해당 함수를 오버로딩 후보군에서 제외한다. 그렇지 않으면 치환 실패는 오류가 아니라는 컴파일러의 신념에 따라 해당 오류는 무시된다.
	 * 즉 enable_if는 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺄 수 있게 도와주는 간단한 템플릿 메타 함수이다.
	 * @tparam B 
	 * @tparam T 
	 */
template <bool B, typename T = void>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T>
{
	typedef T type;
};

/**
 * @brief 두 iterator의 거리 구하기
 * 
 * @tparam InputIterator 
 * @param first 
 * @param last 
 * @return iterator_traits<InputIterator>::difference_type 
 * @version 0.1
 * @author your name (you@domain.com)
 * @date 2022-06-16
 * @copyright Copyright (c) 2022
 */
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
	typename iterator_traits<InputIterator>::difference_type cnt = 0;
	while (first != last) {
		cnt++;
		first++;
	}
	return cnt;
}

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last, random_access_iterator_tag) {
	return last - first;
}

} // namespace ft

#endif