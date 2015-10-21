/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_Factory_CPP)
#define _Tree_Factory_CPP

#include "Tree_Factory.h"
#include "Tree_Factory_Impl.h"
#include "Traversal_Strategy_Impl.h"
#include "Options.h"

// Default constructor.
Tree_Factory::Tree_Factory (void)
{
}

// Copy ctor - needed for reference counting.
Tree_Factory::Tree_Factory (const Tree_Factory &f):
    factory_impl_(f.factory_impl_)
{
}

/// Assignment operator - needed for reference counting.
void
Tree_Factory::operator= (const Tree_Factory &f)
{
      factory_impl_ = f.factory_impl_;
}

// Destructor.
Tree_Factory::~Tree_Factory ()
{
}

// Method to create the binary tree to traverse.
TREE
Tree_Factory::make_tree ()
{
  // You fill in here to create an expression tree for the expression -5 * (3+4).
    NODE *t1 = new NODE ('5');
    NODE *t2 = new NODE ('-',t1);
    NODE *t3 = new NODE ('3');
    NODE *t4 = new NODE ('4');
    NODE *t5 = new NODE ('+',t3,t4);
    return TREE ('*', t2, t5);
}

// Pass method call to implementation for strategy creation.
Traversal_Strategy
Tree_Factory::make_traversal_strategy ()
{
    return Traversal_Strategy(new Level_Order_Traversal_Strategy());
}

#endif /* _Tree_Factory_CPP */
