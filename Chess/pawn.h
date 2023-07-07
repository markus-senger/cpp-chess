#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
    class Pawn : public ChessFigure {
    public:
        Pawn(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
            : ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, swe::FigureIndex::pawn, color, row, col } {

        }

        // ----- pure virtuals override ---------------------------------------------------------------------------------

        std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool const withIsKingThreatened = true) const override {
            std::vector<std::pair<int, bool>> possibleMoves{};

            int direction = (mColor == Color::white) ? -1 : 1;

            int newRow = mRow + direction;
            int newCol = mCol;

            auto king = mChessBoard.getFigure(mColor, swe::FigureIndex::king);

            // normal forward
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE &&
                board[(newRow * CHESS_SIZE) + newCol] == nullptr) {

                bool threatened = withIsKingThreatened ? king->isKingThreatened(mRow, mCol, newRow, newCol) : false;
                if (!threatened) {
                    possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), false));
                }
            }

            // first move forward
            if ((mColor == Color::white && mRow == START_ROW_NUM_FOR_WHITE_PAWN) || (mColor == Color::black && mRow == START_ROW_NUM_FOR_BLACK_PAWN)) {
                newRow = mRow + (2 * direction);
                newCol = mCol;
                if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE &&
                    board[(newRow * CHESS_SIZE) + newCol] == nullptr &&
                    board[((newRow - direction) * CHESS_SIZE) + newCol] == nullptr) {

                    bool threatened = withIsKingThreatened ? king->isKingThreatened(mRow, mCol, newRow, newCol) : false;
                    if (!threatened) {
                        possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), false));
                    }
                }
            }

            // attack left
            newRow = mRow + direction;
            newCol = mCol - 1;
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE &&
                board[(newRow * CHESS_SIZE) + newCol] != nullptr &&
                board[(newRow * CHESS_SIZE) + newCol]->getColor() != mColor) {

                bool threatened = withIsKingThreatened ? king->isKingThreatened(mRow, mCol, newRow, newCol) : false;
                if (!threatened) {
                    possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), true));
                }
            }

            // attack right
            newRow = mRow + direction;
            newCol = mCol + 1;
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE &&
                board[(newRow * CHESS_SIZE) + newCol] != nullptr &&
                board[(newRow * CHESS_SIZE) + newCol]->getColor() != mColor) {

                bool threatened = withIsKingThreatened ? king->isKingThreatened(mRow, mCol, newRow, newCol) : false;
                if (!threatened) {
                    possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), true));
                }
            }

            // En-passant move
            int enPassantRow = (mColor == Color::white) ? ENPASSANT_ROW_BLACK : ENPASSANT_ROW_WHITE;
            int enPassantCol = mChessBoard.getEnPassantCol();
            if (enPassantRow == mRow && (mCol - 1 == enPassantCol || mCol + 1 == enPassantCol)) {
                auto enPassantPawn = board[(enPassantRow * CHESS_SIZE) + enPassantCol];
                if (enPassantPawn != nullptr && enPassantPawn->getType() == swe::FigureIndex::pawn && enPassantPawn->getColor() != mColor) {
                    bool threatened = withIsKingThreatened ? king->isKingThreatened(mRow, mCol, enPassantRow, enPassantCol) : false;
                    if (!threatened) {
                        possibleMoves.push_back(std::make_pair(convTo1D((mColor == Color::white) ? ENPASSANT_ROW_BLACK - 1 : ENPASSANT_ROW_WHITE + 1,
                            enPassantCol), true));
                    }
                }
            }

            return possibleMoves;
        }


        // ----- virtuals override ---------------------------------------------------------------------------------

        std::vector<int> getAttackSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board) const override {
            std::vector<int> attackSteps;

            int direction = (mColor == Color::white) ? -1 : 1;

            int newRow = mRow + direction;
            int newCol = mCol - 1;
            attackSteps.push_back(convTo1D(newRow, newCol));

            newRow = mRow + direction;
            newCol = mCol + 1;
            attackSteps.push_back(convTo1D(newRow, newCol));

            return attackSteps;
        }
    };
}