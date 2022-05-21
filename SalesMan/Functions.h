#pragma once
#include "SFML/Graphics.hpp"
#include "Apex.h"
#include "Edge.h"
#include "Graph.h"
#include <vector>



//



void showWayInfo(Graph& g, std::vector<std::wstring>& names) {
	std::vector<pair<int, int>> wayParts = g.getRoads();
	std::cout << "Отрезки пути гамильтонова цикла:" << endl;
	for (int i = 0; i < wayParts.size(); ++i) {
		std::wcout << names[wayParts[i].first] << L"  ->  " << names[wayParts[i].second] << endl;
	}
	std::cout << endl << "Наименьший замкнутый путь с началом в точке ";
	std::wcout << names[0];
	std::cout << ": ";
	wayParts = g.sortRoads(1);
	std::wcout << names[wayParts[0].first];
	for (int i = 0; i < wayParts.size(); ++i) {
		std::wcout << " --> " << names[wayParts[i].second];
	}
}



std::vector<std::vector<int>> inputMatrix(std::vector<std::wstring>& names) {
	int vertiXCount;
	cout << "Введите количество вершин: ";
	cin >> vertiXCount;
	std::vector<std::vector<int>> matrix(vertiXCount);
	for (int i = 0; i < vertiXCount; ++i) {
		matrix[i] = std::vector<int>(vertiXCount);
	}
	names.erase(names.begin(), names.end());
	names.resize(vertiXCount);
	for (int i = 0; i < vertiXCount; ++i) {
		names[i] = std::to_wstring(i + 1);
	}
	int temp = 0;
	for (int i = 0; i < vertiXCount; ++i) {
		for (int j = i + 1; j < vertiXCount; ++j) {
			if (i != j) {
				cout << "Введите длину дороги между " << i + 1 << " вершиной и " << j + 1 << " вершиной: ";
				cin >> temp;
				if (temp <= 0) {
					matrix[i][j] = _INF;
					matrix[j][i] = _INF;
				} else {
					matrix[i][j] = temp;
					matrix[j][i] = temp;
				}
			} else matrix[i][j] = _INF;

		}
		names.push_back(std::to_wstring(i + 1));
	}
	return matrix;
}




std::vector<std::vector<int>> addVertex(std::vector<std::vector<int>>& matrix, std::vector<std::wstring>& names) {
	matrix.resize(matrix.size() + 1);
	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i].resize(matrix[i].size() + 1);
	}
	matrix.back() = std::vector<int>(matrix.size()); std::wcout << names.back() << endl;
	names.push_back(std::to_wstring(std::stoi(names.back()) + 1));
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	int temp;
	for (int i = 0; i < matrix.size() - 1; ++i) {
		std::cout << "Введите длину дороги из ";
		std::wcout << names[i];
		std::cout << " в ";
		std::wcout << names.back();
		std::cout << ": ";
		cin >> temp;
		if (temp <= 0) { 
			matrix[i].back() = _INF; 
			matrix.back()[i] = _INF;
		} else {
			matrix[i].back() = temp;
			matrix.back()[i] = temp;
		}
	}
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	matrix.back().back() = _INF;
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	return matrix;
}



std::vector<std::vector<int>> removeVertex(std::vector<std::vector<int>>& matrix, std::vector<std::wstring>& names) {
	bool isFind = false;
	int reverseVert;
	do {
		cout << "Введите вершину для удаления: ";
		cin >> reverseVert;
		for (int i = 0; i < names.size() && !isFind; ++i) {
			if (std::to_wstring(reverseVert) == names[i]) {
				isFind = true;
				reverseVert = i;
			}
		}
		if (!isFind) {
			std::cout << "Такой вершины нет, повторите ввод!" << endl;
		}
	} while (!isFind);

	std::vector<std::vector<int>> copy(matrix.size() - 1);
	for (int i = 0; i < copy.size(); ++i) {
		copy[i] = std::vector<int>(copy.size());
	}
		
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = i; j < matrix.size(); ++j) {
			if (i < reverseVert && j < reverseVert) {
				copy[i][j] = matrix[i][j];
			} else if (i < reverseVert && j > reverseVert) {
				copy[i][j - 1] = matrix[i][j];
				copy[i - 1][j] = matrix[i][j];
			} else if (i > reverseVert && j > reverseVert) {
				copy[i - 1][j - 1] = matrix[i][j];
			}
		}
	}
	matrix = copy;
	int i = 0;
	for (auto iter = names.begin(); i <= reverseVert; ++i, ++iter) {
		if (i == reverseVert) {
			names.erase(iter);
			break;
		}
	}
	return matrix;
}



// выбор вершины для движения
void getMove(Apex*& movingApex, std::vector<Apex>& vertList, const sf::Event& event, const sf::Vector2i& cursorPos) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			for (int i = 0; i < vertList.size(); ++i) {
				if (vertList[i].getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
					movingApex = &vertList[i];
				}
			}
		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		if (event.key.code == sf::Mouse::Left) {
			movingApex = nullptr;
		}
	}
}



// движение вершины
void move(Apex*& movingApex, const sf::Vector2i& cursorPos, const int& windowWidth, const int& windowHeight) {
	if (movingApex != nullptr) {
		float dx = cursorPos.x - movingApex->getLocalBounds().width / 2;
		float dy = cursorPos.y - movingApex->getLocalBounds().height / 2;
		if (dx < 0) {
			dx = 2;
		}
		if (dy < 0) {
			dy = 2;
		}
		if (dx + movingApex->getLocalBounds().width > windowWidth) {
			dx = windowWidth - movingApex->getLocalBounds().width;
		}
		if (dy + movingApex->getLocalBounds().height > windowHeight) {
			dy = windowHeight - movingApex->getLocalBounds().height;
		}
		movingApex->setPosition(dx, dy);
	}
}



// вывод матрицы смежности в консоли
void printInfo(std::vector<std::vector<int>>& matrix, std::vector<std::wstring>& names) {
	std::cout << "Матрица смежности:";
	std::cout << '\n' << '\t';
	for (int i = 0; i < matrix.size(); ++i) {
		std::wcout << names[i] << '\t';
	}
	std::cout << '\n';
	for (int i = 0; i < matrix.size(); ++i) {
		std::wcout << names[i] << '\t';
		for (int j = 0; j < matrix.size(); ++j) {
			if (matrix[i][j] == _INF) {
				std::cout << 'N' << '\t';
			}
			else  std::cout << matrix[i][j] << '\t';
		}
		std::cout << '\n';
	}
}