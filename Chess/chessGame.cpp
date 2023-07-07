#include "chessGame.h"
#include "chessBoard.h"
#include "utils.h"

#include <chrono>
#include <thread>

namespace swe {
	ChessGame::ChessGame()
		: mWitdh{ WINDOW_DEFAULT_WIDTH_PX }, mHeight{ WINDOW_DEFAULT_HEIGHT_PX },
		mStarted{ false }, mEnd{ false }, mAiVsAi{ false }, mWinColor{ swe::Color::none },
		mButtonPlayFriend{ sf::Vector2f(WINDOW_DEFAULT_WIDTH_PX / 2, WINDOW_DEFAULT_HEIGHT_PX / 2 + BUTTON_MENU_FIRST_ROW_OFFSET_FROM_CENTER_PX),
											"Images/button_play-with-a-friend.png", "Images/button_hover_play-with-a-friend.png" },
		mButtonPlayAI(sf::Vector2f(WINDOW_DEFAULT_WIDTH_PX / 2, WINDOW_DEFAULT_HEIGHT_PX / 2 + BUTTON_MENU_SECOND_ROW_OFFSET_FROM_CENTER_PX),
											"Images/button_play-with-the-ai.png", "Images/button_hover_play-with-the-ai.png"),
		mButtonPlayAIvsAI(sf::Vector2f(WINDOW_DEFAULT_WIDTH_PX / 2, WINDOW_DEFAULT_HEIGHT_PX / 2 + BUTTON_MENU_THIRD_ROW_OFFSET_FROM_CENTER_PX),
											"Images/button_play-ai-vs-ai.png", "Images/button_hover_play-ai-vs-ai.png"),
		mButtonBack{ swe::Button(BACK_BUTTON_POSITION_V, "Images/button_back.png", "Images/button_hover_back.png") },
		mButtonBackToMenu{ swe::Button("Images/button_backToMenu.png", "Images/button_hover_backToMenu.png") },
		mBoard{ *this } {

		loadFonts();
		createWindow();
	}

	// ----- public methods ---------------------------------------------------------------------------------

	bool ChessGame::isActivePlayerAI() const {
		if (mPlayer1->getTurn())
			return mPlayer1->isAi();
		return mPlayer2->isAi();
	}


	// ----- getter ---------------------------------------------------------------------------------

	sf::RenderWindow& ChessGame::getWindow() {
		return mWindow;
	}

	swe::SpriteHandler& ChessGame::getSpriteHandler() {
		return mSpriteHandler;
	}


	// ----- setter ---------------------------------------------------------------------------------

	void ChessGame::setStarted(bool const value) {
		mStarted = value;
	}

	void ChessGame::setEnd(bool const value, swe::Color const winColor) {
		mEnd = value;
		mWinColor = winColor;
	}

	
	// ----- private methods ---------------------------------------------------------------------------------

	void ChessGame::createWindow() {
		mWindow.create(sf::VideoMode(mWitdh, mHeight), "Chess", sf::Style::Titlebar | sf::Style::Close);

		sf::Image icon;
		icon.loadFromFile("Images/Icon.png");
		mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		while (mWindow.isOpen())
		{
			
			eventLoop();

			mWindow.clear(sf::Color::White);
			draw();
			mWindow.display();
		}
	}

