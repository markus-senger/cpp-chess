#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Pawn : public ChessFigure {
	public:
		Pawn(swe::ChessBoard& chessBoard, sf::Sprite& sprite, bool essential)
			: ChessFigure{ chessBoard, sprite, essential } {

		}

		void showSteps() override {

		}

		void move() override {

		}

		void draw(sf::RenderWindow& window, sf::Vector2f pos) override {
			mSprite.setPosition(pos);
			window.draw(mSprite);
		}

	private:

	};
}