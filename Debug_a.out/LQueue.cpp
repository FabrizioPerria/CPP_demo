/***************************************
Class: CS251
Assignment Number: 3
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include <functional>
#include <algorithm>
#include "LQueue.h"

/* static */
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.

template <typename T> void *
LQueue_Node<T>::operator new (size_t size)
{
	if (free_list_ == nullptr) {
		return ::operator new(size);
	} else {
		LQueue_Node<T> *tmp = free_list_;
		free_list_ = free_list_->next_;
		tmp->next_ = nullptr;
		tmp->prev_ = nullptr;
		return tmp;
	}
}

// Return <ptr> to the <free_list_>.

template <typename T> void
LQueue_Node<T>::operator delete (void *ptr)
{
	if (ptr != nullptr) {
		LQueue_Node<T> *tmp = static_cast<LQueue_Node<T>*>(ptr);
		tmp->next_ = free_list_;
		free_list_ = tmp;
	}
}

// Returns all dynamic memory on the free list to the free store.

template <typename T> void
LQueue_Node<T>::free_list_release (void)
{
	LQueue_Node<T> *tmp = nullptr;
	while (tmp != nullptr) {
		tmp = free_list_;
		free_list_ = free_list_->next_;
		::operator delete(tmp);
	}
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <typename T> void
LQueue_Node<T>::free_list_allocate (size_t n)
{
	if (n > 0) {
		free_list_ = (LQueue_Node<T>*)(::operator new(sizeof(LQueue_Node<T>)));
		free_list_->next_ = free_list_->prev_ = free_list_;
		for (size_t cnt = 1; cnt < n; cnt++){
			LQueue_Node<T> *tmp = (LQueue_Node<T>*)(::operator new(sizeof(LQueue_Node<T>)));
			tmp->prev_ = free_list_;
			tmp->next_ = free_list_->next_;
			free_list_->next_ = tmp;
			free_list_ = tmp;
		}
	}
}

template <typename T>
LQueue_Node<T>::LQueue_Node (LQueue_Node<T> *next,
                             LQueue_Node<T> *prev)
  : next_ (next),
    prev_ (prev)
{
  next_->prev_ = this;
  prev_->next_ = this;
}

template <typename T>
LQueue_Node<T>::LQueue_Node (void)
  // this is helpful to implement the dummy node in a concise way.
  : next_ (0),
    prev_ (0)
{
	next_ = this;
	prev_ = this;
}

template <typename T>
LQueue_Node<T>::~LQueue_Node (void)
{
  next_->prev_ = prev_;
  prev_->next_ = next_;
}

// Returns the current size.
template<typename T, typename LQUEUE_NODE> size_t
LQueue<T, LQUEUE_NODE>::size (void) const
{
  return count_;
}

// Constructor.

template<typename T, typename LQUEUE_NODE> 
LQueue<T, LQUEUE_NODE>::LQueue (size_t size_hint)
  : tail_ (0),
    count_ (0)
{
	LQueue_Node<T>::free_list_allocate(size_hint);
	tail_ = new LQUEUE_NODE();
}

template<typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::swap (LQueue<T, LQUEUE_NODE> &new_queue)
{
	std::swap(tail_,new_queue.tail_);
	std::swap(count_,new_queue.count_);
}

template<typename T, typename LQUEUE_NODE> 
struct copyQ {
	copyQ(LQueue<T,LQUEUE_NODE> &copy) : copy_(copy){}
	void operator()(const T& x)
	{
		copy_.enqueue(x);
	}
	LQueue<T,LQUEUE_NODE> &copy_;
};

// Copy constructor.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (const LQueue<T, LQUEUE_NODE> &rhs)
  // Initialize fields here.
  : tail_ (0), // tail_ will be set correctly by swap().
    count_ (0) // count_ will be set correctly by swap().
{
	LQueue<T,LQUEUE_NODE> tmp(sizeof(LQUEUE_NODE));
	std::for_each(rhs.begin(), rhs.end(), copyQ<T,LQUEUE_NODE>(tmp));
	swap (tmp);
}

// Assignment operator.
template <typename T, typename LQUEUE_NODE> LQueue<T, LQUEUE_NODE> &
LQueue<T, LQUEUE_NODE>::operator= (const LQueue<T, LQUEUE_NODE> &rhs) 
{
	if (*this != rhs) {
		LQueue<T,LQUEUE_NODE> tmp (rhs);
		swap(tmp);
	}
	return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::~LQueue (void)
{
	while (!is_empty())
		dequeue_i();		//do not check if the queue is empty inside the function
							//using dequeue, if the queue is empty, an exception will be raised
	delete tail_;
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const
{
	if (count_ == rhs.size()) {
		//Check the entire list
		return std::equal(begin(), end(), rhs.begin());
	}
	return false;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::enqueue (const T &new_item)
{
	try{
		tail_->item_ = new_item;
		tail_ = new LQUEUE_NODE(tail_->next_,tail_);
		++count_;
	} catch (std::bad_alloc) {
		throw Overflow();
	}
}

// Remove the front item on the queue without checking if the queue is empty.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue_i (void)
{
	LQUEUE_NODE *tmp = tail_;
	tail_= tail_->prev_;
	tail_->next_ = tmp->next_;
	delete tmp;
	--count_;
}

// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue (void)
{
	if(is_empty())
		throw Underflow();
	dequeue_i();
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <typename T, typename LQUEUE_NODE> T 
LQueue<T, LQUEUE_NODE>::front (void) const
{
	if(is_empty())
		throw Underflow();
	return tail_->next_->item_;
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_empty (void) const 
{
	return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_full (void) const 
{
	return false;
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::begin (void)
{
	return LQueue_Iterator<T, LQUEUE_NODE>(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::end (void)
{
	return LQueue_Iterator<T,LQUEUE_NODE>(tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::begin (void) const
{
	return Const_LQueue_Iterator<T, LQUEUE_NODE>(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::end (void) const
{
	return Const_LQueue_Iterator<T, LQUEUE_NODE>(tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void)
{
	return LQueue_Reverse_Iterator<T, LQUEUE_NODE>(tail_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void)
{
	return LQueue_Reverse_Iterator<T, LQUEUE_NODE>(tail_->next_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void) const
{
	return Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>(tail_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void) const
{
	return Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>(tail_->next);
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void)
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
	this->pos_ = pos_->next_;
	return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
	LQueue_Iterator<T,LQUEUE_NODE> tmp (*this);
	++*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
	this->pos_ = pos_->prev_;
	return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) 
{
	LQueue_Iterator<T,LQUEUE_NODE> tmp (*this);
	--*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
	return pos_ == rhs.pos_;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE>::LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) const
{
	this->pos_ = pos_->next_;
	return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) const
{
	Const_LQueue_Iterator<T,LQUEUE_NODE> tmp (*this);
	++*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void) const
{
	this->pos_ = pos_->prev_;
	return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) const
{
	Const_LQueue_Iterator<T,LQUEUE_NODE> tmp (*this);
	--*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
	return pos_ == rhs.pos_;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::Const_LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void)
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
	this->pos_ = pos_->prev_;
	return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> 
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
	LQueue_Reverse_Iterator<T,LQUEUE_NODE> tmp (*this);
	--*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
	this->pos_ = pos_->next_;
	return *this;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
	LQueue_Reverse_Iterator<T,LQUEUE_NODE> tmp (*this);
	++*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
	return pos_ == rhs.pos_;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
	return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) const
{
	this->pos_ = pos_->prev_;
	return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) const
{
	Const_LQueue_Reverse_Iterator<T,LQUEUE_NODE> tmp (*this);
	--*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void) const
{
	this->pos_ = pos_->next_;
	return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int) const
{
	Const_LQueue_Reverse_Iterator<T,LQUEUE_NODE> tmp (*this);
	++*this;
	return tmp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
	return pos_ == rhs.pos_;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::Const_LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

#endif /* _LQUEUE_CPP */
