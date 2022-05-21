#pragma once
#include "Apex.h"
#include "Edge.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace std;


class Graph {
	private:
	public:
		std::vector<Apex> vertexList;
		std::vector<Edge> edgeList;
		std::vector<std::vector<int>> adjMatrix;
		Graph();
		Graph(std::vector<std::vector<int>>&, const std::vector<std::wstring>&, const sf::Font&);
		~Graph();
		int getCountVertex();
		int getCountEdges();
		int minElemOfColumn(std::vector<std::vector<int>>, const int&);
		int minElemOfRow(std::vector<std::vector<int>>, const int&);
		bool isAdjMatrixNotEmpty(std::vector<std::vector<int>>);
		std::vector<std::pair<int, int>> getRoads();
		std::vector<std::pair<int, int>> sortRoads(const int&);
		void snapEdgesToVerts();
		void drawHamiltoneCycle();
		void update(std::vector<std::vector<int>>&, const std::vector<std::wstring>&, const sf::Font&);

};