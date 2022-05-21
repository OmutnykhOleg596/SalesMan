#include "Edge.h"



// ����������� ��� ����������
Edge::Edge() {}



// ����������� � �����������
Edge::Edge(const sf::Font& font, const int& length) {
	this->weight = length;
	this->info = sf::Text(L""/* + std::to_string(this->weight)*/, font, 15);
	this->info.setString(std::to_string(this->weight));
	this->edge[0].color = sf::Color::Blue; this->edge[1].color = sf::Color::Blue;
	this->info.setFillColor(sf::Color::Black);
	this->edge[0].color = sf::Color::Black;
	this->edge[1].color = sf::Color::Black;
}



// ����������
Edge::~Edge() {}



// ��������� ������� ����� ����� ����� �������
sf::Vector2f Edge::getCenter(const sf::Vector2f& first, const sf::Vector2f& second) {
	return sf::Vector2f((first.x + second.x) / 2, (first.y + second.y) / 2);
}



// ��������� ��������� ����������
sf::Vector2f Edge::getFirstPoint() {
	return this->edge[0].position;
}



// ��������� �������� ����������
sf::Vector2f Edge::getSecondPoint() {
	return this->edge[1].position;
}



// ��������� ���� �����
int Edge::getWeight() {
	return this->weight;
}



// ��������� ������� �����
void Edge::setPosition(const sf::Vector2f& first, const sf::Vector2f& second) {
	this->edge[0].position = first; this->edge[1].position = second;
	this->info.setPosition(getCenter(this->edge[0].position, this->edge[1].position));
}



// ��������� ����� �����
void Edge::setFillColor(const sf::Color& color) {
	edge[0].color = color;
	edge[1].color = color;
}



// ��������� �����
void Edge::draw(sf::RenderWindow& window) {
	window.draw(this->edge, 2, sf::Lines);
	window.draw(this->info);
}