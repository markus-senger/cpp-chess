#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class King : public ChessFigure {
	public:
		King(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
            int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
            int dy[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };

            for (int i = 0; i < 8; i++) {
                int newRow = mRow + dy[i];
                int newCol = mCol + dx[i];

                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    if (mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol] == nullptr) {
                        sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                        s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 25, newRow * 85.25 + 60 + 25));
                        window.draw(s);
                    }
                    else if (mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol]->getColor() != mColor) {
                        sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                        s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 3, newRow * 85.25 + 60 + 3));
                        window.draw(s);
                    }
                }
            }
        }

	private:

	};
}