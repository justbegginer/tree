//
// Created by user.v2.0 on 18.02.2021.
//

#ifndef STACK_STACKARRAY_H
#define STACK_STACKARRAY_H
#include "iostream"
#include "stack.h"
#include "StackOverflow.h"
#include "StackUnderflow.h"
#include "WrongStackSize.h"
template <typename T>
class StackArray : public Stack<T> {
public:
    explicit StackArray(int size = 100) :size_(size) , top_(0) , array_(new T[size]){} // size задает размер стека "по умолчанию"
    StackArray(const StackArray<T>& src);
    StackArray(StackArray<T>&& src) noexcept ;
    StackArray<T>& operator=(const StackArray<T>& src) noexcept;
    StackArray<T>& operator=(StackArray<T>&& src) noexcept ;
    virtual ~StackArray();
    void push(const T& e);
    T pop();
    T getTop();
    bool isEmpty() {return top_ == 0;}
    bool isFull() {return  top_-1 == size_;}
private:
    T* array_; // массив элементов стека: !!! array_[0] – не используется, top_ от 1 до size_
    size_t top_ ; // вершина стека, элемент занесенный в стек последним
    size_t size_; // размер стека
    void swap(StackArray<T>& src);
};

template<typename T>
StackArray<T>::StackArray(StackArray<T> &&src) noexcept{
    this->swap(src);
}

template<class T>
StackArray<T> &StackArray<T>::operator=(StackArray<T> &&src) noexcept{
    this->swap(src);
    return *this;
}

template<class T>
StackArray<T>::~StackArray() {
    delete array_;
}

template<class T>
void StackArray<T>::push(const T &e) {
    if (top_ == 100)
        throw StackOverflow();
    top_++;
    *(array_+top_ - 1)  = e;
}

template<class T>
T StackArray<T>::pop() {
    if (top_ == 0)
        throw StackUnderflow();
    T top_element = *(array_+ top_ - 1);
    top_--;
    return top_element;
}

template<class T>
void StackArray<T>::swap(StackArray<T> &src) {
    size_ = src.size_;
    array_ = new T[size_];
    for (int i = 0; i <= src.top_; ++i) {
        *(this->array_ + i) = *(src.array_ + i);
    }
    top_ = src.top_;
    //delete src;
}

template<typename T>
StackArray<T> &StackArray<T>::operator=(const StackArray<T> &src) noexcept{
    StackArray<T> temp (src);
    this->swap(temp);
    return *this;
}

template<typename T>
StackArray<T>::StackArray(const StackArray<T> &src) {
    StackArray<T> temp(src);
    this->swap(temp);
}

template<typename T>
T StackArray<T>::getTop() {
    return top_;

}


#endif //STACK_STACKARRAY_H
