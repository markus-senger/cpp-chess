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
		}

	private:

	};
}