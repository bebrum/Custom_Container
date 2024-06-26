#include <iostream>
#include "List.h"

template <typename T>
List<T>::List()
{
    m_first = new Node<T>();
    m_last = new Node<T>();
    m_first->m_next = m_last;
    m_first->m_prev = nullptr;
    m_last->m_next = nullptr;
    m_last->m_prev = m_first;
    this->m_count = 0;
}

template <typename T>
List<T>::~List()
{
    Node<T>* l_ptr;
    this->m_count = 0;
    while (m_first != nullptr)
    {
        l_ptr = m_first;
        m_first = m_first->m_next;
        delete l_ptr;
    }
}

template <typename T>
List<T>::List(int p_count, T p_data)
{
    m_first = new Node<T>();
    m_last = new Node<T>();
    m_first->m_next = m_last;
    m_first->m_prev = nullptr;
    m_last->m_next = nullptr;
    m_last->m_prev = m_first;
    this->m_count = 0;
    for (int i = 0; i < p_count; i++)
        this->insert(p_data);
}

template <typename T>
List<T>::List(const List<T>& p_list)
{
    m_first = new Node<T>();
    m_last = new Node<T>();
    m_first->m_next = m_last;
    m_first->m_prev = nullptr;
    m_last->m_next = nullptr;
    m_last->m_prev = m_first;
    this->m_count = 0;

    for (auto it = p_list.begin(), end = p_list.end(); it != end; ++it) {
        const auto i = *it;
        this->insert(i.m_node);
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& p_list)
{
    if (this != &p_list)
    {
        this->clear();
        for (auto it = p_list.begin(), end = p_list.end(); it != end; ++it) {
            const auto i = *it;
            this->insert(i.m_node);
        }
    }
    return *this;
}

template <typename T>
const bool List<T>::operator==(const List<T>& p_listSecond)
{
    if (this->size() != p_listSecond.size())
        return false;

    auto iterFirst = this->begin();
    auto iterSecond = p_listSecond.begin();
    for (; (iterFirst != this->end()) && (iterSecond != p_listSecond.end()) && (*iterFirst == *iterSecond); ++iterFirst, ++iterSecond);
    return (iterSecond == p_listSecond.end() && iterFirst == this->end());
}

template <typename T>
const bool List<T>::operator!=(const List<T>& p_listSecond)
{
    return !(*this == p_listSecond);
}

template <typename T>
void List<T>::swap(List<T>& p_list)
{
    Node<T>* l_firstTemp = m_first;
    Node<T>* l_lastTemp = m_last;
    m_first = p_list.m_first;
    m_last = p_list.m_last;
    p_list.m_first = l_firstTemp;
    p_list.m_last = l_lastTemp;
}

template <typename T>
int List<T>::size() const
{
    return this->m_count;
}

template <typename T>
void List<T>::insert(T p_node)
{
    Node<T>* to_add = new Node<T>(p_node);
    Node<T>* buf = m_first->m_next;
    while (buf != m_last)
    {
        buf = buf->m_next;
    }
    buf->m_prev->m_next = to_add;
    to_add->m_next = buf;
    to_add->m_prev = buf->m_prev;
    buf->m_prev = to_add;
    m_count++;
}

template <typename T>
void List<T>::clear()
{
    Node<T>* buf = m_first->m_next;
    while (buf != m_last)
    {
        Node<T>* next = buf->m_next;
        delete buf;
        buf = next;
    }
    m_first->m_next = m_last;
    m_last->m_prev = m_first;
    m_count = 0;
}

template <typename T>
bool List<T>::empty()
{
    return begin() == end();
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(m_first->m_next);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
    return Iterator(m_last);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{
    return ConstIterator(m_first->m_next);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
    return ConstIterator(m_last);
}

template <typename T>
void List<T>::pop_front()
{
    if (m_count > 0)
    {
        Node<T>* buf = m_first->m_next;
        m_first->m_next = buf->m_next;
        buf->m_next->m_prev = m_first;
        delete buf;
        m_count--;
    }
}

template <typename T>
void List<T>::pop_back()
{
    if (m_count > 0)
    {
        Node<T>* buf = m_last->m_prev;
        m_last->m_prev = buf->m_prev;
        buf->m_prev->m_next = m_last;
        delete buf;
        m_count--;
    }
}

template <typename T>
typename List<T>::size_type List<T>::max_size()
{
    return this->MAX_SIZE;
}