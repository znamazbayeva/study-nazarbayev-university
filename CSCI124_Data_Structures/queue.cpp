#include <iostream>
#include "queue.h"

// Creates an empty queue
queue::queue(){
    front = nullptr;
    back = nullptr;
    queue_size = 0;
}

// Copy constructor
queue::queue(const queue& q){
    front = nullptr;
    back = nullptr;
    node* new_node = q.front;
    queue_size = q.queue_size;
    while (new_node){
        node* new_back = new node (new_node -> value);
        if (!front){
            front = new_back;
        } else {
            back -> next = new_back;
        }
        back = new_back;
        new_node = new_node -> next;
        new_back = nullptr;
    }
    
    new_node = nullptr;
}

// Initializer list constructor
queue::queue(std::initializer_list<int> ilist){
    front = nullptr;
    back = nullptr;
    queue_size = ilist.size();
    for (auto i : ilist){
        node* new_back = new node(i);
        if (!front){
            front = new_back;
        } else {
            back -> next = new_back;
        }
        back = new_back;
    }
}


// Copy assignment
queue& queue::operator=(const queue& q){
    if(queue_size==q.queue_size){
		node* q_node = q.front;
		node* node=front;
		while(q_node!=nullptr){

			node->value=q_node->value;
			node=node->next;
			q_node=q_node->next;
		}
    } else {
        clear();
        node* new_node = q.front;
        while (new_node){
            node* new_back = new node(new_node->value);
            if (!front){
                front = new_back;
            } else {
                back -> next = new_back;
            }
            back = new_back;
            new_node = new_node -> next;
            new_back = nullptr;
        }
        queue_size = q.queue_size;
        new_node = nullptr;
    }
    return *this; 
}

// Insert an item at the back of the queue
void queue::push(int val){
    node* new_back = new node (val);
    if (!front){
        front = new_back;
        back = new_back;
    } else {
        back -> next = new_back;
    }
    back = new_back;
    ++queue_size;
}

// Returns the value of the front-most item of the queue;
// throws an exception if the queue is empty
int queue::peek() const{
    if(this -> empty()){
        throw std::invalid_argument("404. queue not found");
    }
    return front -> value;
}

// Remove the front-most item from the queue
// throws an exception if the queue is empty
void queue::pop(){
    if(!front){
        throw std::invalid_argument("404. queue not found");
        // throw an exception
    }
    node* cur = front;
    front = front -> next;
    delete cur;
    queue_size --;
}

// Remove everything from the queue
void queue::clear(){
    while (front){
        pop();
    }
    front = nullptr;
    back = nullptr;
    queue_size = 0;
}

// Returns the number of items on the queue
size_t queue::size() const {
    return queue_size;
}

// Returns whether or not the queue is currently empty
bool queue::empty() const {
    return !queue_size;
}


// Merges the given queue x at the end of this -> queue
// and then clears the queue x.
// If x is the same object with this ->  then does nothing.
void queue::merge (queue& x){
    if (this == &x){
        return;
    } else if (!x.front){
        return;
    } else if (!front){
        front = x.front;
        back = x.back;
        queue_size = x.queue_size;
        x.queue_size=0;
        x.front = nullptr;
        x.back = nullptr;
    } else {
        back-> next = x.front;
        back = x.back;
        queue_size += x.queue_size;
        x.front = x.back = nullptr;
        x.queue_size = 0;
    }
}

// Destructor
queue::~queue(){
    clear();
}