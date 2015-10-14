/***************************************
 Class: CS251
 Assignment Number: 1
 Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
 ***************************************/

// Check if the index is in range.

INLINE bool
Array::in_range (size_t index) const
{
    return index < this->max_size_;
}

// Returns the length of the array.

INLINE size_t
Array::size (void) const
{
    return this->cur_size_;
}

// Returns a reference to the <index> element in the <Array> without
// checking for range errors.

INLINE  const T &
Array::operator[] (size_t index) const
{
    return *(this->array_ + index);
}

// Set an item in the array at location index without
// checking for range errors.

INLINE T &
Array::operator[] (size_t index)
{
    return *(this->array_ + index);
}