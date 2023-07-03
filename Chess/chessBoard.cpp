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
#include "utils.h"

#include <iostream>

namespace swe {
	ChessBoard::ChessBoard(swe::ChessGame& chessGame)
			:	mChessGame{ chessGame } {

		mChessGame.getSpriteHandler().getBoardSprite().setPosition(sf::Vector2f(0, CHESS_BOARD_HEADER_SIZE_PX));
	}

	void ChessBoard::draw(sf::RenderWindow& window) {
        mGraveyard.draw(window, mChessGame.getSpriteHandler().getBoardSprite().getLocalBounds().width, 
            mChessGame.getSpriteHandler().getBoardSprite().getLocalBounds().height);
		window.draw(mChessGame.getSpriteHandler().getBoardSprite());

        int i = 0;
        int j = 0;
        for (auto& figure : mBoardWithFigures) {
            if (figure != nullptr && !figure->getSelected()) {
                figure->draw(window, sf::Vector2f((calcColFromIdx(i)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX, 
                    (calcRowFromIdx(i)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX));
            }
            else if (figure != nullptr) {
                mSelectedFigure = figure;
                j = i;
            }
            i++;
        }
        if(mSelectedFigure)
            mSelectedFigure->draw(window, sf::Vector2f((calcColFromIdx(j)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX, 
                (calcRowFromIdx(j)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX));
	}

	bool ChessBoard::handleEvent(swe::Color currentColor) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(mChessGame.getWindow());
  
        int i = 0;
        for (auto& figure : mBoardWithFigures) {
            if (mouseOverFieldAccordingToIdx(mousePos, i)) {
                if (figure != nullptr && figure == mSelectedFigure) {
                    figure->setSelected(false);
                    mSelectedFigure = nullptr;
                }
                else if (mSelectedFigure != nullptr) {
                    mSelectedFigure->move(calcRowFromIdx(i), calcColFromIdx(i));
                    mSelectedFigure = nullptr;
                    return true;
                }
                else if (figure != nullptr && figure->getColor() == currentColor) {
                    figure->setSelected(true);
                    mSelectedFigure = figure;
                }
            }             
            else if (figure != nullptr)
                figure->setSelected(false);

            i++;
        }
        return false;  
	}

	void ChessBoard::init(std::string const& fen) {
        mBoardWithFigures.fill(nullptr);
        mGraveyard.clear();
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
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Pawn>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::pawn), false, swe::Color::black, row, col);
                    break;
                case 'P':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Pawn>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::pawn), false, swe::Color::white, row, col);
                    break;
                case 'n':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(),
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::knight), false, swe::Color::black, row, col);
                    break;
                case 'N':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::knight), false, swe::Color::white, row, col);
                    break;
                case 'b':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::bishop), false, swe::Color::black, row, col);
                    break;
                case 'B':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::bishop), false, swe::Color::white, row, col);
                    break;
                case 'r':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::rook), false, swe::Color::black, row, col);
                    break;
                case 'R':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::rook), false, swe::Color::white, row, col);
                    break;
                case 'q':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::queen), false, swe::Color::black, row, col);
                    break;
                case 'Q':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::queen), false, swe::Color::white, row, col);
                    break;
                case 'k':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<King>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(FigureIndex::king), true, swe::Color::black, row, col);
                    break;
                case 'K':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<King>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(FigureIndex::king), true, swe::Color::white, row, col);
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

    void ChessBoard::setEnd(bool value, swe::Color winColor) {
        mChessGame.setEnd(value, winColor);
    }

    swe::Graveyard& ChessBoard::getGraveyard() {
        return mGraveyard;
    }
}