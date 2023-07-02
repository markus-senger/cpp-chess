#include "chessFigure.h"
#include "chessBoard.h"

namespace swe {
	ChessFigure::ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
		: mChessBoard{ chessBoard }, mSpriteHandler{ spriteHandler }, mFigureSprite{ figureSprite },
		mEssential{ essential }, mColor{ color }, mSelected{ false }, mRow{ row }, mCol{ col } {

	}

	void ChessFigure::move(int row, int col) {
		mChessBoard.getBoardWithFigures()[(row * 8) + col] = mChessBoard.getBoardWithFigures()[(mRow * 8) + mCol];
		mChessBoard.getBoardWithFigures()[(mRow * 8) + mCol] = nullptr;
		mRow = row;
		mCol = col;
		mSelected = false;
	}

	void ChessFigure::draw(sf::RenderWindow& window, sf::Vector2f pos) {
		if (mSelected) {
			sf::Sprite& spriteSelectedField = mSpriteHandler.getSelectedFieldSprite();
			spriteSelectedField.setPosition(sf::Vector2f(pos.x + 13, pos.y + 15));
			window.draw(spriteSelectedField);
			showSteps(window);

			mFigureSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - mFigureSprite.getGlobalBounds().width / 2, sf::Mouse::getPosition(window).y - mFigureSprite.getGlobalBounds().height / 2));
		}
		else
			mFigureSprite.setPosition(pos);
		window.draw(mFigureSprite);
	};

	void ChessFigure::setSelected(bool value) {
		mSelected = value;
	}

	bool ChessFigure::getSelected() {
		return mSelected;
	}

	swe::Color ChessFigure::getColor() {
		return mColor;
	}
}
