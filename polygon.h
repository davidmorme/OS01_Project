#include <vector>
#include <string>

using namespace std;

class Polygon {
private:
    int n;
    vector<double> X;
    vector<double> Y;

public:
    // Constructor
    Polygon(int n, vector<double>X, vector<double> Y);
	// Constructor without arguments with n=0
	Polygon();

    // Accessors
    int getN();
    vector<double> getX();
    vector<double> getY();

    // Mutators
    void setN(int n);
    void setX(vector<double> X);
    void setY(vector<double> Y);
    
    // Load
    vector <vector<double>> load(string route);

    // Clean
    vector<vector<double>> clean();

    // Same
    bool same(vector<vector<double>> P,vector<vector<double>> Q);

    // Perimeter
    double perimeter(vector<vector<double>> P);

    // Int_Ext
    bool Int_Ext(vector<vector<double>> P, vector<double> point);

    // Area
    double Area(vector<vector<double>> P);

    // Is Simple
    bool isSimple(vector<vector<double>> P);

    // Is Convex
    bool isConvex(vector<vector<double>> P);
    
    void print(vector<vector<double>> P) ;
    bool compareFloats(double a, double b);
    int CrossProduct(int ax, int ay, int bx, int by, int cx, int cy);
    int determinant(int ax, int ay, int bx, int by);
};


