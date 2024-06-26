#include <iostream>
#include <locale.h>


template <typename T>
class Node
{
public:
	T m_node;
	Node<T>* m_next;
	Node<T>* m_prev;
	Node()
	{
		m_node;
		m_next = NULL;
		m_prev = NULL;
	}
	Node(const T data)
	{
		m_node = data;
		m_next = NULL;
		m_prev = NULL;
	}
	~Node() {}

	const bool operator == (const Node<T>& s_node)
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

	List()
	{
		m_first = new Node<T>();
		m_last = new Node<T>();
		m_first->m_next = m_last;
		m_first->m_prev = NULL;
		m_last->m_next = NULL;
		m_last->m_prev = m_first;
		this->m_count = 0;
	}

	~List()
	{
		Node<T>* l_ptr;
		this->m_count = 0;
		while (m_first != NULL)
		{
			l_ptr = m_first;
			m_first = m_first->m_next;
			delete l_ptr;
		}
	}

	List(int p_count, T p_data)
	{
		m_first = new Node<T>();
		m_last = new Node<T>();
		m_first->m_next = m_last;
		m_first->m_prev = NULL;
		m_last->m_next = NULL;
		m_last->m_prev = m_first;
		this->m_count = 0;
		for (int i = 0; i < p_count; i++)
			this->insert(p_data);
	}


	struct Iterator
	{
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Node<T>;
		using pointer = Node<T>*;  // or also value_type*
		using reference = Node<T>&;  // or also value_type&

		// Iterator constructors here...
		Iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() {
			if ((this->m_ptr != NULL) && (this->m_ptr->m_next != 0))
				m_ptr = m_ptr->m_next;
			return *this;
		}
		// Postfix increment
		Iterator operator++(int) {
			Iterator tmp(*this);
			if ((this->m_ptr != NULL) && (this->m_ptr->m_next != 0))
				m_ptr = m_ptr->m_next;
			return tmp;
		}
		// Prefix decrement
		Iterator& operator--() {
			if ((this->m_ptr != NULL) && (this->m_ptr->m_prev != 0))
				m_ptr = m_ptr->m_prev;
			return *this;
		}
		// Postfix decrement
		Iterator operator--(int) {
			Iterator temp(*this);
			if ((this->m_ptr != NULL) && (this->m_ptr->m_prev != 0))
				m_ptr = m_ptr->m_prev;
			return temp;
		}

		Iterator& operator=(Iterator& p_iter)
		{
			m_ptr = p_iter.m_ptr;
			return (*this);
		}

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:

		pointer m_ptr;
	};
	


	struct ConstIterator
	{
		typedef const_iterator self_type;
		typedef std::forward_iterator_tag iterator_category;
		using difference_type = std::ptrdiff_t;
		using value_type = Node<T>;
		using pointer = Node<T>*;  // or also value_type*
		using reference = Node<T>&;  // or also value_type&

		ConstIterator(pointer ptr) : m_cptr(ptr) {}

		const reference operator*() { return *m_cptr->m_node; }
		const pointer operator->() { return m_cptr; }

		ConstIterator& operator ++()
		{
			if ((this->m_cptr != NULL) && (this->m_cptr->m_next != 0))
				m_cptr = m_cptr->m_next;
			return *this;
		}
		
		ConstIterator operator ++(int)
		{
			ConstIterator temp(*this);
			if ((this->m_cptr != NULL) && (this->m_cptr->m_next != 0))
				m_cptr = m_cptr->m_next;
			return temp;
		}
		
		const bool operator == (const ConstIterator& p_second)
		{
			return this->m_cptr == p_second.m_cptr;
		}
		const bool operator != (const ConstIterator& p_second)
		{
			return !(*this == p_second);
		}

	private:

		pointer m_cptr;
	};



	void swap(List<T>& p_list)
	{
		Node<T>* l_firstTemp, * l_lastTemp;
		l_firstTemp = m_first;
		l_lastTemp = m_last;
		m_first = p_list.m_first;
		m_last = p_list.m_last;
		p_list.m_first = l_firstTemp;
		p_list.m_last = l_lastTemp;
	}

	int size() const
	{
		return this->m_count;
	}

	void insert(T p_node)
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

	void clear()
	{
		Node<T>* buf = m_first;
		for (int i = 1; i <= m_count; i++) {
			buf = buf->m_next;
			buf->m_prev->m_next = buf->m_next;
			buf->m_next->m_prev = buf->m_prev;
			m_count--;
		}
		return m_count;
	}

	bool empty()
	{
		if (begin() == end())
			return 1;
		else return 0;
	}

	Iterator begin()const
	{
		return Iterator(m_first->m_next);
	}

	Iterator end()const
	{
		return Iterator(m_last);
	}
	
	ConstIterator cbegin()const
	{
		return ConstIterator(m_first->m_next);
	}
	
	ConstIterator cend()const
	{
		return ConstIterator(m_last);
	}

	void pop_front()
	{
		Node<T>* buf;
		buf = m_first->m_next;
		m_first->m_next = buf->m_next;
		buf->m_next->m_prev = m_first;
	}

	void pop_back()
	{
		Node<T>* buf;
		buf = m_last->m_prev;
		m_last->m_prev = buf->m_prev;
		buf->m_prev->m_next = m_last;
	}

	size_type max_size()
	{
		return this->MAX_SIZE;
	}

	List(const List<T>& p_list)
	{
		m_first = new Node<T>();
		m_last = new Node<T>();
		m_first->m_next = m_last;
		m_first->m_prev = NULL;
		m_last->m_next = NULL;
		m_last->m_prev = m_first;
		this->m_count = 0;

		for (auto it = p_list.begin(), end = p_list.end(); it != end; ++it) {
			const auto i = *it;
			this->insert(i.m_node);
		}
	}

	List<T>& operator=(const List<T>& p_list)
	{
		if (this != &p_list)
		{
			(this)->~List<T>();
			new (this) List<T>(p_list);
			return *this;
		}
		else
			return *this;
	}

	const bool operator == (const List<T>& p_listSecond)
	{
		if (this->size() != p_listSecond.size())
			return 0;

		Iterator iterFirst = this->begin();
		Iterator iterSecond = p_listSecond.begin();
		for (; (iterFirst != this->end()) && (iterSecond != p_listSecond.end()) && (*iterFirst == *iterSecond); iterFirst++, iterSecond++);
		return (iterSecond == p_listSecond.end() && iterFirst == this->end());
	}
	const bool operator != (const List<T>& p_listSecond)
	{
		return !(*this == p_listSecond);
	}
};

int main()
{
	
	/*
	This shows you how to use implemented custom list.
	*/

	List<int> a(List<int>(3, 5));
	List<int> r = List<int>();

	for (auto it = a.begin(), end = a.end(); it != end; ++it) {
		const auto i = *it;
		std::cout << i.m_node << "\n";
	}
	

	if (r.empty())
	{
		std::cout << "List is empty" << std::endl;
	}
	else
	{
		for (auto it = r.begin(), end = r.end(); it != end; ++it) {
			const auto i = *it;
			std::cout << i.m_node << "\n";
		}
	}

	return 0;
}