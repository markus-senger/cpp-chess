#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Queen : public ChessFigure {
	public:
		Queen(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::Color color, int row, int col)
			: ChessFigure{ chessBoard, spriteHandler, figureSprite, essential, color, row, col } {

		}

		void showSteps(sf::RenderWindow& window) override {
			// down right
			for (int i = 1; mRow + i < 8 && mCol + i < 8; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol + i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow + i) * 8) + (mCol + i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol + i) * 85.25 + 60 + 3, (mRow + i) * 85.25 + 60 + 3));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol + i) * 85.25 + 60 + 25, (mRow + i) * 85.25 + 60 + 25));
				window.draw(s);
			}

			// down left
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

			// top right
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

			// top left
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

	private:

	};
}