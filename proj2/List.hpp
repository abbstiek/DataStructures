//Abygail Stiekman 10/08/2016

#ifndef DL_LIST_CPP
#define DL_LIST_CPP

template <typename T>
List<T>::const_iterator::const_iterator() 
	: current{nullptr} {}

	template <typename T>
	const T& List<T>::const_iterator::operator*() const {
		return this-> retrieve();
	}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
	current = current-> next;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
	auto result = *this;
	++(*this);
	return result;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
	current = current-> prev;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
	auto result = *this;
	--(*this);
	return result;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
	return (current == rhs.current);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
	return !(*this == rhs);
}

template <typename T>
T & List<T>::const_iterator::retrieve() const {
	return current -> data;
}

	template <typename T>
List<T>::const_iterator::const_iterator(Node *p) 
	: current{p} {}

	template <typename T>
	List<T>::iterator::iterator() {}

	template <typename T>
	T & List<T>::iterator::operator*() {
		return this-> retrieve();
	}

template <typename T>
const T & List<T>::iterator::operator*() const {
	return this->retrieve();
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
	const_iterator::current = const_iterator::current->next; // we should use base class name for accessing 'current' here
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
	 auto result = *this; // make copy of iterator (we should return original value)
  ++(*this); // re-use prefix increment operator
  return result; // return original iterator value
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
	const_iterator::current = const_iterator::current->prev; // we should use base class name for accessing 'current' here
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
	auto result = *this; // make copy of iterator (we should return original value)
  --(*this); // re-use prefix decrement operator
  return result; // return original iterator value
}

	template <typename T>
List<T>::iterator::iterator(Node *p) 
	: List<T>::const_iterator::const_iterator{p} {}

	template <typename T>
	List<T>::List() {
		init();
	}

template <typename T> 
List<T>::List(const List &rhs) {
	init();
	
	for (auto &x : rhs)
	{
		push_back(x);
	}
}

template <typename T>
List<T>::List(List && rhs) 
	: theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
		init();
		
		*this = std::move(rhs);
	}


template <typename T>
List<T>::List(int num, const T& val) {
	init();
	
	for (auto i = 0; i < num; ++i)
	{
		push_back(val);
	}
}


template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
	
  init();

  for(auto iter = start; iter != end; ++iter) // from 'start' till 'end' iterator
  {
    push_back(*iter); // put element from source list into end of this list
  }
}


template <typename T>
List<T>::List(std::initializer_list<T> iList)
{
   init();
  for(auto i = iList.begin(); i != iList.end(); ++i)
  {
    push_back(*i);
  }
}

template <typename T>
List<T>::~List() {
	clear();
	delete head;
	delete tail;
}

template <typename T>
List<T>& List<T>::operator=(List &&tmp) {
	
  // Swap all members between this one and temporary object
  std::swap(theSize, tmp.theSize);
  std::swap(head, tmp.head);
  std::swap(tail, tmp.tail);

  return *this;

}

template <typename T>
const List<T> & List<T>::operator=(const List & rhs) {
	  if (this != &rhs) // check for self-assigment
  {
  List copy = rhs;
  std::swap(*this,copy);
  return *this;
}
}


template <typename T>
List<T>& List<T>::operator= (std::initializer_list<T> iList)
{
    init();
  for(auto i = iList.begin(); i != iList.end(); ++i)
  {
   push_back(*i);
    return *this;
  }
}

template <typename T>
int List<T>::size() const {
	return theSize;
}

template <typename T>
bool List<T>::empty() const {
	return size() == 0;
}

template <typename T>
void List<T>::clear() {
	while (!empty())
		pop_front();
}


template <typename T>
void List<T>::reverse() {
	auto current = head; // starting from head node

  while(current != nullptr) // till current node is not last (next after last)
  {  
    std::swap(current->next, current->prev); // swap 'next' and 'prev' pointer values
    current = current->prev; // advance next node (we use 'prev' because we swap it before)
  }

  std::swap(head, tail); // swap 'head' and 'tail' nodes
}

template <typename T>
T & List<T>::front() {
	return *begin();
}

template <typename T>
const T& List<T>::front() const {
	return *begin();
}

template <typename T>
T & List<T>::back() {
	return *--end();
}

template <typename T>
const T & List<T>::back() const{
	return *--end();
} 

template <typename T>
void List<T>::push_front(const T & val) {/*
	auto node = new Node(val); // create new node with passed value

  if (head != nullptr)
  {
    node->next = head; // link new node and old head
    head->prev = node;
  }
  head = node; // set new head node

  if (tail == nullptr) // if this node is first set tail node too
  {
    tail = head;
  }

  ++theSize; // change list size*/
  insert(begin(), val);
}


template <typename T>
void List<T>::push_front(T && val) {
	/*auto node = new Node(val); // create new node with passed value

  if (head != nullptr)
  {
    node->next = head; // link new node and old head
    head->prev = node;
  }
  head = node; // set new head node

  if (tail == nullptr) // if this node is first set tail node too
  {
    tail = head;
  }

  ++theSize; // change list size */
  insert(begin(),std::move(val));
}


template <typename T>
void List<T>::push_back(const T & val) {
	/*
	auto node = new Node(val); // create new node with passed value

  if (tail != nullptr)
  {
    node->prev = tail; // link new node and old tail
    tail->next = node;
  }
  tail = node; // set new tail node

  if (head == nullptr) // if this node is first set head node too
  {
    head = tail;
  }

  ++theSize; // change list size*/
  insert(end(),val);
}

