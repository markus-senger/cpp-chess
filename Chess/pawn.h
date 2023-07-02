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
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol] == nullptr) {
                sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 25, newRow * 85.25 + 60 + 25));
                window.draw(s);
            }

            if ((mColor == Color::white && mRow == 6) || (mColor == Color::black && mRow == 1)) {
                newRow = mRow + (2 * direction);
                newCol = mCol;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol] == nullptr && mChessBoard.getBoardWithFigures()[((newRow - direction) * 8) + newCol] == nullptr) {
                    sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
                    s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 25, newRow * 85.25 + 60 + 25));
                    window.draw(s);
                }
            }

            newRow = mRow + direction;
            newCol = mCol - 1;
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol] != nullptr && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol]->getColor() != mColor) {
                sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 3, newRow * 85.25 + 60 + 3));
                window.draw(s);
            }

            newRow = mRow + direction;
            newCol = mCol + 1;
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol] != nullptr && mChessBoard.getBoardWithFigures()[(newRow * 8) + newCol]->getColor() != mColor) {
                sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
                s.setPosition(sf::Vector2f(newCol * 85.25 + 60 + 3, newRow * 85.25 + 60 + 3));
                window.draw(s);
            }
		}

	private:

	};
}