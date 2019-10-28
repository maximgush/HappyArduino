#pragma once

#include <list>
#include <vector>

template <class T>
class List {
 public:
  class ListNode {
    friend class List;

   public:
    T& operator->() { return value; }
    T& operator*() { return value; }

    ListNode* Next() { return next; }
    ListNode* Prev() { return prev; }

	T GetValue() { return value; }

   private:
    ListNode* next = nullptr;
    ListNode* prev = nullptr;

    T value;

    ListNode(T& t) : value(t){};
  };

 private:
  ListNode* first = nullptr;
  ListNode* last = nullptr;

 public:
  ListNode* First() { return first; }
  ListNode* Last() { return last; }

  void push_back(ListNode* node) {
    if (first == nullptr) {
      first = last = node;
    } else {
      node->next = nullptr;
      node->prev = last;
      last->next = node;
      last = node;
    }
  }

  void push_back(T elem) {
    ListNode* node = new ListNode(elem);
    push_back(node);
  }

  void push_front(ListNode* node) {
    if (first == nullptr) {
      first = last = node;
    } else {
      node->prev = nullptr;
      node->next = first;
      first->prev = node;
      first = node;
    }
  }

  void push_front(T elem) {
    ListNode* node = new ListNode(elem);
    push_front(node);
  }

  void erase(ListNode* elem) {
    if (elem->prev != nullptr) elem->prev->next = elem->next;

    if (elem->next != nullptr) elem->next->prev = elem->prev;

    if (first == elem) first = elem->next;

    if (last == elem) last = elem->prev;

    elem->next = nullptr;
    elem->prev = nullptr;
  }

  void insert(ListNode* newNode, ListNode* beforeNode) {
    newNode->next = beforeNode;

    if (beforeNode->prev != nullptr) {
      newNode->prev = beforeNode->prev;
      beforeNode->prev->next = newNode;
    }

    beforeNode->prev = newNode;

    if (first == beforeNode) first = newNode;
  }

  void insert(T elem, ListNode* beforeNode) {
    ListNode* node = new ListNode(elem);
    insert(node, beforeNode);
  }

  unsigned short Size() {
	  unsigned short size = 0;
	  ListNode* node = First();
	  while( node != nullptr ) {
		  size++;
		  node = node->Next();
	  }

	  return size;
  }
};