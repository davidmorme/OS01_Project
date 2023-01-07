#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>

class Polygon {
private:
    int n;
    std::vector<double> X;
    std::vector<double> Y;

public:
    // Constructor
    Polygon(int n, std::vector<double>X, std::vector<double> Y);
	// Constructor without arguments with n=0
	Polygon();

    // Accessors
    int getN() const;
    std::vector<double> getX() const;
    std::vector<double> getY() const;

    // Mutators
    void setN(int n);
    void setX(std::vector<double> X);
    void setY(std::vector<double> Y);
    
    // Load
    std::vector <std::vector<double>> load(std::string route);

    // Clean
    std::vector<std::vector<double>> clean();

    // Same
    bool same(std::vector<std::vector<double>> P,std::vector<std::vector<double>> Q);

    // Perimeter
    double perimeter(std::vector<std::vector<double>> P);

    // Int_Ext
    bool Int_Ext(std::vector<std::vector<double>> P, std::vector<double> point);

    // Area
    double Area(std::vector<std::vector<double>> P);

    // Is Simple
    bool isSimple(std::vector<std::vector<double>> P);

    // Is Convex
    bool isConvex(std::vector<std::vector<double>> P);
};

#endif
