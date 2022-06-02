#ifndef FT_CONTAINERS_MAP_NODE_HPP
#define FT_CONTAINERS_MAP_NODE_HPP

#include "utils/utils.hpp"
#include "utils/is_integral.hpp"
#include "iterator/map_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include <iostream>
#include <memory>

// 기본 생성 시 last노드를 생성한다.
// 노드가 추가될 때마다 균형 이진탐색 트리에 맞도록 연결 해주고, 상황에 따라 root를 변경한다.
// 모든 노드의 끝은 last로 셋팅한다.
// 제일 작은 값(compare에 따라 다름)은 last->left에 연결 후 begin등 에서 사용한다.
// -> 이 부분으로 인해 효율이 떨어져, begin을 호출할 시작 값(노드의 가장 왼쪽 아래)을 수 있도록 변경함
// 제일 큰 값은 last->right에 연결 후 --연산에 사용한다.(last에서 --연산을 하면 제일 큰 값으로 이동해야 함)
// -> 이 부분도 효율이 떨어져 해당 노드의 root만 연결해주는 것으로 변경 / iterator --연산 시 상황에 따라 root로 연산
// allocator_type으로 노드의 content에 value_type값을 넣어준다.
// 할당은 노드 기준으로 할당하기 때문에 std::allocator<Node>로 변수를 만들어 사용한다.
// size_type size_를 만들어 map에 있는 요소 수를 기록한다.
// 추가된 부분
// 복사 및 대입 연산 시 깊은 복사를 위해 insert로 진행하면 효율이 최악이 되기 때문에
// iterator가 노드를 옮겨다니며 값을 빼주고, 새로운 map은 값을 추가 하기 위해 하나의 value당 서치를 계속 해야함..
// 그렇기 때문에 노드를 재귀로 돌아다니며, 해당 노드의 값을 그대로 복사를 하는 것으로 변경
// 그러면 노드 수 만큼만 복사를 진행하기 때문에 효율이 엄청나게 좋아짐.

namespace ft {
template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<Key, T> > >
class map {
  // 사용할 노드를 map클래스 안에서 정의
 private:
  struct Node {
    ft::pair<Key, T> content;
    int height;
    Node *parent;
    Node *left;
    Node *right;
  };

 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<Key, T> value_type;
  typedef Compare key_compare;
  // value_compare은 중첩클래스로(std::map에서도 중첩클래스로 되어 있음), map에서만 사용하는 클래스
  // value_type으로도 Compare을 사용하기 위함(단, first(key_type)만 비교
  class value_compare : public ft::binary_function<value_type, value_type, bool> {
  friend class map;
   public:
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}
  };
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef map_iterator<Node, Compare, ft::pair<Key, T> > iterator;
  typedef map_iterator<Node, Compare, const ft::pair<Key, T> > const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

  //default last 노드를 만들어 값을 추가 할 수 있도록 준비한다.
  map(const key_compare &comp = key_compare (), const allocator_type &alloc = allocator_type())
  : value_type_alloc_(alloc), key_compare_(comp), size_(0) {
    node_alloc_ = std::allocator<Node>();
    last_ = node_alloc_.allocate(1);
    set_node_default();
  }

