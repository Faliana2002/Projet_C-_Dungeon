#include "Obstacles.hpp"

bool Obstacles::inobstacles(Point p)
	{
	if (inrectangle(p))
		{return true;}
	return false;
	}
