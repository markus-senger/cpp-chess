#pragma once

#include <SFML/Graphics.hpp>

namespace swe {
	class ChessBoard;

	class ChessFigure {
	public:
		ChessFigure(swe::ChessBoard& chessBoard, sf::Sprite& sprite, bool essential) 
			: mChessBoard{ chessBoard }, mSprite{ sprite }, mEssential{ essential } {

		}

		virtual void showSteps() = 0;
		virtual void move() = 0;
		virtual void draw(sf::RenderWindow& window, sf::Vector2f pos) = 0;


	protected:
		swe::ChessBoard& mChessBoard;
		sf::Sprite mSprite;

		bool mEssential;

	};
}
