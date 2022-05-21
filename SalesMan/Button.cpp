#include "Button.h"



// конструктор с параметрами
Button::Button(std::wstring& text, sf::Font& font) {
	this->info.setString(text);
	this->info.setFont(font);
	this->info.setCharacterSize(15);
	this->info.setFillColor(sf::Color::Black);
	this->form.setSize(sf::Vector2f(100, 35));
	this->form.setOutlineThickness(2.f);
	//this->form.setOutlineColor(sf::Color::Black);
	//this->form.setFillColor(sf::Color::Red/*(97, 160, 58)*/);
}



// деструктор
Button::~Button() {

}



// установка позиции кнопки
void Button::setPosition(const float& x, const float& y) {
	this->form.setPosition(x - this->form.getLocalBounds().width / 2, y - this->form.getLocalBounds().height / 2);
	this->info.setPosition(x - this->info.getLocalBounds().width / 2, y - this->info.getLocalBounds().height);
}



// обработка нажатия на кнопку
void Button::buttonEvent(const sf::Vector2i& cursorPos, sf::Clock& clock, const sf::Event& event, std::function<void()> action) {
	if (this->form.getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
		float time = clock.getElapsedTime().asMilliseconds();
		bool isActive = true;
		if (time < 5.f) {
			isActive = false;
		} else {
			clock.restart();
			isActive = true;
		}
		this->form.setOutlineThickness(3.f);
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == sf::Mouse::Left && isActive) {
				this->form.setFillColor(sf::Color(97, 160, 58));
			}
		} else if (event.type == sf::Event::MouseButtonReleased && isActive) {
			if (event.key.code == sf::Mouse::Left) {
				this->form.setFillColor(sf::Color(171, 121, 85));
				action();
			}
		}
	} else {
		this->form.setOutlineThickness(2.f);
		this->form.setFillColor(sf::Color(97, 160, 58));
	}
}



// отрисовка кнопка
void Button::draw(sf::RenderWindow& window) {
	window.draw(this->form);
	window.draw(this->info);
}