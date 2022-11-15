#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Medidas.h"
 
using namespace std;

double Moyenne(vector <double> T){
	double somme=0;
	for(int i = 0; i < T.size(); i++) somme += T[i];
	return somme/T.size();
}

double Variance(vector <double> T){
	double moyenne=Moyenne(T);
	double sommeC = 0;
	for(int i = 0; i < T.size(); i++) sommeC += pow(moyenne - T[i],2);
	return sommeC/T.size();
}

double Ecart_type(vector <double> T){
	return sqrt(Variance(T));
}

int Element_entier(vector <double> T){
	double e=0.0001; //Error por el que considero entero el valor.
	int nEnt = 0;
	for(int i = 0; i < T.size(); i++){
		if( (abs(T[i] - trunc(T[i])) < e) || (abs(T[i] - trunc(T[i])) > 1-e) )nEnt++;
	}
	return nEnt;
}