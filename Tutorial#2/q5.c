#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
double euclid_dist (x1,y1,x2,y2)
{
	int distance = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
	return distance; 
}
int main(void)
{
	srand(time(0));
	int i;
	int x1, x2, y1, y2;
	for(i=0;i<10;i++)
	{
		x1 = rand()%101;
		y1 = rand()%101;
		x2 = rand()%101;
		y2 = rand()%101;
		printf ("vector 1: (%d, %d) Vector 2: (%d, %d)\n", x1,y1,x2,y2);
		printf ("distance: %f\n",euclid_dist(x1,y1,x2,y2));
	}
}
