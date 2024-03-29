#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
using namespace std;

class Polygon {
	friend bool same(Polygon &p_1,Polygon &p_2);
private:
    int n;
    vector <vector<double>> Pol;

public:
    // Constructeur
    Polygon(int n, vector <vector<double>> Pol) {
    	n=n;
    	Pol=Pol;
	}
	// Constructeur sans arguments avec n=0
	Polygon() {n=0;}
    // Accessors
    int getN() const;
    vector<double> getPol() const;

    
    void print();

    // Mutators
    void setN(int n);
    void setPol(vector<double> Pol);
    
    // Load
    void load(string route);

    // Clean
    void clean();

    // Perimeter
    double perimeter();

    // Int_Ext
    bool Int_Ext(vector<double> point);

    // Area
    double Area();

    // Is Simple
    bool isSimple();

    // Is Convex
    bool isConvex();
    
    bool regular();
};
bool same(Polygon &p_1,Polygon &p_2);
