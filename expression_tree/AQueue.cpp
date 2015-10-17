/***************************************
 Class: CS251
 Assignment Number: 3
 Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
 ***************************************/

/**
 * @class AQueue
 * @brief Defines a generic "first-in/first-out" (FIFO) Abstract Data Type (ADT) using an Array
 *        that is organized as a "circular queue."
 */

#if !defined (_AQUEUE_C)
#define _AQUEUE_C

#include "AQueue.h"

// Returns the current number of elements in the queue.

template <typename T, typename ARRAY>
size_t
AQueue<T, ARRAY>::size (void) const
{
    return this->count_;
}

// Constructor.

template <typename T, typename ARRAY>
AQueue<T, ARRAY>::AQueue (size_t size) : queue_(ARRAY(size)), head_(0), tail_(0), count_(0)
{
}

// Copy constructor.

template <typename T, typename ARRAY>
AQueue<T, ARRAY>::AQueue (const AQueue<T, ARRAY> &rhs) : queue_(rhs.queue_),
                                                        head_(rhs.head_),
                                                        tail_(rhs.tail_),
                                                        count_(rhs.count_)
{
}

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::swap (AQueue<T, ARRAY> &new_aqueue)
{
    this->queue_.swap(new_aqueue.queue_);
    std::swap(new_aqueue.head_, this->head_);
    std::swap(new_aqueue.tail_, this->tail_);
    std::swap(new_aqueue.count_, this->count_);
}

