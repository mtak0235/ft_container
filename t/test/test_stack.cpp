#include "../iterator/iterator.hpp"
#include "../iterator/vector_iterator.hpp"
#include "../vector.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/utils.hpp"
#include "../stack.hpp"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <stack>

clock_t start;
clock_t end;
class Tmp {
 public:
  Tmp() : i(0) {}
  Tmp(int num) : i(num) {}
  int to_int() const { return i; }
  void set_int(int num) { i = num; }
 private:
  int i;
};

std::ostream &operator<<(std::ostream &out, Tmp const &tmp) {
  out << tmp.to_int();
  return out;
}

void print_elapsed(clock_t start, clock_t end) {
  clock_t elapsed = end - start;
  double time_in_second = (double) (elapsed / CLOCKS_PER_SEC);
  std::cout << "Elapsed: " << time_in_second << "s(" << elapsed << "ms)" << std::endl;
}
int main(void) {
  {
    std::cout << "===== std::stack<int, std::vector<int> > default constructor =====" << std::endl;
    start = clock();
    std::stack<int, std::vector<int> > s;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    start = clock();
    std::stack<int, std::vector<int> > s2(v);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s2.size() << std::endl;
    std::cout << "empty : " << s2.empty() << std::endl;
  }
  {
    std::cout << "===== ft::stack<int, std::vector<int> > default constructor =====" << std::endl;
    start = clock();
    ft::stack<int, std::vector<int> > s;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    start = clock();
    ft::stack<int, std::vector<int> > s2(v);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s2.size() << std::endl;
    std::cout << "empty : " << s2.empty() << std::endl;
  }
  {
    std::cout << "===== std::stack<int, std::vector<int> > push, top, pop =====" << std::endl;
    std::stack<int, std::vector<int> > s;
    std::cout << "-- push 0 ~ 999 --" << std::endl;
    start = clock();
    for (int i = 0; i < 1000; i++)
      s.push(i);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    std::cout << "top : " << s.top() << std::endl;
    std::cout << "-- pop --" << std::endl;
    s.pop();
    std::cout << "top : " << s.top() << std::endl;
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  {
    std::cout << "===== ft::stack<int, std::vector<int> > push, top, pop =====" << std::endl;
    ft::stack<int, std::vector<int> > s;
    std::cout << "-- push 0 ~ 999 --" << std::endl;
    start = clock();
    for (int i = 0; i < 1000; i++)
      s.push(i);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    std::cout << "top : " << s.top() << std::endl;
    std::cout << "-- pop --" << std::endl;
    s.pop();
    std::cout << "top : " << s.top() << std::endl;
    std::cout << "size : " << s.size() << std::endl;
    std::cout << "empty : " << s.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  {
    std::cout << "===== std::stack<int, std::vector<int> > relational operator =====" << std::endl;
    std::stack<int, std::vector<int> > s1;
    std::cout << "-- s1 : push 0 ~ 999 --" << std::endl;
    for (int i = 0; i < 1000; i++)
      s1.push(i);
    std::stack<int, std::vector<int> > s2;
    std::cout << "-- s2 : push 0 ~ 500 --" << std::endl;
    for (int i = 0; i < 500; i++)
      s2.push(i);
    std::stack<int, std::vector<int> > s3;
    std::cout << "-- s3 : push 0 ~ 500 --" << std::endl;
    for (int i = 0; i < 500; i++)
      s3.push(i);
    std::cout << "s1 == s2 : " << (s1 == s2) << std::endl;
    std::cout << "s2 == s3 : " << (s2 == s3) << std::endl;
    std::cout << "s1 > s2 : " << (s1 > s2) << std::endl;
    std::cout << "s1 >= s2 : " << (s1 >= s2) << std::endl;
    std::cout << "s2 > s3 : " << (s2 > s3) << std::endl;
    std::cout << "s2 >= s3 : " << (s2 >= s3) << std::endl;
    std::cout << "s1 < s2 : " << (s1 < s2) << std::endl;
    std::cout << "s1 <= s2 : " << (s1 <= s2) << std::endl;
    std::cout << "s2 < s3 : " << (s2 < s3) << std::endl;
    std::cout << "s2 <= s3 : " << (s2 <= s3) << std::endl;
  }
  {
    std::cout << "===== ft::stack<int, std::vector<int> > relational operator =====" << std::endl;
    ft::stack<int, std::vector<int> > s1;
    std::cout << "-- s1 : push 0 ~ 999 --" << std::endl;
    for (int i = 0; i < 1000; i++)
      s1.push(i);
    ft::stack<int, std::vector<int> > s2;
    std::cout << "-- s2 : push 0 ~ 500 --" << std::endl;
    for (int i = 0; i < 500; i++)
      s2.push(i);
    ft::stack<int, std::vector<int> > s3;
    std::cout << "-- s3 : push 0 ~ 500 --" << std::endl;
    for (int i = 0; i < 500; i++)
      s3.push(i);
    std::cout << "s1 == s2 : " << (s1 == s2) << std::endl;
    std::cout << "s2 == s3 : " << (s2 == s3) << std::endl;
    std::cout << "s1 > s2 : " << (s1 > s2) << std::endl;
    std::cout << "s1 >= s2 : " << (s1 >= s2) << std::endl;
    std::cout << "s2 > s3 : " << (s2 > s3) << std::endl;
    std::cout << "s2 >= s3 : " << (s2 >= s3) << std::endl;
    std::cout << "s1 < s2 : " << (s1 < s2) << std::endl;
    std::cout << "s1 <= s2 : " << (s1 <= s2) << std::endl;
    std::cout << "s2 < s3 : " << (s2 < s3) << std::endl;
    std::cout << "s2 <= s3 : " << (s2 <= s3) << std::endl;
  }
}