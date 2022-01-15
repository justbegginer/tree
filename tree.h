//
// Created by user.v2.0 on 14.03.2021.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H


#include <iostream>
#include <cmath>
#include "stack"
#include "stackArray.h"
#include "Queue.h"

//
// Определение шаблона класса BinarySearchTree
//
template<typename T>
struct Node {
    T key_;         // значение ключа, содержащееся в узле
    Node<T> *left_;     // указатель на левое поддерево
    Node<T> *right_;    // указатель на правое поддерево
    Node<T> *p_;        // указатель на  родителя

    Node(T key, Node *left = nullptr, Node *right = nullptr, Node *p = nullptr) :
        key_(key), left_(left), right_(right), p_(p) {}
};

template<typename T>
class BinarySearchTree {
public:

    // Конструкторы
    // "по умолчанию" создает пустое дерево
    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree<T> &scr) = delete;

    BinarySearchTree(BinarySearchTree<T> &&scr) noexcept;

    //
    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &src) = delete;

    BinarySearchTree<T> &operator=(BinarySearchTree<T> &&src) noexcept;

    // Деструктор освобождает память, занятую узлами дерева
    virtual ~BinarySearchTree();

    // 1.1 Функция поиска по ключу в бинарном дереве поиска
    bool iterativeSearch(const T &key) const;

    // 2 Вставка нового элемента в дерево:
    // true,если элемент добавлен; false, если элемент уже был
    bool insert(const T &key);

    // 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
    // true,если элемент удален; false, если элемента не было
    bool deleteKey(const T &key);

    // 4.1 Печать строкового изображения дерева в выходной поток out
    void print(std::ostream &out) const;

    // 5.1 Определение количества узлов дерева
    int getCount() const;

    // 6.1 Определение высоты дерева
    int getHeight() const;

    // 7 Инфиксный обход дерева (итеративный)
    void iterativeInorderWalk() const;

    // 8.1 Инфиксный обход дерева (рекурсивный)
    void inorderWalk() const;

    void inorderWalk(Node<T> *node) const;

    StackArray<T> buildStack();

    QueueArray<T> buildQueue();

    // 9 Сравнение деревьев: true, если все узлы деревьев одинаковые
    bool operator==(const BinarySearchTree<T> &src);

private:

    // Описание структуры узла со ссылками на детей и родителя

    // Дерево реализовано в виде указателя на корневой узел.
    Node<T> *root_;

    void swap(BinarySearchTree<T> &left, BinarySearchTree<T> &right);

    void swapMoving(Node<T> &left, Node<T> &right);

    // Рекурсивная функция для освобождения памяти
    void deleteSubtree(Node<T> *node);

    // 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
    Node<T> *iterativeSearchNode(const T &key) const;

    Node<T> *iterativeSearchNodeRec(const T &key, Node<T> *current) const;

    // 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
    void printNode(std::ostream &out, Node<T> *root) const;

    // 5.2 Рекурсивная функция определения количества узлов дерева
    int getCountSubTree(const Node<T> *node) const;

    // 6.2 Рекурсивная функция определения высоты дерева
    int getHeightSubTree(Node<T> *node) const;

    // 8.2 Рекурсивная функция для организации обхода узлов дерева.

    void inorderWalkRec(Node<T> *node) const;

    bool operatorEqualRec(const Node<T>* left, const Node<T>* right);

    void buildStackMove(Node<T> *node, StackArray<T> &stackArray);

    void buildQueueMove(Node<T> *node, QueueArray<T> *QueueArray, int deep);

}; // конец шаблона класса TreeBinarySearchTree



// Конструктор "по умолчанию" создает пустое дерево
template<class T>
BinarySearchTree<T>::BinarySearchTree(): root_(nullptr) {}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &&scr) noexcept {
    this->swap(scr);
}

// .........................................................................


// .........................................................................
// Деструктор освобождает память, занятую узлами дерева

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    deleteSubtree(root_);
}

// Рекурсивная функция для освобождения памяти
template<class T>
void BinarySearchTree<T>::deleteSubtree(Node<T> *node) {
    if (node->left_ != nullptr) {
        deleteSubtree(node->left_);
    }
    if (node->right_ != nullptr) {
        deleteSubtree(node->right_);
    }
    delete node;
}

