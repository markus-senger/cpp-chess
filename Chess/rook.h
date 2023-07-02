#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"
#include <iostream>

namespace swe {
	class Rook : public ChessFigure {
	public:
		Rook(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
			// up
			for (int row = mRow + 1; row < 8; row++) {
				if (mChessBoard.getBoardWithFigures()[(row * 8) + mCol] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(row * 8) + mCol]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(mCol * 85.25 + 60 + 3, row * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				if (row != mRow) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(mCol * 85.25 + 60 + 25, row * 85.25 + 60 + 25));
					window.draw(s);
				}
			}

			// down
			for (int row = mRow - 1; row >= 0; row--) {
				if (mChessBoard.getBoardWithFigures()[(row * 8) + mCol] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(row * 8) + mCol]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(mCol * 85.25 + 60 + 3, row * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				if (row != mRow) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(mCol * 85.25 + 60 + 25, row * 85.25 + 60 + 25));
					window.draw(s);
				}
			}

			// right
			for (int col = mCol + 1; col < 8; col++) {
				if (mChessBoard.getBoardWithFigures()[(mRow * 8) + col] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(mRow * 8) + col]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(col * 85.25 + 60 + 3, mRow * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				if (col != mCol) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(col * 85.25 + 60 + 25, mRow * 85.25 + 60 + 25));
					window.draw(s);
				}
			}

			// left
			for (int col = mCol - 1; col >= 0; col--) {
				if (mChessBoard.getBoardWithFigures()[(mRow * 8) + col] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(mRow * 8) + col]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(col * 85.25 + 60 + 3, mRow * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				if (col != mCol) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(col * 85.25 + 60 + 25, mRow * 85.25 + 60 + 25));
					window.draw(s);
				}
			}
		}
	};
}