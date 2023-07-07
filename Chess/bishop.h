#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Bishop : public ChessFigure {
	public:
		Bishop(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, swe::FigureIndex::bishop, color, row, col } {

		}

		// ----- pure virtuals override ---------------------------------------------------------------------------------

		std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool const withIsKingThreatened = true) const override {
			std::vector<std::pair<int, bool>> possibleMoves{};

			// down right
			for (int i = 1; mRow + i < CHESS_SIZE && mCol + i < CHESS_SIZE; i++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getFigure(mColor, swe::FigureIndex::king)->isKingThreatened(mRow, mCol, mRow + i, mCol + i) : false;
				if (board[((mRow + i) * CHESS_SIZE) + (mCol + i)] != nullptr) {
					if (board[((mRow + i) * CHESS_SIZE) + (mCol + i)]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow + i, mCol + i), true));
					}
					break;
				}

				if(!threatened)
					possibleMoves.push_back(std::make_pair(convTo1D(mRow + i, mCol + i), false));
			}

			// down left
			for (int i = 1; mRow + i < CHESS_SIZE && mCol - i >= 0; i++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getFigure(mColor, swe::FigureIndex::king)->isKingThreatened(mRow, mCol, mRow + i, mCol - i) : false;
				if (board[((mRow + i) * CHESS_SIZE) + (mCol - i)] != nullptr) {
					if (board[((mRow + i) * CHESS_SIZE) + (mCol - i)]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow + i, mCol - i), true));
					}
					break;
				}
				if (!threatened)
					possibleMoves.push_back(std::make_pair(convTo1D(mRow + i, mCol - i), false));
			}

			// top right
			for (int i = 1; mRow - i >= 0 && mCol + i < CHESS_SIZE; i++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getFigure(mColor, swe::FigureIndex::king)->isKingThreatened(mRow, mCol, mRow - i, mCol + i) : false;
				if (board[((mRow - i) * CHESS_SIZE) + (mCol + i)] != nullptr) {
					if (board[((mRow - i) * CHESS_SIZE) + (mCol + i)]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow - i, mCol + i), true));
					}
					break;
				}
				if (!threatened)
					possibleMoves.push_back(std::make_pair(convTo1D(mRow - i, mCol + i), false));
			}

			// top left
			for (int i = 1; mRow - i >= 0 && mCol - i >= 0; i++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getFigure(mColor, swe::FigureIndex::king)->isKingThreatened(mRow, mCol, mRow - i, mCol - i) : false;
				if (board[((mRow - i) * CHESS_SIZE) + (mCol - i)] != nullptr) {
					if (board[((mRow - i) * CHESS_SIZE) + (mCol - i)]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow - i, mCol - i), true));
					}
					break;
				}
				if (!threatened)
					possibleMoves.push_back(std::make_pair(convTo1D(mRow - i, mCol - i), false));
			}

			return possibleMoves;
		}
	};
}