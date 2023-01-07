
#define POLYGON_H

#include <vector>

class Polygon {
private:
int n;
std::vector<double> X;
std::vector<double> Y;

public:
// Constructeurs
Polygon(int n, std::vector<double>X, std::vector<double> Y);
Polygon();
// Accesseurs
int getN() const;
std::vector<double> getX() const;
std::vector<double> getY() const;

// Mutateurs
void setN(int n);
void setX(std::vector<double> X);
void setY(std::vector<double> Y);

// Autres méthodes
std::vector <std::vector<double>> load(std::string route);
std::vector<std::vector<double>> clean();
bool same(std::vector<std::vector<double>> Q);
double perimeter();
bool regular();
std::vector<double> Int_Ext(std::vector<std::vector<double>> P, std::vector<double> O);
bool inside(std::vector<double> P, std::vector<double> O);
