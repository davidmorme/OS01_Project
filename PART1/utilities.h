//==============================================================================
// SOME USEFUL FUNCTIONS - HEADER FILE "utilities.h"                    C. PRINS
//============================================================================== 
// - Names begin by uppercase letter to avoid conflicts with system functions.
// - Beware: compiler must be in 2011 mode or later for to_string (-std c++11)!                                       
//------------------------------------------------------------------------------
   
#pragma once                          // To include only once
#include <string>                     // Because string is used in some headers
using std::string;                    // Could be "using namespace std;" as well

//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

extern const int    BigInt;           // Very large integer value
extern const double BigReal;          // Very large real value
extern const double Pi;               // Number Pi

//------------------------------------------------------------------------------
// CLASS FOR RANDOM NUMBER GENERATORS
//------------------------------------------------------------------------------
// - Reproduce the fairly good generator used by ARENA, IMSL, MATLAB & SLAM.
// - Build a random sequence of integers X0 ,X1, ..., Xn (X0 is initial value).
// - Next term is computed as : X(n+1) = A*X(n) modulo M (in 1...M-1).
// - X, A, M denoted _X, _A, _M to minimize name conflicts with C/C++.
// - Several independent generators may be defined.
//----------------------------------------------------------------------

class RandGen {                                  // Class for random generators
	private :                                     // __int64 if long long refused
   	static const long long _A =      16807;    // _A <=_M (here A = 7^5)
    	static const long long _M = 2147483647;    // _M = 2^31-1
	 	long long _X              =       3704;    // _X <=_M, default initial value 
    	double    _P;                              // _P in [0,1[ deduced from X
   public:
    	void   Init     (int seed);                // Initialize with seed <= _M
    	double RandReal (double a, double b);      // Return a random real in [a,b]
    	int    RandInt  (int a, int b);            // Return a random integer in [a,b]
    	double RandNorm (double m, double v);      // Normal law with mean m & variance v
};

//------------------------------------------------------------------------------
// OTHER FUNCTION HEADERS IN APHABETIC ORDER
//------------------------------------------------------------------------------

double   Chrono      ();                           // Chronometer in seconds
void     DelIntMat   (int **A, int m, bool i1);    // Delete integer matrix
void     DelIntVect  (int *T);                     // Delete integer vector
void     DelRealMat  (double **A, int m, bool i1); // Delete real matrix
void     DelRealVect (double *T);                  // Delete real vector
string   EI          (int i, int w = 1);           // Edit integer on w positions
string   ER          (double x, int w, int d);     // Edit real on w pos inc d decimals
void     Error       (string Msg);                 // Stop program with message
string   JL          (string S, int w, char c=' ');// Left-justify S on length w
string   JR          (string S, int w, char c=' ');// Right-justify S on length w
int      Max         (int i, int j);               // Maximum of two integers
double   Max         (double i, double j);         // Maximum of two reals (overload)
int      Min         (int i, int j);               // Minimum of two integers
double   Min         (double i, double j);         // Minimum of two reals (overload)
int**    NewIntMat   (int m, int n, bool i1);      // Create a integer mxn matrix
int*     NewIntVect  (int n, bool i1);             // Create an integer n-vector
double** NewRealMat  (int m, int n, bool i1);      // Create a real mxn matrix
double*  NewRealVect (int n, bool i1);             // Create a real n-vector
void     Pause       (string Msg);                 // Pause with message
string   Trim        (string S);                   // Cut left/right spaces and tabs
string   TrimL       (string S);                   // Cut left spaces and tabs
string   TrimR       (string S);                   // Cut right spaces and tabs
string   UC          (string S);                   // Convert S to upper case