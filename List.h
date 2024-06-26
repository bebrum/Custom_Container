#pragma once
#ifndef LIST_H
#define LIST_H
#include <iostream>

template <typename T>
class List;

template <typename T>
class Node
{
    friend class List<T>;

public:
    T m_node;
    Node<T>* m_next;
    Node<T>* m_prev;

    Node() : m_node(), m_next(nullptr), m_prev(nullptr) {}

    Node(const T& data) : m_node(data), m_next(nullptr), m_prev(nullptr) {}

    ~Node() {}

    const bool operator==(const Node<T>& s_node)
    {
        return (this->m_node == s_node.m_node);
    }
};

template <typename T>
class List
{
private:
    int MAX_SIZE = 1000;
    int m_count;
    Node<T>* m_first;
    Node<T>* m_last;

public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::bidirectional_iterator_tag iterator;
    typedef std::bidirectional_iterator_tag const_iterator;
    typedef std::ptrdiff_t difference_type;
    typedef int size_type;


    class Iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node<T>;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        Iterator() : ptr(nullptr) {}
        Iterator(pointer p) : ptr(p) {}

        reference operator*() const { return*ptr; }
        pointer operator->() const { return ptr; }
        Iterator& operator++() { ptr = ptr->m_next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { ptr = ptr->m_prev; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        bool operator==(const Iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }

    private:
        pointer ptr;
    };

    class ConstIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        ConstIterator() : ptr(nullptr) {}
        ConstIterator(pointer p) : ptr(p) {}

        reference operator*() const { return*ptr; }
        pointer operator->() const { return ptr; }
        ConstIterator& operator++() { ptr = ptr->m_next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
        bool operator==(const ConstIterator& rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const ConstIterator& rhs) const { return !(*this == rhs); }

    private:
        pointer ptr;
    };

    List();
    ~List();
    List(int p_count, T p_data);

    void swap(List<T>& p_list);
    int size() const;
    void insert(T p_node);
    void clear();
    bool empty();
    Iterator begin() const;
    Iterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    void pop_front();
    void pop_back();
    size_type max_size();
    List(const List<T>& p_list);
    List<T>& operator=(const List<T>& p_list);
    const bool operator==(const List<T>& p_listSecond);
    const bool operator!=(const List<T>& p_listSecond);
};

#include "List.cpp"

#endif