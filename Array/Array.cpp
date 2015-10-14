/***************************************
 Class: CS251
 Assignment Number: 1
 Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
 ***************************************/

#ifndef ARRAY_C
#define ARRAY_C

#include <stdexcept>    //std::out_of_range
#include <new>          //std::bad_alloc
#include <array>        //std::out_of_range
#include <algorithm>    //std::fill, std::copy

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

Array::Array (size_t size)
{
    try {
        this->array_ = new T[size]();
    } catch (std::bad_alloc) {
        throw std::bad_alloc();
    }
    this->max_size_ = size;
    this->cur_size_ = size;
}

// Dynamically initialize an array.

Array::Array (size_t size, const T &default_value)
{
    try {
        this->array_ = new T[size]();
    } catch (std::bad_alloc) {
        throw std::bad_alloc();
    }
    std::fill(this->array_, this->array_ + size, default_value);
    this->max_size_ = size;
    this->cur_size_ = size;
}

// The copy constructor (performs initialization).

Array::Array (const Array &s)
{
    try {
        this->array_ = new T[s.size()]();
    } catch (std::bad_alloc) {
        throw std::bad_alloc();
    }
    std::copy(s.array_, s.array_ + s.size(), this-> array_);
    this->max_size_ = s.size();
    this->cur_size_ = s.size();
}

// Compare this array with <s> for equality.

bool
Array::operator== (const Array &s) const
{
    if (this->max_size_ == s.size()){
        for (int i=0; i < s.size(); i++){
            if (this->array_[i] != s.array_[i])
                return false;
        }
        return true;
    }
    return false;
}

// Compare this array with <s> for inequality.

bool
Array::operator!= (const Array &s) const
{
    bool different = false;
    if (this->max_size_ == s.size()){
        for (int i=0; i < this->max_size_; i++){
            if (this->array_[i] != s.array_[i])
                different = true;
        }
        return different;
    }
    return true;
}

// Assignment operator (performs assignment).

Array &
Array::operator= (const Array &s)
{
    if (this-> max_size_ < s.size()){
        delete [] this->array_;
        try {
            this->array_ = new T[s.size()]();
            this->max_size_ = s.size();
        } catch (std::bad_alloc) {
            throw std::bad_alloc();
        }
    }
    this->cur_size_ = s.size();
    
    std::copy(s.array_, s.array_ + s.size(), this-> array_);
    
    return *this;
}

// Clean up the array (e.g., delete dynamically allocated memory).

Array::~Array (void)
{
    delete[] this->array_;
}

// = Set/get methods.

// Set an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::set (const T &new_item, size_t index)
{
    if (!this->in_range(index))
        throw std::out_of_range("Set failed");
    
    this->array_[index] = new_item;
    if (this->cur_size_ < index)
        this->cur_size_ = index;
}

// Get an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::get (T &item, size_t index) const
{
    if (!this->in_range(index))
        throw std::out_of_range("Get failed");
    
   item = this->array_[index];
}

#endif /* ARRAY_C */