#include "Graph.h"



// ����������� ��� ����������
Graph::Graph() {}



// ����������� � �����������
Graph::Graph(vector<vector<int>>& tempMatrix, const vector<wstring>& names, const sf::Font& font) {

	this->adjMatrix.assign(tempMatrix[0].size(), vector<int>(tempMatrix[0].size()));
	for (int i = 0; i < tempMatrix[0].size(); ++i) {
		for (int j = 0; j < tempMatrix[0].size(); ++j) {
			this->adjMatrix[i][j] = tempMatrix[i][j];
		}
	}

	this->vertexList = vector<Apex>(this->getCountVertex());
	for (int i = 0; i < this->getCountVertex(); ++i) {
		this->vertexList[i] = Apex(names[i], font);
	}

	const sf::Vector2f& SPREAD_CENTER = sf::Vector2f(230.f, 230.f);
	const int& SPREAD_RADIUS = 210;
	Apex::getPolygonSpread(this->vertexList, SPREAD_CENTER, SPREAD_RADIUS);

	for (int i = 0; i < this->getCountVertex(); ++i) {
		for (int j = i + 1; j < this->getCountVertex(); ++j) {
			if (this->adjMatrix[i][j] != _INF) {
				this->edgeList.push_back(Edge(font, this->adjMatrix[i][j]));
				this->edgeList.back().setPosition(this->vertexList[i].getCenter(), this->vertexList[j].getCenter());
			}

		}
	}
}



// ����������
Graph::~Graph() {}




// ���������� ������
int Graph::getCountVertex() {
	return this->adjMatrix.size();
}



// ���������� �����
int Graph::getCountEdges() {
	return this->edgeList.size();
}



// ����� ������������ �������� �������
int Graph::minElemOfColumn(vector<vector<int>> matrix, const int& index) {
	int minimum = _INF;
	for (int i = 0; i < this->getCountVertex(); ++i) {
		minimum = (matrix[i][index] < minimum) ? matrix[i][index] : minimum;
	}
	return minimum;
}



// ����� ������������ �������� ������
int Graph::minElemOfRow(vector<vector<int>> matrix, const int& index) {
	int minimum = _INF;
	for (int i = 0; i < this->getCountVertex(); ++i) {
		minimum = (matrix[index][i] < minimum) ? matrix[index][i] : minimum;
	}
	return minimum;
}



// �������� ����� �� �������
bool Graph::isAdjMatrixNotEmpty(vector<vector<int>> matrix) {
	bool isFind = false;
	int checkInf = _INF;
	for (int i = 0; i < this->getCountVertex(); ++i) {
		for (int j = 0; j < this->getCountVertex(); ++j) {
			// ���� ���� ���� ������� ����� � ���������� ���������
			if (matrix[i][j] != checkInf) {
				// �� ���������� true
				isFind = true;
			}
		}
	}
	return isFind;
}



// ��������� ����� ��� �����������
vector<pair<int, int>> Graph::getRoads() {
	int checkInf = _INF;
	vector<pair<int, int>> wayParts;
	vector<vector<int>> tempMatrix;
	tempMatrix = vector<vector<int>>(this->getCountVertex(), vector<int>(this->getCountVertex()));

	for (int i = 0; i < this->getCountVertex(); ++i) {
		for (int j = 0; j < this->getCountVertex(); ++j) {
			tempMatrix[i][j] = (this->adjMatrix[i][j] != 0 and this->adjMatrix[i][j] != checkInf) ? this->adjMatrix[i][j] : _INF;
		}
	}

	// ���� ������� ��������� �� �����
	while (this->isAdjMatrixNotEmpty(tempMatrix)) {

		// �������� �������� �����
		vector<int> minRowList;
		for (int i = 0; i < this->getCountVertex(); ++i) {
			minRowList.push_back(this->minElemOfRow(tempMatrix, i));
		}
		for (int i = 0; i < this->getCountVertex(); ++i) {
			for (int j = 0; j < this->getCountVertex(); ++j) {
				if (tempMatrix[i][j] != checkInf) {
					tempMatrix[i][j] -= minRowList[i];
				}
			}
		}

		vector<int> minColList;
		for (int i = 0; i < this->getCountVertex(); ++i) {
			minColList.push_back(this->minElemOfColumn(tempMatrix, i));
		}
		// �������� �������� ��������
		for (int i = 0; i < this->getCountVertex(); ++i) {
			for (int j = 0; j < this->getCountVertex(); ++j) {
				if (tempMatrix[i][j] != checkInf) {
					tempMatrix[i][j] -= minColList[j];
				}
			}
		}


		// ���������� ��� ������ ���������� ������� �����
		for (int i = 0; i < this->getCountVertex(); ++i) {
			for (int j = 0; j < this->getCountVertex(); ++j) {
				if (tempMatrix[i][j] <= 0) {
					tempMatrix[i][j] = -1 * (this->minElemOfRow(tempMatrix, i) + this->minElemOfColumn(tempMatrix, j));
				}
			}
		}

		//����� ���������� ������(����������)
		int maxGrade = _INF;
		int maxGrade_i = _INF;
		int maxGrade_j = _INF;
		for (int i = 0; i < this->getCountVertex(); ++i) {
			for (int j = 0; j < this->getCountVertex(); ++j) {
				if (maxGrade > tempMatrix[i][j]) {
					maxGrade = tempMatrix[i][j];
					maxGrade_i = i;
					maxGrade_j = j;
				}
			}
		}

		// ���������� ���������� ���� � �������� ������
		wayParts.push_back(pair<int, int>{ maxGrade_i, maxGrade_j });

		// ������� ������� � ������, ������� �� ����������� �������� ��� ������������
		for (int i = 0; i < this->getCountVertex(); ++i) {
			for (int j = 0; j < this->getCountVertex(); ++j) {
				if (i == maxGrade_i) {
					tempMatrix[i][j] = _INF;
				} 
				if (j == maxGrade_j) {
					tempMatrix[i][j] = _INF;
				}
				if (tempMatrix[i][j] < 0) {
					tempMatrix[i][j] = 0;
				}
			}
		}
		tempMatrix[maxGrade_i][maxGrade_j] = _INF;
		tempMatrix[maxGrade_j][maxGrade_i] = _INF;

	}
	return wayParts;
}



