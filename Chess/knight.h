#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
    class Knight : public ChessFigure {
    public:
        Knight(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
            : ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, swe::FigureIndex::knight, color, row, col } {

        }

        std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool withIsKingThreatened = true) override {
            std::vector<std::pair<int, bool>> possibleMoves{};

            int dx[NUM_POSSIBLE_MOVES_KNIGHT] = { 1, 2, 2, 1, -1, -2, -2, -1 };
            int dy[NUM_POSSIBLE_MOVES_KNIGHT] = { 2, 1, -1, -2, -2, -1, 1, 2 };

            for (int i = 0; i < CHESS_SIZE; i++) {
                int newRow = mRow + dy[i];
                int newCol = mCol + dx[i];
                if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE) {
                    bool threatened = withIsKingThreatened ? mChessBoard.getFigure(mColor, swe::FigureIndex::king)->isKingThreatened(mRow, mCol, newRow, newCol) : false;
                    if (!threatened) {
                        if (board[(newRow * CHESS_SIZE) + newCol] == nullptr) {
                            possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), false));
                        }
                        else if (board[(newRow * CHESS_SIZE) + newCol]->getColor() != mColor) {
                            possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), true));
                        }
                    }
                }
            }

            return possibleMoves;
        }
    };
}