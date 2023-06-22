#include "chessBoard.h"
#include "chessGame.h"
#include "chessFigure.h"
#include "figureIndex.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"

namespace swe {
	ChessBoard::ChessBoard(swe::ChessGame& chessGame)
			:	mChessGame{ chessGame }, 
				mButtonBack{ swe::Button(sf::Vector2f(50, 30), "Images/button_back.png", "Images/button_hover_back.png") } {

		mChessGame.getBoardSprite().setPosition(sf::Vector2f(0, 50));
	}

	void ChessBoard::draw(sf::RenderWindow& window) {
		drawHeader(window);
		window.draw(mChessGame.getBoardSprite());

        int i = 0;
        for (auto& figure : chessBoard) {
            if (figure != nullptr) {
                figure->draw(window, sf::Vector2f((i / 8) * 85.25 + 60, (i % 8) * 85.25 + 55));
            }
            i++;
        }
	}

	void ChessBoard::handleEvent() {
		if (mButtonBack.isMouseOver(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mChessGame.getWindow())))) {
			mChessGame.setStarted(false);
		}
	}

	void ChessBoard::drawHeader(sf::RenderWindow& window) {
		mButtonBack.draw(window);
	}

	void ChessBoard::init(std::string const& fen) {
        int row = 7; 
        int col = 0;

        for (char c : fen) {
            if (c == '/') {
                row--;
                col = 0;
            }
            else if (isdigit(c)) {
                col += (c - '0');
            }
            else if (isalpha(c)) {
                switch (c) {
                case 'p':
                    chessBoard[(col * 8) + row] = std::make_shared<Pawn>(*this, mChessGame.getBlackFigureSprite(FigureIndex::pawn), false);
                    break;
                case 'P':
                    chessBoard[(col * 8) + row] = std::make_shared<Pawn>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::pawn), false);
                    break;
                case 'n':
                    chessBoard[(col * 8) + row] = std::make_shared<Knight>(*this, mChessGame.getBlackFigureSprite(FigureIndex::knight), false);
                    break;
                case 'N':
                    chessBoard[(col * 8) + row] = std::make_shared<Knight>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::knight), false);
                    break;
                case 'b':
                    chessBoard[(col * 8) + row] = std::make_shared<Bishop>(*this, mChessGame.getBlackFigureSprite(FigureIndex::bishop), false);
                    break;
                case 'B':
                    chessBoard[(col * 8) + row] = std::make_shared<Bishop>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::bishop), false);
                    break;
                case 'r':
                    chessBoard[(col * 8) + row] = std::make_shared<Rook>(*this, mChessGame.getBlackFigureSprite(FigureIndex::rook), false);
                    break;
                case 'R':
                    chessBoard[(col * 8) + row] = std::make_shared<Rook>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::rook), false);
                    break;
                case 'q':
                    chessBoard[(col * 8) + row] = std::make_shared<Queen>(*this, mChessGame.getBlackFigureSprite(FigureIndex::queen), false);
                    break;
                case 'Q':
                    chessBoard[(col * 8) + row] = std::make_shared<Queen>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::queen), false);
                    break;
                case 'k':
                    chessBoard[(col * 8) + row] = std::make_shared<King>(*this, mChessGame.getBlackFigureSprite(FigureIndex::king), true);
                    break;
                case 'K':
                    chessBoard[(col * 8) + row] = std::make_shared<King>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::king), true);
                    break;
                default:
                    break;
                }
                col++;
            }
        }
	}
}