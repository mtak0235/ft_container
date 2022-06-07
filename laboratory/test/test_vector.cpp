#include "../ft_vector.hpp"
#include <iostream>
int main() {
	ft::vector<int> v;
    for (int i = 0; i < 100; i++)
      v.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.clear(); " << std::endl;
    v.clear();
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  
}