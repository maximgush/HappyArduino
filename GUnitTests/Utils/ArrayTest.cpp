#include "gtest/gtest.h"
#include <HappyArduinoLib/Utils/Array.h>

TEST( ArrayTest, Add ) {

	CArray<int> array;
	ASSERT_EQ( array.Size(), 0 );

	const int numAddElems = 22;	// Чтобы пару раз произошло перевыделение памяти
	for( int i = 0; i < 22; ++i ) {
		array.Add( i );
		ASSERT_EQ( array.Size(), i+1 );
		ASSERT_EQ( array[i],  i);
	}
}

TEST( ArrayTest, Insert ) {

	{
		CArray<int> array;
		// Вставим элемент в пустой массив
		array.Insert( 111, 0 );
		ASSERT_EQ( array.Size(), 1 );
		ASSERT_EQ( array[0], 111 );

		array.Insert( 222, 0 );
		ASSERT_EQ( array.Size(), 2 );
		ASSERT_EQ( array[0], 222 );
		ASSERT_EQ( array[1], 111 );

		array.Insert( 333, array.Size() );
		ASSERT_EQ( array.Size(), 3 );
		ASSERT_EQ( array[0], 222 );
		ASSERT_EQ( array[1], 111 );
		ASSERT_EQ( array[2], 333 );

		// Вставим элемент за пределы массива
		//array.Insert( 111, array.Size() + 1 );
	}

	CArray<int> array = { 1, 2, 3, 4, 5, 6, 7 };

	size_t positionsForInsert[] = { 3, 5, 7 };
	int magicNumber = 111;
	for( int i = 0; i < sizeof( positionsForInsert ) / sizeof(int); ++i ) {
		int size = array.Size();
		int insertingElem = i * magicNumber;
		int prevElem = array[positionsForInsert[i] - 1];
		int nextElem = array[positionsForInsert[i]];
		array.Insert( insertingElem, positionsForInsert[i] );
		ASSERT_EQ( array.Size(), size + 1 );
		ASSERT_EQ( array[positionsForInsert[i]], insertingElem );
		ASSERT_EQ( array[positionsForInsert[i] - 1], prevElem );
		ASSERT_EQ( array[positionsForInsert[i] + 1], nextElem );
	}
}