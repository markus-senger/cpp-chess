#pragma once
#include <SFML/Graphics.hpp>

namespace swe {
	class SpriteHandler {
	public:
		SpriteHandler() {
			createSprites();
		}

		sf::Sprite& getBoardSprite() {
			return mSBoard;
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

	private:
		sf::Texture mTFigures;
		sf::Sprite mSFiguresWhite[6];
		sf::Sprite mSFiguresBlack[6];

		sf::Texture mTBoard;
		sf::Sprite mSBoard;

		sf::Texture mTSelectedField;
		sf::Sprite mSSelectedField;

		sf::Texture mTPossibleMove;
		sf::Sprite mSPossibleMove;

		sf::Texture mTAttackField;
		sf::Sprite mSAttackField;

		void createSprites() {
			mTFigures.loadFromFile("Images/figures.png");

			cutFiguresFromImage(mSFiguresBlack, mTFigures, 0);
			cutFiguresFromImage(mSFiguresWhite, mTFigures, 107.5);

			mTBoard.loadFromFile("Images/board.png");
			mSBoard.setTexture(mTBoard);

			mTSelectedField.loadFromFile("Images/selectedField.png");
			mSSelectedField.setTexture(mTSelectedField);

			mTPossibleMove.loadFromFile("Images/possibleMove.png");
			mSPossibleMove.setTexture(mTPossibleMove);

			mTAttackField.loadFromFile("Images/attackField.png");
			mSAttackField.setTexture(mTAttackField);
		}

		void cutFiguresFromImage(sf::Sprite(&figures)[6], sf::Texture const& tFigures, int const yOffset) {
			for (int i = 0; i < 6; i++) {
				figures[i].setTexture(tFigures);
				figures[i].setTextureRect(sf::IntRect(99.2 * i, yOffset, 99.2, 107.5));
			}
		}
	};
}