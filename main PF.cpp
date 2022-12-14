#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string> 
#include <cmath>
#include "utilities.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

vector <vector<double>> load(string route){
	int n; 
	fstream F;
	F.open(route);
	F>>n;
	vector <vector<double>> P;
	vector <double> X(n+1), Y(n+1); 
	int i=0;
	while(i<n){
		F>>X[i];
		F>>Y[i];
		i++;
	}
	F.close();
	
	X[n]=X[0];
	Y[n]=Y[0];
	
	P.push_back(X);
	P.push_back(Y);
	
	return P;
}

vector<vector<double>> clean(vector<vector<double>> P){
		//secondToLast = myVector[myVector.size() - 2];
		vector<double> m(P[0].size()-1);

		for(int i = 1; i<P[0].size();i++){
			m[i-1]=(P[0][i]-P[0][i-1])/(P[1][i]-P[1][i-1]);
		}
		
		m.push_back(m[0]);
		vector<double> X, Y;

		for (int i=1;i<m.size();i++){
			if(m[i]!=m[i-1]){
				X.push_back(P[0][i]);
				Y.push_back(P[1][i]);
			}
			
		}
		X.push_back(X[0]);
		Y.push_back(Y[0]);
		vector<vector<double>> PN;
		PN.push_back(X);
		PN.push_back(Y);
	return PN;
}

bool same(vector<vector<double>> P,vector<vector<double>> Q){
	int n=P[0].size()-1;
	if(P[0].size()!=Q[0].size()){
		return false;
	}
	for(int j=0; j<n-1;j++){
		bool S = true;
		for(int i = 0; i<n;i++){
			if(i+j<n){
				if (P[0][i]!=Q[0][i+j] or P[1][i]!=Q[1][i+j] ){
					S=false;
					break;
				}
			}else{
				if (P[0][i]!=Q[0][i+j-n] or P[1][i]!=Q[1][i+j-n] ){
					S=false;
					break;
				}
			}
		}
		if(S){
			cout << "The two polygons are the same" << endl;
			return true;
		}
	}
	cout << "The two polygons are different" << endl;
	return false;		
}

double perimeter(vector<vector<double>> P){
	double per = 0.0;
	for (int i = 1; i<P[0].size(); i++){
		per += pow( pow(P[0][i]-P[0][i-1], 2) + pow(P[1][i]-P[1][i-1], 2) , 0.5);
	} 
	cout << "Le perimeter du polygon est: " << per <<endl;
	return per;
}

//print 
void print(vector<vector<double>> P){
		for(int j = 0; j < P[0].size(); j++){
		cout << "P" << j << "= (" << P[0][j] << " , " << P[1][j] << ")" << endl;
	}
}

//verifier si un point est l'intérieur d'un polygone 
bool Int_Ext(vector<vector<double>> P, vector<double> punt){
	int n=P[0].size()-1;
	double maxY = P[1][0]; for (int i = 1; i < n; i++) maxY = Max(maxY,P[1][i]);
		
	double x = punt[0];
	double y;
	int cpt=0;
	
	for(int i = 1; i<P[0].size();i++){
		double m = (P[1][i]-P[1][i-1])/(P[0][i]-P[0][i-1]);	
		
		y = m*(x-P[0][i]) + P[1][i];

		if ((x-P[0][i])*(x-P[0][i-1])<0 && (y-punt[1])*(y-maxY-1)<0) cpt += 1;	
	}
	
	if (cpt%2 != 0){
		cout << "The point is Inside of the polygon" << endl;
		return true;
	}else{
		cout << "The point is Outside of the polygon" << endl;
		return false;
	}
}

bool compareFloats(double a, double b){
    if (abs(a - b) < 0.000001) {
		return true;
    }
    else {
        return false;
    }
}

bool regular(vector<vector<double>> P){
	int n=P[0].size()-1;
	
	double x1, x2, y1, y2, prodP, mag1, mag2, ang, ang0;
	
	for(int i = 1; i<n; i++){
			
		x1=P[0][i-1]-P[0][i];
		x2=P[0][i+1]-P[0][i];
		
		y1=P[1][i-1]-P[1][i];
		y2=P[1][i+1]-P[1][i];
	
	
		prodP = x1*x2 + y1*y2 ;
		mag1 = pow( pow(x1, 2) + pow(y1, 2) , 0.5);
		mag2 = pow( pow(x2, 2) + pow(y2, 2) , 0.5);
	
		ang = acos(prodP/(mag1*mag2));
	    
		if(!compareFloats(mag1,mag2)){
			cout << "Le polygon n'est pas regulier" << endl;
			return false;
		}
		
		if(i!=1){
			if(!compareFloats(ang,ang0)){
				cout << "Le polygon n'est pas regulier" << endl;
				return false;
			}
		}else{
			ang0 = ang;
		}
		
		
	}
	cout << "Le polygon est regulier" << endl;
	return true;
}

int CrossProduct(int ax, int ay, int bx, int by, int cx, int cy){
	  int Xab = ax - bx;
      int Yab = ay - by;
      int Xcb = cx - bx;
      int Ycb = cy - by;
      return (Xab * Ycb - Yab * Xcb);
}

bool isConvex(vector <vector<double>> P){
	// tous les angles sont inférieur à 180 deg 
	// Calculer le cross product entre deux points consécutifs si c'est <0 c'est que le sinus est négatif et l'angle entre les deux c'est > 180 
	// 
	
	int n=P[0].size()-1;
	int cp=0;
	bool neg=false;
	bool pos=false;
//	int cp= CrossProduct(P[0][0],P[1][0], P[0][1],P[1][1],P[0][2],P[1][2]); 
	for (int k=0;k<n;k++){
		int ax=P[0][k];
		int bx=P[0][k+1];
		int cx=P[0][k+2];
		
		int ay=P[1][k];
		int by=P[1][k+1];
		int cy=P[1][k+2];
		
		int cp= CrossProduct( ax, ay,  bx,  by,  cx,  cy);
		// cp<0 : angle>180		
	if (cp<0) neg=true;	
	else if (cp>0) pos=true;
	if (neg&&pos)  {
		cout << "Polygone non convexe";
		return false;
	}
}
	cout <<"Polygone convexe";
	return true;
	
}


/*
bool isConvex(vector <vector<double>> P){
	// tous les angles sont inférieur à 180 deg 
	int n=P[0].size()-1;
	numInt=0;
	//verifier que tous les points sont à l'interieur
	for(int i = 1; i<n; i++){
		//punt=getPoint(); // verticies
		
		if(Int_Ext(vector<vector<double>> P, vector<double> point)):
			numInt+=1; 
	}
	if (numInt==n):
		return true;
	else return false; 
		
	
} */

bool isSimple(vector <vector<double>> P){
	if (isConvex(P)){
		return true; 
	}
	else {
		//code
	}
	return true; 
} 


int main() {
	vector <vector<double>> P;   
	P = load("convexe.txt");
	
	cout << "Original polygon loaded" << endl;
	print(P);
	vector <vector<double>> Q=P;
	P=clean(P);
	cout << "Polygon after cleaning" << endl;
	print(P);
	
	Q[0][0]=9;
	cout << "Polygon for comparing" << endl;
	print(Q);
	same(P,Q);
	
	perimeter(P);
	
	regular(P);
	
	
	vector<double> punt (2);
	punt[0]=2.3;
	punt[1]=2.3;
	Int_Ext(P,punt);
	
	isConvex(P);
	
	return 0;
}