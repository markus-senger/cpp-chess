#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "text.h"
#include "player.h"
#include "playerHuman.h"
#include "playerAI.h"
#include "chessBoard.h"

namespace swe {
	class ChessGame {
	public:
		ChessGame();
		sf::RenderWindow& getWindow();
		sf::Sprite& getBoardSprite();
		sf::Sprite& getWhiteFigureSprite(int idx);
		sf::Sprite& getBlackFigureSprite(int idx);

		void setStarted(bool value);


	private:
		void createWindow();
		void draw();
		void drawTitleScreen();
		void createSprites();
		void cutFiguresFromImage(sf::Sprite(&figures)[6], sf::Texture const& tFigures, int const yOffset);
		void loadFonts();

		float mWitdh;
		float mHeight;
		sf::RenderWindow mWindow;

		sf::Texture mTFigures;
		sf::Sprite mSFiguresWhite[6];
		sf::Sprite mSFiguresBlack[6];

		sf::Texture mTBoard;
		sf::Sprite mSBoard;

		sf::Font mFont;

		bool mStarted;

		swe::Button mButtonPlayFriend;
		swe::Button mButtonPlayAI;

		swe::Player mPlayer1;
		swe::Player mPlayer2;

		swe::ChessBoard mBoard;
	};
}