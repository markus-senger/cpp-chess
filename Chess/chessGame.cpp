#include "chessGame.h"
#include "chessBoard.h"

namespace swe {
	ChessGame::ChessGame()
		: mStarted{ false },
		mWitdh{ 756 },
		mHeight{ 820 },
		mButtonPlayFriend{ sf::Vector2f(mWitdh / 2, mHeight / 2 - 80), "Images/button_play-with-a-friend.png", "Images/button_hover_play-with-a-friend.png" },
		mButtonPlayAI(sf::Vector2f(mWitdh / 2, mHeight / 2 + 20), "Images/button_play-with-the-ai.png", "Images/button_hover_play-with-the-ai.png"),
		mBoard{ *this } {

		loadFonts();
		createSprites();
		createWindow();
	}

	sf::RenderWindow& ChessGame::getWindow() {
		return mWindow;
	}

	sf::Sprite& ChessGame::getBoardSprite() {
		return mSBoard;
	}

	sf::Sprite& ChessGame::getWhiteFigureSprite(int idx) {
		return mSFiguresWhite[idx];
	}

	sf::Sprite& ChessGame::getBlackFigureSprite(int idx) {
		return mSFiguresBlack[idx];
	}

	sf::Sprite& ChessGame::getSelectedFieldSprite() {
		return mSSelectedField;
	}

	void ChessGame::setStarted(bool value) {
		mStarted = value;
	}


	void ChessGame::createWindow() {
		mWindow.create(sf::VideoMode(mWitdh, mHeight), "Chess", sf::Style::Titlebar | sf::Style::Close);

		while (mWindow.isOpen())
		{
			sf::Event evt;
			while (mWindow.pollEvent(evt)) {
				if (evt.type == evt.Closed) {
					mWindow.close();
				}

				if (evt.type == sf::Event::MouseButtonPressed) {
					if (evt.key.code == sf::Mouse::Left && !mStarted) {
						mBoard.init();
						if (mButtonPlayFriend.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
							mStarted = true;
							mPlayer1 = PlayerHuman();
							mPlayer2 = PlayerHuman();
						}
						else if (mButtonPlayAI.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)))) {
							mStarted = true;
							mPlayer1 = PlayerHuman();
							mPlayer2 = PlayerAI();
						}
					}
					else if (evt.key.code == sf::Mouse::Left && mStarted) {
						mBoard.handleEvent();
					}
				}

			}
			mWindow.clear(sf::Color::White);

			// TODO

			draw();

			mWindow.display();
		}
	}

	void ChessGame::draw() {
		if (!mStarted)
			drawTitleScreen();
		else {
			mBoard.draw(mWindow);
		}
	}

	void ChessGame::drawTitleScreen() {
		swe::Text title(sf::Vector2f(mWitdh / 2, 150), mFont, 24, "\"A Game of Chess\"");
		title.draw(mWindow);

		swe::Text owner(sf::Vector2f(mWitdh / 2, 190), mFont, 16, "Markus Senger");
		owner.draw(mWindow);

		mButtonPlayFriend.draw(mWindow);
		mButtonPlayAI.draw(mWindow);
	}

	void ChessGame::createSprites() {
		mTFigures.loadFromFile("Images/figures.png");

		cutFiguresFromImage(mSFiguresBlack, mTFigures, 0);
		cutFiguresFromImage(mSFiguresWhite, mTFigures, 107.5);

		mTBoard.loadFromFile("Images/board.png");
		mSBoard.setTexture(mTBoard);

		mTSelectedField.loadFromFile("Images/selectedField.png");
		mSSelectedField.setTexture(mTSelectedField);
	}

	void ChessGame::cutFiguresFromImage(sf::Sprite(&figures)[6], sf::Texture const& tFigures, int const yOffset) {
		for (int i = 0; i < 6; i++) {
			figures[i].setTexture(tFigures);
			figures[i].setTextureRect(sf::IntRect(99.2 * i, yOffset, 99.2, 107.5));
		}
	}

	void ChessGame::loadFonts() {
		mFont.loadFromFile("Fonts/animeace2_reg.ttf");
	}
}