#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string> 
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

bool same(vector<vector<double>> P,vector<vector<double>> Q){
	for(int i = 1; i<P[0].size();i++){
		if (P[i,0]!=Q[i,0] or P[i,1]!=Q[i,1] ){
			cout << "The two polygons are different" << endl;
			return false;
		}
	}
	cout << "The two polygons are the same" << endl;
	return true; 
		
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

void print(vector<vector<double>> P){
		for(int j = 0; j < P[0].size(); j++){
		cout << "P" << j << "= (" << P[0][j] << " , " << P[1][j] << ")" << endl;
	}
}

int main() {
	vector <vector<double>> P;   
	P = load();
	cout << "Original polygon loaded" << endl;
	print(P);
	
	P=clean(P);
	cout << "Polygon after cleaning" << endl;
	print(P);
	vector <vector<double>> Q=P;
	Q[0][0]=9;
	cout << "Polygon for comparing" << endl;
	print(Q);
	same(P,Q);
	
	
	/*
	for(int j = 0; j < X.size(); j++){
		cout << "P" << j << "= (" << X[j] << " , " << Y[j] << ")" << endl;
	}
	*/
	
	return 0;
}