// Assignment operator.
template <typename T, typename ARRAY>
AQueue<T, ARRAY>&
AQueue<T, ARRAY>::operator= (const AQueue<T, ARRAY> &rhs)
{
    if(*this != rhs){
        AQueue tmp(rhs);
        swap(tmp);
    }
    return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename ARRAY>
AQueue<T, ARRAY>::~AQueue (void)
{
    // There's nothing to do here since we didn't dynamically
    // allocate any memory. The queue_ dtor handles that.
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::operator== (const AQueue<T, ARRAY> &rhs) const
{
    if(head_ != rhs.head_ || tail_ != rhs.tail_ || count_ != rhs.count_)
        return false;
    else
        return queue_ == rhs.queue_;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::operator!= (const AQueue<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::enqueue (const T &new_item)
{
    if (this->is_full())
        throw Overflow();
    this->queue_[this->tail_] = new_item;
    this->tail_ = increment(this->tail_);
    ++count_;
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::dequeue (void)
{
    if (this->is_empty())
        throw Underflow();
    this->head_ = increment(this->head_);
    --count_;
}

// Returns the front queue item without removing it.  Throws the
// <Underflow> exception if the queue is empty.

template <typename T, typename ARRAY>
T
AQueue<T, ARRAY>::front (void) const
{
    if (this->is_empty())
        throw Underflow();
    return this->queue_[this->head_];
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::is_empty (void) const
{
    return this->count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::is_full (void) const
{
    return this->count_ == this->queue_.size();
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::begin (void)
{
    return AQueue_Iterator<T, ARRAY>(*this,this->head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::end (void)
{
    return AQueue_Iterator<T, ARRAY>(*this,this->tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator
AQueue<T, ARRAY>::begin (void) const
{
    return Const_AQueue_Iterator<T, ARRAY>(*this,this->head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator
AQueue<T, ARRAY>::end (void) const
{
    return Const_AQueue_Iterator<T, ARRAY>(*this,this->tail_);
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator
AQueue<T, ARRAY>::rbegin (void)
{
    size_t tmp = decrement(this->tail_);
    return AQueue_Reverse_Iterator<T, ARRAY>(*this,tmp);
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator
AQueue<T, ARRAY>::rend (void)
{
    size_t tmp = decrement(this->head_);
    return AQueue_Reverse_Iterator<T, ARRAY>(*this,tmp);
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rbegin (void) const
{
    size_t tmp = decrement(this->tail_);
    return Const_AQueue_Reverse_Iterator<T, ARRAY>(*this,tmp);
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rend (void) const
{
    size_t tmp = decrement(this->head_);
    return Const_AQueue_Reverse_Iterator<T, ARRAY>(*this,tmp);
}

/// Calculate the appropriate index when incrementing.
template <typename T, typename ARRAY>
size_t
AQueue<T, ARRAY>::increment (size_t index) const
{
    if (index + 1 >= this->queue_.size())
        return 0;
    else
        return index + 1;
}

/// Calculate the appropriate index when decrementing.
template <typename T, typename ARRAY>
size_t
AQueue<T, ARRAY>::decrement (size_t index) const
{
    if (index == 0)
        return this->queue_.size();
    else
        return index - 1;
}

template <typename T, typename ARRAY>
T &
AQueue_Iterator<T, ARRAY>::operator* (void)
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T &
AQueue_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_->queue_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> &
AQueue_Iterator<T, ARRAY>::operator++ (void)
{
    pos_=aqueue_ref_.increment(pos_);
    return *this;
}

// Post-increment.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>
AQueue_Iterator<T, ARRAY>::operator++ (int)
{
    AQueue_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.increment(pos_);
    return tmp;

}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> &
AQueue_Iterator<T, ARRAY>::operator-- (void)
{
    pos_=aqueue_ref_.decrement(pos_);
    return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>
AQueue_Iterator<T, ARRAY>::operator-- (int)
{
    AQueue_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.decrement(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
bool
AQueue_Iterator<T, ARRAY>::operator== (const AQueue_Iterator<T, ARRAY> &rhs) const
{
    if (pos_!=rhs.pos_)
        return false;
    else
        return aqueue_ref_ == rhs.aqueue_ref_;
}

template <typename T, typename ARRAY>
bool
AQueue_Iterator<T, ARRAY>::operator!= (const AQueue_Iterator<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>::AQueue_Iterator (AQueue<T, ARRAY> &queue_ref,
                                            size_t pos) :
                                            aqueue_ref_(queue_ref),
                                            pos_(pos)

{
}

template <typename T, typename ARRAY>
const T &
Const_AQueue_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator++ (void) const
{
    pos_=aqueue_ref_.increment(pos_);
    return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator++ (int) const
{
    Const_AQueue_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.increment(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator-- (void) const
{
    pos_=aqueue_ref_.decrement(pos_);
    return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator-- (int) const
{
    AQueue_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.decrement(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Iterator<T, ARRAY>::operator== (const Const_AQueue_Iterator<T, ARRAY> &rhs) const
{
    if (pos_!=rhs.pos_)
        return false;
    else
        return aqueue_ref_ == rhs.aqueue_ref_;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Iterator<T, ARRAY>::operator!= (const Const_AQueue_Iterator<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>::Const_AQueue_Iterator (const AQueue<T, ARRAY> &queue_ref,
                                                        size_t pos) :
                                                        aqueue_ref_(queue_ref),
                                                        pos_(pos)
{
}

template <typename T, typename ARRAY>
T &
AQueue_Reverse_Iterator<T, ARRAY>::operator* (void)
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T &
AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> &
AQueue_Reverse_Iterator<T, ARRAY>::operator++ (void)
{
    pos_=aqueue_ref_.decrement(pos_);
    return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::operator++ (int)
{
    AQueue_Reverse_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.decrement(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> &
AQueue_Reverse_Iterator<T, ARRAY>::operator-- (void)
{
    pos_=aqueue_ref_.increment(pos_);
    return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::operator-- (int)
{
    AQueue_Reverse_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.increment(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
bool
AQueue_Reverse_Iterator<T, ARRAY>::operator== (const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
    if (pos_!=rhs.pos_)
        return false;
    else
        return aqueue_ref_ == rhs.aqueue_ref_;
}

template <typename T, typename ARRAY>
bool
AQueue_Reverse_Iterator<T, ARRAY>::operator!= (const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::AQueue_Reverse_Iterator (AQueue<T, ARRAY> &queue_ref,
                                                            size_t pos)  :
                                                            aqueue_ref_(queue_ref), pos_(pos)
{
}

template <typename T, typename ARRAY>
const T &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (void) const
{
    pos_=aqueue_ref_.decrement(pos_);
    return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (int) const
{
    Const_AQueue_Reverse_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.decrement(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (void) const
{
    pos_=aqueue_ref_.increment(pos_);
    return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (int) const
{
    Const_AQueue_Reverse_Iterator<T,ARRAY> tmp(*this);
    pos_=aqueue_ref_.increment(pos_);
    return tmp;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator== (const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
    if (pos_!=rhs.pos_)
        return false;
    else
        return aqueue_ref_ == rhs.aqueue_ref_;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator!= (const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::Const_AQueue_Reverse_Iterator (const AQueue<T, ARRAY> &queue_ref,
                                                                        size_t pos)  :
                                                                        aqueue_ref_(queue_ref),pos_(pos)
{
}

#endif /* _AQUEUE_C */
