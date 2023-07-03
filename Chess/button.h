#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace swe {
    class Button {
    public:
        Button(std::string const path, std::string const pathMouseOver) : Button(sf::Vector2f(0, 0), path, pathMouseOver) {
        }

        Button(sf::Vector2f const& position, std::string const path, std::string const pathMouseOver) {
            mTexture.loadFromFile(path);
            mSprite.setTexture(mTexture);

            sf::Vector2f spriteSize(mSprite.getLocalBounds().width, mSprite.getLocalBounds().height);
            mSprite.setOrigin(spriteSize / 2.001f); // with 2.0 there seems to be a pixel bug
            mSprite.setPosition(position);

            mTextureMouseOver.loadFromFile(pathMouseOver);
            mSpriteMouseOver.setTexture(mTextureMouseOver);
            mSpriteMouseOver.setPosition(position);
            mSpriteMouseOver.setOrigin(spriteSize / 2.001f); // with 2.0 there seems to be a pixel bug
        }

        void setPosition(sf::Vector2f const& position) {
            mSprite.setPosition(position);
            mSpriteMouseOver.setPosition(position);
        }

        void draw(sf::RenderWindow& window) {
            if (isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                window.draw(mSpriteMouseOver);
            else
                window.draw(mSprite);
        }

        bool isMouseOver(const sf::Vector2f& mousePosition) const {
            return mSprite.getGlobalBounds().contains(mousePosition);
        }

    private:
        sf::Texture mTexture;
        sf::Sprite mSprite;
        sf::Texture mTextureMouseOver;
        sf::Sprite mSpriteMouseOver;
    };
}