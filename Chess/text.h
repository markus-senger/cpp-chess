#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace swe {
    class Text {
    public:
        Text(sf::Vector2f const& position, sf::Font const& font, unsigned int const fontSize, std::string const& str, sf::Color const color = sf::Color::Black) {
            text.setFont(font);
            text.setCharacterSize(fontSize);
            text.setString(str);
            text.setFillColor(color);
            sf::Vector2f size(text.getLocalBounds().width, text.getLocalBounds().height);
            text.setOrigin(size / 2.0f);
            text.setPosition(position);
        }

        void draw(sf::RenderWindow& window) const {
            window.draw(text);
        }

    private:
        sf::Text text;
    };
}
