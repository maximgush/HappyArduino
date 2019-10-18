
// Кусочно-линейная аппроксимация по массиву точек
class LinearSpline
{
  struct Point
  {
    float x;
    float y;
  };
  List<Point> points;

  bool CheckXLimits(float x)
  {	  
    return points.size() > 1 && points.First().x < x && x < points.Last().x)
  }

  float GetValue(float x)
  {
    if (!CheckXLimits(x))
      return 0.f;
      
    List<Point<T>>::ListNode point = points.First();
    while( x > point.x )
    {
      point = point->Next();
    }

    float k = (point->y - point->Next()->y) / (point->x - point->Next()->x);
    float b = k * point->x - point->y;

    return k * x + b;
  }
  
  // TODO: Методы для добавления значений, а также сортировку
  // А может и сделать быструю реализацию через массив
};