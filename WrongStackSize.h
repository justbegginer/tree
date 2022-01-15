//
// Created by user.v2.0 on 14.03.2021.
//

#ifndef STACK_WRONGSTACKSIZE_H
#define STACK_WRONGSTACKSIZE_H
#include <exception>
class WrongStackSize : public std::exception
{
public:
    WrongStackSize() : reason("Wrong Stack Size") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};
#endif //STACK_WRONGSTACKSIZE_H
