// Komiwojazer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#define max_Tops 50 

using namespace std;

struct edge{
	int top, lenght;
};

int lenght_Ham = INT_MAX,
lenght = 0,
top_Start;

vector <edge> L[max_Tops + 1];
vector <int> cyckle_Ham, cyckle;

bool visited[max_Tops + 1];
ifstream file;

int load_Graph(char *name, int args)
{
	edge edge;
	file.open(name);
	if (!file || args != 3)
	{
		system("Pause");
		exit(1);
	}

	int i = 0;
	int j = 0;
	while (!file.eof())
	{
		file >> edge.lenght;
		if (edge.lenght != 0)
		{
			edge.top = i;
			L[j].push_back(edge);
			edge.top = j;
			L[i].push_back(edge);
		}
		if ((char)file.get() == '\n')
		{
			i = 1;
			j++;
		}
		else
		{
			i++;
		}
	}
	file.close();
	if (j<top_Start || i>top_Start)
	{
		system("Pause");
		exit(1);
	}
	return j;
}

void print_Graph()
{
	cout << "Krawedzie: \n<od>-<do>-<dlugosc>\n";
	for (int j = 1; j <= 8; j++)
	{
		cout << "\n";
		for (int i = 0; i < L[j].size(); i++)
		{
			cout << j << "-" << L[j][i].top << "-" << L[j][i].lenght << "  ";
		}
	}
	cout << "\n\n";
}

void komi(int v, int top_count)
{
	cyckle.push_back(v);
	if (cyckle.size() == top_count)
	{
		for (int i = 0; i < L[v].size(); i++)
		{
			if (L[v][i].top == top_Start)
			{
				lenght += L[v][i].lenght;
				if (lenght < lenght_Ham)
				{
					lenght_Ham = lenght;
					cyckle_Ham.assign(cyckle.begin(), cyckle.end());
					cyckle_Ham.push_back(top_Start);
				}
				lenght -= L[v][i].lenght;
				break;
			}
		}
	}
	else                                                      //w przeciwnym wypadku
	{
		visited[v] = true;                                   //oznacz wierzcholek jako odwiedzony
		for (int i = 0; i < L[v].size(); i++)                        //dla kazdej krawedzi danego wierzcholka
		{
			if (!visited[L[v][i].top])              //jezeli dany wierzcholek jeszcze nei odwiedzony
			{
				lenght += L[v][i].lenght;                     //zwieksz dlugosc
				komi(L[v][i].top, top_count); //wywolaj rekurencyjnie funkcje dla danego wierzcholka
				lenght -= L[v][i].lenght;                     //zmniejsz dlugosc
			}
		}
		visited[v] = false;                                  //oznacz wierzcholek jako nieodwiedzony
	}
	cyckle.pop_back();
}

void print_Cycle()                                            //drukowanie cyklu
{
	if (cyckle_Ham.size() != 0)
	{
		cout << "Znaleziony cykl Hamiltona:\n";
		for (int i = 0; i < cyckle_Ham.size(); i++)
		{
			cout << cyckle_Ham[i] << " ";
		}
		cout << "\n\nDlugosc drogi: " << lenght_Ham << "\n";
	}
	else cout << "Podany graf nie ma cyklu hamiltona.\n";
	cout << "\nNacisnij dowolny klawisz aby zakonczyc ...";
	getchar();
}

int _tmain(int argc, char *argv[])
{
	top_Start = atoi(argv[2]);                               

	int ilosc_wierzcholkow = load_Graph(argv[1], argc);      

	for (int i = 1; i <= ilosc_wierzcholkow; i++)visited[i] = false;

	print_Graph();                                          

	komi(top_Start, ilosc_wierzcholkow);                   

	print_Cycle();                                            

	return 0;
}

