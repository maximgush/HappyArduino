#include "Array.h"

struct Point2D
{
	float x;
	float y;
};

// Кусочно-линейная аппроксимация по массиву точек
class LinearSpline
{
public:
	explicit LinearSpline( const CArray<Point2D>& _points );

	bool CheckXLimits( float x );
	float GetValue( float x );

private:
	CArray<Point2D> points;
};