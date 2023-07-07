#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
    class King : public ChessFigure {
    public:
        King(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
            : ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, swe::FigureIndex::king, color, row, col } {

        }

        void draw(sf::RenderWindow& window, sf::Vector2f pos) override {
            if (mCheck) {
                sf::Sprite& s = mSpriteHandler.getCheckFieldSprite();
                s.setPosition(sf::Vector2f(mCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, mRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
                window.draw(s);
            }
            ChessFigure::draw(window, pos);
        }

        std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool withIsKingThreatened = true) override {
            std::vector<std::pair<int, bool>> possibleMoves{};

            int dx[NUM_POSSIBLE_MOVES_KING] = { 1, 1, 1, 0, 0, -1, -1, -1 };
            int dy[NUM_POSSIBLE_MOVES_KING] = { 1, 0, -1, 1, -1, 1, 0, -1 };

            for (int i = 0; i < CHESS_SIZE; i++) {
                int newRow = mRow + dy[i];
                int newCol = mCol + dx[i];

                if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE) {
                    auto target = board[(newRow * CHESS_SIZE) + newCol];
                    bool threatened = withIsKingThreatened ? isKingThreatened(mRow, mCol, newRow, newCol) : false;
                    if (target == nullptr && !threatened) {
                        possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), false));
                    }
                    else if (target != nullptr && target->getColor() != mColor && !threatened) {
                        possibleMoves.push_back(std::make_pair(convTo1D(newRow, newCol), true));
                    }
                }
            }

            // rochade
            if (mFirstMove && !mCheck && withIsKingThreatened) {
                if(mColor == swe::Color::black)
                    mChessBoard.setRochadePossibleBlack(true);
                else if (mColor == swe::Color::white)
                    mChessBoard.setRochadePossibleWhite(true);


                // short
                if (board[convTo1D(mRow, mCol + 1)] == nullptr && board[convTo1D(mRow, mCol + 2)] == nullptr &&
                    !isKingThreatened(mRow, mCol, mRow, mCol + 1) && !isKingThreatened(mRow, mCol, mRow, mCol + 2)) {

                    auto rook = board[convTo1D(mRow, mCol + 3)];
                    if (rook != nullptr && rook->getFirstMove()) {
                        possibleMoves.push_back(std::make_pair(convTo1D(mRow, mCol + 2), false));
                    }
                }

                // long
                if (board[convTo1D(mRow, mCol - 1)] == nullptr && board[convTo1D(mRow, mCol - 2)] == nullptr && board[convTo1D(mRow, mCol - 3)] == nullptr &&
                    !isKingThreatened(mRow, mCol, mRow, mCol - 1) && !isKingThreatened(mRow, mCol, mRow, mCol - 2)) {

                    auto rook = board[convTo1D(mRow, mCol - 4)];
                    if (rook != nullptr && rook->getFirstMove()) {
                        possibleMoves.push_back(std::make_pair(convTo1D(mRow, mCol - 2), false));
                    }
                }
            }
            else if(!mFirstMove || mCheck) {
                if (mColor == swe::Color::black)
                    mChessBoard.setRochadePossibleBlack(false);
                else if (mColor == swe::Color::white)
                    mChessBoard.setRochadePossibleWhite(false);
            }

            return possibleMoves;
        }

        bool isKingThreatened(int orgRow, int orgCol, int row, int col) override {
            auto board = mChessBoard.getBoardWithFigures();
            int curKingRow = mRow;
            int curKingCol = mCol;
            if (board[convTo1D(orgRow, orgCol)] != nullptr && board[convTo1D(orgRow, orgCol)]->getType() == swe::FigureIndex::king) {
                curKingRow = row;
                curKingCol = col;
            }

            auto copyField = board[convTo1D(row, col)];
            board[convTo1D(row, col)] = board[convTo1D(orgRow, orgCol)];
            board[convTo1D(orgRow, orgCol)] = nullptr;
            for (auto const& figure : board) {
                if (figure != nullptr && figure.get() != this && figure->getColor() != mColor) {
                    for (auto const& step : figure->getAttackSteps(board)) {
                        if (step == convTo1D(curKingRow, curKingCol)) {
                            board[convTo1D(orgRow, orgCol)] = board[convTo1D(row, col)];
                            board[convTo1D(row, col)] = copyField;
                            return true;
                        }
                    }
                }
            }

            board[convTo1D(orgRow, orgCol)] = board[convTo1D(row, col)];
            board[convTo1D(row, col)] = copyField;

            return false;  
        }

        void setCheck(bool value) {
            mCheck = value;
        }

    private:
        bool mCheck{ false };
    };
}