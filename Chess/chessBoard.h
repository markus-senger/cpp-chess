#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "button.h"
#include "chessFigure.h"
#include "graveyard.h"

namespace swe {
	class ChessGame;

	class ChessBoard {
	public:
		ChessBoard(swe::ChessGame& chessGame);
		void draw(sf::RenderWindow& window);
		bool handleEvent(swe::Color currentColor);
		void init(std::string const& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
		std::array<std::shared_ptr<swe::ChessFigure>, 64>& getBoardWithFigures();
		void setEnd(bool value, swe::Color winColor);
		swe::Graveyard& getGraveyard();
		std::shared_ptr<swe::ChessFigure> getFigure(swe::Color color, swe::FigureIndex type, int row = -1, int col = -1);
		void setPromotion(int row, int col);
		bool getPromotion();
		bool isActivePlayerAI();
		bool handlePromotion(int idx = -1);
		void setEnPassant(int col, int row);
		int getEnPassantCol();
		int getEnPassantRow();
		void removeEnPassantFigure();
		std::string getCurBoardFEN();
		int getPosOfBoardWithString(std::string pos, bool getFigure);

	private:
		swe::ChessGame& mChessGame;
		swe::Graveyard mGraveyard;
		std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> mBoardWithFigures{};
		std::shared_ptr<ChessFigure> mSelectedFigure{};
		bool mPromotion;
		int mPromotionRow;
		int mPromotionCol;
		int mEnPassantCol;
		int mEnPassantRow;

		void drawPromotionBoard(sf::RenderWindow& window);
		void replaceFigure(int idx, std::shared_ptr<ChessFigure> newFigure);
		int mouseOverPromotionBoardField();
	};
}