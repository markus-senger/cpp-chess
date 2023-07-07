#include "chessFigure.h"
#include "chessBoard.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"

#include <cmath>

namespace swe {
	ChessFigure::ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, 
							swe::FigureIndex type, swe::Color color, int row, int col)
		: mChessBoard{ chessBoard }, mSpriteHandler{ spriteHandler }, mFigureSprite{ figureSprite },
		mEssential{ essential }, mType{ type }, mColor{ color }, mFirstMove{ true }, mSelected{ false }, mRow{ row }, mCol{ col } {

	}

	// ----- virtuals ---------------------------------------------------------------------------------

	void ChessFigure::draw(sf::RenderWindow& window, sf::Vector2f const pos) {
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

	std::vector<int> ChessFigure::getAttackSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board) const {
		std::vector<int> attackSteps;

		for (const auto& entry : getPossibleSteps(board, false)) {
			attackSteps.push_back(entry.first);
		}

		return attackSteps;
	}

	bool ChessFigure::isKingThreatened(int const orgRow, int const orgCol, int const row, int const col) const {
		throw std::logic_error("function not implemented");
	}

	void ChessFigure::setCheck(bool const value) {
		throw std::logic_error("function not implemented");
	}


	// ----- public methods ---------------------------------------------------------------------------------

	void ChessFigure::initPossibleSteps() {
		mCurPossibleSteps = getPossibleSteps(mChessBoard.getBoardWithFigures());
	}

	void ChessFigure::showPossibleSteps(sf::RenderWindow& window) {
		initPossibleSteps();
		for (auto entry : mCurPossibleSteps) {
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

	bool ChessFigure::move(int const row, int const col, bool const force, char const promotion, bool const lastMove) {
		int move = convTo1D(row, col);
		auto it = std::find_if(mCurPossibleSteps.begin(), mCurPossibleSteps.end(), [move](const std::pair<int, bool>& entry) {
			return entry.first == move;
		});
		if (it != mCurPossibleSteps.end() || force) {
			if (mChessBoard.getBoardWithFigures()[convTo1D(row, col)] != nullptr) {
				mChessBoard.getGraveyard().add(mChessBoard.getBoardWithFigures()[convTo1D(row, col)], mChessBoard.getBoardWithFigures()[convTo1D(row, col)]->getColor());

				if (mChessBoard.getBoardWithFigures()[convTo1D(row, col)]->mEssential)
					mChessBoard.setEnd(true, mChessBoard.getBoardWithFigures()[convTo1D(mRow, mCol)]->mColor);
			}
			
			checkSpecialRules(row, col, force ? false : it->second);

			if (lastMove)
				mChessBoard.setLastMoveOrgIdx(convTo1D(mRow, mCol));

			mChessBoard.getBoardWithFigures()[convTo1D(row, col)] = mChessBoard.getBoardWithFigures()[convTo1D(mRow, mCol)];
			mChessBoard.getBoardWithFigures()[convTo1D(mRow, mCol)] = nullptr;
			mRow = row;
			mCol = col;
			mSelected = false;
			mFirstMove = false;

			if (lastMove)
				mChessBoard.setLastMoveNewIdx(convTo1D(row, col));
	
			bool blackCheck = checkEnd(swe::Color::black);
			bool whiteCheck = checkEnd(swe::Color::white);
			if (blackCheck && whiteCheck) {
				mChessBoard.setEnd(true, swe::Color::none);
			}

			if (mChessBoard.getPromotion() && mChessBoard.isActivePlayerAI()) {
				switch (promotion) {
					case 'q': mChessBoard.handlePromotion(0); break;
					case 'r': mChessBoard.handlePromotion(1); break;
					case 'b': mChessBoard.handlePromotion(2); break;
					case 'k': mChessBoard.handlePromotion(3); break;
					default: 
						std::srand(std::time(nullptr));
						mChessBoard.handlePromotion(std::rand() % 4);
				}
			}

			return true;
		}
		mSelected = false;
		return false;
	}

	void ChessFigure::scale(sf::Vector2f const scaleFactor) {
		mFigureSprite.scale(scaleFactor);
	}

	bool ChessFigure::checkEnd(swe::Color const color) const {
		auto king = mChessBoard.getFigure(color, swe::FigureIndex::king);
		bool tooLessMaterial = false;

		if (king->isKingThreatened(king->getRow(), king->getCol(), king->getRow(), king->getCol())) {
			king->setCheck(true);

			int cntPossibleMoves = 0;
			for (auto& figure : mChessBoard.getBoardWithFigures()) {
				if (figure != nullptr && figure->getColor() == color)
					cntPossibleMoves += figure->getPossibleSteps(mChessBoard.getBoardWithFigures()).size();
			}
			if (cntPossibleMoves <= 0)
				mChessBoard.setEnd(true, color == swe::Color::white ? swe::Color::black : swe::Color::white);
		}
		else {
			king->setCheck(false);

			int cntPossibleMoves = 0;

			int numKings = 0;
			int numBishops = 0;
			int numKnights = 0;
			int numPawns = 0;
			int numOthers = 0;

			for (auto& figure : mChessBoard.getBoardWithFigures()) {
				if (figure != nullptr && figure->getColor() == color) {
					cntPossibleMoves += figure->getPossibleSteps(mChessBoard.getBoardWithFigures()).size();
				
					if (figure->getType() == swe::FigureIndex::king) {
						numKings++;
					}
					else if (figure->getType() == swe::FigureIndex::bishop) {
						numBishops++;
					}
					else if (figure->getType() == swe::FigureIndex::knight) {
						numKnights++;
					}
					else if (figure->getType() == swe::FigureIndex::pawn) {
						numPawns++;
					}
					else {
						numOthers++;
					}
				}
			}

			if (numKings == 1 && numBishops == 1 && numKnights == 0 && numPawns == 0 && numOthers == 0) {
				tooLessMaterial = true;
			}
			else if (numKings == 1 && numBishops == 0 && numKnights == 1 && numPawns == 0 && numOthers == 0) {
				tooLessMaterial = true;
			}
			else if (numKings == 1 && numBishops == 0 && numKnights == 0 && numPawns == 0 && numOthers == 0) {
				tooLessMaterial = true;
			}

			if (cntPossibleMoves <= 0)
				mChessBoard.setEnd(true, swe::Color::none);
		}

		return tooLessMaterial;
	}


	// ----- getter ---------------------------------------------------------------------------------

	bool ChessFigure::getSelected() const {
		return mSelected;
	}

	swe::FigureIndex ChessFigure::getType() const {
		return mType;
	}

	swe::Color ChessFigure::getColor() const {
		return mColor;
	}

	bool ChessFigure::getFirstMove() const {
		return mFirstMove;
	}

	float ChessFigure::getHeight() const {
		return mFigureSprite.getLocalBounds().height;
	}

	int ChessFigure::getRow() const {
		return mRow;
	}

	int ChessFigure::getCol() const {
		return mCol;
	}


	// ----- setters ---------------------------------------------------------------------------------

	void ChessFigure::setFirstMove(bool const value) {
		mFirstMove = value;
	}

	void ChessFigure::setSelected(bool const value) {
		mSelected = value;
	}


	// ----- protected methods ---------------------------------------------------------------------------------

	void ChessFigure::checkSpecialRules(int const row, int const col, bool const isAttack) {
		// rochade
		if (getType() == swe::FigureIndex::king && std::abs(mCol - col) == 2) {
			if (col == 2) { // long rochade
				auto rook = mChessBoard.getFigure(mColor, swe::FigureIndex::rook, -1, 0);
				rook->move(rook->getRow(), 3, true, ' ', false);
			}
			else if (col == 6) { // short rochade
				auto rook = mChessBoard.getFigure(mColor, swe::FigureIndex::rook, -1, CHESS_SIZE - 1);
				rook->move(rook->getRow(), 5, true, ' ', false);
			}
		}

		// pawn promotion
		if (getType() == swe::FigureIndex::pawn) {
			if ((mColor == swe::Color::white && row == 0) || (mColor == swe::Color::black && row == CHESS_SIZE - 1)) {
				mChessBoard.setPromotion(row, col);
			}
		}

		// en passant
		if (isAttack && mChessBoard.getBoardWithFigures()[convTo1D(row, col)] == nullptr) {
			mChessBoard.getGraveyard().add(mChessBoard.getBoardWithFigures()[convTo1D(mChessBoard.getEnPassantRow(), mChessBoard.getEnPassantCol())],
				mChessBoard.getBoardWithFigures()[convTo1D(mChessBoard.getEnPassantRow(), mChessBoard.getEnPassantCol())]->getColor());
			mChessBoard.removeEnPassantFigure();
		}

		if (mType == swe::FigureIndex::pawn && mFirstMove && ((mColor == swe::Color::white && row == ENPASSANT_ROW_WHITE)
			|| (mColor == swe::Color::black && row == ENPASSANT_ROW_BLACK))) {

			mChessBoard.setEnPassant(col, row);
		}
		else {
			mChessBoard.setEnPassant(-1, -1);
		}
	}
}