  // last노드를 생성 후 InputIterator에 값들을 추가 한다.
  template<class InputIterator>
  map(InputIterator first, InputIterator last, const key_compare &comp = key_compare (), const allocator_type &alloc = allocator_type(),
  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
  : value_type_alloc_(alloc), key_compare_(comp), size_(0) {
    node_alloc_ = std::allocator<Node>();
    last_ = node_alloc_.allocate(1);
    set_node_default();
    while (first != last) {
      insert_node(root_, *first);
      first++;
    }
  }

  // 복사 생성자
  map(const map &x) : size_(0) {
    value_type_alloc_ = x.value_type_alloc_;
    node_alloc_ = x.node_alloc_;
    last_ = node_alloc_.allocate(1);
    set_node_default();
    if (x.size_ != 0) {
      root_= creat_node(last_, x.root_->content);
      root_->height = x.root_->height;
      size_++;
      copy_node(this->root_, x.root_, x.last_);
    }
  }

  // 대입연산자
  map &operator=(const map &other) {
    if (this != &other) {
      if (this->root_ != last_) {
        clear();
      }
      value_type_alloc_ = other.value_type_alloc_;
      node_alloc_ = other.node_alloc_;
      if (other.size_ == 0)
        return (*this);
      else {
        root_= creat_node(last_, other.root_->content);
        root_->height = other.root_->height;
        size_++;
        copy_node(this->root_, other.root_, other.last_);
      }
    }
    return *this;
  }

  // 소멸 시 조건에 따라 clear를 진행하고, 기본으로 만들었던 last노드를 해제한다.
  ~map() {
    if (root_ != last_) {
      clear();
    }
    node_alloc_.destroy(last_);
    node_alloc_.deallocate(last_, 1);
  }

  // last->left에 있는 최소값으로 iterator를 생성해 리턴한다.
  iterator begin() {
    Node *tmp = root_;
    while (tmp->left != last_)
      tmp = tmp->left;
    return (iterator(tmp, last_));
  }

  const_iterator begin() const {
    Node *tmp = root_;
    while (tmp->left != last_)
      tmp = tmp->left;
    return (const_iterator(tmp, last_)); }

  // last로 iterator를 생성해 리턴한다.
  iterator end() { return (iterator(last_, last_)); }

  const_iterator end() const { return (const_iterator(last_, last_)); }

  // end()를 보내면 reverse_iterator에서 iterator-- 연산을 진행한다.
  // iterator기준 만약 현 위치가 last면 last->right(최대값)으로 노드 위치 변경
  reverse_iterator rbegin() { return (reverse_iterator(end())); }

  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

  reverse_iterator rend() { return (reverse_iterator(begin())); }

  const_reverse_iterator rend() const { return reverse_iterator(begin()); }

  // size_로도 확인 가능함
  bool empty() const { return (root_ == last_); }

  size_type size() const { return (size_); }

  // 구현한 사람에 따라 STL과 다르게 나오는데, 똑같이 나옴(환경차이도 확인해야 함)
  size_type max_size() const { return node_alloc_.max_size(); }

  // key값으로 데이터 찾아서 있으면 mapped값 참조 리턴, 없으면 키로 노드 생성 후 mapped 참조 리턴
  mapped_type &operator[](const key_type &k) {
    Node *new_node = insert_node(root_, ft::make_pair(k, mapped_type())).first;
    return (new_node->content.second);
  }

  pair<iterator, bool> insert (const value_type &val) {
    ft::pair<Node*, bool> new_node_pair = insert_node(root_, val);
    return (ft::make_pair(iterator(new_node_pair.first, last_), new_node_pair.second));
//    if (new_node_pair.second == true) {
//      return (ft::make_pair(iterator(new_node_pair.first, last_), true));
//    }
//    return (ft::make_pair(iterator(new_node_pair.first, last_), false));
  }

  iterator insert(iterator position, const value_type &val) {
    if ((key_compare_(position->first, val.first))) {
      for (; position != end(); position++) {
//        std::cout << "position" <<  position->first << std::endl;
        if (!key_compare_(position->first, val.first))
          break;
      }
    }
    else {
      for (; position != begin(); position--) {
//        std::cout << "position" <<  position->first << std::endl;
        if (!key_compare_(val.first, position->first))
          break;
      }
    }

//    bool low_comp = (key_compare_(position->first, val.first)) ? true : false;
//    for (; position != end(); position++) {
//      std::cout << "position" <<  position->first << std::endl;
//
//      if (low_comp == true && !key_compare_(position->first, val.first))
//        break;
//      if (low_comp == false && !key_compare_(val.first, position->first))
//        break;
//    }

    if (position == end() || position == begin()) {
      return (iterator(insert_node(root_, val).first, last_));
    }
    Node *root = search_node(root_, *position);
    if (root->parent != last_)
      root = root->parent;
    return (iterator(insert_node(root, val).first, last_));
  }

//  iterator insert(iterator position, const value_type &val) {
//    Node *root = search_node(root_, *position);
//    if (root == last_)
//      return (iterator(insert_node(root_, val).first, last_));
//    while (root != root_ && key_compare_(root->parent->content.first, val.first)) {
//      root = root->parent;
//    }
//    return (iterator(insert_node(root, val).first, last_));
//  }


//  iterator insert(iterator position, const value_type &val) {
//    Node *root = position.base();
//    if (root == last_)
//      return (iterator(insert_node(root_, val).first, last_));
//    while (root != root_ && key_compare_(root->parent->content.first, val.first)) {
//      root = root->parent;
//    }
//    return (iterator(insert_node(root, val).first, last_));
//  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      insert_node(root_, *first);
      first++;
    }
  }

  void erase (iterator position) {
    delete_node(*position);
  }

  size_type erase (const key_type& k) {
    size_type tmp = size_;
    delete_node(ft::make_pair(k, mapped_type()));
    return (tmp - size_);
  }

  void erase (iterator first, iterator last) {
    while (first != last) {
      iterator tmp(first);
      first++;
      delete_node(*tmp);
    }
  }

  void swap(map &x) {
    swap(root_, x.root_);
    swap(last_, x.last_);
    swap(value_type_alloc_, x.value_type_alloc_);
    swap(node_alloc_, x.node_alloc_);
    swap(key_compare_, x.key_compare_);
    swap(size_, x.size_);
  }

