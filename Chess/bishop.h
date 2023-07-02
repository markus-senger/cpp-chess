#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Bishop : public ChessFigure {
	public:
		Bishop(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
			// up right
			for (int i = 1; mRow + i < 8 && mCol + i < 8; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol + i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol + i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol - i) * 85.25 + 60 + 3, (mRow + i) * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol + i) * 85.25 + 60 + 25, (mRow + i) * 85.25 + 60 + 25));
				window.draw(s);
			}

			// up left
			for (int i = 1; mRow + i < 8 && mCol - i >= 0; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol - i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol - i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol - i) * 85.25 + 60 + 3, (mRow + i) * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol - i) * 85.25 + 60 + 25, (mRow + i) * 85.25 + 60 + 25));
				window.draw(s);
			}

			// down right
			for (int i = 1; mRow - i >= 0 && mCol + i < 8; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow - i) * 8) + (mCol + i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow - i) * 8) + (mCol + i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol + i) * 85.25 + 60 + 3, (mRow - i) * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol + i) * 85.25 + 60 + 25, (mRow - i) * 85.25 + 60 + 25));
				window.draw(s);
			}

			// down left
			for (int i = 1; mRow - i >= 0 && mCol - i >= 0; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow - i) * 8) + (mCol - i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow - i) * 8) + (mCol - i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol - i) * 85.25 + 60 + 3, (mRow - i) * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol - i) * 85.25 + 60 + 25, (mRow - i) * 85.25 + 60 + 25));
				window.draw(s);
			}
		}

	private:

	};
}