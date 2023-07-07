#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "text.h"
#include "player.h"
#include "playerHuman.h"
#include "playerAIRandom.h"
#include "playerAIStockfish.h"
#include "chessBoard.h"
#include "spriteHandler.h"
#include "color.h"

namespace swe {
	class ChessGame {
	public:
		ChessGame();

		// methods
		bool isActivePlayerAI() const;

		// getter
		sf::RenderWindow& getWindow();
		swe::SpriteHandler& getSpriteHandler();

		// setter
		void setStarted(bool const value);
		void setEnd(bool value, swe::Color winColor);


	private:
		sf::RenderWindow mWindow;
		swe::SpriteHandler mSpriteHandler;
		sf::Font mFont;

		swe::Button mButtonPlayFriend;
		swe::Button mButtonPlayAI;
		swe::Button mButtonPlayAIvsAI;
		swe::Button mButtonBack;
		swe::Button mButtonBackToMenu;

		std::unique_ptr<swe::Player> mPlayer1;
		std::unique_ptr<swe::Player> mPlayer2;

		swe::ChessBoard mBoard;

		float mWitdh;
		float mHeight;
		bool mStarted;
		bool mEnd;
		bool mAiVsAi;
		swe::Color mWinColor;

		// private methods
		void createWindow();
		void eventLoop();
		void draw();
		void drawEndScreen();
		void drawTitleScreen();
		void loadFonts();
	};
}