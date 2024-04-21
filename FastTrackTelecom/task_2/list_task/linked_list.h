#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
class LinkedList {
 private:
  struct Node {
    T value_;
    Node* next;
    Node(const T value) : value_(value), next(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  // Node* root;
  size_t m_size;

 public:
  template <typename D>
  class LinkedListIterator {
   public:
    using iterator = LinkedListIterator<D>;
    Node* cur_;
    LinkedListIterator() : cur_(nullptr) {}
    LinkedListIterator(Node* cur) : cur_(cur) {}
    T& operator*() { return cur_->value_; }
    iterator& operator++() {
      cur_ = cur_->next;
      return *this;
    }

    bool operator!=(const iterator& other) const { return cur_ != other.cur_; }
    bool operator==(const iterator& other) const { return cur_ == other.cur_; }
  };

  template <typename D>
  class LinkedListConstIterator : public LinkedListIterator<D> {
   public:
    LinkedListConstIterator() : LinkedListIterator<D>() {}
    LinkedListConstIterator(Node* cur_) : LinkedListIterator<D>(cur_) {}
    const T& operator*() const { return this->cur_->value_; }
  };

  using iterator = LinkedListIterator<T>;
  using const_iterator = LinkedListConstIterator<T>;

  LinkedList();
  LinkedList(std::initializer_list<T> const& items);
  LinkedList(LinkedList&& other);
  LinkedList(const LinkedList& other);
  ~LinkedList() noexcept;
  LinkedList& operator=(LinkedList&& other);
  LinkedList& operator=(const LinkedList& other);
  iterator begin() { return iterator(head_->next); }
  iterator end() { return iterator(tail_); }
  iterator before_begin() { return iterator(head_); }
  const_iterator cbegin() const { return const_iterator(head_->next); }
  const_iterator cend() const { return const_iterator(tail_); }
  const T& front() const;
  iterator insert_after(iterator pos, const T& value);
  void erase_after(iterator pos);
  void clear();
  size_t size() { return m_size; }
  void swap(LinkedList& other);
  bool empty() { return m_size == 0; }
  void push_front(const T& value);
  void pop_front();
  iterator find(const T& value);
  void erase(const T& value);
};

#include "linked_list.tpp"
#endif