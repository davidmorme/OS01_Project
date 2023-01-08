set biomasse;

param n integer >0; #Quantité de jours
param m integer >0; #Quantité de fournisseurs pour chaque biomasse

param T{b in biomasse} >0; #Taux de production d'electricité de biomasse b (MWh/tonne)
param D{t in 1..n} >0; #Demande d'electricité dans le jour t (MWh)

param SD{b in biomasse, f in 1..m} >0; #Stock disponible de biomasse b en fournisseur f (tonnes)
param P{b in biomasse, f in 1..m} >0; #Prix de achat de biomasse b en fournisseur f (tonnes)
param DI{b in biomasse, f in 1..m} >0; #Distance de fournisseur f de biomasse b (km)


param KC >0; #Capacité du camion (tonnes)
param VC >0; #Vitesse moyenne du camion (km/h)
param KH >0; #Capacité de travail du conducteur (h)
param CT >0; #Coût de transport (euros/km)
param CH >0; #Coût du conducteur (euros/h)
param KV integer >0; #Maximum de voyages par jour
param TA >0; #Temps d’attendre au fournisseur pour chaque voyage (min)
param TD >0; #Temps de chargement pour chaque voyage (min)
param KS >0; #Capacité de stockage par chaque biomasse dans la centrale (tonnes)

param SI{b in biomasse} >0; #Stock Initial de biomasse b (tonnes)
param CS{b in biomasse} >0; #Coût de stockage par jour de biomasse b (euros/tonnes)

############## Variables ##############
var X{b in biomasse, f in 1..m, t in 1..n} >= 0; #Quantité acheté de biomasse b au fournisseur f dans le jour t
var Y{b in biomasse, t in 1..n} >= 0; #Quantité de biomasse b brûlées dans le jour t
var S{b in biomasse, t in 1..n} >= 0; #Stock de biomasse b dans le jour t

var V{b in biomasse, f in 1..m, t in 1..n} integer >= 0; #Quantité de voyages pour biomasse b au fournisseur f dans le jour t
var H{t in 1..n} integer >= 0; #Quantité de heures travaillées pour le conducteur dans le jour t

############## Fonction objectif ###########

minimize Z: sum{b in biomasse, f in 1..m, t in 1..n}( P[b,f]*X[b,f,t] + 2*CT*DI[b,f]*V[b,f,t] ) + sum{t in 1..n}( CH*H[t] ) + sum{b in biomasse, t in 1..n}( CS[b]*S[b,t] );

############## Contraintes ##############

demande{t in 1..n}:								sum{b in biomasse} T[b]*Y[b,t] = D[t];
maxdisp{b in biomasse, f in 1..m}:				sum{t in 1..n} X[b,f,t] <= SD[b,f];
maxstock{b in biomasse, t in 1..n}:				S[b,t] <= KS;
capcam{b in biomasse, f in 1..m, t in 1..n}:	X[b,f,t] <= KC*V[b,f,t];
maxvoyage{t in 1..n}:							sum{b in biomasse, f in 1..m} V[b,f,t] <= KV;
maxtravail{t in 1..n}:							H[t] <= KH;
jourlibre:										H[5] = 0;
heurtravail{t in 1..n}:							H[t] >= sum{b in biomasse, f in 1..m}( (2*DI[b,f]/VC + TA/60 + TD/60)*V[b,f,t] );
stock1{b in biomasse}:							S[b,1] = SI[b] + sum{f in 1..m} X[b,f,1] - Y[b,1];
stock{b in biomasse, t in 2..n}:				S[b,t] = S[b,t-1] + sum{f in 1..m} X[b,f,t] - Y[b,t];

solve;
display Z, X, Y, S, V, H;

printf "Tableau de Quantité acheté de biomasse b au fournisseur f dans le jour t (X)\n    ";
for{t in 1..n}: printf "%7d",t;
printf "\n";
for{b in biomasse}{
	for{f in 1..m}{
		printf "%6s", b; printf " %d", f;
		for{t in 1..n}: printf "%7.3f",X[b,f,t];
		printf "\n";
	}
}
printf "\n";

printf "Tableau de Quantité de biomasse b brûlées dans le jour t (Y)\n    ";
for{t in 1..n}: printf "%7d",t;
printf "\n";
for{b in biomasse}{
	printf "%6s", b;
	for{t in 1..n}: printf "%7.3f",Y[b,t];
	printf "\n";
}
printf "\n";

printf "Tableau de Stock de biomasse b dans le jour t (S)\n";
for{t in 1..n}: printf "%7d",t;
printf "\n";
for{b in biomasse}{
	printf "%6s", b;
	for{t in 1..n}: printf "%7.3f",S[b,t];
	printf "\n";
}
printf "\n";

printf "Tableau de Quantité de voyages pour biomasse b au fournisseur f dans le jour t (V)\n";
for{t in 1..n}: printf "%7d",t;
printf "\n";
for{b in biomasse}{
	for{f in 1..m}{
		printf "%6s", b; printf " %d", f;
		for{t in 1..n}: printf "%7d",V[b,f,t];
		printf "\n";
	}
}
printf "\n";

printf "Tableau de Quantité de heures travaillées pour le conducteur dans le jour t (H)\n";
for{t in 1..n}: printf "%7d",t;
printf "\n";
for{t in 1..n}: printf "%7.3f",H[t];
printf "\n";

data;

set biomasse := bois, paille;

param n := 8; #Quantité de jours
param m := 2; #Quantité de fournisseurs pour chaque biomasse

param T := bois 6, paille 4; #Taux de production d'electricité de biomasse b (MWh/tonne)
param D := 1 130, 2 200, 3 120, 4 450, 5 300, 6 270, 7 420, 8 250 ; #Demande d'electricité dans le jour t (MWh)

param SD:	1	2 := #Stock disponible de biomasse b en fournisseur f (tonnes)
	bois	80	120
	paille	110	150; 

param P:	1	2 := #Prix de achat de biomasse b en fournisseur f (tonnes)
	bois	60	65
	paille	40	42; 

param DI:	1	2 := #Distance de fournisseur f de biomasse b (km)
	bois	20	30
	paille	18	25;

param KC := 30; #Capacité du camion (tonnes)
param VC := 70; #Vitess moyenne du camion (km/h)
param KH := 5; #Capacité de travail du conducteur (h)
param CT := 8; #Coût de transport (euros/km)
param CH := 35; #Coût du conducteur (euros/h)
param KV := 3; #Maximum de voyages par jour
param TA := 30; #Temps atandé au fournisseur pour chaque voyage (min)
param TD := 10; #Temps de chargement pour chaque voyage (min)
param KS := 30; #Capacité de stockage par chaque biommasse camion (tonnes)

param SI := bois 15, paille 20; #Stock Initial de biomasse b (tonnes)
param CS := bois 1.5, paille 1; #Coût de stockage par our de biomasse b (euros/tonnes)

end;
