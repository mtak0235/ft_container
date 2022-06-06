#include <iostream>
#include <iomanip>
#include <type_traits>
 
class A {};
 
enum E : int {};
 
template <class T>
T f(T i)
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    return i;
}
 
#define SHOW(...) std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'
 
int main()
{
    std::cout << std::boolalpha;
 
    SHOW( std::is_integral<A>::value );
    SHOW( std::is_integral_v<E> );
    SHOW( std::is_integral_v<float> );
    SHOW( std::is_integral_v<int> );
    SHOW( std::is_integral_v<const int> );
    SHOW( std::is_integral_v<bool> );
    SHOW( f(123) );
}