#include "chessFigure.h"
#include "chessBoard.h"

namespace swe {
	ChessFigure::ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
		: mChessBoard{ chessBoard }, mSpriteHandler{ spriteHandler }, mFigureSprite{ figureSprite },
		mEssential{ essential }, mColor{ color }, mSelected{ false }, mRow{ row }, mCol{ col } {

	}

	void ChessFigure::move(int row, int col) {
		if (mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + col] != nullptr) {
			mChessBoard.getGraveyard().add(mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + col], mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + col]->getColor());

			if(mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + col]->mEssential)
				mChessBoard.setEnd(true, mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + mCol]->mColor);
		}
		mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + col] = mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + mCol];
		mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + mCol] = nullptr;
		mRow = row;
		mCol = col;
		mSelected = false;
	}

	void ChessFigure::draw(sf::RenderWindow& window, sf::Vector2f pos) {
		if (mSelected) {
			sf::Sprite& spriteSelectedField = mSpriteHandler.getSelectedFieldSprite();
			spriteSelectedField.setPosition(sf::Vector2f(pos.x + MOVE_SYMBOL_SELECTED_FIELD_OFFSET_PX, pos.y + MOVE_SYMBOL_SELECTED_FIELD_OFFSET_PX));
			window.draw(spriteSelectedField);
			showSteps(window);

			mFigureSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - mFigureSprite.getGlobalBounds().width / 2, sf::Mouse::getPosition(window).y - mFigureSprite.getGlobalBounds().height / 2));
		}
		else
			mFigureSprite.setPosition(pos);
		window.draw(mFigureSprite);
	}

	void ChessFigure::scale(sf::Vector2f scaleFactor) {
		mFigureSprite.scale(scaleFactor);
	}

	void ChessFigure::setSelected(bool value) {
		mSelected = value;
	}

	bool ChessFigure::getSelected() {
		return mSelected;
	}

	swe::Color ChessFigure::getColor() {
		return mColor;
	}

	float ChessFigure::getHeight() {
		return mFigureSprite.getLocalBounds().height;
	}
}
