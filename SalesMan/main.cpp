#include "Apex.h"
#include "Button.h"
#include "Edge.h"
#include "Functions.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>



using namespace std;
using namespace sf;



Font font;



int main() {
	// настройка окна, загрузка шрифта
	setlocale(LC_ALL, "Rus");
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(800, 600), "MainWindow", sf::Style::Default, settings);

	vector<vector<int>> matrix = {
		vector<int> { _INF, 10, 7, 5, 1, 35, 13 },
		vector<int> { 10, _INF, 38, 45, 58, 17, 47 },
		vector<int> { 7, 38, _INF, 23, 32, 25, 9 },
		vector<int> { 5, 45, 23, _INF, 11, 17, 31 },
		vector<int> { 1, 58, 32, 11, _INF, 8, 1 },
		vector<int> { 35, 17, 25, 17, 8, _INF, 23 },
		vector<int> { 13, 47, 9, 31, 1, 23, _INF }
	};
	vector<wstring> names = { L"1", L"2", L"3", L"4", L"5", L"6", L"7"};
	vector<wstring> buttonNames = { L"Ввод", L"Добавить", L"Удалить" };

	Graph g(matrix, names, font);
	Apex* movingApex = nullptr;

	Button enterButton(buttonNames[0], font);
	enterButton.setPosition(100.f, 530.f);
	Button addButton(buttonNames[1], font);
	addButton.setPosition(275.f, 530.f);
	Button deleteButton(buttonNames[2], font);
	deleteButton.setPosition(450.f, 530.f);

	Clock timer;

	g.drawHamiltoneCycle();
	printInfo(g.adjMatrix, names);
	showWayInfo(g, names);

	while (window.isOpen()) {
		Vector2i cursorPos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			enterButton.buttonEvent(cursorPos, timer, event, [&g, &names]()->void {
				system("cls");
				vector<vector<int>> matrix = inputMatrix(names);
				g.update(matrix, names, font);
				g.drawHamiltoneCycle();
				printInfo(g.adjMatrix, names);
				showWayInfo(g, names);
			});

			addButton.buttonEvent(cursorPos, timer, event, [&g, &names]()->void {
				if (g.adjMatrix.size() < 10) {
					system("cls");
					std::vector<std::vector<int>> matrix = addVertex(g.adjMatrix, names);
					printInfo(g.adjMatrix, names);
					g.update(matrix, names, font);
					g.drawHamiltoneCycle();
					printInfo(g.adjMatrix, names);
					showWayInfo(g, names);
				} else {
					cout << "Максимальное количество вершин, невозможно добавить!" << endl;
				}
			});

			deleteButton.buttonEvent(cursorPos, timer, event, [&g, &names]()->void {
				if (g.adjMatrix.size() > 3) {
					system("cls");
					std::vector<std::vector<int>> matrix = removeVertex(g.adjMatrix, names);
					g.update(matrix, names, font);
					g.drawHamiltoneCycle();
					printInfo(g.adjMatrix, names);
					showWayInfo(g, names);
				}
				else {
					std::cout << "Дальнейшее удаление невозможно!" << endl;
				}
			});

			getMove(movingApex, g.vertexList, event, cursorPos);

		}

		window.clear(Color::White);

		g.snapEdgesToVerts();
		move(movingApex, cursorPos, 800, 500);

		// отрисовка всех объектов
		for (unsigned int i = 0; i < g.edgeList.size(); ++i) {
			g.edgeList[i].draw(window);
		}

		for (unsigned int i = 0; i < g.vertexList.size(); ++i) {
			g.vertexList[i].draw(window);
		}

		enterButton.draw(window);
		deleteButton.draw(window);
		addButton.draw(window);
		window.display();
	}
}