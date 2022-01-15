//
// Created by user.v2.0 on 14.03.2021.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
#include <exception>
#include <iostream>
//========================================================================
// Классы QueueOverflow и QueueUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе с очередью
//========================================================================

class QueueOverflow: public std::exception
{
public:
    QueueOverflow() : reason("Queue Overflow") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};

class QueueUnderflow: public std::exception
{
public:
    QueueUnderflow() : reason("Queue Underflow") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};


// =============================================================
//  Шаблон класса Queue представляет понятие абстрактного очередь
//==============================================================

template <class T>
class Queue
{
public:
    virtual ~Queue() {}

    // Абстрактные операции со стеком

    virtual void enQueue(const T& e) = 0; // Добавление элемента в стек

    virtual T deQueue() = 0;// Удаление и возвращение верхнего элемента.
    // Если элементов нет, может возникнуть QueueUnderflow

    virtual bool isEmpty() const = 0; // Проверка на пустоту

};


//==============================================================
// Исключительная ситуация WrongQueueSize может возникнyть,
// если в конструкторе очереди неправильно задан размер.
//==============================================================

class WrongQueueSize : public std::exception
{
public:
    WrongQueueSize() : reason("Queue Stack Size") {}
    const char* what() const noexcept { return reason; }
private:
    const char* reason;
};



//==============================================================
// Шаблон класса QueueArray - реализация ограниченной очереди.
// Элементы очереди помещаются в массив.
//==============================================================

template <typename T>
class QueueArray final : public Queue<T> // модификатор final запрещает наследование от класса
{
public:
    explicit QueueArray(size_t size = 100);  // size задает размер "по умолчанию"
    QueueArray(const QueueArray<T>& src) = delete;
    QueueArray(QueueArray<T>&& src) noexcept ;  //

    QueueArray<T>& operator= (QueueArray<T>&& src); // оператор перемещающего присваивания

    ~QueueArray() override { delete[] array_; }

    void enQueue(const T& e) override;
    T deQueue() override;
    bool isEmpty() const override { return head_  == tail_; }


private:
    T* array_;         // массив элементов очереди
    size_t head_ = 1;  // Очередь пуста, если  head[Q] = tail[Q].
    size_t tail_ = 1;  // Первоначально: head[Q] = tail[Q] = 1;
    size_t size_;      // размер очереди
    void swap(QueueArray<T> &right);
};

template <typename T>
QueueArray<T>::QueueArray(size_t size):
    size_(size), head_ (1), tail_ (1)
{
    try {
        array_ = new T[size];// пытаемся заказать память под элементы очереди...
    }
    catch (...) {
        throw WrongQueueSize();
    }
}

template <typename T>
void QueueArray<T>::swap(QueueArray<T>& right)
{
    std::swap(this->array_, right.array_);
    std::swap(this->head_, right.head_);
    std::swap(this->tail_, right.tail_);
    std::swap(this->size_, right.size_);
}
template <typename T>
QueueArray<T>::QueueArray(QueueArray<T>&& src) noexcept
{
    this->swap(src);
}

template <typename T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T>&& src)
{
    this->swap(src);
}

template <typename T>
void QueueArray<T>::enQueue(const T& e)
{
    if (tail_ + 1 == head_)
        throw QueueOverflow(); // нет места для нового элемента
    tail_++;
    if (tail_ == size_+1){
        tail_ = 1;
    }
    *(array_+tail_ - 1) = e;
}

template <typename T>
T QueueArray<T>::deQueue()
{
    if (head_ == tail_)
        throw QueueUnderflow(); // очередь пуста
    head_++;
    if (head_ == size_ + 1){
        head_ = 1;
    }
    return array_[head_ - 1];
}



#endif //QUEUE_QUEUE_H
