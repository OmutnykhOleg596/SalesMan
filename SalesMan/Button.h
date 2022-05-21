#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Button {
	private:
		sf::RectangleShape form;
		sf::Text info;
	public:
		Button(std::wstring&, sf::Font&);
		~Button();
		void setPosition(const float& x, const float& y);
		void buttonEvent(const sf::Vector2i& cursorPos, sf::Clock& timer, const sf::Event& event, std::function<void()> action);
		void draw(sf::RenderWindow&);
};