//  void clear() {
//    if (root_ != last_) {
//      iterator iter = begin();
//      while (iter != end()) {
//        iterator tmp = iter;
//        iter++;
//        delete_node(*tmp);
//      }
//      set_node_default();
//    }
//  }

  void clear() {
    if (root_ != last_) {
      clear_node(root_);
      size_ = 0;
      set_node_default();
    }
  }



  key_compare key_comp() const { return (key_compare_); }

  value_compare value_comp() const { return value_compare(key_compare_); }

  iterator find(const key_type &k) { return (iterator(search_node(root_, ft::make_pair(k, mapped_type())), last_)); }

  const_iterator find(const key_type &k) const { return (const_iterator(search_node(root_, ft::make_pair(k, mapped_type())), last_)); }

  size_type count (const key_type& k) const {
    if (search_node(root_, ft::make_pair(k, mapped_type())) == last_)
      return 0;
    else
      return 1;
  }

  iterator lower_bound(const key_type &k) {
    iterator begin_iterator = begin();
    for (; begin_iterator != end(); begin_iterator++) {
      if (!key_compare_(begin_iterator->first, k))
        break;
    }
    return (begin_iterator);
  }

  const_iterator lower_bound(const key_type &k) const {
    const_iterator begin_iterator = begin();
    for (; begin_iterator != end(); begin_iterator++) {
      if (!key_compare_(begin_iterator->first, k))
        break;
    }
    return (begin_iterator);
  }

  iterator upper_bound(const key_type &k) {
    iterator begin_iterator = begin();
    for (; begin_iterator != end(); begin_iterator++) {
      if (key_compare_(k, begin_iterator->first))
        break;
    }
    return (begin_iterator);
  }

  const_iterator upper_bound(const key_type &k) const {
    const_iterator begin_iterator = begin();
    for (; begin_iterator != end(); begin_iterator++) {
      if (key_compare_(k, begin_iterator->first))
        break;
    }
    return (begin_iterator);
  }

  ft::pair<iterator, iterator> equal_range(const key_type &k) {
    return (ft::make_pair(lower_bound(k), upper_bound(k)));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return (ft::make_pair(lower_bound(k), upper_bound(k)));
  }

  allocator_type get_allocator() const { return (value_type_alloc_); }

 private:
  Node *root_;
  Node *last_;
  allocator_type value_type_alloc_;
  std::allocator<Node> node_alloc_;
  Compare key_compare_;
  size_type size_;

  template<class U>
  void swap(U &a, U &b) {
    U tmp = a;
    a = b;
    b = tmp;
  }

  void set_node_default() {
    root_ = last_;
    last_->parent = last_;
    last_->left = last_;
    last_->right = last_;
    last_->height = 0;
  }

  void destory_node(Node *root) {
    value_type_alloc_.destroy(&(root->content));
    node_alloc_.deallocate(root, 1);
  }

  void clear_node(Node *root) {
    if (root->left != last_)
      clear_node(root->left);
    destory_node(root);
    if (root->right != last_)
      clear_node(root->right);
  }

  void correction_height(Node *root) {
    while (root != last_) {
      root->height = 1 + std::max(root->left->height, root->right->height);
      root = root->parent;
    }
  }

  Node *find_max_node (Node *root) {
    Node *tmp = root;
    while (tmp->right != last_)
      tmp = tmp->right;
    return (tmp);
  }

  Node *find_min_node (Node *root) {
    Node *tmp = root;
    while (tmp->left != last_)
      tmp = tmp->left;
    return (tmp);
  }

  Node *creat_node(Node *parent, value_type val) {
    Node *new_node = node_alloc_.allocate(1);
    value_type_alloc_.construct(&(new_node->content), val);
    new_node->left = last_;
    new_node->right = last_;
    new_node->parent = parent;
    new_node->height = 1;
    return (new_node);
  }

  ft::pair<Node *, bool>insert_node(Node *root, value_type val) {
    ft::pair<Node*, Node*> node_pair = search_node_parent(root, val.first);
    Node *new_node = node_pair.first;
    Node *parent = node_pair.second;
    if (new_node != last_) {
      return (ft::make_pair(new_node, false));
    }
    size_++;
    if (new_node == root_) {
      root_ = creat_node(last_, val);
      last_->left = root_;
      last_->right = root_;
      return (ft::make_pair(root_, true));
    }
    new_node = creat_node(parent, val);
    if (key_compare_(val.first, parent->content.first))
      parent->left = new_node;
    else
      parent->right = new_node;
    correction_height(new_node);
    rebalance(new_node);
    last_->right = root_;
    return (ft::make_pair(new_node, true));
  }

  Node *search_node(Node *root, value_type val) const {
    while (root != last_) {
      if (root->content.first == val.first)
        return (root);
      else if (key_compare_(val.first, root->content.first))
        root = root->left;
      else
        root = root->right;
    }
    return (root);
  }

  ft::pair<Node*, Node*> search_node_parent(Node *root, key_type k) const {
    Node *parent = (root->parent == root_) ? root_ : root->parent;
    while (root != last_) {
      if (root->content.first == k)
        return (ft::make_pair(root, parent));
      parent = root;
      if (key_compare_(k, root->content.first))
        root = root->left;
      else
        root = root->right;
    }
    return (ft::make_pair(root, parent));
  }

  void delete_node(value_type val) {

    Node *del = search_node(root_, val);
    Node *tmp;
    Node *del_parent;

    if (del == last_)
      return ;
      //자식이 없는 경우
    else if (del->left == last_ && del->right == last_) {
      del_parent = del->parent;
      if (del_parent == last_) {
        root_ = last_;
      }
      else if (del_parent->left == del) {
        del_parent->left = last_;
      }
      else {
        del_parent->right = last_;
      }
      value_type_alloc_.destroy(&(del->content));
      node_alloc_.deallocate(del, 1);
      if (del_parent->left->height > del_parent->right->height) {
        rebalance(find_min_node(del_parent));
      }
      else if (del_parent->left->height < del_parent->right->height){
        rebalance(find_max_node(del_parent));
      }
    }
      // 자식이 둘 다 있는 경우
    else if (del->left != last_ && del->right != last_) {
      tmp = find_max_node(del->left);
      value_type_alloc_.destroy(&(del->content));
      value_type_alloc_.construct(&(del->content), tmp->content);
      tmp->left->parent = tmp->parent;
      if (tmp->parent->left == tmp)
        tmp->parent->left = tmp->left;
      else
        tmp->parent->right = tmp->left;
      value_type_alloc_.destroy(&(tmp->content));
      node_alloc_.deallocate(tmp, 1);
      if (del->left->height > del->right->height) {
        rebalance(find_min_node(del));
      }
      else if (del->left->height < del->right->height){
        rebalance(find_max_node(del));
      }
    }
      // 자식이 한 쪽만 있는 경우
    else {
      Node *child = (del->left != last_) ? del->left : del->right;
      child->parent = del->parent;
      del_parent = del->parent;
      if (del->parent != last_) {
        if (del->parent->left == del)
          del->parent->left = child;
        else
          del->parent->right = child;
      }
      else {
        root_ = child;
      }
      value_type_alloc_.destroy(&(del->content));
      node_alloc_.deallocate(del, 1);
      if (del_parent->left->height > del_parent->right->height) {
        rebalance(find_min_node(del_parent));
      }
      else if (del_parent->left->height < del_parent->right->height){
        rebalance(find_max_node(del_parent));
      }
    }
    last_->right = root_;
    size_--;
    if (size_ == 0) {
      set_node_default();
    }
  }

  Node *right_rotate(Node *root) {
//    std::cout << "***************************rr************************" << std::endl;
    Node *new_root = root->left;
    if (root == root_)
      root_ = new_root;
    Node *new_root_rchild = new_root->right;
    new_root->parent = root->parent;
    if (new_root->parent != last_ && new_root->parent->left == root) {
      new_root->parent->left = new_root;
    }
    else if (new_root->parent != last_ && new_root->parent->right == root) {
      new_root->parent->right = new_root;
    }
    new_root->right = root;
    root->left = new_root_rchild;
    root->left->parent = root;
    root->parent = new_root;
    root->height = 1 + std::max(root->left->height, root->right->height);
    correction_height(root);
    return (new_root);
  }

  Node *left_rotate(Node *root) {
//    std::cout << "***************************lr************************" << std::endl;
    Node *new_root = root->right;
    if (root == root_)
      root_ = new_root;
    Node *new_root_lchild = new_root->left;
    new_root->parent = root->parent;
    if (new_root->parent != last_ && new_root->parent->left == root) {
      new_root->parent->left = new_root;
    }
    else if (new_root->parent != last_ && new_root->parent->right == root) {
      new_root->parent->right = new_root;
    }
    new_root->left = root;
    root->right = new_root_lchild;
    root->right->parent = root;
    root->parent = new_root;
    root->height = 1 + std::max(root->left->height, root->right->height);
    correction_height(root);
    return (new_root);
  }

  int get_balance(Node *n) {
    if (n == last_)
      return (0);
    return (n->left->height - n->right->height);
  }

  Node *rebalance(Node *root) {
    int balance;
    while (root != last_) {
      balance = get_balance(root);
      // RR case
      if (balance < -1 && get_balance(root->right) < 0) {
        left_rotate(root);
      } // RL case 5->7->6 순서로 들어오면 RR로 인식해서 left_rotate -> 순서 꼬임
      else if (balance < -1 && get_balance(root->right) > 0) {
        right_rotate(root->right);
        left_rotate(root);
      } // LL case
      else if (balance > 1 && get_balance(root->left) > 0) {
        right_rotate(root);
      } // LR case 5->3->4 순서로 들어오면 LL로 인식해서 right_rotate -> 순서 꼬임
      else if (balance > 1 && get_balance(root->left) < 0) {
        left_rotate(root->left);
        right_rotate(root);
      }
      root = root->parent;
    }
    return (root);
  }

  void copy_node(Node *root, Node *other, Node *other_last) {
    if (other->left == other_last) {
      root->left = last_;
    }
    else {
      root->left = creat_node(root, other->left->content);
      root->left->height = other->left->height;
      size_++;
      copy_node(root->left, other->left, other_last);
    }
    if (other->right == other_last) {
      root->right = last_;
    }
//    else if (other->right->right == other_last) {
//      root->right = creat_node(root, other->right->content);
//      root->right->height = other->right->height;
//      size_++;
//      root->right->right = last_;
//    }
    else {
      root->right = creat_node(root, other->right->content);
      root->right->height = other->right->height;
      size_++;
      copy_node(root->right, other->right, other_last);
    }
  }

  void print_tree() {
    std::cout << last_->right->content.first << std::endl;
    print_tree(root_);
    if (!root_)
      std::cout << "empty" << std::endl;
  }

  void print_tree(Node *root) {
    if (root->left != last_)
      print_tree(root->left);
    std::cout << "===================================" << std::endl;
    std::cout << "ele : " << root->content.first << std::endl;
    std::cout << "parent : " << root->parent->content.first << std::endl;
    std::cout << "left : " << root->left->content.first << std::endl;
    std::cout << "right : " << root->right->content.first << std::endl;
    std::cout << "height : " << root->height << std::endl;
    std::cout << "root : " << root_->content.first << std::endl;
    std::cout << "===================================" << std::endl;
    if (root->right != last_)
      print_tree(root->right);
  }
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
  typedef typename ft::map<Key, T, Compare, Alloc>::size_type size_type;
  typedef typename ft::map<Key, T, Compare, Alloc>::const_iterator const_iterator;

  if (lhs.size() != rhs.size()) {
    return (false);
  }
  const_iterator lsh_iter = lhs.begin();
  const_iterator rsh_iter = rhs.begin();
  size_type size = lhs.size();
  for (size_type i = 0; i < size; i++) {
    if (lsh_iter->first != rsh_iter->first) {
      return (false);
    }
    if (lsh_iter->second != lsh_iter->second) {
      return (false);
    }
    lsh_iter++;
    rsh_iter++;
  }
  return (true);
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
  return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key,T,Compare, Alloc>& lhs, const ft::map<Key,T,Compare, Alloc>& rhs ) {
  typename ft::map<Key, T, Compare, Alloc>::const_iterator first1 = lhs.begin();
  typename ft::map<Key, T, Compare, Alloc>::const_iterator first2 = rhs.begin();
  Compare comp;
  while (first1 != lhs.end()) {
    if (first2 == rhs.end() || comp(first2->first,first1->first) || comp(first2->second,first1->second))
      return false;
    else if (comp(first1->first, first2->first) || comp(first1->second, first2->second))
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
  return (!(lhs < rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
  return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
  return (!(rhs < lhs));
}
}
#endif //FT_CONTAINERS_MAP_NODE_HPP
