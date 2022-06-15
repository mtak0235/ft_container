#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
namespace ft
{
	/**
	 * @brief iterator의 properties를 정의하는 클래스
	 * 중첨 의존 타입은 typename이 없으면 컴파일러가 변수로 착각하기 때문에 붙여줘야 한다.
	 * @tparam Iterator
	 */
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	/**
	 * @brief 포인터형 변수는 random tag의 기능을 모두 사용할 수 있어서 템플릿 특수화를 시켰다.
	 *  
	 * @tparam T 
	 * @version 0.1
	 * @author your name (you@domain.com)
	 * @date 2022-06-15
	 * @copyright Copyright (c) 2022
	 */
	template <class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};
	/**
	 * @brief const 포인터를 위한 템플릿 특수화
	 * 
	 * @tparam T 
	 * @version 0.1
	 * @author your name (you@domain.com)
	 * @date 2022-06-15
	 * @copyright Copyright (c) 2022
	 */
	template <class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/**
	 * @brief iterator_traits class 에 필요한 멤버
	 */
	struct input_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};

	/**
	 * @brief 이 struct는 iterator_traits class 에 필요한 멤버를 정의해 의도한 인스턴스를 자동으로 생성되게 한다.

	 * @tparam Category
	 * @tparam T 반복자가 가리키는 요소의 타입
	 * @tparam Distance 두 iterator의 차이를 나타내는 타입
	 * @tparam Pointer iterator에게 pointed된 요소의 pointer 타입
	 * @tparam Reference iterator에게 pointed된 요소의 레퍼런스 타입
	 */
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

} // namespace ft
#endif