// .........................................................................
template<class T>
void BinarySearchTree<T>::swap(BinarySearchTree<T> &left, BinarySearchTree<T> &right) {
    left = new BinarySearchTree<T>();
    left.root_ = new Node<T>((right.root_)->key_);
    swapMoving(left, right);
    delete right;
}

// .........................................................................
template<class T>
void BinarySearchTree<T>::swapMoving(Node<T> &left, Node<T> &right) {
    left.key_ = right.key_;
    if (right.left_ != nullptr) {
        swapMoving(left.left_, right.left_);
    }
    if (right.right_ != nullptr) {
        swapMoving(left.right_, right.right_);
    }
}

// 1.1 Функция поиска по ключу в бинарном дереве поиска
template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T &key) const {
    return (iterativeSearchNode(key) != nullptr);
}
// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска

template<typename T>
Node<T> *BinarySearchTree<T>::iterativeSearchNode(const T &key) const {
    return iterativeSearchNodeRec(key, root_);
}

template<typename T>
Node<T> *BinarySearchTree<T>::iterativeSearchNodeRec(const T &key, Node<T> *current) const {
    if (current == nullptr || key == current->key_) {
        return current;
    } else if (key < current->key_) {
        return iterativeSearchNodeRec(key, current->left_);
    } else {
        return iterativeSearchNodeRec(key, current->right_);
    }
}

// .........................................................................

// 2. Вставка нового элемента в дерево:
// true,если элемент добавлен; false, если элемент уже был

template<class T>
bool BinarySearchTree<T>::insert(const T &key) {
    Node<T> *current = root_; // Проверяемый узел.
    Node<T> *parent = nullptr; // для родителя (изначально nullptr).

    if (current == nullptr) // Если дерево изначально пустое, то просто делаем корень.
    {
        Node<T> *newRoot = new Node<T>(key, nullptr, nullptr, nullptr);
        root_ = newRoot;
        return true;
    }

    while (current != nullptr) // Пока не нашли нужную пустую ячейку...
    {
        if (current->key_ == key) // Не добавляем элемент с ключем, который есть в дереве.
        {
            return false;
        }
        // Родителем становится проверяемый элемент,
        // так как x пойдет глубже- он будет на 1 узел впереди.
        parent = current;
        if (key < current->key_) {
            current = current->left_;
        } else {
            current = current->right_;
        }
    }
    // Смотрим, в какую сторону от родителя вставлять элемент.
    if (key < parent->key_) {
        parent->left_ = new Node<T>(key, nullptr, nullptr, parent);
        return true;
    } else {
        parent->right_ = new Node<T>(key, nullptr, nullptr, parent);
        return true;
    }
}
// .........................................................................