	void ChessGame::eventLoop() {
		sf::Event evt;
		while (mWindow.pollEvent(evt)) {
			if (evt.type == evt.Closed) {
				if (mPlayer1 != nullptr) mPlayer1->closeEngine();
				if (mPlayer2 != nullptr) mPlayer2->closeEngine();
				mWindow.close();
			}

			if (evt.type == sf::Event::MouseButtonPressed || (mPlayer1 != nullptr && mPlayer1->getTurn() && mPlayer1->getPreparation()) ||
				(mPlayer2 != nullptr && mPlayer2->getTurn() && mPlayer2->getPreparation())) {

				if (mEnd) {
					if (mButtonBack.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow))) ||
						mButtonBackToMenu.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
						mStarted = false;
						mEnd = false;
					}
				}
				else if (evt.key.code == sf::Mouse::Left && !mStarted) {
					mBoard.init();
					if (mPlayer1 != nullptr) mPlayer1->closeEngine();
					if (mPlayer2 != nullptr) mPlayer2->closeEngine();
					if (mButtonPlayFriend.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
						mStarted = true;
						mPlayer1 = std::make_unique<PlayerHuman>(swe::Color::white, true, mBoard);
						mPlayer2 = std::make_unique<PlayerHuman>(swe::Color::black, false, mBoard);
					}
					else if (mButtonPlayAI.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
						mStarted = true;
						mPlayer1 = std::make_unique<PlayerHuman>(swe::Color::white, true, mBoard);
						mPlayer2 = std::make_unique<PlayerAIStockfish>(swe::Color::black, false, mBoard);
					}
					else if (mButtonPlayAIvsAI.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
						mStarted = true;
						mAiVsAi = true;
						mPlayer1 = std::make_unique<PlayerAIStockfish>(swe::Color::white, true, mBoard, 100);
						mPlayer2 = std::make_unique<PlayerAIStockfish>(swe::Color::black, false, mBoard, 100);
					}
				}
				else if (mStarted && (evt.key.code == sf::Mouse::Left || (mPlayer1->getTurn() && mPlayer1->getPreparation()) || (mPlayer2->getTurn() && mPlayer2->getPreparation()))) {
					if (mButtonBack.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
						mStarted = false;
						mAiVsAi = false;
					}

					bool nextPlayerWithoutDelay = true;
					if (mPlayer1->turn()) {
						mPlayer2->setTurn(mEnd ? false : true);
						mPlayer1->setTurn(false);
						if (mAiVsAi)
							nextPlayerWithoutDelay = false;
					}

					mWindow.clear(sf::Color::White);
					draw();
					mWindow.display();
					if (nextPlayerWithoutDelay && mPlayer2->turn()) {
						mPlayer1->setTurn(mEnd ? false : true);
						mPlayer2->setTurn(false);
					}
				}
			}
		}
	}

	void ChessGame::draw() {	
		if (!mStarted)
			drawTitleScreen();
		else {
			if ((mPlayer1 != nullptr && mPlayer1->getTurn() && mPlayer1->getPreparation()) ||
				(mPlayer2 != nullptr && mPlayer2->getTurn() && mPlayer2->getPreparation())) {

				swe::Text AICalcInfo(INFO_MOUSE_BUTTON_PRESS_V, mFont, 16, "AI calculates the next move", sf::Color::Magenta);
				AICalcInfo.draw(mWindow);
			}
			else if (mAiVsAi) {

				swe::Text mouseClickInfo(INFO_MOUSE_BUTTON_PRESS_V, mFont, 16, "press left mouse button for next move", sf::Color::Blue);
				mouseClickInfo.draw(mWindow);
			}

			if (mPlayer1->getTurn()) {
				sf::Sprite& turnInfo = mSpriteHandler.getTurnInfoWhite();
				turnInfo.setPosition(TURN_INFO_POSITION_V);
				mWindow.draw(turnInfo);
			}
			else if (mPlayer2->getTurn()) {
				sf::Sprite& turnInfo = mSpriteHandler.getTurnInfoBlack();
				turnInfo.setPosition(TURN_INFO_POSITION_V);
				mWindow.draw(turnInfo);
			}

			mButtonBack.draw(mWindow);
			mBoard.draw(mWindow);
			if (mEnd)
				drawEndScreen();
		}
	}

	void ChessGame::drawEndScreen() {
		sf::Sprite popUpWindow = mSpriteHandler.getPopUpWindowSprite();
		popUpWindow.setPosition(mWitdh / 2 - popUpWindow.getLocalBounds().width / 2, mHeight / 2 - popUpWindow.getLocalBounds().height / 2);

		swe::Text endText(sf::Vector2f(mWitdh / 2, mHeight / 2 + POPUP_WINDOW_FIRST_ROW_OFFSET_FROM_CENTER_PX), mFont, 24, "End!");
		swe::Text winnerText(sf::Vector2f(mWitdh / 2, mHeight / 2), mFont, 20, mWinColor == swe::Color::none ? "remis!" : colorToString(mWinColor) + " wins!");

		mButtonBackToMenu.setPosition(sf::Vector2f(mWitdh / 2, mHeight / 2 + POPUP_WINDOW_THIRD_ROW_OFFSET_FROM_CENTER_PX));

		mWindow.draw(popUpWindow);
		endText.draw(mWindow);
		winnerText.draw(mWindow);
		mButtonBackToMenu.draw(mWindow);
	}

	void ChessGame::drawTitleScreen() {
		swe::Text title(sf::Vector2f(mWitdh / 2, TITLE_MENU_FIRST_ROW_OFFSET_FROM_CENTER_PX), mFont, 24, "\"A Game of Chess\"");
		title.draw(mWindow);

		swe::Text owner(sf::Vector2f(mWitdh / 2, TITLE_MENU_SECOND_ROW_OFFSET_FROM_CENTER_PX), mFont, 16, "Markus Senger");
		owner.draw(mWindow);

		mButtonPlayFriend.draw(mWindow);
		mButtonPlayAI.draw(mWindow);
		mButtonPlayAIvsAI.draw(mWindow);
	}

	void ChessGame::loadFonts() {
		mFont.loadFromFile("Fonts/animeace2_reg.ttf");
	}
}