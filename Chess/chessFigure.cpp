#include "chessFigure.h"
#include "chessBoard.h"

namespace swe {
	ChessFigure::ChessFigure(swe::ChessBoard& chessBoard, sf::Sprite& spriteFigrue, sf::Sprite& spriteSelectedField, bool essential, int row, int col)
		: mChessBoard{ chessBoard }, mSpriteFigure{ spriteFigrue }, mSpriteSelectedField{ spriteSelectedField },
		mEssential{ essential }, mSelected{ false }, mRow{ row }, mCol{ col } {

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
			mSpriteSelectedField.setPosition(sf::Vector2f(pos.x + 13, pos.y + 15));
			window.draw(mSpriteSelectedField);
			mSpriteFigure.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - mSpriteFigure.getGlobalBounds().width / 2, sf::Mouse::getPosition(window).y - mSpriteFigure.getGlobalBounds().height / 2));
		}
		else
			mSpriteFigure.setPosition(pos);
		window.draw(mSpriteFigure);
	};

	void ChessFigure::setSelected(bool value) {
		mSelected = value;
	}

	bool ChessFigure::getSelected() {
		return mSelected;
	}
}
