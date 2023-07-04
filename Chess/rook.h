#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"
#include <iostream>

namespace swe {
	class Rook : public ChessFigure {
	public:
		Rook(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, swe::FigureIndex::rook, color, row, col } {

		}

		std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool withIsKingThreatened = true) override {
			std::vector<std::pair<int, bool>> possibleMoves{};

			// up
			for (int row = mRow + 1; row < CHESS_SIZE; row++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getKing(mColor)->isKingThreatened(mRow, mCol, row, mCol) : false;
				if (board[(row * CHESS_SIZE) + mCol] != nullptr) {
					if (board[(row * CHESS_SIZE) + mCol]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(row, mCol), true));
					}
					break;
				}

				if (row != mRow && !threatened) {
					possibleMoves.push_back(std::make_pair(convTo1D(row, mCol), false));
				}
			}

			// down
			for (int row = mRow - 1; row >= 0; row--) {
				bool threatened = withIsKingThreatened ? mChessBoard.getKing(mColor)->isKingThreatened(mRow, mCol, row, mCol) : false;
				if (board[(row * CHESS_SIZE) + mCol] != nullptr) {
					if (board[(row * CHESS_SIZE) + mCol]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(row, mCol), true));
					}
					break;
				}

				if (row != mRow && !threatened) {
					possibleMoves.push_back(std::make_pair(convTo1D(row, mCol), false));
				}
			}

			// right
			for (int col = mCol + 1; col < CHESS_SIZE; col++) {
				bool threatened = withIsKingThreatened ? mChessBoard.getKing(mColor)->isKingThreatened(mRow, mCol, mRow, col) : false;
				if (board[(mRow * CHESS_SIZE) + col] != nullptr) {
					if (board[(mRow * CHESS_SIZE) + col]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow, col), true));
					}
					break;
				}

				if (col != mCol && !threatened) {
					possibleMoves.push_back(std::make_pair(convTo1D(mRow, col), false));
				}
			}

			// left
			for (int col = mCol - 1; col >= 0; col--) {
				bool threatened = withIsKingThreatened ? mChessBoard.getKing(mColor)->isKingThreatened(mRow, mCol, mRow, col) : false;
				if (board[(mRow * CHESS_SIZE) + col] != nullptr) {
					if (board[(mRow * CHESS_SIZE) + col]->getColor() != mColor && !threatened) {
						possibleMoves.push_back(std::make_pair(convTo1D(mRow, col), true));
					}
					break;
				}

				if (col != mCol && !threatened) {
					possibleMoves.push_back(std::make_pair(convTo1D(mRow, col), false));
				}
			}

			return possibleMoves;
		}
	};
}