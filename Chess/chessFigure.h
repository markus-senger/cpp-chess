#pragma once

#include <SFML/Graphics.hpp>

namespace swe {
	class ChessBoard;

	class ChessFigure {
	public:
		ChessFigure(swe::ChessBoard& chessBoard, sf::Sprite& spriteFigrue, sf::Sprite& spriteSelectedField, bool essential, int row, int col);

		virtual void showSteps() = 0;
		void move(int row, int col);

		void draw(sf::RenderWindow& window, sf::Vector2f pos);

		void setSelected(bool value);

		bool getSelected();


	protected:
		swe::ChessBoard& mChessBoard;
		sf::Sprite& mSpriteFigure;
		sf::Sprite& mSpriteSelectedField;

		bool mEssential;
		bool mSelected;
		int mRow;
		int mCol;
	};
}
