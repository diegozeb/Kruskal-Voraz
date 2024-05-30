#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Arista 
{
    int origen, destino, peso;
};

struct Grafo 
{
    int V, E;
    vector<Arista> aristas;
};


struct Subconjunto 
{
    int padre;
    int rango;
};

int encontrar(Subconjunto subconjuntos[], int i) 
{
    if (subconjuntos[i].padre != i) 
    {
        subconjuntos[i].padre = encontrar(subconjuntos, subconjuntos[i].padre);
    }
    return subconjuntos[i].padre;
}

void unir(Subconjunto subconjuntos[], int x, int y) 
{
    int x_raiz = encontrar(subconjuntos, x);
    int y_raiz = encontrar(subconjuntos, y);

    if (subconjuntos[x_raiz].rango < subconjuntos[y_raiz].rango) 
    {
        subconjuntos[x_raiz].padre = y_raiz;
    }

    else if (subconjuntos[x_raiz].rango > subconjuntos[y_raiz].rango) 
    {
        subconjuntos[y_raiz].padre = x_raiz;
    }

    else 
    {
        subconjuntos[y_raiz].padre = x_raiz;
        subconjuntos[x_raiz].rango++;
    }
}

bool comparar(Arista a, Arista b) 
{
    return a.peso < b.peso;
}

void kruskal(Grafo& grafo) 
{
    int V = grafo.V;
    vector<Arista> resultado;
    int e = 0;
    int i = 0;

    sort(grafo.aristas.begin(), grafo.aristas.end(), comparar);

    Subconjunto* subconjuntos = new Subconjunto[V * sizeof(Subconjunto)];

    for (int v = 0; v < V; ++v) 
    {
        subconjuntos[v].padre = v;
        subconjuntos[v].rango = 0;
    }

    while (e < V - 1 && i < grafo.aristas.size()) 
    {
        Arista arista_actual = grafo.aristas[i++];

        int x = encontrar(subconjuntos, arista_actual.origen);
        int y = encontrar(subconjuntos, arista_actual.destino);

        if (x != y) 
        {
            resultado.push_back(arista_actual);
            unir(subconjuntos, x, y);
            e++;
        }
    }

    cout << "Las aristas del arbol de expansion son:" << endl;
    for (auto& arista : resultado) 
    {
        cout << arista.origen << " -- " << arista.destino << " == " << arista.peso << endl;
    }

    delete[] subconjuntos;
}

Grafo crearGrafo(int V, int E) 
{
    Grafo grafo;
    grafo.V = V;
    grafo.E = E;
    return grafo;
}

int main() 
{
    int V = 4;
    int E = 5;
    Grafo grafo = crearGrafo(V, E);

    grafo.aristas.push_back({ 0, 1, 10 });
    grafo.aristas.push_back({ 0, 2, 6 });
    grafo.aristas.push_back({ 0, 3, 5 });
    grafo.aristas.push_back({ 1, 3, 15 });
    grafo.aristas.push_back({ 2, 3, 4 });

    kruskal(grafo);

    return 0;
}
