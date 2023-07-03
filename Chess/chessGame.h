#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "text.h"
#include "player.h"
#include "playerHuman.h"
#include "playerAI.h"
#include "chessBoard.h"
#include "spriteHandler.h"
#include "color.h"

namespace swe {
	class ChessGame {
	public:
		ChessGame();
		sf::RenderWindow& getWindow();
		swe::SpriteHandler& getSpriteHandler();
		void setStarted(bool value);
		void setEnd(bool value, swe::Color winColor);


	private:
		void createWindow();
		void draw();
		void drawEndScreen();
		void drawTitleScreen();
		void loadFonts();

		float mWitdh;
		float mHeight;
		sf::RenderWindow mWindow;
		swe::SpriteHandler mSpriteHandler;

		sf::Font mFont;

		bool mStarted;
		bool mEnd;
		swe::Color mWinColor;

		swe::Button mButtonPlayFriend;
		swe::Button mButtonPlayAI;
		swe::Button mButtonBack;
		swe::Button mButtonBackToMenu;

		std::unique_ptr<swe::Player> mPlayer1;
		std::unique_ptr<swe::Player> mPlayer2;

		swe::ChessBoard mBoard;
	};
}