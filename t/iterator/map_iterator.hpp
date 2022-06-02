#ifndef FT_CONTAINERS_MAP_ITERATOR_HPP
#define FT_CONTAINERS_MAP_ITERATOR_HPP

#include "iterator.hpp"

// 기본적인 운영은 노드를 받아서 left, right 등으로 위치를 움직인다.
// 단, avl_tree 특성상 내부에서 left, right 등이 last인지 확인을 해야 하기 때문에 last도 인자로 받는다.

namespace ft {
template<class Iterator, class Compare, class Value_type>
class map_iterator : ft::iterator<ft::bidirectional_iterator_tag, Iterator> {
 public:
  // typedef
  // iterator_type은 노드
  typedef Iterator iterator_type;
  typedef iterator_type* node_pointer;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, Value_type>::iterator_category iterator_category;
  typedef Value_type value_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
  // iterator에 *연산 시 노드가 아닌, content(기본값은 ft::pair로 Value_type으로 받아온다)로 리턴을 한다.
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;



 public:
  // construct, ...
  map_iterator() : node_(0), last_(0) {}

  explicit map_iterator(node_pointer node, node_pointer last) : node_(node), last_(last) {}

  map_iterator(const map_iterator &copy) : node_(copy.node_), last_(copy.last_) {}

  map_iterator &operator=(const map_iterator &other) {
    if (this != &other) {
      node_ = other.node_;
      last_ = other.last_;
    }
    return *this;
  }

  ~map_iterator() {}

  node_pointer const base() { return node_; }
  // operator..
  bool operator==(map_iterator const &other) const { return (this->node_ == other.node_); }
  bool operator!=(map_iterator const &other) const { return (this->node_ != other.node_); }
  reference operator*() const { return node_->content; }
  pointer operator->() const { return &(node_->content); }

  map_iterator &operator++() {
    if (node_ != NULL) {
      if (node_->right != last_) {
        node_ = node_->right;
        while (node_->left != last_) {
          node_ = node_->left;
        }
      }
      else {
        while (node_->parent != last_ && node_->parent->right == node_)
          node_ = node_->parent;
        node_ = node_->parent;
      }
    }
    return *this;
  }

  map_iterator operator++(int) {
    map_iterator tmp(*this);
    operator++();
    return tmp;
  }

  map_iterator &operator--() {
    if (node_ != NULL) {
      if (node_ == last_) {
        node_ = node_->right;
        while (node_->right != last_)
          node_ = node_->right;
      }
      else if (node_->left != last_) {
        node_ = node_->left;
        while (node_->right != last_)
          node_ = node_->right;
      }
      else {
        while (node_->parent != last_ && node_->parent->left == node_)
          node_ = node_->parent;
        node_ = node_->parent;
      }
    }
    return *this;
  }

  map_iterator operator--(int) {
    map_iterator tmp(*this);
    operator--();
    return tmp;
  }

//  vector_iterator와 같이 const 대응을 위해 연산자 추가
  operator map_iterator<Iterator, Compare, const Value_type>() const {
    return (map_iterator<Iterator, Compare, const Value_type>(this->node_, this->last_));
  }

 private:
  node_pointer node_;
  node_pointer last_;

};
}

#endif //FT_CONTAINERS_MAP_ITERATOR_HPP
