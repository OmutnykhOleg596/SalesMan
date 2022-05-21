#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Edge {
	private:

		sf::Vertex edge[2];
		sf::Text info;
		int weight;

	public:

		Edge();
		Edge(const sf::Font&, const int&);
		~Edge();
		sf::Vector2f getFirstPoint();
		sf::Vector2f getSecondPoint();
		sf::Vector2f getCenter(const sf::Vector2f&, const sf::Vector2f&);
		int getWeight();
		void setPosition(const sf::Vector2f&, const sf::Vector2f&);
		void setFillColor(const sf::Color&);
		void draw(sf::RenderWindow&);

};