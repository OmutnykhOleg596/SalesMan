#include "Apex.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace std;



// конструктор без параметров
Apex::Apex() {}



// конструктор копирования
Apex::Apex(const Apex& temp) {
	this->circle = temp.circle;
	this->text = temp.text;
}



// конструктор с параметрами
Apex::Apex(const sf::String& text, const sf::Font& font) {
	this->text = sf::Text(L"" + text, font, 15);
	this->text.setFillColor(sf::Color::Black);
	this->radius = 30.f;
	this->circle = sf::CircleShape(radius);
	this->circle.setFillColor(sf::Color::Red/*(125, 150, 100)*/);
}



// деструктор
Apex::~Apex() {}



// перегрузка оператора присваивания
Apex& Apex::operator=(const Apex& temp) {
	this->circle = temp.circle;
	this->text = temp.text;
	return *this;
}



// получение границ вершины
sf::FloatRect Apex::getLocalBounds() {
	return this->circle.getLocalBounds();
}



// получение границ вершины в глобальной системе координат
sf::FloatRect Apex::getGlobalBounds() {
	return this->circle.getGlobalBounds();
}



// получение позиции вершины
sf::Vector2f Apex::getPosition() {
	return this->circle.getPosition();
}



// получение позиции центра вершины
sf::Vector2f Apex::getCenter() {
	return sf::Vector2f(this->circle.getPosition().x + (this->circle.getLocalBounds().width / 2), this->circle.getPosition().y + (this->circle.getLocalBounds().height / 2));
}



// расстановка графа
void Apex::getPolygonSpread(std::vector<Apex>& vertexList, const sf::Vector2f& SPREAD_CENTER, const int& SPREAD_RADIUS) {
	const float PI = acosf(-1);
	for (int i = 0; i < vertexList.size(); ++i) {
		vertexList[i].setPosition(SPREAD_CENTER.x + SPREAD_RADIUS * cosf(2 * PI * i / vertexList.size()), SPREAD_CENTER.y + SPREAD_RADIUS * sinf(2 * PI * i / vertexList.size()));
	}
}



// установка вершины по заданным координатам
void Apex::setPosition(float x, float y) {
	this->circle.setPosition(x, y);
	this->text.setPosition(x + (this->circle.getLocalBounds().width / 2) - (this->text.getLocalBounds().width / 2), y + (this->circle.getLocalBounds().height / 2) - (this->text.getLocalBounds().height));
}



// отрисовка вершины
void Apex::draw(sf::RenderWindow& window) {
	window.draw(this->circle);
	window.draw(this->text);
}