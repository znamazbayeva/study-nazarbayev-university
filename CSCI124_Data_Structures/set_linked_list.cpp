//
//  main.cpp
//  assign5
//
//  Created by macbook on 7/11/19.
//  Copyright © 2019 team9. All rights reserved.
//

#include <iostream>
#include "set_linked_list.h"


// Copy constructor
set::set (const set& q):    set_size ( q.set_size ), head( nullptr )
{
    node *N = q.head;
    while(N)
    {
        node* copy = new node(N->value);
        node *it;
        if(!head)
        {
            head = copy;
            it = head;
        }
        else
        {
            it->next = copy;
            copy->prev = it;
            it = copy;
        }
        N = N->next;
    }
}

// Initializer list constructor
set::set (std::initializer_list<int> ilist):
set_size( 0 ),
head( nullptr )

{
    for( auto N : ilist )
        insert(N);
}

// Copy assignment
set& set::operator=(const set& q)
{
    //self assignment:
    if( this != &q )
    {
        //clear *this:
        clear();
        //copy, i.e. insert nodes
        node *N = q.head;
        while(N)
        {
            insert(N->value);
            N = N->next;
        }
    }
    return* this;
}



// Insert an item into the set.
void set::insert (int val)
{
    node* val_node = new node(val);
    node* cur = head;
    
    if(!head)
        head = val_node;
    else if(val < cur->value)
    {
        val_node->next = cur;
        cur->prev = val_node;
        head = val_node;
    }
    else
    {
        while(cur)
        {
            node* next = cur->next;
            if(val == cur->value)
            {
                delete val_node;
                return;
            }
            else if( (!next) && (val > cur->value) )
            {
                cur->next = val_node;
                val_node->prev = cur;
                break;
            }
            else if( (val < next->value) && (val > cur->value) )
            {
                
                cur->next = val_node;
                val_node->prev = cur;
                val_node->next = next;
                next->prev = val_node;
                break;
            }
            else cur = next;
        }
    }
    set_size++;
}


// Searches for an item in the set.
// If found, returns the node containing val; otherwise returns nullptr.
set::node* set::find (int val)
{
    node* N = head;
    while(N)
    {
        if(N->value == val)
            return N;
        N = N->next;
    }
    return nullptr;
}

// Erases the node "it" from the set.
void set::erase (node *it)
{
    if(it != nullptr)
    {
        node* before_it = it->prev;
        node* after_it = it->next;
        
        if(!before_it)
            head = after_it;
        else if(!after_it)
            before_it->next = nullptr;
        else
        {
            before_it->next = after_it;
            after_it->prev = before_it;
        }
        delete it;
        set_size -= 1 ;
    }
}

// Remove everything from the set
void set::clear()
{
    set_size = 0;
    node *N = head;
    while(N)
    {
        node* after_N = N->next;
        head = after_N;
        delete N;
        N = after_N;
    }
}

// Returns the number of items in the set
size_t set::size() const
{
    return set_size;
}

// Returns whether or not the set is currently empty
bool set::empty() const
{
    return set_size==0;
}

// Returns a pointer to the first node in the set.
set::node* set::begin () const
{
    return head;
}


// Destructor
set::~set()
{
    node *N = head;
    
    while(N)
    {
        node* after_N = N->next;
        head = after_N;
        delete N;
        N = after_N;
    }
}


