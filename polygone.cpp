#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string> 
#include <cmath>
#include "utilities.h"
using namespace std;

class Polygon {
private:
    int n;
    vector<double> X;
    vector<double> Y;

public:
    // Constructeur
    Polygon(int n, vector<double>X, vector<double> Y) {
    	n=n;
    	X=X;
    	Y=Y;
	}
	// Constructeur sans arguments avec n=0
	Polygon(){
		n=0;
	};
	
    // Accesseurs
    int getN() const { return n; }
    vector<double> getX() const { return X; }
    vector<double> getY() const { return Y; }

    // Mutateurs
    void setN(int n) { this->n = n; }
    void setX(vector<double> X) { this->X = X; }
    void setY(vector<double> Y) { this->Y = Y; }
    
	//Load
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

//Clean
vector<vector<double>> clean() {
  vector<double> m(this->X.size()-1);
  for(int i = 1; i<this->X.size();i++){
    m[i-1] = (this->X[i]-this->X[i-1])/(this->Y[i]-this->Y[i-1]);
  }
  m.push_back(m[0]);
  vector<double> X, Y;
  for (int i=1;i<m.size();i++){
    if(m[i]!=m[i-1]){
      X.push_back(this->X[i]);
      Y.push_back(this->Y[i]);
    }   
  }
  X.push_back(X[0]);
  Y.push_back(Y[0]);
  vector<vector<double>> PN;
  PN.push_back(X);
  PN.push_back(Y);
  return PN;
}

/*
vector<vector<double>> clean(vector<vector<double>> P){
		vector<double> m(P[0].size()-1);
		for(int i = 1; i<P[0].size();i++){
			m[i-1] = (P[0][i]-P[0][i-1])/(P[1][i]-P[1][i-1]);
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
*/
//Same
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
//perimetre

double perimeter(vector<vector<double>> P){
	double per = 0.0;
	for (int i = 1; i<P[0].size(); i++){
		per += pow( pow(P[0][i]-P[0][i-1], 2) + pow(P[1][i]-P[1][i-1], 2) , 0.5);
	} 
	cout << "Le perimetere du polygone est: " << per <<endl;
	return per;
}
/*
double perimeter() {
    double per = 0.0;
    for (int i = 1; i<this->X.size(); i++){
        per += pow( pow(this->X[i]-this->X[i-1], 2) + pow(this->Y[i]-this->Y[i-1], 2) , 0.5);
    } 
    cout << "Le perimetere du polygone est: " << per <<endl;
    return per;
}
*/

//print 
void print(vector<vector<double>> P){
		for(int j = 0; j < P[0].size(); j++){
		cout << "P" << j << "= (" << P[0][j] << " , " << P[1][j] << ")" << endl;
	}
}

	//verifier si un point est l'intérieur d'un polygone 
	//Int_ext
	bool Int_Ext(vector<vector<double>> P, vector<double> point){
		int n=P[0].size()-1;
		double maxY = P[1][0];
		for (int i = 1; i < n; i++) maxY = Max(maxY,P[1][i]);	
		double x = point[0];
		double y;
		int cpt=0;
		for(int i = 1; i<P[0].size();i++){
			double m = (P[1][i]-P[1][i-1])/(P[0][i]-P[0][i-1]);	
			
			y = m*(x-P[0][i]) + P[1][i];
	
			if ((x-P[0][i])*(x-P[0][i-1])<0 && (y-point[1])*(y-maxY-1)<0) cpt += 1;	
		}
		
		if (cpt%2 != 0){
			cout << "Le point est à l'interieur du polygone'" << endl;
			return true;                 
		}else{
			cout << "Le point est à l'exterieur du polygone'" << endl;
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
//regular ou pas?
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
			cout << "Le polygone n'est pas regulier" << endl;
			return false;
		}
		
		if(i!=1){
			if(!compareFloats(ang,ang0)){
				cout << "Le polygone n'est pas regulier" << endl;
				return false;
			}
		}else{
			ang0 = ang;
		}
		
		
	}
	cout << "Le polygon est regulier" << endl;
	return true;
}

//CrossProduct
int CrossProduct(int ax, int ay, int bx, int by, int cx, int cy){
	  int Xab = ax - bx;
      int Yab = ay - by;
      int Xcb = cx - bx;
      int Ycb = cy - by;
      return (Xab * Ycb - Yab * Xcb);
}

// Calcul de déterminent 
int determinant(int ax, int ay, int bx, int by){
	  return (ax*by)-(ay*bx);
}

bool isConvex(vector <vector<double>> P){
	// tous les angles sont inférieur à 180 deg 
	// Calculer le cross product entre deux points consécutifs si c'est <0 c'est que le sinus est négatif et l'angle entre les deux c'est > 180 	
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
		cout << "Le Polygone n'est pas convexe"<<endl;
		return false;
	}
}	
	cout <<"Le polygone est convexe" <<endl;
	return true;
}
//isSimple
bool isSimple(vector <vector<double>> P){
	bool intersection;
	int n=P[0].size()-1;
	//cout <<"n"<< n << endl;
	  if (n < 3) {
    cout << "Le polygone n'a pas assez de points pour être considéré comme un polygone" << endl;
    return false;
  }
    for (int k=0;k<n-2;k++){
		int ax=P[0][k];
		int bx=P[0][k+2];
	
		int ay=P[1][k];
		int by=P[1][k+2];
		if (determinant (ax,ay,bx,by)==0){
			intersection=false;
		}
		else {
			intersection=true;
		}		
}
if (!intersection)
	cout << "Le polygone est simple " <<endl;
else
	cout << "Le polygone n'est pas simple" <<endl;
return intersection;
}
//Area
double Area(vector <vector<double>> P){
	double area;
	int n=P[0].size()-1;
	double a=0;
	double b=0;
	
	for (int k=0;k<=n-1;k++){		
		a+= P[0][k-1]*P[1][k];
		b+= P[1][k-1]*P[0][k]; 
	}
	a+= P[0][n-1]*P[1][0];
	b+= P[1][n-1]*P[0][0];
	area= abs((a-b)/2);
	cout <<"area =" << area<< endl; 
	return (area);
}
    
};

int main(){
	Polygon polygon;
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
	bool isInt = polygon.Int_Ext(P,point);
	double area = polygon.Area(P);
	bool isSimple=polygon.isSimple(P);
	bool isConvex=polygon.isConvex(P);


/*
// Afficher les abcisses
for (auto x : X) {
    std::cout << x << " ";
std::cout << std::endl;
} */

}


