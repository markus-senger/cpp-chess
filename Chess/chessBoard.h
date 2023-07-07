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

		// methods
		void init(std::string const& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
		void draw(sf::RenderWindow& window);
		bool handleEvent(swe::Color const currentColor);
		bool isActivePlayerAI() const;
		bool handlePromotion(int const idx = -1);
		void removeEnPassantFigure();


		// getter
		std::array<std::shared_ptr<swe::ChessFigure>, 64>&	getBoardWithFigures();
		std::shared_ptr<swe::ChessFigure>					getFigure(swe::Color const color, swe::FigureIndex const type, int const row = -1, int const col = -1) const;
		int													getPosOfBoardWithString(std::string pos, bool const getFigure) const;
		swe::Graveyard&										getGraveyard();
		std::string											getCurBoardFEN() const;
		int													getEnPassantRow() const;
		int													getEnPassantCol() const;
		bool												getPromotion() const;
		bool												getRochadePossibleWhite() const;
		bool												getRochadePossibleBlack() const;


		// setter
		void setEnd(bool const value, swe::Color const winColor);
		void setRochadePossibleWhite(bool const value);
		void setRochadePossibleBlack(bool const value);
		void setPromotion(int const row, int const col);
		void setEnPassant(int const col, int const row);
		void setLastMoveOrgIdx(int const idx);
		void setLastMoveNewIdx(int const idx);

	private:
		swe::ChessGame&														mChessGame;
		swe::Graveyard														mGraveyard;
		std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS>	mBoardWithFigures{};
		std::shared_ptr<ChessFigure>										mSelectedFigure{};

		bool	mPromotion;
		int		mPromotionRow;
		int		mPromotionCol;
		int		mEnPassantRow;
		int		mEnPassantCol;
		bool	mShowLastMove;
		int		mLastMoveOrgIdx;
		int		mLastMoveNewIdx;
		bool	mRochadePossibleWhite;
		bool	mRochadePossibleBlack;

		// private methods
		void	drawPromotionBoard(sf::RenderWindow& window) const;
		void	replaceFigure(int const idx, std::shared_ptr<ChessFigure> const newFigure);
		int		mouseOverPromotionBoardField() const;
	};
}