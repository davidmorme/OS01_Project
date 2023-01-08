param n integer > 0; # Nombre de jours

param SIU > 0; # Stock Initiale dans le usine
param K  > 0; #Capacit� de production par jour
param C > 0; # Co�t de production
param CSU > 0; # Co�t de stockage dans l'usine
param KSU > 0; # Capacit� de stock dans la usine
param cam integer > 0; # Quantit� de camions disponible
param Kcam  > 0; # Capacit� de chaque camion
param CT > 0; # Co�t de transport de usine � CD par tonne
param CFT > 0; # Co�t fix� si on utilise chaque camion en le jour
param CAT > 0; # Co�t Aditional pour utiliser plusier camions en le jour
param KSCD >0; # Capacit� de stockage dans le CD
param CSCD >0; # Co�t de stockage dans le CD par jour
param SICD >0; # Stock initial dans le CD 
param D {t in 1..n}; # Demande de jour t

var X{t in 1..n} >= 0; #Quantit� � faire en le jour t
var SU{t in 1..n} >= 0; #Stock dans l'usine � la fin de jour t
var SCD{t in 1..n} >= 0; #Stock dans le CD � la fin de jour t
var XTR{t in 1..n} >= 0; #Quantit� transport� de la usine � le CD en le jour t
var V{t in 1..n} integer >= 0; #Quantit� de vehicles utilis� en le jour t
var VA{t in 1..n} integer >= 0; #Quantit� de vehicles qu'on doit louer en le jour t

minimize Z: sum{t in 1..n} (C*X[t] + CSU*SU[t] + CSCD*SCD[t] + CT*XTR[t] + CFT*V[t] + CAT*VA[t] ) ;

maxp {t in 1..n} :		X[t] <= K ;
maxSU {t in 1..n} :		SU[t] <= KSU;
maxSCD {t in 1..n} :	SCD[t] <= KSCD;
maxTR {t in 1..n} :		XTR[t] <= Kcam*V[t];
maxCam {t in 1..n} :	V[t] <= cam + VA[t];

StockU1 :				SU[1] = SIU + X[1] - XTR[1] ;
StockU {t in 2..n}:		SU[t] = SU[t-1] + X[t] - XTR[t] ;
StockCD1 : 				SCD[1] = SICD + XTR[1] - D[1] ;
StockCD {t in 2..n} :	SCD[t] = SCD[t-1] + XTR[t] - D[t] ;

Weekend {t in 6..7} :	XTR[t] = 0;

solve;
display Z, X, SU, SCD, XTR, V, VA;

data;
param n := 12;
param SIU := 50;
param K := 260;
param C := 150;
param CSU := 20;
param KSU := 350;
param cam := 3;
param Kcam := 35;
param CT := 30;
param CFT := 500;
param CAT := 700;
param KSCD := 300;
param CSCD := 25;
param SICD := 20;

param D := 1 100, 2 250, 3 280, 4 430, 5 140, 6 0, 7 0, 8 170, 9 410, 10 110, 11 240, 12 130;

end;