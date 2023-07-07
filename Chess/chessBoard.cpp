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
        : mChessGame{ chessGame }, mPromotion{ false }, mPromotionRow{ -1 }, mPromotionCol{ -1 }, 
        mEnPassantRow{ -1 }, mEnPassantCol{ -1 }, mShowLastMove{ false }, mLastMoveOrgIdx{ -1 }, mLastMoveNewIdx{ -1 },
        mRochadePossibleBlack{ true }, mRochadePossibleWhite{ true }{

		mChessGame.getSpriteHandler().getBoardSprite().setPosition(sf::Vector2f(0, CHESS_BOARD_HEADER_SIZE_PX));
	}

    // ----- public methods ---------------------------------------------------------------------------------

    void ChessBoard::init(std::string const& fen) {
        mShowLastMove = false;
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

	void ChessBoard::draw(sf::RenderWindow& window) {
        mGraveyard.draw(window, mChessGame.getSpriteHandler().getBoardSprite().getLocalBounds().width, 
            mChessGame.getSpriteHandler().getBoardSprite().getLocalBounds().height);
		window.draw(mChessGame.getSpriteHandler().getBoardSprite());

        // last move
        if (mShowLastMove) {
            sf::Sprite lastMoveOrgPosSprite = mChessGame.getSpriteHandler().getLastMoveSymbolSprite();
            sf::Sprite lastMoveNewPosSprite = mChessGame.getSpriteHandler().getLastMoveSymbolSprite();
            lastMoveOrgPosSprite.setPosition(sf::Vector2f((calcColFromIdx(mLastMoveOrgIdx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX,
                (calcRowFromIdx(mLastMoveOrgIdx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX));
            lastMoveNewPosSprite.setPosition(sf::Vector2f((calcColFromIdx(mLastMoveNewIdx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX,
                (calcRowFromIdx(mLastMoveNewIdx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX));
            window.draw(lastMoveOrgPosSprite);
            window.draw(lastMoveNewPosSprite);
        }

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
        // draw selected figure last
        if(mSelectedFigure)
            mSelectedFigure->draw(window, sf::Vector2f((calcColFromIdx(j)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX, 
                (calcRowFromIdx(j)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX));

        if (mPromotion) {
            drawPromotionBoard(window);
        }
	}

	bool ChessBoard::handleEvent(swe::Color const currentColor) {
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

    bool ChessBoard::isActivePlayerAI() const {
        return mChessGame.isActivePlayerAI();
    }

    bool ChessBoard::handlePromotion(int const idx) {
        int choice = idx != -1 ? idx : mouseOverPromotionBoardField();

        switch (choice) {
        case 0:
            replaceFigure(convTo1D(mPromotionRow, mPromotionCol), std::make_shared<Queen>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), FigureIndex::queen), 
                false, mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), mPromotionRow, mPromotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->checkEnd(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor() == 
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 1:
            replaceFigure(convTo1D(mPromotionRow, mPromotionCol), std::make_shared<Rook>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), FigureIndex::rook), 
                false, mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), mPromotionRow, mPromotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->checkEnd(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 2:
            replaceFigure(convTo1D(mPromotionRow, mPromotionCol), std::make_shared<Bishop>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), FigureIndex::bishop), 
                false, mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), mPromotionRow, mPromotionCol));
            
            mPromotion = false;
            mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->checkEnd(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        case 3:
            replaceFigure(convTo1D(mPromotionRow, mPromotionCol), std::make_shared<Knight>(*this, mChessGame.getSpriteHandler(),
                mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), FigureIndex::knight), 
                false, mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(), mPromotionRow, mPromotionCol));

            mPromotion = false;
            mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->checkEnd(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor() ==
                swe::Color::white ? swe::Color::black : swe::Color::white);
            return true;
        }
        return false;
    }

    void ChessBoard::removeEnPassantFigure() {
        mBoardWithFigures[convTo1D(mEnPassantRow, mEnPassantCol)] = nullptr;
        mEnPassantCol = -1;
        mEnPassantRow = -1;
    }


    // ----- getter ---------------------------------------------------------------------------------

    std::array<std::shared_ptr<swe::ChessFigure>, 64>& ChessBoard::getBoardWithFigures() {
        return mBoardWithFigures;
    }

    std::shared_ptr<swe::ChessFigure> ChessBoard::getFigure(swe::Color const color, swe::FigureIndex const type, int const row, int const col) const {
        for (auto figure : mBoardWithFigures) {
            if (figure != nullptr && figure->getColor() == color && figure->getType() == type)
                if ((row == -1 || figure->getRow() == row) && (col == -1 || figure->getCol() == col))
                    return figure;
        }
        return nullptr;
    }

    int ChessBoard::getPosOfBoardWithString(std::string pos, bool const getFigure) const {
        if (pos.length() == 4) {
            std::transform(pos.begin(), pos.end(), pos.begin(), [](unsigned char c) { return std::tolower(c); });
            int col = pos[getFigure ? 0 : 2] - 'a';
            int row = std::abs(pos[getFigure ? 1 : 3] - '0' - CHESS_SIZE - 1) - 1;
            return convTo1D(row, col);
        }
        return -1;
    }

    swe::Graveyard& ChessBoard::getGraveyard() {
        return mGraveyard;
    }

    std::string ChessBoard::getCurBoardFEN() const {
        std::string fen;
        int emptyCount = 0;

        for (int row = 0; row < CHESS_SIZE; row++) {
            for (int col = 0; col < CHESS_SIZE; col++) {
                auto figure = mBoardWithFigures[convTo1D(row, col)];
                if (figure) {
                    if (emptyCount > 0) {
                        fen += std::to_string(emptyCount);
                        emptyCount = 0;
                    }

                    char type = ' ';
                    switch (figure->getType()) {
                    case swe::FigureIndex::pawn:    type = 'P'; break;
                    case swe::FigureIndex::king:    type = 'K'; break;
                    case swe::FigureIndex::queen:   type = 'Q'; break;
                    case swe::FigureIndex::knight:  type = 'N'; break;
                    case swe::FigureIndex::bishop:  type = 'B'; break;
                    case swe::FigureIndex::rook:    type = 'R'; break;
                    }
                    if (figure->getColor() == swe::Color::white && type != ' ')
                        fen += type;
                    else if (type != ' ')
                        fen += std::tolower(type);
                }
                else {
                    emptyCount++;
                }
            }
            if (emptyCount > 0) {
                fen += std::to_string(emptyCount);
                emptyCount = 0;
            }

            if (row < CHESS_SIZE) {
                fen += '/';
            }
        }

        return fen;
    }

    int ChessBoard::getEnPassantRow() const {
        return mEnPassantRow;
    }

    int ChessBoard::getEnPassantCol() const {
        return mEnPassantCol;
    }

    bool ChessBoard::getPromotion() const {
        return mPromotion;
    }

    bool ChessBoard::getRochadePossibleWhite() const {
        return mRochadePossibleWhite;
    }

    bool ChessBoard::getRochadePossibleBlack() const {
        return mRochadePossibleBlack;
    }


    // ----- setter ---------------------------------------------------------------------------------

    void ChessBoard::setEnd(bool const value, swe::Color const winColor) {
        mChessGame.setEnd(value, winColor);
    }

    void ChessBoard::setRochadePossibleWhite(bool const value) {
        mRochadePossibleWhite = value;
    }

    void ChessBoard::setRochadePossibleBlack(bool const value) {
        mRochadePossibleBlack = value;
    }

    void ChessBoard::setPromotion(int const row, int const col) {
        mPromotion = true;
        mPromotionRow = row;
        mPromotionCol = col;
    }

    void ChessBoard::setEnPassant(int const col, int const row) {
        mEnPassantCol = col;
        mEnPassantRow = row;
    }

    void ChessBoard::setLastMoveOrgIdx(int const idx) {
        mLastMoveOrgIdx = idx;
    }

    void ChessBoard::setLastMoveNewIdx(int const idx) {
        mShowLastMove = true;
        mLastMoveNewIdx = idx;
    }


    // ----- private methods ---------------------------------------------------------------------------------

    void ChessBoard::drawPromotionBoard(sf::RenderWindow& window) const {
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
                sf::Sprite queenSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(),
                    FigureIndex::queen);
                queenSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                queenSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                window.draw(queenSprite);
                break;
            }
            case 1:
            {
                sf::Sprite rookSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(),
                    FigureIndex::rook);
                rookSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                rookSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                window.draw(rookSprite);
                break;
            }
            case 2:
            {
                sf::Sprite bishopSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(),
                    FigureIndex::bishop);
                bishopSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                bishopSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                window.draw(bishopSprite);
                break;
            }
            case 3:
            {
                sf::Sprite knightSprite = mChessGame.getSpriteHandler().getPromotionFigureSprite(mBoardWithFigures[convTo1D(mPromotionRow, mPromotionCol)]->getColor(),
                    FigureIndex::knight);
                knightSprite.setPosition(posX + PROMOTION_FIELD_FIGURE_OFFSET_X_PX, posY + PROMOTION_FIELD_FIGURE_OFFSET_Y_PX);
                knightSprite.scale(sf::Vector2(PROMOTION_FIELD_FIGURE_SCALE, PROMOTION_FIELD_FIGURE_SCALE));
                window.draw(knightSprite);
                break;
            }
            }
        }
    }

    void ChessBoard::replaceFigure(int const idx, std::shared_ptr<ChessFigure> const newFigure) {
        for (int i = 0; i < CHESS_NUM_OF_FIELDS; i++) {
            if (i == idx) {
                mBoardWithFigures[i] = newFigure;
                break;
            }
        }
    }
  
    int ChessBoard::mouseOverPromotionBoardField() const {
        sf::Vector2i mousePos = sf::Mouse::getPosition(mChessGame.getWindow());

        sf::Sprite& promotionBoard = mChessGame.getSpriteHandler().getPromotionBoardSprite();
        sf::Sprite& promotionBoardField = mChessGame.getSpriteHandler().getPromotionBoardFieldSprite();

        for (int i = 0; i < NUM_OF_PROMOTION_OPTIONS; i++) {
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
}