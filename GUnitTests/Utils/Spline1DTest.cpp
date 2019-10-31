#include "gtest/gtest.h"
#include <HappyArduinoLib/Utils/LinearSpline.h>

TEST( Spline1DTest, Test ) {

	CArray<Point2D> points = {{2,2},{4,4}};

	LinearSpline spline1D( points );

	ASSERT_EQ( spline1D.GetValue( 2 ), 2);
	ASSERT_EQ( spline1D.GetValue( 2.5 ), 2.5 );
	ASSERT_EQ( spline1D.GetValue( 3 ), 3 );
	ASSERT_EQ( spline1D.GetValue( 4 ), 4 );
}