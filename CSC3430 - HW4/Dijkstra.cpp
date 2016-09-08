//////////////////////////////////////////////////////////////////////////////////////////////
//Dijkstra.cpp																				//
//Written by: Benjamin Stout																//
//Date: 2/17/16																				//
//Description: CSC 3430 HW #4 - Dijkstra shortest-path algorithm							//
//Loosely adapted from Dijkstra algorithm C++ program at									//
//http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/	//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include "Dmap.h"

using namespace std;

void Dsearch(int[SIZE][SIZE], int);

int main() {
	char ch;
	//weighted adjacency matrix (undirected, connected, no self-cycles)
	int matrix[SIZE][SIZE] = {	{ 0,  4,  0,  0,  0,  0,  0,  8,  0 },
								{ 4,  0,  8,  0,  0,  0,  0, 11,  0 },
								{ 0,  8,  0,  7,  0,  4,  0,  0,  2 },
								{ 0,  0,  7,  0,  9, 14,  0,  0,  0 },
								{ 0,  0,  0,  9,  0, 10,  0,  0,  0 },
								{ 0,  0,  4, 14, 10,  0,  2,  0,  0 },
								{ 0,  0,  0,  0,  0,  2,  0,  1,  6 },
								{ 8, 11,  0,  0,  0,  0,  1,  0,  7 },
								{ 0,  0,  2,  0,  0,  0,  6,  7,  0 }
								};

	//run Dijkstra algorithm starting from each vertex
	for (int i = 0; i < SIZE; ++i) Dsearch(matrix, i);

	cout << "Press any key to close...";
	cin.get(ch);
	return 0;
}

void Dsearch(int graph[SIZE][SIZE], int start) {
	//new dijkstra map
	Dmap map;

	//set starting node's distance to 0
	map.Dset(start, start, 0);

	for (int i = 0; i < SIZE; ++i) {
		//find closest vertex
		int closest = map.Dmin();
		//set closest vertex's parent and mark as processed
		map.Dset(closest, -1, -1, true);
		//update distances
		map.Dupdate(closest, graph[closest]);
	}
	//print dijkstra map
	map.Dprint(start);
}