#include <iostream>
#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class lado {
	public:
		int index;
		int vertex;
		int costo;
		int win;
		int * veces;
		lado(int g, int v, int c, int w) : index(g), vertex(v), costo(c), win(w){
			veces = new int(0);
		};
	
	int get_costo(){
		if ( !(*veces) ){
			return -(win - costo);
		}	
		else
			return  costo;
	}

	bool operator<(lado g){

		return ( win - costo < (g.win-g.costo) ) ;
	}

};

class solucion
{
public:
	vector<lado> camino;
	int beneficio;
	solucion():beneficio(0){};
	
	void agregar(lado e){
		beneficio += e.win - e.costo;
		camino.push_back(e);
	}

	void eliminarUL(){
		if(!camino.empty()){
			lado l = camino.back();
			beneficio -= l.win - l.costo;
    		camino.pop_back();
		} 
	}

	int verticeExterno(){
		if(!camino.empty()){
			return camino.back().vertex;
		} else {
			return 1;
		}
	}

	bool print(){
		cout << "Imprimiendo solucion: " << endl;
		vector<lado>::iterator end = --camino.end();
		cout << "Beneficio: " << beneficio << endl;  
		for (std::vector<lado>::iterator i = camino.begin(); i != camino.end(); ++i){
			cout << (*i).index << " " ;
			if (i == end){
				cout << (*i).vertex << endl;
			}
		}
	}
	
	bool cumple_acotamiento(lado e, int b_disponible, int b_mejor_sol){
		int b = e.win - e.costo;
		int b_parcial = beneficio + b;
		int max_beneficio = b_disponible - max(0, b) + b_parcial;
		if (max_beneficio <= b_mejor_sol) return false;
		return true;
	}

	lado * ciclo(lado e){
		for (std::vector<lado>::iterator i = camino.begin(); i != camino.end(); ++i){
			if( (*i).vertex == e.vertex ) {
				return &(*i);
			}
		}
		return NULL;
	}

	bool repite_ciclo(lado e){
		// PORQUE EN EL ENUNCIADO ESTA LISTA(V)?
		lado * r = ciclo(e);
		if (r != NULL ){
			if ( (e.win - e.costo) < (r->win - r->costo) ){
				return false;
			} else { return true; }
		} 
		return false;
	}

	bool ciclo_negativo(lado e){
		agregar(e);
		// PUEDE HACERSE CON UN SOLO CICLO
		for (std::vector<lado>::iterator i = camino.begin(); i != camino.end(); ++i){
			for (std::vector<lado>::iterator j = i; j != camino.end(); ++j){
				if( (*i).index == (*j).vertex ){
					vector<lado> ciclo(i,j+1);
					if (negativo(ciclo)){
						eliminarUL();
						return true;
					}
				} 
			}
		}
		eliminarUL();
		return false;
	}

	bool negativo(vector<lado> ls){
		int acum = 0;
		for (std::vector<lado>::iterator i = ls.begin(); i != ls.end(); ++i) {
			acum += i->win - i->costo;
		}
		return acum < 0;
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
			cout << index << " * " << endl;
			for (vector<lado>::iterator it = adj.begin(); it != adj.end(); ++it){
				cout << it->vertex << " " << it->costo << " * " ; 
			}
			cout << endl;
		}

		vector<lado> obtener_adj(){
			vector<lado> temp;
			lado * g;
			for (std::vector<lado>::iterator i = adj.begin(); i != adj.end(); ++i) {
				temp.push_back(*i);
				// may lead to leak 
				// need delet
				g = new lado(i->index, i->vertex, i->costo, 0);
				temp.push_back(*g);
			}

			sort(temp.begin(), temp.end());
			return temp;
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
		int maxbeneficio;

		grafo() : costo(0), maxbeneficio(0){};

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