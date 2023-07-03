#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Knight : public ChessFigure {
	public:
		Knight(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
            : ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
            int dx[NUM_POSSIBLE_MOVES_KNIGHT] = { 1, 2, 2, 1, -1, -2, -2, -1 };
            int dy[NUM_POSSIBLE_MOVES_KNIGHT] = { 2, 1, -1, -2, -2, -1, 1, 2 };

            for (int i = 0; i < 8; i++) {
                int newRow = mRow + dy[i];
                int newCol = mCol + dx[i];

                if (newRow >= 0 && newRow < CHESS_SIZE && newCol >= 0 && newCol < CHESS_SIZE) {
                    if (mChessBoard.getBoardWithFigures()[(newRow * CHESS_SIZE) + newCol] == nullptr) {
                        sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                        s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
                        window.draw(s);
                    }
                    else if (mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol]->getColor() != mColor) {
                        sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                        s.setPosition(sf::Vector2f(newCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, newRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
                        window.draw(s);
                    }
                }
            }
		}

	private:

	};
}