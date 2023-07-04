#include "chessFigure.h"
#include "chessBoard.h"

namespace swe {
	ChessFigure::ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, 
							swe::FigureIndex type, swe::Color color, int row, int col)
		: mChessBoard{ chessBoard }, mSpriteHandler{ spriteHandler }, mFigureSprite{ figureSprite },
		mEssential{ essential }, mType{ type }, mColor{ color }, mSelected{ false }, mRow{ row }, mCol{ col } {

	}

	void ChessFigure::showPossibleSteps(sf::RenderWindow& window) {
		for (auto entry : getPossibleSteps(mChessBoard.getBoardWithFigures())) {
			if (entry.second) {
				sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
				s.setPosition(sf::Vector2f(calcColFromIdx(entry.first) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, calcRowFromIdx(entry.first) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
				window.draw(s);
			}
			else {
				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f(calcColFromIdx(entry.first) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, calcRowFromIdx(entry.first) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
				window.draw(s);
			}
		}
	}

	bool ChessFigure::isKingThreatened(int orgRow, int orgCol, int row, int col) {
		throw std::logic_error("function not implemented");
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

		auto blackKing = mChessBoard.getKing(swe::Color::black);
		blackKing->isKingThreatened(blackKing->getRow(), blackKing->getCol(), blackKing->getRow(), blackKing->getCol());

		auto whiteKing = mChessBoard.getKing(swe::Color::white);
		whiteKing->isKingThreatened(whiteKing->getRow(), whiteKing->getCol(), whiteKing->getRow(), whiteKing->getCol());
	}

	void ChessFigure::draw(sf::RenderWindow& window, sf::Vector2f pos) {
		if (mSelected) {
			sf::Sprite& spriteSelectedField = mSpriteHandler.getSelectedFieldSprite();
			spriteSelectedField.setPosition(sf::Vector2f(pos.x + MOVE_SYMBOL_SELECTED_FIELD_OFFSET_PX, pos.y + MOVE_SYMBOL_SELECTED_FIELD_OFFSET_PX));
			window.draw(spriteSelectedField);
			showPossibleSteps(window);

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

	swe::FigureIndex ChessFigure::getType() {
		return mType;
	}

	swe::Color ChessFigure::getColor() {
		return mColor;
	}

	float ChessFigure::getHeight() {
		return mFigureSprite.getLocalBounds().height;
	}

	int ChessFigure::getRow() {
		return mRow;
	}

	int ChessFigure::getCol() {
		return mCol;
	}
}
