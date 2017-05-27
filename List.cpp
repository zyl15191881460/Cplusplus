#pragma once
template<class T>
struct ListNode
{
	ListNode(const T& data = T())
	: _prev(0)
	, _next(0)
	, _data(data)
	{}

	ListNode<T>* _prev;
	ListNode<T>* _next;
	T _data;
};


template<class T, class Ref, class Ptr>
class __ListIterator__
{
	typedef __ListIterator__<T, T&, T*> Iterator;
	typedef __ListIterator__<T, const T&, const T*> ConstIterator;
	typedef __ListIterator__<T, Ref, Ptr> Self;
	typedef ListNode<T>* LinkType;
	typedef Ref Reference;
	typedef Ptr Pointer;

public:
	__ListIterator__(LinkType x = 0)
		: _node(x)
	{}
	__ListIterator__(const Iterator& x)
		: _node(x._node)
	{}
	bool operator==(const Iterator& x)
	{
		return _node == x._node;
	}
	bool operator!=(const Iterator& x)
	{
		return _node != x._node;
	}
	Reference operator*()
	{
		return *(_node)._data;
	}
	Pointer operator->()
	{
		return &(operator*());
	}
	Self& operator++()//前置++
	{
		_node = _node->_next;
		return *this;
	}
	Self operator++(int)//后置++
	{
		Self tmp = _node;
		_node = _node->_next;
		return tmp;
	}
	Self& operator--()//前置--
	{
		_node =  _node->_prev;
		return *this;
	}
	Self operator--(int)
	{
		Self tmp(_node);
		_node = _node->_prev;
		return tmp;
	}
public:
	LinkType _node;
};


template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef T ValueType;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;
	typedef ValueType* Pointer;
	typedef const ValueType* ConstPointer;
	typedef Node* LinkType;
	typedef size_t SizeType;
	typedef __ListIterator__<T, T&, T*> Iterator;
	typedef __ListIterator__<T, const T&, const T*> ConstIterator;

public:
	List() //创建一个头结点
	{
		EmptyInit();
	}
	List(SizeType n, const T& data)  
	{
		EmptyInit();
		for (size_t idx = 0; idx < n; ++idx)
		{
			PushBack(data);
		}
	}
	List(const List<T>& l)
	{
		EmptyInit();
		Iterator it = l._node->_next;
		for (SizeType idx = 0; idx < Size(); ++idx)
		{
			PushBack(it._node->_data);
			it++;
		}
	}

	~List()
	{
		Clear();
		delete _node;
	}
	////////////////////////////////////////////
	Iterator Begin()
	{
		return _node->_next;
	}
	ConstIterator Begin()const
	{
		return _node->_next;
	}
	Iterator End()
	{
		return _node;
	}
	ConstIterator End()const
	{
		return _node;
	}
	bool Empty()
	{
		return _node == _node->_next;
	}
	SizeType Size()const  
	{
		Iterator it = _node->_next;
		SizeType count = 0;
		while (it != _node)
		{
			count = count + 1;
			it++;
		}
	}

	Reference Front()
	{
		return *(Begin());
	}
	ConstIterator Front()const
	{
		return *(Begin());
	}
	Reference Back()
	{
		return *(--End());
	}
	ConstReference Back()const
	{
		return *(--End());
	}
	Iterator Insert(Iterator pos, const T& x = T())   //插入元素
	{
		LinkType temp = new Node(x);
		temp->_next = pos._node;
		temp->_prev = pos._node->_prev;
		pos._node->_prev->_next = temp;
		pos._node->_prev = temp;
		return temp;
	}
	void PushFront(const T& x)  //头插
	{
		Insert(Begin(), x);
	}
	void PushBack(const T& x)//尾插
	{
		Iterator it = End();
		Insert(it, x); 
	}
	Iterator Erase(Iterator pos)//删除指定的元素，返回下一个元素
	{
		LinkType next_node = pos._node->_next;
		LinkType prev_node = pos._node->_prev;
	
		prev_node->_next = next_node;
		next_node->_prev = prev_node;
		delete pos._node;
		return next_node;
	
	}
	void PopFront()//头删
	{
		Erase(Begin());
	}
	void PopBack()//尾删
	{
		Iterator tmp = End();
		Erase(--tmp);
	}
	void ReSize(SizeType n, const T& data)//对List的大小重新进行赋值
	{
		if (Size() >= n)
		{
			SizeType size1 = Size() - n;
			while (size1--)
			{
				PopBack();
			}
		}
		else
		{
			SizeType size2 = n - Size();
			while (size2--)
			{
				PushBack(data);
			}
		}
	}
	void Assign(SizeType n, const T& data)  //赋值
	{
		Iterator pTemp = _node->_next;
		if (Size() >= n)
		{
			for (size_t idx = 0; idx < n; ++idx)
			{
				pTemp._node->_data = data;
				++pTemp;
			}
			for (size_t idx = 0; idx < Size() - n; ++idx)
			{
				PopBack();
			}
		}
		else
		{
			pTemp = _node->_next;
			size_t size = Size();
			for (size_t idx = 0; idx < size; ++idx)
			{
				pTemp._node->_data = data;
				++pTemp;
			}
			for (size_t idx = 0; idx < n - size; ++idx)
			{
				PushBack(data);
			}
		}
	}
	void Clear() //清除所有元素
	{
		LinkType pDel = _node->_next;
		while (pDel != _node)
		{
			LinkType tmp = pDel;
			pDel = pDel->_next;
			delete tmp;
			tmp = NULL;
		}
		_node->_next = _node;
		_node->_prev = _node;
	}
private:
	void EmptyInit()
	{
		_node = new Node;
		_node->_data = 0;
		_node->_next = _node;
		_node->_prev = _node;
	}
protected:
	LinkType _node;    //是一个普通的指针，来指向list的结点；
};