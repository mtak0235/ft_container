#include "../iterator/iterator.hpp"
#include "../iterator/vector_iterator.hpp"
#include "../vector.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <ctime>

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
  //test int
  {
    std::cout << "===== std::vector<int> default constructor =====" << std::endl;
    start = clock();
    std::vector<int> v;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> default constructor =====" << std::endl;
    start = clock();
    std::vector<int> v;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> fill constructor =====" << std::endl;
    start = clock();
    std::vector<int> v(100, 10000);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> fill constructor =====" << std::endl;
    start = clock();
    ft::vector<int> v(100, 10000);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> range constructor =====" << std::endl;
    int ints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    start = clock();
    std::vector<int> v(ints, ints + 10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> range constructor =====" << std::endl;
    int ints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    start = clock();
    ft::vector<int> v(ints, ints + 10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> copy constructor =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<int> v2(v);
    end = clock();
    print_elapsed(start, end);
    v[0] = 300;
    std::cout << "-- copy --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << std::endl;
    std::cout << "capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> copy constructor =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<int> v2(v);
    end = clock();
    print_elapsed(start, end);
    v[0] = 300;
    std::cout << "-- copy --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << std::endl;
    std::cout << "capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> operator= =====" << std::endl;
    std::vector<int> v(10, 10);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::vector<int> v2(15, 42);
    start = clock();
    v = v2;
    end = clock();
    print_elapsed(start, end);
    v2[0] = 300;
    std::cout << "-- operator= --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> operator= =====" << std::endl;
    ft::vector<int> v(10, 10);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    ft::vector<int> v2(15, 42);
    start = clock();
    v = v2;
    end = clock();
    print_elapsed(start, end);
    v2[0] = 300;
    std::cout << "-- operator= --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  //test class
  {
    std::cout << "===== std::vector<class> default constructor =====" << std::endl;
    start = clock();
    std::vector<Tmp> v;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::vector<class> default constructor =====" << std::endl;
    start = clock();
    std::vector<Tmp> v;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<class> fill constructor =====" << std::endl;
    start = clock();
    std::vector<Tmp> v(100, 10000);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<class> fill constructor =====" << std::endl;
    start = clock();
    ft::vector<Tmp> v(100, 10000);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<class> range constructor =====" << std::endl;
    Tmp tmps[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    start = clock();
    std::vector<Tmp> v(tmps, tmps + 10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<class> range constructor =====" << std::endl;
    Tmp tmps[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    start = clock();
    ft::vector<Tmp> v(tmps, tmps + 10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<class> copy constructor =====" << std::endl;
    std::vector<Tmp> v(100, 10000);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<Tmp> v2(v);
    end = clock();
    print_elapsed(start, end);
    v[0].set_int(300);
    std::cout << "-- copy --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << std::endl;
    std::cout << "capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<class> copy constructor =====" << std::endl;
    ft::vector<Tmp> v(100, 10000);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<Tmp> v2(v);
    end = clock();
    print_elapsed(start, end);
    v[0].set_int(300);
    std::cout << "-- copy --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << std::endl;
    std::cout << "capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<class> operator= =====" << std::endl;
    std::vector<Tmp> v(10, 10);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::vector<Tmp> v2(15, 42);
    start = clock();
    v = v2;
    end = clock();
    print_elapsed(start, end);
    v2[0].set_int(300);
    std::cout << "-- operator= --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<class> operator= =====" << std::endl;
    ft::vector<Tmp> v(10, 10);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    ft::vector<Tmp> v2(15, 42);
    start = clock();
    v = v2;
    end = clock();
    print_elapsed(start, end);
    v2[0].set_int(300);
    std::cout << "-- operator= --" << std::endl;
    for (int i = 0; i < v2.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> begin() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<int>::iterator iter = v.begin();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*iter : " << *iter << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> begin() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<int>::iterator iter = v.begin();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*iter : " << *iter << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> end() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<int>::iterator iter = v.end();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*(--iter) : " << *(--iter) << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> end() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<int>::iterator iter = v.end();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*(--iter) : " << *(--iter) << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> rbegin() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<int>::reverse_iterator iter = v.rbegin();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*iter : " << *iter << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> rbegin() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<int>::reverse_iterator iter = v.rbegin();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*iter : " << *iter << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> rend() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    std::vector<int>::reverse_iterator iter = v.rend();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*(--iter) : " << *(--iter) << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> rend() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    start = clock();
    ft::vector<int>::reverse_iterator iter = v.rend();
    end = clock();
    print_elapsed(start, end);
    std::cout << "*(--iter) : " << *(--iter) << std::endl;
    std::cout << "*iter = 300" << std::endl;
    *iter = 300;
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  // size는 생략
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> max_size() =====" << std::endl;
    std::vector<int> v;
    start = clock();
    std::cout << "max_size: " << v.max_size() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> max_size() =====" << std::endl;
    ft::vector<int> v;
    start = clock();
    std::cout << "max_size: " << v.max_size() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> resize() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(5) --" << std::endl;
    start = clock();
    v.resize(5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(10) --" << std::endl;
    start = clock();
    v.resize(10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(20, 42) --" << std::endl;
    start = clock();
    v.resize(20, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> resize() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(5) --" << std::endl;
    start = clock();
    v.resize(5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(10) --" << std::endl;
    start = clock();
    v.resize(10);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- resize(20, 42) --" << std::endl;
    start = clock();
    v.resize(20, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  // capacity 생략
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> empty() =====" << std::endl;
    std::vector<int> v;
    start = clock();
    std::cout << v.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
    std::cout << "-- push_back(42); --" << std::endl;
    v.push_back(42);
    start = clock();
    std::cout << v.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> empty() =====" << std::endl;
    ft::vector<int> v;
    start = clock();
    std::cout << v.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
    std::cout << "-- push_back(42); --" << std::endl;
    v.push_back(42);
    start = clock();
    std::cout << v.empty() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> reserve() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- reserve(5); --" << std::endl;
    start = clock();
    v.reserve(5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- reserve(42); --" << std::endl;
    start = clock();
    v.reserve(42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> reserve() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- reserve(5); --" << std::endl;
    start = clock();
    v.reserve(5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- reserve(42); --" << std::endl;
    start = clock();
    v.reserve(42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
  }
  // operator[] 생략
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> at() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    std::cout << "-- v.at(i) --" << std::endl;
    start = clock();
    for (int i = 0; i < v.size(); i++)
      std::cout << v.at(i) << " ";
    std::cout << std::endl;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- v.at(100) --" << std::endl;
    try {
      v.at(100);
    }
    catch (std::exception &e) {
      std::cout << "typeid(e).name() : " << typeid(e).name() << std::endl;
      std::cout << "e.what() : " << e.what() << std::endl;
    }
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> at() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    std::cout << "-- v.at(i) --" << std::endl;
    start = clock();
    for (int i = 0; i < v.size(); i++)
      std::cout << v.at(i) << " ";
    std::cout << std::endl;
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "-- v.at(100) --" << std::endl;
    try {
      v.at(100);
    }
    catch (std::exception &e) {
      std::cout << "typeid(e).name() : " << typeid(e).name() << std::endl;
      std::cout << "e.what() : " << e.what() << std::endl;
    }
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> front(), back() =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    start = clock();
    std::cout << "v.front(): " << v.front() << std::endl;
    end = clock();
    print_elapsed(start, end);
    start = clock();
    std::cout << "v.back(): " << v.back() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> front(), back() =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    start = clock();
    std::cout << "v.front(): " << v.front() << std::endl;
    end = clock();
    print_elapsed(start, end);
    start = clock();
    std::cout << "v.back(): " << v.back() << std::endl;
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> assign() fill =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "v.assign(10, 42) " << std::endl;
    start = clock();
    v.assign(10, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> assign() fill =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "v.assign(10, 42) " << std::endl;
    start = clock();
    v.assign(10, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> assign() range =====" << std::endl;
    std::vector<int> v(10, 42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::vector<int> v2;
    for (int i = 0; i < 10; i++)
      v2.push_back(i);
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "v.assign(v2.,begin(), v2.end()) " << std::endl;
    start = clock();
    v.assign(v2.begin(), v2.end());
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> assign() range =====" << std::endl;
    ft::vector<int> v(10, 42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    ft::vector<int> v2;
    for (int i = 0; i < 10; i++)
      v2.push_back(i);
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "v.assign(v2.,begin(), v2.end()) " << std::endl;
    start = clock();
    v.assign(v2.begin(), v2.end());
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> push_back =====" << std::endl;
    std::vector<int> v;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    start = clock();
    for (int i = 0; i < 9; i++) {
      v.push_back(i);
      std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    }
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "===== std::vector<int> pop_back =====" << std::endl;
    start = clock();
    for (int i = 0; i < 9; i++) {
      v.pop_back();
      std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    }
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> push_back =====" << std::endl;
    ft::vector<int> v;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    start = clock();
    for (int i = 0; i < 9; i++) {
      v.push_back(i);
      std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    }
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "===== ft::Vector<int> pop_back =====" << std::endl;
    start = clock();
    for (int i = 0; i < 9; i++) {
      v.pop_back();
      std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    }
    end = clock();
    print_elapsed(start, end);
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> insert() fill =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.insert(v.bigin() + 5 , 10, 42); " << std::endl;
    start = clock();
    v.insert(v.begin() + 5, 10, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> insert() fill =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.insert(v.bigin() + 5 , 10, 42); " << std::endl;
    start = clock();
    v.insert(v.begin() + 5, 10, 42);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> insert() range =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    int ints[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
    std::cout << "int ints[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};" << std::endl;
    std::cout << "v.insert(v.begin() + 1 , ints, ints + 9); " << std::endl;
    start = clock();
    v.insert(v.begin() + 1, ints, ints + 9);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> insert() range =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    int ints[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
    std::cout << "int ints[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};" << std::endl;
    std::cout << "v.insert(v.begin() + 1 , ints, ints + 9); " << std::endl;
    start = clock();
    v.insert(v.begin() + 1, ints, ints + 9);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> erase =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.erase(v.begin() + 5); " << std::endl;
    start = clock();
    v.erase(v.begin() + 5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.erase(v.begin(), v.begin() + 5); " << std::endl;
    start = clock();
    v.erase(v.begin(), v.begin() + 5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> erase =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.erase(v.begin() + 5); " << std::endl;
    start = clock();
    v.erase(v.begin() + 5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.erase(v.begin(), v.begin() + 5); " << std::endl;
    start = clock();
    v.erase(v.begin(), v.begin() + 5);
    end = clock();
    print_elapsed(start, end);
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> swap =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::vector<int> v2(5, 42);
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    std::cout << "v.swap(v2); " << std::endl;
    start = clock();
    v.swap(v2);
    end = clock();
    print_elapsed(start, end);
    std::cout << "v2.push_back(100);" << std::endl;
    v2.push_back(100);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> swap =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 10; i++)
      v.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    ft::vector<int> v2(5, 42);
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    std::cout << "v.swap(v2); " << std::endl;
    start = clock();
    v.swap(v2);
    end = clock();
    print_elapsed(start, end);
    std::cout << "v2.push_back(100);" << std::endl;
    v2.push_back(100);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> clear =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 100; i++)
      v.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.clear(); " << std::endl;
    start = clock();
    v.clear();
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> clear =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 100; i++)
      v.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v.clear(); " << std::endl;
    start = clock();
    v.clear();
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> get_allocator =====" << std::endl;
    std::vector<int> v;
    std::vector<int>::allocator_type alloc = v.get_allocator();
    std::cout << typeid(alloc).name() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> get_allocator =====" << std::endl;
    ft::vector<int> v;
    ft::vector<int>::allocator_type alloc = v.get_allocator();
    std::cout << typeid(alloc).name() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> operator==, operator!= =====" << std::endl;
    std::vector<int> v(10, 42);
    std::vector<int> v2;
    for (int i = 0; i < 10; i++)
      v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v == v2)
      std::cout << "result : v == v2" << std::endl;
    else
      std::cout << "result : v != v2" << std::endl;
    std::cout << std::endl;
    v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v == v2)
      std::cout << "result : v == v2" << std::endl;
    if (v != v2)
      std::cout << "result : v != v2" << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> operator==, operator!= =====" << std::endl;
    ft::vector<int> v(10, 42);
    ft::vector<int> v2;
    for (int i = 0; i < 10; i++)
      v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v == v2)
      std::cout << "result : v == v2" << std::endl;
    else
      std::cout << "result : v != v2" << std::endl;
    std::cout << std::endl;
    v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v == v2)
      std::cout << "result : v == v2" << std::endl;
    if (v != v2)
      std::cout << "result : v != v2" << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> operator<, operator<=, operator>, operator>= =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 5; i++)
      v.push_back(i);
    std::vector<int> v2;
    for (int i = 0; i < 6; i++)
      v2.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v > v2)
      std::cout << "result : v > v2" << std::endl;
    if (v >= v2)
      std::cout << "result : v >= v2" << std::endl;
    if (v < v2)
      std::cout << "result : v < v2" << std::endl;
    if (v <= v2)
      std::cout << "result : v <= v2" << std::endl;
    std::cout << std::endl;
    v.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v > v2)
      std::cout << "result : v > v2" << std::endl;
    if (v >= v2)
      std::cout << "result : v >= v2" << std::endl;
    if (v < v2)
      std::cout << "result : v < v2" << std::endl;
    if (v <= v2)
      std::cout << "result : v <= v2" << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> operator<, operator<=, operator>, operator>= =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 5; i++)
      v.push_back(i);
    ft::vector<int> v2;
    for (int i = 0; i < 6; i++)
      v2.push_back(i);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v > v2)
      std::cout << "result : v > v2" << std::endl;
    if (v >= v2)
      std::cout << "result : v >= v2" << std::endl;
    if (v < v2)
      std::cout << "result : v < v2" << std::endl;
    if (v <= v2)
      std::cout << "result : v <= v2" << std::endl;
    std::cout << std::endl;
    v.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    if (v > v2)
      std::cout << "result : v > v2" << std::endl;
    if (v >= v2)
      std::cout << "result : v >= v2" << std::endl;
    if (v < v2)
      std::cout << "result : v < v2" << std::endl;
    if (v <= v2)
      std::cout << "result : v <= v2" << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> ft::swap =====" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 5; i++)
      v.push_back(i);
    std::vector<int> v2;
    for (int i = 0; i < 6; i++)
      v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    std::cout << "std::swap(v, v2)" << std::endl;
    std::swap(v, v2);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> ft::swap =====" << std::endl;
    ft::vector<int> v;
    for (int i = 0; i < 5; i++)
      v.push_back(i);
    ft::vector<int> v2;
    for (int i = 0; i < 6; i++)
      v2.push_back(42);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
    std::cout << "ft::swap(v, v2)" << std::endl;
    ft::swap(v, v2);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    std::cout << "v2 : ";
    for (int i = 0; i < v2.size(); i++)
      std::cout << v2[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v2.size() << " | capacity : " << v2.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<int> elapsed =====" << std::endl;
    std::vector<int> v;
    std::cout << "v2.push_back(i); X 1,000,000" << std::endl;
    start = clock();
    for (int i = 0; i < 1000000; i++)
      v.push_back(i);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<int> elapsed =====" << std::endl;
    ft::vector<int> v;
    std::cout << "v2.push_back(i); X 1,000,000" << std::endl;
    start = clock();
    for (int i = 0; i < 1000000; i++)
      v.push_back(i);
    end = clock();
    print_elapsed(start, end);
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
  }
  std::cout << std::endl;
  {
    std::cout << "===== std::vector<std::string> test =====" << std::endl;
    std::vector<std::string> v;
    start = clock();
    for (int i = 0; i < 10; i++)
      v.push_back("hello");
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    v.pop_back();
    v.clear();
  }
  std::cout << std::endl;
  {
    std::cout << "===== ft::Vector<std::string> test =====" << std::endl;
    ft::vector<std::string> v;
    start = clock();
    for (int i = 0; i < 10; i++)
      v.push_back("hello");
    end = clock();
    print_elapsed(start, end);
    std::cout << "v : ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
    v.pop_back();
    v.clear();
  }
}