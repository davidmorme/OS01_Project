#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

vector <vector<double>> load(){
	int n; 
	fstream F;
	F.open("readFile.txt");
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
	/*
	vector <double> P;
	P.insert(P.begin(),X.begin(),X.end());
	P.insert(P.end(),Y.begin(),Y.end());
	*/
	return P;
}


int main() {
	vector <vector<double>> P;   
	P = load();
	for(int j = 0; j < P[0].size(); j++){
		cout << "P" << j << "= (" << P[0][j] << " , " << P[1][j] << ")" << endl;
	}
	
	
	/*
	for(int j = 0; j < X.size(); j++){
		cout << "P" << j << "= (" << X[j] << " , " << Y[j] << ")" << endl;
	}
	*/
	
	return 0;
}