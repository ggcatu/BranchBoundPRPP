#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

using namespace std;

class lado {
	public:
		int vertex;
		int costo;
		int win;
		int * veces;
		lado(int v, int c, int w) : vertex(v), costo(c), win(w){
			veces = new int(0);
		};
	
	int get_costo(){
		if ( !(*veces) ){
			return -(win - costo);
		}	
		else
			return  costo;
	}

};

class vertice{
	public:
		int index, distancia;
		bool conex;
		vertice * padre;
		vector<lado> adj;
		vertice() : conex(0){ padre = NULL;};
		vertice(int i) : conex(0), index(i){ padre = NULL;};

		void print_adj(){
			cout << " * " << endl;
			for (vector<lado>::iterator it = adj.begin(); it != adj.end(); ++it){
				cout << it->vertex << " " << it->costo << " * " ; 
			}
			cout << endl;
		}

		int return_path(vector<int> * ac){
			if (padre == NULL){
				ac->push_back(index);
				//cout << index << " ";
				return index;
			} else {
				padre->return_path(ac);
				ac->push_back(index);
				//cout << index << " ";
				return index;
			}
		}

		void limpiar(){
			conex = 0;
			padre = NULL;
		}
};



class grafo {
	public:
		vector<vertice> v;
		vector<int> recorrido;
		int costo;

		grafo() : costo(0){};

		void resize(int n){
			v.resize(n);
		}

		void agregar_recorrido(vector<int> * r){
			vector<int>::iterator g;
			g = r->begin();
			if(!recorrido.empty()){
				g++;
			}
			recorrido.insert( recorrido.end(), g, r->end() );
		}

		void print_recorrido(){
			cout << "Recorrido completo: " <<endl;
			for (vector<int>::iterator it = recorrido.begin(); it != recorrido.end(); ++it){
				cout << *it << " ";
			}
			cout << endl;
		}

		void limpiar(){
			for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				it->limpiar();
			}
		}

		void enumerar(){
			int n = 0;
			for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				it->index = n++;
			}
		}

		void agregar_lado(int nodo, lado r){
			v[nodo].adj.push_back(r);
		}
		
		lado * buscar_lado(int a, int b){
			vector<lado> * lista = &(v[a].adj);
			for (vector<lado>::iterator it = lista->begin(); it != lista->end(); ++it)
				{
					if(it->vertex == b) return &(*it);
				}
		}

		void recorrer(vector<int> * ac){
			int r = -1;
			for ( vector<int>::iterator it = ac->begin(); it != ac->end(); ++it ){
				cout << *it << " ";
				if (r != -1){
					(*buscar_lado(r,*it)->veces)++ ;
				}
				r = *it;
			}
			cout << endl;
			agregar_recorrido(ac);
		}
};

int obtener_numero(){
	int numero;
	string g;
    while(1){
    	cin >> numero;
    	if (cin.fail()){
    		cin.clear();
        	cin.ignore(256,' ');
    	} else {
    		cout << "what" << endl;
    		return numero;
    	}
    }
	return numero;
}



grafo leer_grafo(){
	
	int nodos, ladosR, ladosE;
	int n1,n2,n3,n4;
	grafo g,f;
	lado * temp1, * temp2;
	int * rtmp;



	ifstream in("Instancias\\D1NoRPP.txt");
	cin.rdbuf(in.rdbuf());
	
	nodos = obtener_numero();
	cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero();
	cout << "Lados R: " << ladosR << endl;

	g.resize(nodos+1);
	g.enumerar();
	for(int i = 0; i < ladosR; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n2,n3,n4);
		temp2 = new lado(n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}

	ladosE = obtener_numero();
	for(int i = 0; i < ladosE; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n2,n3,n4);
		temp2 = new lado(n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}

	return g;
}

int main(int argc, char const *argv[])
{
	grafo g = leer_grafo();
	g.v[0].print_adj();
	return 0;
}