// ���������� ��� ������
vector<pair<int, int>> Graph::sortRoads(const int& number) {
	int index = number - 1;
	vector<pair<int, int>> roads = this->getRoads();
	for (int i = 0; i < roads.size(); ++i) {
		if (roads[i].first == index) {
			swap(roads[i], roads[0]);
		}
	}
	for (int i = 0; i < roads.size() - 1; ++i) {
		for (int j = i + 1; j < roads.size(); ++j) {
			if (roads[i].second == roads[j].first) {
				swap(roads[i + 1], roads[j]);
			}
		}
	}
	return roads;
}



// ���������� ������ ���� � ���������
void Graph::snapEdgesToVerts() {
	int counter = 0;
	for (int i = 0; i < this->getCountVertex(); ++i) {
		for (int j = i + 1; j < this->getCountVertex(); ++j) {
			if (this->adjMatrix[i][j] != _INF || this->adjMatrix[j][i] != _INF) {
				this->edgeList[counter].setPosition(this->vertexList[i].getCenter(), this->vertexList[j].getCenter());
				counter++;
			}
		}
	}
}



// ��������� ���� �����������
void Graph::drawHamiltoneCycle() {
	std::vector<pair<int, int>> wayParts = this->getRoads();
	for (int i = 0; i < wayParts.size(); ++i) {
		for (int j = 0; j < this->edgeList.size(); ++j) {
			if ((this->edgeList[j].getFirstPoint() == this->vertexList[wayParts[i].first].getCenter() && this->edgeList[j].getSecondPoint() == this->vertexList[wayParts[i].second].getCenter()) or
				(this->edgeList[j].getFirstPoint() == this->vertexList[wayParts[i].second].getCenter() && this->edgeList[j].getSecondPoint() == this->vertexList[wayParts[i].first].getCenter())) {
				this->edgeList[j].setFillColor(sf::Color::Cyan);
			}
		}
	}
}



// ���������� ����� � ����
void Graph::update(vector<vector<int>>& tempMatrix, const vector<wstring>& namesOfEdges, const sf::Font& font) {
	this->edgeList.erase(this->edgeList.begin(), this->edgeList.end());
	this->adjMatrix.assign(tempMatrix[0].size(), vector<int>(tempMatrix[0].size()));

	for (int i = 0; i < tempMatrix[0].size(); ++i) {
		for (int j = 0; j < tempMatrix[0].size(); ++j) {
			this->adjMatrix[i][j] = tempMatrix[i][j];
		}
	}
	this->vertexList = vector<Apex>(this->getCountVertex());
	for (int i = 0; i < this->getCountVertex(); ++i) {
		this->vertexList[i] = Apex(namesOfEdges[i], font);
	}

	const sf::Vector2f& SPREAD_CENTER = sf::Vector2f(230.f, 230.f);
	const int& SPREAD_RADIUS = 210;
	Apex::getPolygonSpread(vertexList, SPREAD_CENTER, SPREAD_RADIUS);

	for (int i = 0; i < this->getCountVertex(); ++i) {
		for (int j = i + 1; j < this->getCountVertex(); ++j) {
			if (this->adjMatrix[i][j] != _INF) {
				this->edgeList.push_back(Edge(font, this->adjMatrix[i][j]));
				this->edgeList.back().setPosition(this->vertexList[i].getCenter(), this->vertexList[j].getCenter());
			}

		}
	}
}
