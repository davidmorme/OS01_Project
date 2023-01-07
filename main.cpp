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
	Polygon polygon=Polygon();
	
	vector <vector<double>> P= polygon.load("Rectangulo.txt");
	vector<double>X;
	vector<double>Y;
	int n=P[0].size()-1;
	X.resize(n);
	Y.resize(n);
	polygon.setN(n);
	polygon.setX(X);
	polygon.setY(Y);
	for (int i=0;i<n;i++){
		X[i] = P[0][i];
		Y[i] = P[1][i];	
	}
	polygon.clean();
	double per = polygon.perimeter(P);
	vector<vector<double>> Q = P;
	bool isSame = polygon.same(P, Q);
	vector<double> point(2);
	point[0]=2.3;
	point[1]=2.3;
//	bool isInt = polygon.Int_Ext(P,point);
	double area = polygon.Area(P);
//	bool isSimple=polygon.isSimple(P);
//	bool isConvex=polygon.isConvex(P);
} 