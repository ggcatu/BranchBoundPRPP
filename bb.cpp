#include <iostream>
#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>
#include "includes.cpp"
#include <time.h>

using namespace std;


solucion * sol_parcial;
solucion mejor_solucion;
int beneficio_disp = 0; 
grafo g;
int i = 0;
double tiempo = 0;
clock_t tStart;

int obtener_numero(ifstream& in){
	int numero;
    while(1){
    	in >> numero;
    	if (in.fail()){
    		in.clear();
        	in.ignore(256,' ');
    	} else {
    		return numero;
    	}
    }
	return numero;
}

grafo leer_grafo(ifstream& in){
	
	int nodos, ladosR, ladosE;
	int n1,n2,n3,n4;
	grafo g;
	lado * temp1, * temp2;
	int * rtmp;
	
	nodos = obtener_numero(in);
	//cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero(in);
	//cout << "Lados R: " << ladosR << endl;

	g.resize(nodos+1);
	//g.enumerar();
	for(int i = 0; i < ladosR; i++){
		in >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n1,n2,n3,n4);
		temp2 = new lado(n2,n1,n3,n4);
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
		beneficio_disp += n4-n3;
	}

	ladosE = obtener_numero(in);
	for(int i = 0; i < ladosE; i++){
		in >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n1,n2,n3,n4);
		temp2 = new lado(n2,n1,n3,n4);
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}

	return g;
}


void busqueda_en_profundidad(){
	tiempo = (double)(clock() - tStart)/CLOCKS_PER_SEC;
	if (tiempo > 30){
		return;
	}
	i++;
	if (i % 500000 == 0){
		sol_parcial->print_recorrido();
	}
	vector<lado> v_adj;
	int v = sol_parcial->verticeExterno();
	if (v == 1) {
		//cout << "Comparando " << sol_parcial->beneficio << " y " << mejor_solucion->beneficio <<endl;
		if (sol_parcial->beneficio > mejor_solucion.beneficio){
			cout << "Nueva solucion parcial!" << endl;
			sol_parcial->print();
			mejor_solucion = (*sol_parcial);
		}
	}

	v_adj = g.v[v].obtener_adj();
	for (vector<lado>::iterator i = v_adj.begin(); i != v_adj.end(); ++i){
		if (!sol_parcial->ciclo_negativo(*i) && 
			!sol_parcial->repite_ciclo(*i) &&
			!sol_parcial->esta_sol_parcial(*i) &&
			sol_parcial->cumple_acotamiento(*i, beneficio_disp, mejor_solucion.beneficio) ){
			
			sol_parcial->agregar(*i);
			beneficio_disp -= max(0, i->win - i->costo);
			busqueda_en_profundidad();
		}
	}
	while(!v_adj.empty()){
		v_adj.erase(v_adj.begin());
	}
	lado e = sol_parcial->eliminarUL();
	beneficio_disp += max(0, e.win - e.costo);
	delete(&e);
}


int main(int argc, char const *argv[])
{	
    if (! (argc > 1 )) return 1;
 	tStart = clock();
    string instance(argv[1]);
    string initial(instance + string("-salida.txt"));
    cout << "Evaluando " << argv[1] << endl;
    cout << "Solucion inicial: " << initial << endl; 

	//streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	ifstream in(argv[1]);
	//cin.rdbuf(in.rdbuf());
	ifstream in_sol(initial.c_str());
	g = leer_grafo(in);
	sol_parcial = new solucion();
	mejor_solucion.cargar_solucion(in_sol);
	//cin.rdbuf(cinbuf);   //reset to standard input again

	busqueda_en_profundidad();

	if (tiempo > 30){
		cout << "######### Overtime ############" << endl;
	}
	cout << "Mejor solucion encontrada!" << endl;
	mejor_solucion.print_recorrido();
	/* Do your stuff here */
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}