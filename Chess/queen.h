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
			for (int i = 1; mRow + i < CHESS_SIZE && mCol + i < CHESS_SIZE; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow + i) * CHESS_SIZE) + (mCol + i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow + i) * CHESS_SIZE) + (mCol + i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, (mRow + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, (mRow + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
				window.draw(s);
			}

			// down left
			for (int i = 1; mRow + i < CHESS_SIZE && mCol - i >= 0; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow + i) * CHESS_SIZE) + (mCol - i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow + i) * CHESS_SIZE) + (mCol - i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, (mRow + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, (mRow + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
				window.draw(s);
			}

			// top right
			for (int i = 1; mRow - i >= 0 && mCol + i < CHESS_SIZE; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow - i) * CHESS_SIZE) + (mCol + i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow - i) * CHESS_SIZE) + (mCol + i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, (mRow - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol + i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, (mRow - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
				window.draw(s);
			}

			// top left
			for (int i = 1; mRow - i >= 0 && mCol - i >= 0; i++) {
				if (mChessBoard.getBoardWithFigures()[((mRow - i) * CHESS_SIZE) + (mCol - i)] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[((mRow - i) * CHESS_SIZE) + (mCol - i)]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f((mCol - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, (mRow - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
				s.setPosition(sf::Vector2f((mCol - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, (mRow - i) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
				window.draw(s);
			}

			// up
			for (int row = mRow + 1; row < CHESS_SIZE; row++) {
				if (mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + mCol] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + mCol]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(mCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, row * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				if (row != mRow) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(mCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, row * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
					window.draw(s);
				}
			}

			// down
			for (int row = mRow - 1; row >= 0; row--) {
				if (mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + mCol] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(row * CHESS_SIZE) + mCol]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(mCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, row * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				if (row != mRow) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(mCol * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, row * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
					window.draw(s);
				}
			}

			// right
			for (int col = mCol + 1; col < CHESS_SIZE; col++) {
				if (mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + col] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + col]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(col * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, mRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				if (col != mCol) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(col * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, mRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
					window.draw(s);
				}
			}

			// left
			for (int col = mCol - 1; col >= 0; col--) {
				if (mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + col] != nullptr) {
					if (mChessBoard.getBoardWithFigures()[(mRow * CHESS_SIZE) + col]->getColor() != mColor) {
						sf::Sprite& s = mSpriteHandler.getAttackFieldSprite();
						s.setPosition(sf::Vector2f(col * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX, mRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX));
						window.draw(s);
					}
					break;
				}

				if (col != mCol) {
					sf::Sprite& s = mSpriteHandler.getPossibleMoveSprite();
					s.setPosition(sf::Vector2f(col * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX, mRow * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX));
					window.draw(s);
				}
			}
		}

	private:

	};
}