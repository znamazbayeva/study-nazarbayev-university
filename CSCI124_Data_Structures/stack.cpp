#include <iostream>
#include <deque>
#include "stack.h"
#include <math.h>
#include <stdexcept>

int tests_run = 0;
int tests_correct = 0;

// Copy constructor
stack::stack(const stack& stk):
values(new int[stk.array_capacity]),
stack_size(stk.stack_size),
array_capacity(stk.array_capacity)
{
    for (size_t num = 0; num < stk.stack_size; num++)
    {
        values[num] = stk.values[num];
    }
    
}

// Initializer list constructor
stack::stack(std::initializer_list<int> ilist):
values(new int[ilist.size()]),
stack_size(ilist.size()),
array_capacity(ilist.size())


{
    size_t i = 0;
    for (int val : ilist) {
        values[i] = val;
        ++i;
    }
}

// Copy assignment
stack& stack::operator=(const stack& stk){
    
    if (array_capacity != stk.array_capacity)
    {
        stack_size = stk.stack_size;
        delete [] values;
        values = new int[stk.array_capacity];
        array_capacity = stk.array_capacity;
        for (size_t i = 0; i < stk.stack_size; i++)
        {
            values[i] = stk.values[i];
        }
    }
    else {
        for (size_t num = 0; num < stk.stack_size; num++) {
            values[num] = stk.values[num];
        }
        if(this == &stk){
            return *this;
        }
       
    }
     return *this;
}

    



// Insert an item at the top of the stack
void stack::push(int val)
{
    if (stack_size == array_capacity) {
        int *new_values;
        new_values = new int[array_capacity*2];
        
        for (int i = 0; i < array_capacity; i++) {
            new_values[i] = values[i];
        }
        values = new_values;
        array_capacity *= 2;

    }

    values[stack_size] = val;
        ++stack_size;
    
}

// Returns the value of the topmost item of the stack;
// throws an exception if the stack is empty
int stack::peek() const
{
    if (stack_size == 0) {
        throw std::invalid_argument("Nothing over there");
    }
    return values[stack_size -1];
}

// Remove the topmost item from the stack
// throws an exception if the stack is empty
void stack::pop()
{
    if (stack_size == 0) {
        throw std::invalid_argument{"It is already emty"};
    }
    stack_size--;
}

// Remove everything from the stack
void stack::clear()
{
    if (stack_size == 0) {
        throw std::invalid_argument("ALREADY EMPTY");
    }
    stack_size = 0;
}

// Returns the number of items on the stack
size_t stack::size() const
{
    return stack_size;
}

// Returns whether or not the stack is currently empty
bool stack::empty() const
{
    return (stack_size == 0);
}

// Print out the contents of the stack
// kerek emes void stack::print(std::ostream& out) const;

// Destructor
stack::~stack() {
    delete [] values;
}

void checkBool( const std::string &s, const bool&  given, const bool& correct )
{
    tests_run++;
    if( given != correct )
    {
        std::cout << "~INCORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
    } else {
        std::cout << "~CORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
        tests_correct++;
    }
}

void checkSizet( const std::string &s, const size_t&  given, const size_t& correct )
{
    tests_run++;
    if( given != correct )
    {
        std::cout << "~INCORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
    } else {
        std::cout << "~CORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
        tests_correct++;
    }
}

void checkDouble( const std::string &s, const double&  given, const double& correct )
{
    tests_run++;
    if( abs(given - correct) > 0.1 )
    {
        std::cout << "~INCORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
    } else {
        std::cout << "~CORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
        tests_correct++;
    }
}

void checkString( const std::string s, const std::string&  given, const std::string& correct )
{
    tests_run++;
    if( given != correct )
    {
        std::cout << "~INCORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
    } else {
        std::cout << "~CORRECT " << s << " : " << given <<
        " SHOULD HAVE BEEN " << correct << "\n";
        tests_correct++;
    }
}


int main(){
    std::string message = "DEFAULT CONSTRUCTOR";
    stack defst;
    std::deque<int> defdq;
    checkSizet(message, defst.size(), defdq.size());
    checkBool(message, defst.empty(), 1);
    
    try{
        tests_run++;
        defst.peek();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    message = "INIT_LIST CONSTRUCTOR";
    stack initst = {1,3,5,7,9,11,13};
    std::deque<int> initdq {1,3,5,7,9,11,13};
    checkSizet(message, initst.size(), initdq.size());
    checkBool(message, initst.empty(), 0);
    checkSizet(message, initst.peek(), initdq.back());
    
    message = "COPY CONSTRUCTOR";
    stack copyst {initst};
    std::deque<int> copydq {initdq};
    checkSizet(message, copyst.size(), copydq.size());
    checkBool(message, copyst.empty(), 0);
    
    message = "PUSH and POP";
    
    for(int i = 1; i < 20000; i *= 2){
        defst.push(i);
        defdq.push_back(i);
    }
    
    while(!defdq.empty()){
        checkSizet(message, defst.peek(), defdq.back());
        checkSizet(message, defst.size(), defdq.size());
        defst.pop();
        defdq.pop_back();
    }
    
    try{
        tests_run++;
        defst.peek();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    try{
        tests_run++;
        defst.pop();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    message = "ASSIGNMENT OPERATOR";
    
    defst = initst;
    defdq = initdq;
    
    for(int i = 1; i > -23; i -= 2){
        defst.push(i);
        defdq.push_back(i);
    }
    
    
    
    copyst = defst;
    copydq = defdq;
    
    while(!defdq.empty()){
        checkSizet(message, defst.peek(), defdq.back());
        checkSizet(message, defst.size(), defdq.size());
        defst.pop();
        defdq.pop_back();
    }
    
    try{
        tests_run++;
        defst.peek();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    try{
        tests_run++;
        defst.pop();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    message = "SELF ASSIGNMENT";
    for(size_t i = 0; i < 3; i++){
        copyst.pop();
        copydq.pop_back();
    }
    
    checkSizet(message, copyst.peek(), copydq.back());
    checkSizet(message, copyst.size(), copydq.size());
    
    message = "CLEAR";
    copyst.clear();
    copydq.clear();
    
    checkSizet(message, copyst.size(), copydq.size());
    
    try{
        tests_run++;
        copyst.peek();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    try{
        tests_run++;
        copyst.pop();
        std::cout << "~INCORRECT " << message << " : EXCEPTION HAS NOT BEEN CAUGHT\n";
    } catch ( ... ) {
        tests_correct++;
        std::cout << "~CORRECT " << message << " : EXCEPTION HAS BEEN CAUGHT\n";
    }
    
    copyst.push(42);
    copydq.push_back(42);
    
    message = "WHAT'S MEANING OF LIFE?";
    
    checkSizet(message, copyst.peek(), copydq.back());
    
    std::cout << "\nTESTS RUN: " << tests_run << std::endl;
    std::cout << "\nTESTS CORRECT: " << tests_correct << std::endl;
    return 0;
}

