#pragma once
#include <SFML/Graphics.hpp>



const int _INF = 2147483647;



class Apex {
	private:

		sf::CircleShape circle;
		sf::Text text;
		float radius;
		//Sprite sprite;

	public:

		Apex();
		Apex(const Apex&);
		Apex(const sf::String&, const sf::Font&);
		~Apex();
		Apex& operator=(const Apex&);
		void setPosition(float, float);
		void draw(sf::RenderWindow&);
		sf::Vector2f getPosition();
		sf::Vector2f getCenter();
		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();
		static void getPolygonSpread(std::vector<Apex>&, const sf::Vector2f&, const int&);

};