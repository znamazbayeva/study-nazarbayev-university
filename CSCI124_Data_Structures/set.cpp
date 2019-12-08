////
////  main.cpp
////  assign7
////
////  Created by macbook on 7/18/19.
////  Copyright © 2019 team9. All rights reserved.
////
//


#include "set.h"
#include <iostream>
#include <sstream>

// Case insensitive string equality

bool equal(const std::string& s1, const std::string& s2) {
    
    if (s2.length() != s1.length()) {
        
        return false;
        
    }
    
    for (size_t i = 0; i < s1.length(); i++) {
        
        if(tolower(s1[i]) != tolower(s2[i])) {
            
            return false;
            
        }
        
    }
    return true;
    
}


// Hash function for strings

size_t hash(const std::string& s)

{
    
    
    
    size_t hash_value = 0;
    
    
    for (size_t  i = 0; i < s.length(); i++) {
        
        hash_value = hash_value*31 + tolower(s[i]);
        
    }
    
    return hash_value;
    
}


// Copy constructor

set::set(const set& s):

bucket_array(new std::list<std::string>[s.bucket_array_size]),

bucket_array_size(s.bucket_array_size),

set_size(0)


{
    
    size_t i = 0;
    
    while (i < s.bucket_array_size)
        
    {
        
        for (std::list<std::string>::iterator it = s.bucket_array[i].begin();it!=s.bucket_array[i].end();it++)
            
        {
            
            insert(*it);
            
        }
        
        i++;
        
    }
    
}


// Initializer list constructor

set::set(std::initializer_list<std::string> ilist):

bucket_array(new std::list<std::string>[ilist.size()]),

set_size(0),

bucket_array_size(ilist.size())

{
    for (auto word : ilist) {
        insert(word);
    }
}



// Copy assignment

set& set::operator=(const set& s)

{
    
    if (bucket_array_size != s.bucket_array_size) {
        
        bucket_array_size = s.bucket_array_size;
        
        delete [] bucket_array;
        
        bucket_array = new std::list<std::string>[s.bucket_array_size];
        
    }
    
    set_size = 0;
    
    size_t i = 0;
    
    while (i < s.bucket_array_size) {
        
        for (std::list<std::string>::iterator it = s.bucket_array[i].begin();it!=s.bucket_array[i].end();it++)
            
        {

            insert(*it);
            
        }
        
        i++;
        
    }
    
    
    return *this;
    
}


// Insert the given value into the set, if it is not already there.

// Returns true if and only if the value was not already there

bool set::insert(std::string val)

{
    
    double load_factor = loadfactor();
    
    if (contains(val) == true) {
        
        return false;
        
    } else {
        
        if (load_factor >= max_load_factor) {
            
            
            bucket_array_size = bucket_array_size*2;
            
            std::list<std::string>* bucket_array1 = new std::list<std::string>[bucket_array_size];
            
            size_t i = 0;
            
            while (i < bucket_array_size/2) {
                
                for ( std::string s : bucket_array[i])
                    
                {
                    
                    size_t index = hash(s)%bucket_array_size;
                    
                    bucket_array1[index].push_back(s);
                    
                }
                
                i++;
                
            }
            delete [] bucket_array;
            bucket_array = bucket_array1;
            
        }
        
        
        
        size_t bucket_id = hash(val) % bucket_array_size;
        
        bucket_array[bucket_id].push_back(val);
        
        set_size++;
        
        return true;
        
    }
    
    
    
    
    
    
    
}


// Returns true if and only if the value is in the set

bool set::contains(std::string val) const

{
    
    size_t index = hash(val)%bucket_array_size;
    
    for (std::string s : bucket_array[index]) {
        
        if(equal(s,val) == true){
            
            return true;
            
        } }
    
    //    for(it = bucket_array[index].begin();it!=bucket_array[index].end();it++){
    
    //        if(equal(*it,val) == true){
    
    //            return true;
    
    //        }
    
    //    }
    
    return false;
    
}


// Removes the given value from the set, if it is currently there

// Returns true if and only if the value was there to be removed

bool set::remove(std::string val)

{
    
    if (set_size == 0) {
        
        return false;
        
    }
    
    size_t index = hash(val)%bucket_array_size;
    
    if (contains(val) == true) {
        
        std::list<std::string>::iterator it;
        
        for(it = bucket_array[index].begin();it!=bucket_array[index].end();it++){
            
            if(equal(*it,val) == true){
                
                bucket_array[index].remove(*it);
                
                set_size--;
                
                return true;
                
            }
            
        }
        
        return true;
        
    } else
        
    {
        
        return false;
        
    }
    
}


// Remove everything from the set

void set::clear() {
    
    
    
    
    
    size_t i = 0;
    
    while ( i < bucket_array_size){
        
        bucket_array[i].erase(bucket_array[i].begin(), bucket_array[i].end());
        
        i++;
        
    }
    
    set_size = 0;
    
}


// Returns the number of items on the set

size_t set::size() const

{
    
    return set_size;
    
}

set::~set() {
    clear();
    
    delete[] bucket_array;
    
}


// Returns whether or not the set is currently empty

bool set::empty() const {
    
    if (set_size == 0)
        
        return true;
    
    else
        
        return false;
    
}



