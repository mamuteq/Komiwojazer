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

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

