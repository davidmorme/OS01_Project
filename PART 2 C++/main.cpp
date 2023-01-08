#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include "utilities.h"
#include "polygon.h"

using namespace std;

int main(){
	Polygon polygon_1;
	polygon_1.load("Cuadrado.txt");
	polygon_1.print();
	polygon_1.clean();
	cout << "Polygon cleaned: " << endl;
	polygon_1.print();
	polygon_1.perimeter();
	
	Polygon polygon_2;
	polygon_2.load("Cuadrado.txt");
	
	same(polygon_1,polygon_2);
	vector<double> point(2);
	point[0]=2.3;
	point[1]=2.3;
	polygon_1.Int_Ext(point);
	polygon_1.Area();
	polygon_1.isSimple();
	polygon_1.isConvex();
	polygon_1.regular();

}  