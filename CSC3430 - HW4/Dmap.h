//////////////////////////////////////////////////////////////////////////////////////////////
//Dmap.h																					//
//Written by: Benjamin Stout																//
//Date: 2/17/16																				//
//Description: CSC 3430 HW #4 - Dijkstra map class for Dijkstra algorithm implementation	//
//Loosely adapted from Dijkstra algorithm C++ program at									//
//http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/	//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <limits>

#define SIZE 9

class Dmap {
public:
	//type definitition for vector objects
	typedef std::tuple<int, int, bool> Dnode;

	//constructor
	Dmap() {
		for (int i = 0; i < SIZE; ++i) {
			data.push_back(Dnode(i, INT_MAX, false));
		}
	};

	//sets vertex info (vertex,[parent=-1],[distance=-1],[set=false])
	void Dset(int vertex, int parent = -1, int distance = -1, bool set = false) {
		//populate empty parameters
		if (parent == -1 || distance == -1 || !set) {
			Dnode node = data.at(vertex);
			if (parent == -1)			parent = std::get<0>(node);
			if (distance == -1)			distance = std::get<1>(node);
			if (!set && std::get<2>(node))	set = std::get<2>(node);
		}
		//set updated node info
		data.at(vertex) = Dnode(parent, distance, set);
	};

	//finds minimum distance vertex not yet set and returns index
	int Dmin() {
		int min = INT_MAX, i = 0, index;

		for (std::vector<Dnode>::iterator it = data.begin(); it != data.end(); ++it, ++i) {
			int dist = std::get<1>(*it);
			bool set = std::get<2>(*it);

			if (!set && dist <= min) {
				min = dist;
				index = i;
			}
		}
		return index;
	};

	//updates distances of all vertexes adjacent to source
	void Dupdate(int source, int adj[SIZE]) {
		Dnode srcnode = data.at(source);
		int srcdist = std::get<1>(srcnode);

		for (int i = 0; i < SIZE; ++i) {
			Dnode adjnode = data.at(i);
			int adjdist = adj[i];

			if (!std::get<2>(adjnode) && adjdist && srcdist != INT_MAX && srcdist + adjdist < std::get<1>(adjnode))
				Dset(i, source, srcdist + adjdist, false);
		}
	};

	//prints contents of data vector
	void Dprint(int start) {
		int i = 0;

		std::cout << "Vertex\tDistance from Source:\t" << start << std::endl;

		for (std::vector<Dnode>::iterator it = data.begin(); it != data.end(); ++it, ++i) {
			int parent = i;
			std::string path = "";

			std::cout << i << "\t\t" << std::get<1>(*it) << "\tPath:\t" << start;
			while (parent != start) {
				path.insert(0, "-->" + std::to_string(parent));
				parent = std::get<0>(data.at(parent));
			}
			std::cout << path << std::endl;
		}
		std::cout << std::endl;
	};

private:
	std::vector<Dnode> data;
};