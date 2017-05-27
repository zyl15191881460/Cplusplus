#include <iostream>
using namespace std;

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;
	typedef size_t SizeType;

	Vector()
		: _start(0)
		, _finish(0)
		, _endOfStorage(0)
	{}
	Vector(size_t n, const T& value = T())
	{
		_start = new T[n * sizeof(T)];
		for (size_t idx = 0; idx < n; ++idx)
		{
			_start[idx] = value;
		}
		_finish = _start + n;
		_endOfStorage = _finish;
	}
	Vector(const Vector<T>& v)
	{
		size_t size = v._finish - v._start;
		size_t capacity = v._endOfStorage - v._start;
		_start = new T[capacity];
		for (size_t idx = 0; idx < size; ++idx)
		{
			_start[idx] = v._start[idx];
		}
		_finish = _start + size;
		_endOfStorage = _start + capacity;

	//	_finish = v._finish;   不能这样赋值，会发生内存泄漏
	//	_endOfStorage = v._endOfStorage;
	}
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (_start != v._start)
		{
			T* tmp = new T[v.Capacity()];
			memcpy(tmp, v._start, v.Size()*sizeof(T));
			delete[] _start;
			_start = tmp;
			_finish = _start + Size();
			_endOfStorage = _start + v.Capacity();
		}
		return *this;
	}
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = NULL;
		}
	}
	Iterator Begin()
	{
		assert(_start);
		return _start;
	}
	ConstIterator Begin()const
	{
		assert(_start);
		return _start;
	}
	Iterator End()
	{
		assert(_finish);
		return _finish;
	}
	ConstIterator End()const
	{
		assert(_finish);
		return _finish;
	}
	SizeType Size()const
	{
		return (End() - Begin());
	}
	SizeType Capacity()const
	{
		return (_endOfStorage - Begin());
	}
	bool Empty()const
	{
		return Begin() == End();
	}
	Reference operator[](size_t index)
	{
		assert(index >= 0 && index < Size());
		return *(Begin() + n);
	}
	ConstReference operator[](size_t index)const
	{
		assert(index >= 0 && index < Size());
		return *(Begin() + n);
	}
	Reference Front()
	{
		assert(_start);
		return *Begin();
	}
	ConstReference Front()const
	{
		assert(_start);
		return *Begin();
	}
	Reference Back()
	{
		assert(_finish);
		return *(End() - 1);
	}
	ConstReference Back()const
	{
		assert(_finish);
		return *(End() - 1);
	}
	void PushBack(const T& value)
	{
		CheckCapacity();
		*_finish = value;
		++_finish;
	}
	void PopBack()
	{
		if (_start == NULL)
			return;
		Iterator tmp = _finish;
		--_finish;
		delete tmp;
	}
	
	Iterator Insert(Iterator pos, const T& value)
	{
		assert(pos >= _start && pos <= _endOfStorage);
		CheckCapacity();
		if (pos == _start)
			*_start = value;
		else if (pos == _finish)
			*_finish = value;
		else
		{
			size_t tmp = _finish - pos;
			size_t i = 0;
			for (i = Size(); i >= tmp; --i)
			{
				_start[i] = _start[i - 1];
			}
			_start[i] = value;
		}
		_finish++;
		return pos;
	}
	Iterator Erase(Iterator pos)
	{
		assert(_start != _finish);
		if (pos == _finish - 1)
		{
			PopBack();
		}
		else
		{
			size_t tmp = pos - _start;
			for (size_t i = tmp; i < Size() - 1; ++i)
			{
				_start[i] = _start[i + 1];
			}
		}
		_finish--;
		return pos;
	}
	void ReSize(SizeType newSize, const T& value = T())
	{
		if (Size() >= newSize)
		{
			_finish = _start + newSize;
		}
		else
		{
			size_t size = Size();
			_finish = _start + newSize;
			CheckCapacity();
			for (size_t i = size; i < newSize; ++i)
			{
				_start[i] = value;
			}
		}
	}
	void Clear()const
	{
		assert(_start != _finish);
		_finish = _start;
	}

private:
	void CheckCapacity()  //检查容量
	{
		if (Size() >= capacity())
		{
			size_t size = Size();
			size_t capacity = Capacity() * 2 + 3;
			Iterator tmp = new T[capacity];
			if (NULL != tmp)
				memcpy(tmp, _start, size*sizeof(T));
			if (NULL != _start)
				delete[] _start;

			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + capacity;
		}
	}


protected:
	Iterator _start;		//表示目前使用空间的头
	Iterator _finish;		//表示目前使用空间的尾
	Iterator _endOfStorage;	//表示目前可用空间的尾
};