template <typename T>
void List<T>::push_back(T && val) {/*
	 auto node = new Node(val); // create new node with passed value

  if (tail != nullptr)
  {
    node->prev = tail; // link new node and old tail
    tail->next = node;
  }
  tail = node; // set new tail node

  if (head == nullptr) // if this node is first set head node too
  {
    head = tail;
  }

  ++theSize; // change list size*/
  insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front() {
	/*
	auto todelete = head; // remember old head pointer for later deletion
 
  head = head->next; // set new head pointer - use second element

  if (head == nullptr) // if new head is nullptr list is empty
  {
    tail = nullptr; // set tail pointer to nullptr also
  }
  else
  {
    head->prev = nullptr; // just remove link to old head from new head
  }

  --theSize; // change list size

  delete todelete; // free memory*/
  erase(begin());
}

template <typename T>
void List<T>::pop_back() {/*
	auto todelete = tail; // remember old tail pointer for later deletion

  tail = tail->prev; // set new tail pointer - use pre-tail element

  if (tail == nullptr) // if new tail is nullptr list is empty
  {
    head = nullptr; // set head pointer to nullptr also
  }
  else
  {
    tail->next = nullptr; // just remove link to old tail from new tail
  }

  --theSize; // change list size

  delete todelete; // free memory*/
  
  erase(--end());
}


template <typename T>
void List<T>::remove(const T &val) {
	 for(auto iter = begin(); iter != end(); ++iter) // for each nodes in list
  {
    if (*iter == val) // if value from node equal to value for deletion...
    {
      erase(iter); // delete item and return
      //return;
    }
  }
}


template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
	for (auto itr = begin(); itr != end(); itr++)
	{
		if (pred(*itr))
			erase(itr);
	}
}



template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
	ofc = ' ';
	 for(auto itr = begin(); itr != end(); ++itr) // for all items in list
  {
    os << *itr << ofc; // put item value into stream + separator char
  }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
	return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
	return const_iterator(head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
	return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
	return const_iterator(tail);
}


template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
	/*auto node = itr.current; // store current node
  if (node == nullptr) // unable to insert into incorrect position
  {
    return;
  }

  auto new_node = new Node(val); // create new node for insertion

  new_node->next = node; // link new node and current iterator node
  new_node->prev = node->prev;

  node->prev = node; // link current iterator node and new node
  if (node->prev == nullptr) // insertion into begining of the list
  {
    head = new_node; // update head pointer
  }
  else
  {
    node->perv->next = node; // we insert new node before so we should update this pointer too
  }

  ++theSize; // change list size

  return iterator(new_node); // return new iterator pointed to new node
*/
	Node *p = itr.current;
	++theSize;
	return iterator(p->prev = p->prev->next = new Node{val,p->prev,p});
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) {/*
	auto node = itr.current; // store current node
  if (node == nullptr) // unable to insert into incorrect position
  {
    return;
  }

  auto new_node = new Node(val); // create new node for insertion

  new_node->next = node; // link new node and current iterator node
  new_node->prev = node->prev;

  node->prev = node; // link current iterator node and new node
  if (node->prev == nullptr) // insertion into begining of the list
  {
    head = new_node; // update head pointer
  }
  else
  {
    node->perv->next = node; // we insert new node before so we should update this pointer too
  }

  ++theSize; // change list size

  return iterator(new_node); // return new iterator pointed to new node*/
  Node *p = itr.current;
  ++theSize;
  return iterator(p->prev = p->prev->next = new Node{std::move(val),p->prev,p});
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {/*
	 auto node = itr.current; // store current node pointer

  if (node->prev != nullptr) // if current node is not head
  {
    node->prev->next = node->next; // update previous node - link it with next
  }
  else
  {
    head = node->next; // else just upate 'head' pointer
  }

  if (node->next != nullptr) // if current node is not tail
  {
    node->next->prev = node->prev; // update next node - link it with previous
  }
  else
  {
    tail = node->prev; // else just upate 'tail' pointer
  }

  ++itr; // advance iterator

  delete node; // free node memory
  --theSize; // change list size

  return itr;*/
  
  Node *p = itr.current;
 iterator retVal( p->next );
 p->prev->next = p->next;
 p->next->prev = p->prev;
 delete p;
 --theSize;
 return retVal;

}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
	/*while(start != end) // for all elements between two iterators
  {
    start = erase(start); // erase item pointed by 'start' (and advance 'start' as result of 'erase' call)
  }

  return start;*/
  
  for( iterator itr = start; itr != end; )
 itr = erase( itr );
 return end;

}


template <typename T>
void List<T>::init() {	
	theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}


template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
	if (lhs.size() != rhs.size()) // if sizes are not equal - return false
  {
    return false;
  }

  // we should iterate both lists head-to-head and compare item values
  for(auto lhs_itr = lhs.begin(), rhs_itr = rhs.begin(); lhs_itr != lhs.end(); ++lhs_itr, ++rhs_itr)
  {
      if (*lhs_itr != *rhs_itr) // if item values are not equal - return false
      {
        return false;
      }
  }

  return true; // it's possible only if all elements are equal
}


template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
	return !(lhs == rhs);
}



template <typename T>
std::ostream & operator<<(std::ostream & os, const List<T> &l) {
	l.print(os);
	return os;
}
#endif
