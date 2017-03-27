#include <iostream>
#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>
#include "includes.cpp"

using namespace std;


solucion * sol_parcial;
solucion * mejor_solucion;
int beneficio_disp; 
grafo g;


int obtener_numero(){
	int numero;
    while(1){
    	cin >> numero;
    	if (cin.fail()){
    		cin.clear();
        	cin.ignore(256,' ');
    	} else {
    		return numero;
    	}
    }
	return numero;
}

grafo leer_grafo(){
	
	int nodos, ladosR, ladosE;
	int n1,n2,n3,n4;
	grafo g;
	lado * temp1, * temp2;
	int * rtmp;
	
	nodos = obtener_numero();
	cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero();
	cout << "Lados R: " << ladosR << endl;

	g.resize(nodos+1);
	g.enumerar();
	for(int i = 0; i < ladosR; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n1,n2,n3,n4);
		temp2 = new lado(n2,n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
		beneficio_disp += n4-n3;
	}

	ladosE = obtener_numero();
	for(int i = 0; i < ladosE; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n1,n2,n3,n4);
		temp2 = new lado(n2,n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}

	return g;
}


void busqueda_en_profundidad(){
	//sol_parcial->print();
	vector<lado> v_adj;
	int v = sol_parcial->verticeExterno();
	if (v == 1) {
		if (sol_parcial->beneficio > mejor_solucion->beneficio){
			sol_parcial->print();
			mejor_solucion = sol_parcial;
		}
	}

	v_adj = g.v[v].obtener_adj();
	for (vector<lado>::iterator i = v_adj.begin(); i != v_adj.end(); ++i){
		//cout << !sol_parcial->ciclo_negativo(*i) << " ";
		//cout << !sol_parcial->repite_ciclo(*i) << " ";
		//cout << sol_parcial->cumple_acotamiento(*i, beneficio_disp, mejor_solucion->beneficio) << " ";
		//cout << !sol_parcial->esta_sol_parcial(*i) << endl;
		if (!sol_parcial->ciclo_negativo(*i) && 
			!sol_parcial->repite_ciclo(*i) &&
			!sol_parcial->esta_sol_parcial(*i) &&
			sol_parcial->cumple_acotamiento(*i, beneficio_disp, mejor_solucion->beneficio) ){
			
			sol_parcial->agregar(*i);
			beneficio_disp -= max(0, i->win - i->costo);
			busqueda_en_profundidad();
		}
	}
	lado e = sol_parcial->eliminarUL();
	beneficio_disp += max(0, e.win - e.costo);
}


int main(int argc, char const *argv[])
{
	ifstream in("Instancias\\D1NoRPP");
	cin.rdbuf(in.rdbuf());
	g = leer_grafo();
	//beneficio_disp = g.maxbeneficio;
	cout << "Beneficio " << beneficio_disp << endl; 
	sol_parcial = new solucion();
	mejor_solucion = new solucion();
	mejor_solucion->cargar_solucion("Instancias\\D1NoRPP-salida.txt");
	busqueda_en_profundidad();
	return 0;
}