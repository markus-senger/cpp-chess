#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"

namespace swe {
	class SpriteHandler {
	public:
		SpriteHandler() {
			createSprites();
		}

		sf::Sprite& getBoardSprite() {
			return mSBoard;
		}

		sf::Sprite& getTurnInfoBlack() {
			return mSTurnInfoBlack;
		}

		sf::Sprite& getTurnInfoWhite() {
			return mSTurnInfoWhite;
		}

		sf::Sprite& getPopUpWindowSprite() {
			return mSPopUpWindow;
		}

		sf::Sprite& getWhiteFigureSprite(int idx) {
			return mSFiguresWhite[idx];
		}

		sf::Sprite& getBlackFigureSprite(int idx) {
			return mSFiguresBlack[idx];
		}

		sf::Sprite& getSelectedFieldSprite() {
			return mSSelectedField;
		}

		sf::Sprite& getPossibleMoveSprite() {
			return mSPossibleMove;
		}

		sf::Sprite& getAttackFieldSprite() {
			return mSAttackField;
		}

		sf::Sprite& getCheckFieldSprite() {
			return mSCheckField;
		}

	private:
		sf::Texture mTFigures;
		sf::Sprite mSFiguresWhite[CHESS_NUM_DIFFERENT_FIGURES];
		sf::Sprite mSFiguresBlack[CHESS_NUM_DIFFERENT_FIGURES];

		sf::Texture mTBoard;
		sf::Sprite mSBoard;

		sf::Texture mTTurnInfoBlack;
		sf::Sprite mSTurnInfoBlack;

		sf::Texture mTTurnInfoWhite;
		sf::Sprite mSTurnInfoWhite;

		sf::Texture mTPopUpWindow;
		sf::Sprite mSPopUpWindow;

		sf::Texture mTSelectedField;
		sf::Sprite mSSelectedField;

		sf::Texture mTPossibleMove;
		sf::Sprite mSPossibleMove;

		sf::Texture mTAttackField;
		sf::Sprite mSAttackField;

		sf::Texture mTCheckField;
		sf::Sprite mSCheckField;

		void createSprites() {
			mTFigures.loadFromFile("Images/figures.png");

			cutFiguresFromImage(mSFiguresBlack, mTFigures, IMAGE_FIGURES_Y_OFFSET_FIRST_ROW_PX);
			cutFiguresFromImage(mSFiguresWhite, mTFigures, IMAGE_FIGURES_Y_OFFSET_SECOND_ROW_PX);

			mTBoard.loadFromFile("Images/board.png");
			mSBoard.setTexture(mTBoard);

			mTTurnInfoBlack.loadFromFile("Images/turnInfo_black.png");
			mSTurnInfoBlack.setTexture(mTTurnInfoBlack);

			mTTurnInfoWhite.loadFromFile("Images/turnInfo_white.png");
			mSTurnInfoWhite.setTexture(mTTurnInfoWhite);

			mTPopUpWindow.loadFromFile("Images/popUpWindow.png");
			mSPopUpWindow.setTexture(mTPopUpWindow);

			mTSelectedField.loadFromFile("Images/selectedField.png");
			mSSelectedField.setTexture(mTSelectedField);

			mTPossibleMove.loadFromFile("Images/possibleMove.png");
			mSPossibleMove.setTexture(mTPossibleMove);

			mTAttackField.loadFromFile("Images/attackField.png");
			mSAttackField.setTexture(mTAttackField);

			mTCheckField.loadFromFile("Images/checkField.png");
			mSCheckField.setTexture(mTCheckField);
		}

		void cutFiguresFromImage(sf::Sprite(&figures)[6], sf::Texture const& tFigures, int const yOffset) {
			for (int i = 0; i < 6; i++) {
				figures[i].setTexture(tFigures);
				figures[i].setTextureRect(sf::IntRect(IMAGE_FIGURES_WITDH_PX * i, yOffset, IMAGE_FIGURES_WITDH_PX, IMAGE_FIGURES_HEIGHT_PX));
			}
		}
	};
}