#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Pawn : public ChessFigure {
	public:
		Pawn(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
            : ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
            int direction = (mColor == Color::white) ? -1 : 1;

            int newRow = mRow + direction;
            int newCol = mCol;
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE && 
                    mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol] == nullptr) {

                sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
                window.draw(s);
            }

            if ((mColor == Color::white && mRow == START_ROW_NUM_FOR_WHITE_PAWN) || (mColor == Color::black && mRow == START_ROW_NUM_FOR_BLACK_PAWN)) {
                newRow = mRow + (2 * direction);
                newCol = mCol;
                if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE && 
                        mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol] == nullptr &&
                        mChessBoard.getBoardWithFigures()[((newRow - direction) * CHESS_SIZE) + newCol] == nullptr) {

                    sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                    s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
                    window.draw(s);
                }
            }

            newRow = mRow + direction;
            newCol = mCol - 1;
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE && 
                    mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol] != nullptr &&
                    mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol]->getColor() != mColor) {

                sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
                window.draw(s);
            }

            newRow = mRow + direction;
            newCol = mCol + 1;
            if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE && 
                    mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol] != nullptr && 
                    mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol]->getColor() != mColor) {

                sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
                window.draw(s);
            }
		}

	private:

	};
}