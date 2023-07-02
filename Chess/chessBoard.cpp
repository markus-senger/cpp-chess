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

#include <iostream>

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
        int j = 0;
        for (auto& figure : mBoardWithFigures) {
            if (figure != nullptr && !figure->getSelected()) {
                figure->draw(window, sf::Vector2f((i % 8) * 85.25 + 60, (i / 8) * 85.25 + 55));
            }
            else if (figure != nullptr) {
                mSelectedFigure = figure;
                j = i;
            }
            i++;
        }
        if(mSelectedFigure)
            mSelectedFigure->draw(window, sf::Vector2f((j % 8) * 85.25 + 60, (j / 8) * 85.25 + 55));
	}

	void ChessBoard::handleEvent() {
        sf::Vector2i mousePos = sf::Mouse::getPosition(mChessGame.getWindow());

		if (mButtonBack.isMouseOver(static_cast<sf::Vector2f>(mousePos))) {
			mChessGame.setStarted(false);
		}
  
        int i = 0;
        for (auto& figure : mBoardWithFigures) {
            if (mousePos.x > (i % 8) * 85.25 + 60 && mousePos.x < (i % 8) * 85.25 + 60 + 85.25 &&
                mousePos.y >(i / 8) * 85.25 + 55 && mousePos.y < (i / 8) * 85.25 + 55 + 85.25) {
                if (figure != nullptr) {
                    figure->setSelected(true);
                    mSelectedFigure = figure;
                }
                else if (mSelectedFigure != nullptr) {
                    mSelectedFigure->move(i / 8, i % 8);
                    mSelectedFigure = nullptr;
                }
            }             
            else if (figure != nullptr)
                figure->setSelected(false);

            i++;
        }

        
	}

	void ChessBoard::drawHeader(sf::RenderWindow& window) {
		mButtonBack.draw(window);
	}

	void ChessBoard::init(std::string const& fen) {
        mBoardWithFigures.fill(nullptr);
        int row = 0; 
        int col = 0;

        for (char c : fen) {
            if (c == '/') {
                row++;
                col = 0;
            }
            else if (isdigit(c)) {
                col += (c - '0');
            }
            else if (isalpha(c)) {
                switch (c) {
                case 'p':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Pawn>(*this, mChessGame.getBlackFigureSprite(FigureIndex::pawn), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'P':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Pawn>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::pawn), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'n':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Knight>(*this, mChessGame.getBlackFigureSprite(FigureIndex::knight), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'N':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Knight>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::knight), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'b':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Bishop>(*this, mChessGame.getBlackFigureSprite(FigureIndex::bishop), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'B':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Bishop>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::bishop), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'r':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Rook>(*this, mChessGame.getBlackFigureSprite(FigureIndex::rook), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'R':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Rook>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::rook), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'q':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Queen>(*this, mChessGame.getBlackFigureSprite(FigureIndex::queen), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'Q':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<Queen>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::queen), mChessGame.getSelectedFieldSprite(), false, row, col);
                    break;
                case 'k':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<King>(*this, mChessGame.getBlackFigureSprite(FigureIndex::king), mChessGame.getSelectedFieldSprite(), true, row, col);
                    break;
                case 'K':
                    mBoardWithFigures[(row * 8) + col] = std::make_shared<King>(*this, mChessGame.getWhiteFigureSprite(FigureIndex::king), mChessGame.getSelectedFieldSprite(), true, row, col);
                    break;
                default:
                    break;
                }
                col++;
            }
        }
	}

    std::array<std::shared_ptr<swe::ChessFigure>, 64>& ChessBoard::getBoardWithFigures() {
        return mBoardWithFigures;
    }
}