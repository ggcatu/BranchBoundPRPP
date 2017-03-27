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
	vector<lado> v_adj;
	int v = sol_parcial->verticeExterno();
	if (v == 1) {
		if (sol_parcial->beneficio > mejor_solucion->beneficio){
			mejor_solucion = sol_parcial;
		}
	}

	v_adj = g.v[v].obtener_adj();
	for (vector<lado>::iterator i = v_adj.begin(); i != v_adj.end(); ++i){
		// if cochino
		if (!sol_parcial->ciclo_negativo(*i) && 
			sol_parcial->cumple_acotamiento(*i, beneficio_disp, mejor_solucion->beneficio) &&

			true ){
			sol_parcial->agregar(*i);
			// What ? Ese max ahi esta muy loco
			busqueda_en_profundidad();
		}
		
	}
	sol_parcial->eliminarUL();
	// What ? Ese max ahi esta muy loco
}


int main(int argc, char const *argv[])
{
	ifstream in("Instancias\\D1NoRPP");
	cin.rdbuf(in.rdbuf());
	g = leer_grafo();
	sol_parcial = new solucion();
	lado r = lado(1,3,15,10);
	lado t = lado (3,5,15,12);
	lado p = lado (5,12, 18, 15);
	lado l = lado (12, 3, 21, 3);
	sol_parcial->agregar(r);
	sol_parcial->agregar(t);
	sol_parcial->agregar(p);
//	sol_parcial->agregar(l);
	cout << "Hay ciclo: " << sol_parcial->ciclo_negativo(l) << endl;
	// Leer solucion inicial

	return 0;
}