#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_CORE_CONTAINER_ADAPTORS_S21_STACK_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_CORE_CONTAINER_ADAPTORS_S21_STACK_H_

#include <algorithm>
#include <cstddef>
#include <deque>
#include <initializer_list>

#include "s21_container_adaptor.h"

namespace s21 {

template <class T, class C = std::deque<T>>
class stack : public container_adaptor<T, C> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using container_adaptor<T, C>::container_;

  stack() = default;
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack() = default;

  reference top();
  void pop() override;
  void push(const_reference value) override;
  template <class... Args>
  void insert_many_front(Args &&...args);

  stack operator=(const stack &other);
  bool operator==(const stack &other) const;
};  // class stack

template <class T, class C>
stack<T, C>::stack(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

template <class T, class C>
stack<T, C>::stack(const stack &other) {
  container_ = other.container_;
}

template <class T, class C>
stack<T, C>::stack(stack &&other) noexcept {
  container_ = std::move(other.container_);
}

template <class T, class C>
typename stack<T, C>::reference stack<T, C>::top() {
  return container_.back();
}

template <class T, class C>
void stack<T, C>::push(const_reference value) {
  container_.push_back(value);
}

template <class T, class C>
void stack<T, C>::pop() {
  container_.pop_back();
}

template <class T, class C>
stack<T, C> stack<T, C>::operator=(const stack &other) {
  container_ = other.container_;
  return *this;
}

template <class T, class C>
bool stack<T, C>::operator==(const stack &other) const {
  return container_ == other.container_;
}

template <class T, class C>
template <class... Args>
void stack<T, C>::insert_many_front(Args &&...args) {
  for (auto &arg : {args...}) {
    container_.push_back(arg);
  }
}

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_CORE_CONTAINER_ADAPTORS_S21_STACK_H_
