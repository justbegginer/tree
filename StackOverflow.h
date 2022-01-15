//
// Created by user.v2.0 on 18.02.2021.
//

#ifndef STACK_STACKOVERFLOW_H
#define STACK_STACKOVERFLOW_H
#include <iostream>
class StackOverflow : public std::exception
{
public:
    StackOverflow() : reason("Stack Overflow") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};
#endif //STACK_STACKOVERFLOW_H
