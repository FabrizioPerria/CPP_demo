/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Traversal_Strategy_Impl_CPP)
#define _Traversal_Strategy_Impl_CPP

#include <iostream>
#include <stack>
#include "Traversal_Strategy_Impl.h"
#include "Options.h"
#include "Node.h"
#include "Queue.h"
#include "Typedefs.h"

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
Traversal_Strategy_Impl::Traversal_Strategy_Impl ()
  : use_ (1)
{
}

// This needs to be virtual so that subclasses are correctly destroyed.
Traversal_Strategy_Impl::~Traversal_Strategy_Impl ()
{
}

// Ctor
Level_Order_Traversal_Strategy::Level_Order_Traversal_Strategy ():
  queue_(make_queue_strategy(Options::instance()->queue_type()))
{
}

// Dtor
Level_Order_Traversal_Strategy::~Level_Order_Traversal_Strategy ()
{
  // auto_ptr takes care of queue deletion
}

// Traverse the tree in level order.
void
Level_Order_Traversal_Strategy::traverse (const TREE &root)
{
    queue_->enqueue(root);
    while (!queue_->is_empty()){
        TREE tmp = queue_->front();
        queue_->dequeue();
        if (!tmp.is_null()){
            std::cout << tmp.item()<< " ";
            if (!tmp.left().is_null())
                queue_->enqueue(tmp.left());
            if (!root.right().is_null())
                queue_->enqueue(tmp.right());
        }
    }
}

// A Factory method for creating queues.
QUEUE *
Level_Order_Traversal_Strategy::make_queue_strategy (const std::string &queue_type)
{
    return new LQUEUE_ADAPTER(30);
}

// Traverse the tree in preorder.
void
Pre_Order_Traversal_Strategy::traverse (const TREE &root)
{
    if(root.is_null())
        return;
    std::cout << root.item() << " ";
    traverse(root.left());
    traverse(root.right());
}

// Traverse the tree in postorder.
void
Post_Order_Traversal_Strategy::traverse (const TREE &root)
{
    if(root.is_null())
        return;
    traverse(root.left());
    traverse(root.right());
    std::cout << root.item() << " ";
}

// Traverse the tree in inorder.
void
In_Order_Traversal_Strategy::traverse (const TREE &root)
{
    std::stack<TREE> stack_;
    TREE tmp = root;
    bool done = false;

    while(!done){
        if(!tmp.left().is_null()) {
            stack_.push(tmp);
            tmp = tmp.left();
        } else {
            if(!stack_.empty()){
                std::cout << tmp.item() << " ";
                tmp = stack_.top();
                stack_.pop();
                std::cout << tmp.item() << " ";
                tmp = tmp.right();
            } else {
                std::cout << tmp.item() << " ";
                done = true;
            }
        }
    }
    /*
     with recursion
    if (!root.left().is_null()){
        traverse(root.left());
    }
    std::cout << root.item() << " ";
    if (!root.right().is_null())
        traverse(root.right());

        */
}

// Traverse the tree in inorder.
void
Null_Traversal_Strategy::traverse (const TREE &)
{
  // no-op
}

#endif /* _Traversal_Strategy_Impl_CPP */
