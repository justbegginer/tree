//
// Created by user.v2.0 on 18.02.2021.
//
#pragma once
#ifndef STACK_STACK_H
#define STACK_STACK_H


template <class T>
class Stack
{
public:
    virtual ~Stack() {}
    virtual void push(const T& e) = 0; // Добавление элемента в стек
    virtual T pop() = 0; // Удаление и возвращение верхнего элемента.
// Если элементов нет, может возникнуть StackUnderflow
    virtual bool isEmpty() = 0; // Проверка стека на пустоту
};

#endif //STACK_STACK_H
