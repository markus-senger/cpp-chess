#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "text.h"
#include "player.h"
#include "playerHuman.h"
#include "playerAI.h"
#include "chessBoard.h"
#include "spriteHandler.h"

namespace swe {
	class ChessGame {
	public:
		ChessGame();
		sf::RenderWindow& getWindow();
		swe::SpriteHandler& getSpriteHandler();
		void setStarted(bool value);


	private:
		void createWindow();
		void draw();
		void drawTitleScreen();
		void loadFonts();

		float mWitdh;
		float mHeight;
		sf::RenderWindow mWindow;
		swe::SpriteHandler mSpriteHandler;

		sf::Font mFont;

		bool mStarted;

		swe::Button mButtonPlayFriend;
		swe::Button mButtonPlayAI;

		swe::Player mPlayer1;
		swe::Player mPlayer2;

		swe::ChessBoard mBoard;
	};
}