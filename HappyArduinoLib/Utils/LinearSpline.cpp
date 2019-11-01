#include "LinearSpline.h"

LinearSpline::LinearSpline( const CArray<Point2D>& _points )
	: points( _points )
{
}


bool LinearSpline::CheckXLimits(float x)
{
	return points.Size() > 1 && points[0].x < x && x < points[0].x;
}

float LinearSpline::GetValue(float x)
{
	assert( CheckXLimits( x ) );

	for(int i = 0; i < points.Size(); ++i ) {
		if (x >= points[i].x) {
			float k = ( points[i].y - points[i+1].y ) / ( points[i].x - points[i+1].x );
			float b = k * points[i].x - points[i].y;

			return k * x + b;
		}
	}

	assert( false );
	return 0;
}