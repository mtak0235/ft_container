#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include "../map.hpp"
#include <ctime>

clock_t start;
clock_t end;

void print_elapsed(clock_t start, clock_t end) {
  clock_t elapsed = end - start;
  double time_in_second = (double) (elapsed / CLOCKS_PER_SEC);
  std::cout << "Elapsed: " << time_in_second << "s(" << elapsed << "ms)" << std::endl;
}

int main() {
  {
    std::cout << "===== std::map<int, int> begin() =====" << std::endl;
    std::map<int, int> m;

    for (int i = 2; i >= 0; i--) // m[2] = 12 부터 생성
      m[i] = i + 10;
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first <<"] = " << iter->second << std::endl;
    std::map<int, int>::iterator iter = m.begin();
    std::cout << "iter->second = 1000" << std::endl;
    iter->second = 1000;
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first <<"] = " << iter->second << std::endl;
  }
  std::cout << "===== ft::map<int, int> begin() =====" << std::endl;
  ft::map<int, int> m;

  for (int i = 2; i >= 0; i--) // m[2] = 12 부터 생성
    m[i] = i + 10;
  for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
    std::cout << "m[" << iter->first <<"] = " << iter->second << std::endl;
  ft::map<int, int>::iterator iter = m.begin();
  std::cout << "iter->second = 1000" << std::endl;
  iter->second = 1000;
  for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
    std::cout << "m[" << iter->first <<"] = " << iter->second << std::endl;
  {
    std::cout << "===== std::map<int, int> rbegin() =====" << std::endl;
    std::map<int, int> m;

    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    for (std::map<int, int>::reverse_iterator riter = m.rbegin(); riter != m.rend(); riter++)
      std::cout << "m[" << riter->first <<"] = " << riter->second << std::endl;
    std::map<int, int>::reverse_iterator riter = m.rbegin();
    std::cout << "riter->second = 1000" << std::endl;
    riter->second = 1000;
    for (std::map<int, int>::reverse_iterator riter = m.rbegin(); riter != m.rend(); riter++)
      std::cout << "m[" << riter->first <<"] = " << riter->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> rbegin() =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    for (ft::map<int, int>::reverse_iterator riter = m.rbegin(); riter != m.rend(); riter++)
      std::cout << "m[" << riter->first <<"] = " << riter->second << std::endl;
    ft::map<int, int>::reverse_iterator riter = m.rbegin();
    std::cout << "riter->second = 1000" << std::endl;
    riter->second = 1000;
    for (ft::map<int, int>::reverse_iterator riter = m.rbegin(); riter != m.rend(); riter++)
      std::cout << "m[" << riter->first <<"] = " << riter->second << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> empty() =====" << std::endl;
    std::map<int, int> m;
    std::cout << m.empty() << std::endl; // true 1
    std::cout << "-- m[0] = 10; --" << std::endl;
    m[0] = 10;
    std::cout << m.empty() << std::endl; // false 0
  }
  {
    std::cout << "===== ft::map<int, int> empty() =====" << std::endl;
    ft::map<int, int> m;
    std::cout << m.empty() << std::endl; // true 1
    std::cout << "-- m[0] = 10; --" << std::endl;
    m[0] = 10;
    std::cout << m.empty() << std::endl; // false 0
  }
  {
    std::cout << "===== std::map<int, int> size() =====" << std::endl;
    std::map<int, int> m;
    std::cout << "size = " << m.size() << std::endl; // size = 0
    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    std::cout << "size = " << m.size() << std::endl; // size =3
  }
  {
    std::cout << "===== ft::map<int, int> size() =====" << std::endl;
    ft::map<int, int> m;
    std::cout << "size = " << m.size() << std::endl; // size = 0
    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    std::cout << "size = " << m.size() << std::endl; // size =3
  }
  {
    std::cout << "===== std::map<int, int> max_size() =====" << std::endl;
    std::map<int, int> m;
    std::cout << "max_size() = " << m.max_size() << std::endl;// max_size: 461168601842738790
  }
  {
    std::cout << "===== ft::map<int, int> max_size() =====" << std::endl;
    ft::map<int, int> m;
    std::cout << "max_size() = " << m.max_size() << std::endl;// max_size: 461168601842738790
  }
  {
    std::cout << "===== std::map<int, int> operator[] =====" << std::endl;
    std::map<int, int> m;

    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 3
    for (int i = 0; i < 5; i++) // map의 값을 출력하려는 의도, 실수로 i를 5까지 증가
      std::cout << "m[" << i <<"] = " << m[i] << std::endl;
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 5
  }
  {
    std::cout << "===== ft::map<int, int> operator[] =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 2; i >= 0; i--)
      m[i] = i + 10;
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 3
    for (int i = 0; i < 5; i++) // map의 값을 출력하려는 의도, 실수로 i를 5까지 증가
      std::cout << "m[" << i <<"] = " << m[i] << std::endl;
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 5
  }
  {
    std::cout << "===== std::map<int, int> insert single element =====" << std::endl;
    std::map<int, int> m;

    m.insert(std::pair<int, int>(5, 10));
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 1
    std::cout << "m[5] = " <<  m[5] << std::endl; // m[5] = 10
  }
  {
    std::cout << "===== ft::map<int, int> insert single element =====" << std::endl;
    ft::map<int, int> m;

    m.insert(ft::pair<int, int>(5, 10));
    std::cout << "m.size = " << m.size() << std::endl; // m.size = 1
    std::cout << "m[5] = " <<  m[5] << std::endl; // m[5] = 10
  }
  {
    std::cout << "===== std::map<int, int> insert with hint =====" << std::endl;
    std::map<int, int> m;
    for (int i = 0; i < 1000000; i++) {
      if (i == 500000)
        continue;
    }
    start = clock();
    m.insert(std::pair<int, int>(500000, 500000));
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(7ms)

    std::map<int, int> m2;
    for (int i = 0; i < 1000000; i++) {
      if (i == 500000)
        continue;
      m2[i] = i;
    }
    std::map<int, int>::iterator iter = m2.begin();
    m2.insert(iter, std::pair<int, int>(500000, 500000));
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(11ms)
  }
  {
    std::cout << "===== ft::map<int, int> insert with hint =====" << std::endl;
    ft::map<int, int> m;
    for (int i = 0; i < 1000000; i++) {
      if (i == 500000)
        continue;
      m[i] = i;
    }

    start = clock();
    m.insert(ft::pair<int, int>(500000, 500000));
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(7ms)

    ft::map<int, int> m2;
    for (int i = 0; i < 1000000; i++) {
      if (i == 500000)
        continue;
      m2[i] = i;
    }
    ft::map<int, int>::iterator iter = m2.begin();
    m2.insert(iter, ft::pair<int, int>(500000, 500000));
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(11ms)
  }
  {
    std::cout << "===== std::map<int, int> insert range =====" << std::endl;
    std::map<int, int> m;
    std::map<int, int> m2;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (int i = 3; i < 5; i++) {
      m[i] = i;
    }
    m.insert(m2.begin(), m2.end());

    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> insert range =====" << std::endl;
    ft::map<int, int> m;
    ft::map<int, int> m2;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (int i = 3; i < 5; i++) {
      m[i] = i;
    }
    m.insert(m2.begin(), m2.end());

    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> erase position =====" << std::endl;
    std::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    std::cout << std::endl;
    m.erase(++(m.begin()));
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> erase position =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    std::cout << std::endl;
    m.erase(++(m.begin()));
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> erase key_type =====" << std::endl;
    std::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    std::map<int, int>::size_type size = m.erase(1);
    std::cout << "size = " << size << std::endl; // size = 1
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [2] = 2
  }
  {
    std::cout << "===== ft::map<int, int> erase key_type =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    ft::map<int, int>::size_type size = m.erase(1);
    std::cout << "size = " << size << std::endl; // size = 1
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [2] = 2
  }
  {
    std::cout << "===== std::map<int, int> erase range =====" << std::endl;
    std::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    std::cout << std::endl;
    m.erase(m.begin(), --(m.end()));
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [2] = 2
  }
  {
    std::cout << "===== ft::map<int, int> erase range =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [0] = 0, [1] = 1, [2] = 2
    std::cout << std::endl;
    m.erase(m.begin(), --(m.end()));
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    // [2] = 2
  }
  {
    std::cout << "===== std::map<int, int> swap =====" << std::endl;
    std::map<int, int> m, m2;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (int i = 10; i < 12; i++) {
      m2[i] = i;
    }
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    for (std::map<int, int>::iterator iter = m2.begin(); iter != m2.end(); iter++)
      std::cout << "m2[" << iter->first << "] = " << iter->second << std::endl;
    m.swap(m2);
    std::cout << std::endl;
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    for (std::map<int, int>::iterator iter = m2.begin(); iter != m2.end(); iter++)
      std::cout << "m2[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> swap =====" << std::endl;
    ft::map<int, int> m, m2;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (int i = 10; i < 12; i++) {
      m2[i] = i;
    }
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    for (ft::map<int, int>::iterator iter = m2.begin(); iter != m2.end(); iter++)
      std::cout << "m2[" << iter->first << "] = " << iter->second << std::endl;
    m.swap(m2);
    std::cout << std::endl;
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    for (ft::map<int, int>::iterator iter = m2.begin(); iter != m2.end(); iter++)
      std::cout << "m2[" << iter->first << "] = " << iter->second << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> clear =====" << std::endl;
    std::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    std::cout << "size = " << m.size() << std::endl;
    m.clear();
    std::cout << std::endl;
    for (std::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    std::cout << "size = " << m.size() << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> clear =====" << std::endl;
    ft::map<int, int> m;

    for (int i = 0; i < 3; i++) {
      m[i] = i;
    }
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    std::cout << "size = " << m.size() << std::endl;
    m.clear();
    std::cout << std::endl;
    for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
      std::cout << "m[" << iter->first << "] = " << iter->second << std::endl;
    std::cout << "size = " << m.size() << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> key_comp =====" << std::endl;
    std::map<int, int> m;

    std::map<int, int>::key_compare key_comp = m.key_comp();
    std::cout << typeid(key_comp).name() << std::endl; // NSt3__14lessIiEE
    std::cout << typeid(std::less<int>).name() << std::endl; //NSt3__14lessIiEE
  }
  {
    std::cout << "===== ft::map<int, int> key_comp =====" << std::endl;
    ft::map<int, int> m;

    ft::map<int, int>::key_compare key_comp = m.key_comp();
    std::cout << typeid(key_comp).name() << std::endl;
    std::cout << typeid(ft::less<int>).name() << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> value_comp =====" << std::endl;
    std::map<int, char> m;

    for(int i = 0; i < 3; i++) {
      m[i] = 'a' + i;
    }
    // iterator로 반복
    for (std::map<int, char>::iterator iter = m.begin(); iter != m.end(); iter++) {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    std::cout << std::endl; // [0] = a [1] = b [2] = c

    // key_comp로 값을 비교 출력
    std::map<int, char>::key_compare key_comp = m.key_comp();
    std::map<int, char>::iterator iter = m.begin();
    std::pair<int, char>highest = *m.rbegin();
    // 각 요소의 key_type을 이용해 비교
    do {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    while (key_comp((iter++)->first, highest.first));
    std::cout << std::endl; // [0] = a [1] = b [2] = c
    // value_comp로 값을 비교 출력
    std::map<int, char>::value_compare val_comp = m.value_comp();
    iter = m.begin();
    // 맵의 value_type(요소)을 이용해 비교
    do {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    while (val_comp(*iter++, highest));
  }
  {
    std::cout << "===== ft::map<int, int> value_comp =====" << std::endl;
    ft::map<int, char> m;

    for(int i = 0; i < 3; i++) {
      m[i] = 'a' + i;
    }
    // iterator로 반복
    for (ft::map<int, char>::iterator iter = m.begin(); iter != m.end(); iter++) {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    std::cout << std::endl; // [0] = a [1] = b [2] = c

    // key_comp로 값을 비교 출력
    ft::map<int, char>::key_compare key_comp = m.key_comp();
    ft::map<int, char>::iterator iter = m.begin();
    ft::pair<int, char>highest = *m.rbegin();
    // 각 요소의 key_type을 이용해 비교
    do {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    while (key_comp((iter++)->first, highest.first));
    std::cout << std::endl; // [0] = a [1] = b [2] = c
    // value_comp로 값을 비교 출력
    ft::map<int, char>::value_compare val_comp = m.value_comp();
    iter = m.begin();
    // 맵의 value_type(요소)을 이용해 비교
    do {
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    }
    while (val_comp(*iter++, highest));
  }
  {
    std::cout << "===== std::map<int, int> find =====" << std::endl;
    std::map<int, int> m;

    for(int i = 0; i < 10000; i++) {
      m[i] = i;
    }
    std::map<int, int>::iterator iter;
    start = clock();
    iter = m.find(999);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [0] = a
    iter = m.find(998);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [1] = b
    iter = m.find(997);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [2] = c
    iter = m.find(996);
    if (iter != m.end()) // iter == m.end()
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(7ms)
  }
  {
    std::cout << "===== ft::map<int, int> find =====" << std::endl;
    ft::map<int, int> m;

    for(int i = 0; i < 10000; i++) {
      m[i] = i;
    }
    ft::map<int, int>::iterator iter;
    start = clock();
    iter = m.find(999);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [0] = a
    iter = m.find(998);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [1] = b
    iter = m.find(997);
    if (iter != m.end())
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl; // [2] = c
    iter = m.find(996);
    if (iter != m.end()) // iter == m.end()
      std::cout << "[" << iter->first << "] = " << iter->second << std::endl;
    end = clock();
    print_elapsed(start, end); // Elapsed: 0s(7ms)
  }
  {
    std::cout << "===== std::map<int, int> count =====" << std::endl;
    std::map<int, char> m;

    for(int i = 0; i < 3; i++) {
      m[i] = 'a' + i;
    }

    for (int i = 0; i < 5; i++) {
      std::cout << " m.count(" << i << ") = " << m.count(i) << std::endl;
    }
  }
  {
    std::cout << "===== ft::map<int, int> count =====" << std::endl;
    ft::map<int, char> m;

    for(int i = 0; i < 3; i++) {
      m[i] = 'a' + i;
    }

    for (int i = 0; i < 5; i++) {
      std::cout << " m.count(" << i << ") = " << m.count(i) << std::endl;
    }
  }
  {
    std::cout << "===== std::map<int, int> lower_bound, upper_bound =====" << std::endl;
    std::map<int, char> m;

    for(int i = 0; i < 5; i++) {
      m[i] = 'a' + i;
    }
    std::map<int, char>::iterator itlow, itup;
    itlow = m.lower_bound(2);
    std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    // itlow : [2] = c
    itup = m.upper_bound(2);
    std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
    // itup : [3] = d

    itlow = m.lower_bound(0);
    if (itlow != m.end())
      std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    //  itlow : [0] = a
    itup = m.upper_bound(0);
    if (itup != m.end())
      std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
    // itup : [1] = b
    itlow = m.lower_bound(4);
    if (itlow != m.end())
      std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    // itlow : [4] = e
    itup = m.upper_bound(4);
    if (itup != m.end()) // itup == m.end()
      std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> lower_bound, upper_bound =====" << std::endl;
    ft::map<int, char> m;

    for(int i = 0; i < 5; i++) {
      m[i] = 'a' + i;
    }
    ft::map<int, char>::iterator itlow, itup;
    itlow = m.lower_bound(2);
    std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    // itlow : [2] = c
    itup = m.upper_bound(2);
    std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
    // itup : [3] = d

    itlow = m.lower_bound(0);
    if (itlow != m.end())
      std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    //  itlow : [0] = a
    itup = m.upper_bound(0);
    if (itup != m.end())
      std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
    // itup : [1] = b
    itlow = m.lower_bound(4);
    if (itlow != m.end())
      std::cout << "itlow : [" << itlow->first << "] = " << itlow->second << std::endl;
    // itlow : [4] = e
    itup = m.upper_bound(4);
    if (itup != m.end()) // itup == m.end()
      std::cout << "itup : [" << itup->first << "] = " << itup->second << std::endl;
  }
  {
    std::cout << "===== std::map<int, int> equal_range =====" << std::endl;
    std::map<int, char> m;

    for(int i = 0; i < 5; i++) {
      m[i] = 'a' + i;
    }

    std::pair<std::map<int, char>::iterator, std::map<int, char>::iterator> range;
    range = m.equal_range(2);

    std::cout << "lower_bound : " << "[" << range.first->first << "] = " << range.first->second << std::endl;
    std::cout << "upper_bound : " << "[" << range.second->first << "] = " << range.second->second << std::endl;
  }
  {
    std::cout << "===== ft::map<int, int> equal_range =====" << std::endl;
    ft::map<int, char> m;

    for(int i = 0; i < 5; i++) {
      m[i] = 'a' + i;
    }

    ft::pair<ft::map<int, char>::iterator, ft::map<int, char>::iterator> range;
    range = m.equal_range(2);

    std::cout << "lower_bound : " << "[" << range.first->first << "] = " << range.first->second << std::endl;
    std::cout << "upper_bound : " << "[" << range.second->first << "] = " << range.second->second << std::endl;
  }
}