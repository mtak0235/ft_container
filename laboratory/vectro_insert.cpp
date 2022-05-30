#include <iostream>
#include <vector>

using namespace std;
int main() { 
	std::cout << "===== std::vector<int> insert() fill =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " "; // 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl; // size : 10 | capacity : 16
    std::cout << "v.insert(v.begin() + 5 , 10, 42); " << std::endl;
    v.insert(v.begin() + 5, 25, 42);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " "; // 0 1 2 3 4 42 42 42 42 42 42 42 42 42 42 5 6 7 8 9
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl; // size : 20 이전 capacity에서 2배 해도 커버 안되면 전략 수정한다. 그냥 풀방으로 간다.

}