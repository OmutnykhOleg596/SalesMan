#include "Edge.h"



// конструктор без параметров
Edge::Edge() {}



// конструктор с параметрами
Edge::Edge(const sf::Font& font, const int& length) {
	this->weight = length;
	this->info = sf::Text(L""/* + std::to_string(this->weight)*/, font, 15);
	this->info.setString(std::to_string(this->weight));
	this->edge[0].color = sf::Color::Blue; this->edge[1].color = sf::Color::Blue;
	this->info.setFillColor(sf::Color::Black);
	this->edge[0].color = sf::Color::Black;
	this->edge[1].color = sf::Color::Black;
}



// деструктор
Edge::~Edge() {}



// получение средней точки между двумя точками
sf::Vector2f Edge::getCenter(const sf::Vector2f& first, const sf::Vector2f& second) {
	return sf::Vector2f((first.x + second.x) / 2, (first.y + second.y) / 2);
}



// получение начальной координаты
sf::Vector2f Edge::getFirstPoint() {
	return this->edge[0].position;
}



// получение конечной координаты
sf::Vector2f Edge::getSecondPoint() {
	return this->edge[1].position;
}



// получение веса ребра
int Edge::getWeight() {
	return this->weight;
}



// установка позиции ребра
void Edge::setPosition(const sf::Vector2f& first, const sf::Vector2f& second) {
	this->edge[0].position = first; this->edge[1].position = second;
	this->info.setPosition(getCenter(this->edge[0].position, this->edge[1].position));
}



// установка цвета ребра
void Edge::setFillColor(const sf::Color& color) {
	edge[0].color = color;
	edge[1].color = color;
}



// отрисовка ребра
void Edge::draw(sf::RenderWindow& window) {
	window.draw(this->edge, 2, sf::Lines);
	window.draw(this->info);
}