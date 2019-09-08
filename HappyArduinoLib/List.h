#pragma once

template<class T>
class List
{
public:
  class ListNode
  {
    friend class List;
    
    public:
      T& operator->() { return value; }
      T& operator *() { return value; }
    
      ListNode* Next() { return next; }
      ListNode* Prev() { return prev; }      

    private:              
      ListNode* next = NULL;
      ListNode* prev = NULL;        

      T value;      

      ListNode(T& t) : value(t) {};
  };
  
private:
  ListNode* first = NULL;
  ListNode* last = NULL;
  
public:
  ListNode* First() { return first; }
  ListNode* Last() { return last; }
    
  void push_back(ListNode * node)
  {
	if (first == NULL)
    {
      first = last = node;
    }    
    else
    {          
      node->next = NULL;
	  node->prev = last;
	  last->next = node;
      last = node;
    }
  }  
  
  void push_back(T elem)
  {    
    ListNode * node = new ListNode(elem);  
	push_back(node);
  }
  
  void push_front(ListNode * node)
  {    
    if (first == nullptr)
    {
      first = last = node;
    }
    else
    {      
      node->prev = NULL;
      node->next = first;
	  first->prev = node;
	  first = node;
    }
  }

  void push_front(T elem)
  {
    ListNode * node = new ListNode(elem); 
	push_front(node);
  }

  void erase(ListNode* elem)
  {    
    if (elem->prev != NULL)
      elem->prev->next = elem->next;

    if (elem->next != NULL)
      elem->next->prev = elem->prev;

    if (first == elem)
      first = elem->next;

    if (last == elem)
        last = elem->prev;
		
	elem->next = NULL;
	elem->prev = NULL;
  }
  
  void insert(ListNode* newNode, ListNode* beforeNode)
  {    	
	newNode->next = beforeNode;
	
    if (beforeNode->prev != NULL)
    {	
		newNode->prev = beforeNode->prev;
		beforeNode->prev->next = newNode;		
	}
	
	beforeNode->prev = newNode;	

    if (first == beforeNode)
      first = newNode;
  }
  
  void insert(T elem, ListNode* beforeNode)
  {    	
	ListNode * node = new ListNode(elem); 
	insert(node,beforeNode);
  }
};