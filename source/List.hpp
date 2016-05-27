#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>
#include "assert.h"

template <typename T>
struct List;

template <typename T>
struct ListNode
{
	ListNode(): m_value(), m_prev(nullptr), m_next(nullptr){}
	ListNode(T const& v, ListNode *prev, ListNode *next) 
		: m_value(v), m_prev(prev), m_next(next)
	{}
	T m_value;
	ListNode * m_prev;
	ListNode * m_next;
};

template <typename T>
struct ListIterator
{
	friend class List<T>;
	// to be implemented
private:
	ListNode<T>* m_node = nullptr;
};

template <typename T>
struct ListConstIterator
{
	friend class List<T>;
public :
	// not implemented yet
private :
	ListNode<T>* m_node = nullptr;
};

template <typename T>
class List
{
public :
	typedef T value_type;
	typedef T * pointer;
	typedef const T * const_pointer;
	typedef T& reference;
	typedef const T & const_reference;
	typedef ListIterator <T> iterator;
	typedef ListConstIterator <T> const_iterator;
	friend class ListIterator <T>;
	friend class ListConstIterator <T>;

//===== aufgabe 4.1
	bool empty() const
	{
		return m_size == 0;
	}
	std::size_t size() const 
	{
		return m_size;
	}
	List() : m_size(0), m_first(nullptr), m_last(nullptr) {}

//===== aufgabe 4.2
	void push_front(T const& element)
	{
		if (m_size==0)
		{
			ListNode<T> * front = new ListNode<T> {element, nullptr, nullptr};
			m_first=front;
			m_last=front;
		}
		else
		{
			ListNode<T> * front = new ListNode<T> {element, nullptr, m_first};
			m_first->m_prev = front;
			m_first=front;
		}
		++m_size;
	}

	void push_back(T const& element)
	{
		if (m_size==0)
		{
			ListNode<T> * back = new ListNode<T> {element, nullptr, nullptr};
			m_first=back;
			m_last=back;
		}
		else
		{
			ListNode<T> * back = new ListNode<T> {element, m_last, nullptr};
			m_last->m_next = back;
			m_last=back;
		}
		++m_size;
	}

	void pop_front()
	{
		if (m_size == 1)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
		}
		if (m_size > 1)
		{
			ListNode<T> *second = m_first->m_next;
			assert(m_first!=nullptr);
			delete m_first;
			m_first = second;
			m_first->m_prev = nullptr;
			second = nullptr;
		}
		--m_size;
	}

	void pop_back()
	{
		if (m_size == 1)
		{
			delete m_last;
			m_first = nullptr;
			m_last = nullptr;
		}
		if (m_size > 1)
		{
			ListNode<T> *second_last = m_last->m_prev;
			assert(m_last!=nullptr);
			delete m_last;
			m_last = second_last;
			m_last->m_next = nullptr;
			second_last = nullptr;
		}
		--m_size;
	}

    T const& front() const
    {
    	return m_first->m_value;
    }

    T& front()
    {
    	return m_first->m_value;
    }

    T const& back() const
    {
    	return m_last->m_value;
    }

    T& back() 
    {
    	return m_last->m_value;
    }

//===== aufgabe 4.3
    void clear()
    {
    	while(m_size!=0)
    	{
    		pop_back();
    	}
    }


private :
	std::size_t m_size = 0;
	ListNode<T> * m_first = nullptr;
	ListNode<T> * m_last = nullptr;
};





# endif // # define BUW_LIST_HPP