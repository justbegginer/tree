//
// Created by user.v2.0 on 18.02.2021.
//

#ifndef STACK_STACKUNDERFLOW_H
#define STACK_STACKUNDERFLOW_H
#include <iostream>
class StackUnderflow : public std::exception
{
public:
    StackUnderflow() : reason("Stack Underflow") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};
#endif //STACK_STACKUNDERFLOW_H
