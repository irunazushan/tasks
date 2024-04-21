#include "linked_list.h"

template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr), tail_(nullptr), m_size(0) {
  head_ = new Node(T{});
  head_->next = tail_;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
  this->swap(other);
  return (*this);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
  LinkedList<T> tmpL;
  for (auto it = other.cbegin(); it != other.cend(); ++it) {
    tmpL->push_front(*it);
  }
  for (auto it = tmpL.cbegin(); it != tmpL.cend(); ++it) {
    this->push_front(*it);
  }
  return (*this);
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> const& items)
    : LinkedList() {
  auto it = items.end();
  for (size_t i = items.size(); i > 0; i--) {
    push_front(*--it);
  }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) : LinkedList() {
  this->swap(other);
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : LinkedList() {
  this = other;
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept {
  clear();
  delete head_;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert_after(iterator pos,
                                                             const T& value) {
  Node* newNode = new Node(value);
  newNode->next = pos.cur_->next;
  pos.cur_->next = newNode;

  ++m_size;
  return iterator(newNode);
}

template <typename T>
template <typename U>
T& LinkedList<T>::LinkedListIterator<U>::operator*() {
  if (cur_ == nullptr) {
    static T nothing{};
    return nothing;
  } 
  return cur_->value_;
}

template <typename T>
const T& LinkedList<T>::front() const {
  return head_->next->value_;
}

template <typename T>
void LinkedList<T>::erase_after(iterator pos) {
  Node* nextNode = pos.cur_->next->next;
  delete pos.cur_->next;
  pos.cur_->next = nextNode;
  --m_size;
}

template <typename T>
void LinkedList<T>::clear() {
  while (m_size != 0) {
    pop_front();
  }
}

template <typename T>
void LinkedList<T>::swap(LinkedList& other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->m_size, other.m_size);
}
template <typename T>
void LinkedList<T>::push_front(const T& value) {
  insert_after(before_begin(), value);
}

template <typename T>
void LinkedList<T>::pop_front() {
  erase_after(before_begin());
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::find(const T& value) {
  iterator cur = this->begin();
  while (cur != this->end() && *cur != value) {
    ++cur;
  }
  if (cur == this->end()) {
    cur = this->begin();
  }
  return iterator(cur);
}

template <typename T>
void LinkedList<T>::erase(const T& value) {
  iterator prevCur = this->before_begin();
  iterator cur = this->begin();
  while (cur != this->end()) {
    if (*cur == value) {
      this->erase_after(prevCur);
      break;
    } else {
      ++cur;
      ++prevCur;
    }
  }
}