// 3. Удаление элемента из дерева, не нарушающее порядка элементов
template<class T>
bool BinarySearchTree<T>::deleteKey(const T &key) {
    Node<T> *node = iterativeSearchNode(key);
    if (node == nullptr) {
        return false;
    }
    if ((node->left_ == nullptr) && (node->right_ == nullptr)) {
        if (node->p_ == nullptr) // Если этот лист - корень...
        {
            root_ = nullptr;
            delete node;
            return true;
        } else {
            if ((node->p_->left_ != nullptr) &&
                (node->p_->left_->key_ == node->key_)) // Если этот лист слева от родителя...
            {
                node->p_->left_ = nullptr;
                node->key_ = 0;
                delete node;
                return true;
            }
            if ((node->p_->right_ != nullptr) &&
                (node->p_->right_->key_ == node->key_)) // Если этот лист справа от родителя...
            {
                node->p_->right_ = nullptr;
                node->key_ = 0;
                delete node;
                return true;
            }
        }
    } else if (((node->left_ != nullptr) && (node->right_ == nullptr))) { // Удаляем узел только с левым ребенком.
        if (node->p_ == nullptr) // Если этот узел - корень...
        {
            //node->left_->p_ = nullptr;
            root_ = node->left_;
            delete node;
            return true;
        } else {
            if ((node->p_->left_ != nullptr) &&
                (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
            {
                node->left_->p_ = node->p_;
                node->p_->left_ = node->left_;
                delete node;
                return true;
            }
            if ((node->p_->right_ != nullptr) &&
                (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
            {
                node->left_->p_ = node->p_;
                node->p_->right_ = node->left_;
                delete node;
                return true;
            }
        }
    } else if (((node->left_ == nullptr) && (node->right_ != nullptr))) { // Удаляем узел только с правым ребенком.
        if (node->p_ == nullptr) // Если этот узел - корень...
        {
            //node->right_->p_ = nullptr;
            root_ = node->right_;
            delete node;
            return true;
        } else {
            if ((node->p_->left_ != nullptr) &&
                (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
            {
                node->right_->p_ = node->p_;
                node->p_->left_ = node->right_;
                delete node;
                return true;
            }
            if ((node->p_->right_ != nullptr) &&
                (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
            {
                node->right_->p_ = node->p_;
                node->p_->right_ = node->right_;
                delete node;
                return true;
            }
        }
    } else if (((node->left_ != nullptr) && (node->right_ !=
                                             nullptr))) { // Удаляем узел с обоими детьми. Будем искать минимальный(левый) элемент из правого поддерева.
        Node<T> *x = node->right_; // Смотрим правое поддерево.
        while (x->left_ != nullptr) // Пока есть левые дети - будем идти по ним.
        {
            x = x->left_;
        } // Теперь x - минимальный элемент из правого поддерева.
        if ((x->p_->left_ != nullptr) && (x->p_->left_->key_ == x->key_)) // Если x - слева от своего родителя.
        {
            x->p_->left_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
            if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
            {
                x->right_->p_ = x->p_;
            }
        }
        if ((x->p_->right_ != nullptr) && (x->p_->right_->key_ == x->key_)) // Если x - справа от своего родителя.
        {
            x->p_->right_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
            if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
            {
                x->right_->p_ = x->p_;
            }
        }
        // У нас "в буфере" появился элемент x, которым мы должны заменить удаляемый элемент.
        // Вроде бы нужно поработать с указателями...
        // Но мы можем сделать проще - в удаляемом элементе поставить значение элемента x, а элемент x удалить.
        node->key_ = x->key_;
        delete x;
        return true;
    }
    return false;
}
// .........................................................................

// 4.1 Печать строкового изображения дерева в выходной поток out
template<class T>
void BinarySearchTree<T>::print(std::ostream &out) const {
    printNode(out, root_);
    out << std::endl;
}

// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
template<class T>
void BinarySearchTree<T>::printNode(std::ostream &out, Node<T> *root) const {
    // Изображение дерева заключается в круглые скобки.
    if (root != nullptr) {
        // Для узлов дерева должна быть определена (или переопределена)
        // операция вывода в выходной поток <<
        out << root->key_ << " ";
        printNode(out, root->left_);
        printNode(out, root->right_);
    }

}
// .........................................................................

//5.1 Определение количества узлов дерева
template<class T>
int BinarySearchTree<T>::getCount() const {
    return getCountSubTree(this->root_);
}

// 5.2 Рекурсивная функция определения количества узлов дерева
template<class T>
int BinarySearchTree<T>::getCountSubTree(const Node<T> *node) const {
    if (node == nullptr)
        return 0;
    return (1 + getCountSubTree(node->left_) +
            getCountSubTree(node->right_));
}
// .........................................................................

// 6.1 Определение высоты дерева
template<class T>
int BinarySearchTree<T>::getHeight() const {
    return getHeightSubTree(this->root_);
}

// 6.2 Рекурсивная функция определения высоты дерева
template<class T>
int BinarySearchTree<T>::getHeightSubTree(Node<T> *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(1 + getHeightSubTree(node->left_), 1 + getHeightSubTree(node->right_));
}

// .........................................................................

// 7. Инфиксный обход дерева (итеративный)
template<class T>
void BinarySearchTree<T>::iterativeInorderWalk() const {
    std::stack<Node<T> *> nodeStack; // Стек, хранящий указатели на узлы.
    Node<T> *current = root_;
    while ((nodeStack.size() != 0) || (current != nullptr)) {
        if (current != nullptr) {
            nodeStack.push(current); // Заносим в очередь на просмотр.
            current = current->left_;
        } else {
            current = nodeStack.top();
            nodeStack.pop();
            std::cout << current->key_;
            std::cout << " ";
            current = current->right_;
        }
    }
    std::cout << "\n";
}
// .........................................................................

// 8.1 Инфиксный обход дерева (рекурсивный)
template<class T>
void BinarySearchTree<T>::inorderWalk(Node<T> *node) const {
    inorderWalkRec(node);
}

// 8.2 Рекурсивная функция для организации обхода узлов дерева.
template<class T>
void BinarySearchTree<T>::inorderWalkRec(Node<T> *node) const {
    if (node->left_ != nullptr) {
        inorderWalkRec(node->left_);
        std::cout << (node->left_)->key_ << " ";
    }
    if (node == root_) {
        std::cout << root_->key_ << " ";
    }
    if (node->right_ != nullptr) {
        inorderWalkRec(node->right_);
        std::cout << node->right_->key_ << " ";
    }
}

// .........................................................................
// 9. Сравнение деревьев: true, если все узлы деревьев одинаковые
template<class T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<T> &src) {
    if (this->getCount() != src.getCount()) {
        return false;
    }
    return operatorEqualRec(this->root_, src.root_);
}

template<class T>
bool BinarySearchTree<T>::operatorEqualRec(const Node<T>* left, const Node<T>* right) {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    if (left->key_ != right->key_) {
        return false;
    } else {
        return operatorEqualRec(left->left_, right->left_) && operatorEqualRec(left->right_, right->right_);
    }

}

template<class T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(BinarySearchTree<T> &&src) noexcept {
    this->swap(src);
}

template<typename T>
void BinarySearchTree<T>::inorderWalk() const {
    inorderWalkRec(this->root_);
}

template<typename T>
StackArray<T> BinarySearchTree<T>::buildStack() {
    StackArray<T> stackArray(getCountSubTree(root_));
    buildStackMove(root_, stackArray);
    return stackArray;
}


template<typename T>
QueueArray<T> BinarySearchTree<T>::buildQueue() { // q
    QueueArray<T> queueArray(getCountSubTree(root_)+1);
    auto *array_of_queue = new QueueArray<T>[getHeight()];
    for (int i = 0; i < getHeight(); ++i) {
        array_of_queue[i] = QueueArray<T>(pow(2 , i) + 1);
    }
    buildQueueMove(root_, array_of_queue, 0);
    for (int i = 0; i < getHeight(); ++i) {
        while (!array_of_queue[i].isEmpty()) {
            queueArray.enQueue(array_of_queue[i].deQueue());
        }
    }
    delete[] array_of_queue;
    return queueArray;
}

template<typename T>
void BinarySearchTree<T>::buildStackMove(Node<T> *node, StackArray<T> &stackArray) {
    if (node != nullptr) {
        buildStackMove(node->right_, stackArray);
        stackArray.push(node->key_);
        buildStackMove(node->left_, stackArray);
    }
}

template<typename T>
void BinarySearchTree<T>::buildQueueMove(Node<T> *node, QueueArray <T> *QueueArray, int deep) {
    if (node != nullptr) {
        (QueueArray[deep]).enQueue(node->key_);
        buildQueueMove(node->left_, QueueArray, deep + 1);
        buildQueueMove(node->right_, QueueArray, deep + 1);
    }
}

template<class T>
 void BinarySearchTree<T>::wideWalk() const
{
    std::queue<Node<T>*> queue; queue.push(root_);
    while (!(queue.empty()))
    {
        Node<T>* temp = queue.front(); queue.pop();
        if (temp->left_ != nullptr)
        {
            queue.push(temp->left_);
        }
        if (temp->right_ != nullptr)
        {
            queue.push(temp->right_);
        }
        std::cout << temp->key_ << " ";
    }
}


#endif //TREE_TREE_H
