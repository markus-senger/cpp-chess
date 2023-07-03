#pragma once

#include <SFML/Graphics.hpp>
#include "spriteHandler.h"
#include "color.h"

namespace swe {
	class ChessBoard;

	class ChessFigure {
	public:
		ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col);

		virtual void showSteps(sf::RenderWindow& window) = 0;
		void move(int row, int col);

		void draw(sf::RenderWindow& window, sf::Vector2f pos);

		void scale(sf::Vector2f scaleFactor);

		void setSelected(bool value);

		bool getSelected();

		swe::Color getColor();

		float getHeight();


	protected:
		swe::ChessBoard& mChessBoard;
		swe::SpriteHandler& mSpriteHandler;
		sf::Sprite mFigureSprite;

		bool mEssential;
		swe::Color mColor;
		bool mSelected;
		int mRow;
		int mCol;
	};
}
