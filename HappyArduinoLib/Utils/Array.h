#pragma once

#include <initializer_list>
#include <string>

#define assert(a)

template<class T>
T min( const T& a, const T& b )
{
	return a < b ? a : b;
}

template<class T>
T max( const T& a, const T& b )
{
	return a > b ? a : b;
}

template<class T>
T clamp( const T& val, const T& a, const T& b )
{
	return val < min ? min : ( val > max ? max : val );
}

template <class T>
class CArray {
 public:
	CArray();
	CArray( std::initializer_list<T> list );
	CArray(const CArray<T>&);
	CArray(CArray<T>&&);
	~CArray();

	CArray& operator=( std::initializer_list<T> list );
	CArray& operator=(const CArray<T>& arr);

	T& operator[](size_t i) { return data[i]; }
	const T& operator[]( size_t i ) const;

	// Добавляет элемент в конец массива
	void Add(const T& elem);
	// Вставляет элемент на указанную позицию и сдвигает следующие элементы вправо 
	void Insert(const T& elem, size_t pos);
	// Удаляет элемент на указанной позиции и сдвигает следующие элементы влево
	void Remove( size_t pos );
	// Удаляет все элементы в указанном диапазоне индексов и сдвигает следующие элементы влево
	void Remove( size_t startPos, size_t endPos);
	// Аллоцирует  память под массив
	void Reserve( size_t size );
	// Удаляет все элементы из массива
	void Clear();

	// Возвращает количество элементов в массиве
	size_t Size() const;
	// Возвращает размер массива в элементах
	size_t BufferSize() const;


private:
	T* data = nullptr;
	size_t size = 0;
	size_t bufferSize = 0;

	// Перемещает данные в новую область памяти указанного размера, если размер больше текущего буфера 
	void realloc( size_t newSize );
	// Увеличивает размер буфера в 2 раза и перемещает в него данные
	void realloc();
};

template<class T>
CArray<T>::CArray()
{
}

template<class T>
CArray<T>::CArray( const CArray<T>& arr)
{
	size = arr.size;
	bufferSize = arr.bufferSize;
	data = new T[bufferSize];
	memmove( data, arr.data, size * sizeof( T ) );
}

template<class T>
CArray<T>::CArray(CArray<T>&& arr)
{
	size = arr.size;
	bufferSize = arr.bufferSize;
	data = arr.data;
	arr.size = 0;
	arr.bufferSize = 0;
	arr.data = nullptr;
}

template<class T>
CArray<T>::CArray( std::initializer_list<T> list )
{
	Reserve( list.size() );
	for( auto& elem : list )
	{
		Add( elem );
	}
}

template<class T>
CArray<T>::~CArray()
{
	Clear();
}

template<class T>
void CArray<T>::Add( const T& elem )
{
	if (size == bufferSize) {
		realloc();
	}

	data[size] = elem;
	size++;
}

template<class T>
void CArray<T>::Insert( const T& elem, size_t pos )
{
	if( size == bufferSize ) {
		realloc();
	}

	memmove( data + pos + 1, data + pos, (size - pos) * sizeof( T ) );
	data[pos] = elem;
	size++;
}

template<class T>
size_t CArray<T>::Size() const
{
	return size;
}

template<class T>
size_t CArray<T>::BufferSize() const
{
	return bufferSize;
}

template<class T>
inline const T& CArray<T>::operator[]( size_t i ) const
{
	assert( 0 <= i && i < size );
	return data[i];
}

template<class T>
CArray<T>& CArray<T>::operator=( const CArray<T>& arr )
{
	Clear();

	size = arr.size;
	bufferSize = arr.bufferSize;
	data = new T[size];
	memmove( data, arr.data, size * sizeof( T ) );

	return *this;
}

template<class T>
CArray<T>& CArray<T>::operator=( std::initializer_list<T> list )
{
	Clear();
	Reserve( list.size() );
	for( auto& elem : list )
	{
		Add( elem );
	}

	return *this;
}

template<class T>
void CArray<T>::realloc(size_t newSize)
{
	if( newSize <= bufferSize )
		return;

	bufferSize = newSize;
	T* newData = new T[bufferSize];
	if( data != nullptr )
	{
		memmove( newData, data, size * sizeof( T ) );
		delete data;
	}
	data = newData;
}

template<class T>
void CArray<T>::realloc()
{
	realloc( max( bufferSize * ( size_t )2, ( size_t )8 ) );
}

template<class T>
void CArray<T>::Reserve( size_t reservedSize )
{
	if( bufferSize < reservedSize )
	{
		realloc( reservedSize );
	}
}

template<class T>
void CArray<T>::Clear()
{
	if (data != nullptr )
	delete[] data;
	size = 0;
	bufferSize = 0;

}