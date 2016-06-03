#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>
#include "assert.h"
#include <utility>

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
struct ListConstIterator
{
	friend class List<T>;
public :
	// not implemented yet
private :
	ListNode<T>* m_node = nullptr;
};

template <typename T>
struct ListIterator
{
	typedef ListIterator<T> Self;

	typedef T value_type;
	typedef T * pointer;
	typedef T & reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class List<T>;

	//aufgabe 4.4
	ListIterator(): m_node(nullptr) {} 
	ListIterator(ListNode<T>* n): m_node(n) {} 

	reference operator *() const { return m_node->m_value; } 
	pointer operator->() const {return &m_node->m_value; } // & refers on the address
	Self& operator ++() { *this = next(); return *this; } 
	Self operator ++(int) 
	{ 
		Self tmp = *this; 
		operator++(); 
		return tmp; 
	} 
	bool operator ==(const Self& x) const { return m_node==x.m_node; } 
	bool operator !=(const Self& x) const { return m_node!=x.m_node; } 
	//aufgabe 4.8 insert
//	Self operator +(int n) const
//	{
//		for (int i = 0; i < n; ++i)
//		{
//			*this = next();
//		}
//		return *this;
//	}
//
//	Self operator -(int n) const
//	{
//		for (int i = 0; i < n; ++i)
//		{
//			*this = last();
//		}
//		return *this;
//	}

	Self next() const
	{
		if( m_node )
			return ListIterator(m_node->m_next);
		else
			return ListIterator(nullptr);
	}

	Self last() const
	{
		if (m_node)
			return ListIterator(m_node->m_prev);
		else
			return ListIterator(nullptr);
	}


private :
	// The Node the iterator is pointing to
	ListNode <T>* m_node = nullptr;
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
	// default constructor
	List() : m_size{0}, m_first{nullptr}, m_last{nullptr} {}

//===== aufgabe 4.7    copy constructor
	List(List const& x) : m_size{0}, m_first{nullptr}, m_last{nullptr}
	{
		for (iterator it = x.begin(); it != x.end(); ++it)
		{
			push_back(*it);
		}
	}

//===== aufgabe 4.11   Tiefer Zuweisungsoperator
	List& operator=(List l_new_value)
	{
		std::swap(m_first, l_new_value.m_first);   // swap pointers
		std::swap(m_last, l_new_value.m_last);
		std::swap(m_size, l_new_value.m_size);    // swap member value
		return *this;
	}

//===== aufgabe 4.12    move constructor
	List(List&& l_new_value) : m_size{l_new_value.m_size}, m_first{l_new_value.m_first}, m_last{l_new_value.m_last}
	{
		l_new_value.m_size = 0;
		l_new_value.m_first = nullptr;
		l_new_value.m_last = nullptr;
	}

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
//===== aufgabe 4.5
    iterator begin() const
    {
    	return iterator(m_first);
    }

    iterator end() const
    {
    	return iterator();
    }

//===== aufgabe 4.8
    void insert(iterator const& it, T const& new_elem)
    {
    	if (it == begin())
    	{
    		push_front(new_elem);
    	}
    	else if (it == end() )
    	{	
    		push_back(new_elem);
    	}
    	else
    	{
    		++m_size;
    		ListNode<T> * new_node = new ListNode<T> {new_elem, it.m_node->m_prev, it.m_node};
    		it.m_node->m_prev->m_next = new_node;
    		it.m_node->m_prev = new_node;
    	}
    }

//===== aufgabe 4.9
    void reverse ()
    {
    	unsigned int s = m_size;
    	iterator it = begin();
    	++it;
    	while (it!=end())
    	{
    		push_front(*it);
    		++it;
    	}
    	for (unsigned int i = 1; i < s; ++i)
    	{
    		pop_back();
    	}
    }

private :
	std::size_t m_size = 0;
	ListNode<T> * m_first = nullptr;
	ListNode<T> * m_last = nullptr;
};


//===== aufgabe 4.6
template < typename T >
bool operator ==( List <T> const & xs , List <T> const & ys )
{
	typedef ListIterator <T> iterator;

	if (xs.size()!= ys.size())
	{
		return false;
	}
	
	iterator itx = xs.begin();
	iterator ity = ys.begin();

	for (unsigned int i = 0; i < xs.size(); ++i)
	{
		if (*itx != *ity)	{ return false;	}
		++itx;
		++ity;
	}
	return true;
}

template < typename T >
bool operator !=( List <T> const & xs , List <T> const & ys )
{
	return !(xs == ys);
}
//===== aufgabe 4.9
template <typename T>
List<T> reverse(List<T> const& list)
{
	ListIterator<T> it = list.begin();
	List<T> newlist;
	while (it!=list.end())
	{
		newlist.push_front(*it);
		++it;
	}
	return newlist;
}


# endif // # define BUW_LIST_HPP