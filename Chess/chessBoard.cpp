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
        : mChessGame{ chessGame }, mPromotion{ false }{

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

        if (mPromotion) {
            drawPromotionBoard(window);
        }
	}

    void ChessBoard::drawPromotionBoard(sf::RenderWindow& window) {
        sf::Sprite& promotionBoard = mChessGame.getSpriteHandler().getPromotionBoardSprite();
        promotionBoard.setPosition(WINDOW_DEFAULT_WIDTH_PX / 2 - promotionBoard.getLocalBounds().width / 2, 
            WINDOW_DEFAULT_HEIGHT_PX / 2 - promotionBoard.getLocalBounds().height / 2);
        window.draw(promotionBoard);

        sf::Sprite& promotionBoardField = mChessGame.getSpriteHandler().getPromotionBoardFieldSprite();
        sf::Sprite& promotionBoardSelectedField = mChessGame.getSpriteHandler().getPromotionBoardSelectedFieldSprite();
        for (int i = 0; i < NUM_OF_PROMOTION_OPTIONS; i++) {
            float posX = WINDOW_DEFAULT_WIDTH_PX / 2 - promotionBoard.getLocalBounds().width / 2 +
                i * (promotionBoardField.getLocalBounds().width + PROMOTION_FIELD_SPACE_BETWEEEN_PX) + PROMOTION_FIELD_OFFSET_X_PX;
            float posY = WINDOW_DEFAULT_HEIGHT_PX / 2 - promotionBoard.getLocalBounds().height / 2 + PROMOTION_FIELD_OFFSET_Y_PX;

            if (mouseOverPromotionBoardField() == i) {
                promotionBoardSelectedField.setPosition(posX, posY);
                window.draw(promotionBoardSelectedField);
            }
            else {
                promotionBoardField.setPosition(posX, posY);
                window.draw(promotionBoardField);
            }

            switch (i) {
                case 0:
                {
                    sf::Sprite queenSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(),
                        FigureIndex::queen);
                    queenSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                    queenSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                    window.draw(queenSprite);
                    break;
                }
                case 1:
                {
                    sf::Sprite rookSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(),
                        FigureIndex::rook);
                    rookSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                    rookSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                    window.draw(rookSprite);
                    break;
                }
                case 2:
                {
                    sf::Sprite bishopSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(),
                        FigureIndex::bishop);
                    bishopSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                    bishopSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                    window.draw(bishopSprite);
                    break;
                }
                case 3:
                {
                    sf::Sprite knightSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(),
                        FigureIndex::knight);
                    knightSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                    knightSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                    window.draw(knightSprite);
                    break;
                }
            }
        }
    }

    int ChessBoard::mouseOverPromotionBoardField() {
        sf::Vector2i mousePos = sf::Mouse::getPosition(mChessGame.getWindow());

        sf::Sprite& promotionBoard = mChessGame.getSpriteHandler().getPromotionBoardSprite();
        sf::Sprite& promotionBoardField = mChessGame.getSpriteHandler().getPromotionBoardFieldSprite();

        for(int i = 0; i < NUM_OF_PROMOTION_OPTIONS; i++) {
            float posX = WINDOW_DEFAULT_WIDTH_PX / 2 - promotionBoard.getLocalBounds().width / 2 +
                i * (promotionBoardField.getLocalBounds().width + PROMOTION_FIELD_SPACE_BETWEEEN_PX) + PROMOTION_FIELD_OFFSET_X_PX;
            float posY = WINDOW_DEFAULT_HEIGHT_PX / 2 - promotionBoard.getLocalBounds().height / 2 + PROMOTION_FIELD_OFFSET_Y_PX;
            if (mousePos.x >= posX && mousePos.x <= posX + promotionBoardField.getLocalBounds().width &&
                mousePos.y >= posY && mousePos.y <= posY + promotionBoardField.getLocalBounds().height) {
                return i;
            }
        }
        return -1;
    }

	bool ChessBoard::handleEvent(swe::Color currentColor) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(mChessGame.getWindow());
  
        if (mPromotion) {
            return handlePromotion();
        }
        else {
            int i = 0;
            for (auto& figure : mBoardWithFigures) {
                if (mouseOverFieldAccordingToIdx(mousePos, i)) {
                    if (figure != nullptr && figure == mSelectedFigure) {
                        figure->setSelected(false);
                        mSelectedFigure = nullptr;
                    }
                    else if (mSelectedFigure != nullptr) {
                        bool moveOk = mSelectedFigure->move(calcRowFromIdx(i), calcColFromIdx(i));
                        mSelectedFigure = nullptr;
                        return mPromotion ? false : moveOk;
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
        }
        return false;  
	}

    bool ChessBoard::handlePromotion(int idx) {
        int choice = idx != -1 ? idx : mouseOverPromotionBoardField();

        switch (choice) {
        case 0:
            replaceFigure(convTo1D(promotionRow, promotionCol), std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), FigureIndex::queen), 
                false, mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), promotionRow, promotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->checkEnd(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor() == 
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 1:
            replaceFigure(convTo1D(promotionRow, promotionCol), std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), FigureIndex::rook), 
                false, mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), promotionRow, promotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->checkEnd(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 2:
            replaceFigure(convTo1D(promotionRow, promotionCol), std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), FigureIndex::bishop), 
                false, mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), promotionRow, promotionCol));
            
            mPromotion = false;
            mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->checkEnd(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 3:
            replaceFigure(convTo1D(promotionRow, promotionCol), std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), FigureIndex::knight), 
                false, mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor(), promotionRow, promotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->checkEnd(mBoardWithFigures[convTo1D(promotionRow, promotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        }
        return false;
    }

	void ChessBoard::init(std::string const& fen) {
        mPromotion = false;
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
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::pawn)), false, swe::Color::black, row, col);
                    break;
                case 'P':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Pawn>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::pawn)), false, swe::Color::white, row, col);
                    break;
                case 'n':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(),
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::knight)), false, swe::Color::black, row, col);
                    break;
                case 'N':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::knight)), false, swe::Color::white, row, col);
                    break;
                case 'b':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::bishop)), false, swe::Color::black, row, col);
                    break;
                case 'B':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::bishop)), false, swe::Color::white, row, col);
                    break;
                case 'r':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::rook)), false, swe::Color::black, row, col);
                    break;
                case 'R':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::rook)), false, swe::Color::white, row, col);
                    break;
                case 'q':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::queen)), false, swe::Color::black, row, col);
                    break;
                case 'Q':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::queen)), false, swe::Color::white, row, col);
                    break;
                case 'k':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<King>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getBlackFigureSprite(static_cast<int>(FigureIndex::king)), true, swe::Color::black, row, col);
                    break;
                case 'K':
                    mBoardWithFigures[convTo1D(row, col)] = std::make_shared<King>(*this, mChessGame.getSpriteHandler(), 
                        mChessGame.getSpriteHandler().getWhiteFigureSprite(static_cast<int>(FigureIndex::king)), true, swe::Color::white, row, col);
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

    std::shared_ptr<swe::ChessFigure> ChessBoard::getFigure(swe::Color color, swe::FigureIndex type, int row, int col) {
        for (auto figure : mBoardWithFigures) {
            if (figure != nullptr && figure->getColor() == color && figure->getType() == type)
                if((row == -1 || figure->getRow() == row) && (col == -1 || figure->getCol() == col))
                    return figure;
        }
        return nullptr;
    }

    void ChessBoard::setPromotion(int row, int col) {
        mPromotion = true;
        promotionRow = row;
        promotionCol = col;
    }

    void ChessBoard::replaceFigure(int idx, std::shared_ptr<ChessFigure> newFigure) {
        for (int i = 0; i < CHESS_NUM_OF_FIELDS; i++) {
            if (i == idx) {
                mBoardWithFigures[i] = newFigure;
                break;
            }
        }
    }

    bool ChessBoard::getPromotion() {
        return mPromotion;
    }
    
    bool ChessBoard::isActivePlayerAI() {
        return mChessGame.isActivePlayerAI();
    }
}