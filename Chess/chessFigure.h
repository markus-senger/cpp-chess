#pragma once

#include <SFML/Graphics.hpp>
#include "spriteHandler.h"
#include "color.h"
#include "figureIndex.h"

#include <vector>

namespace swe {
	class ChessBoard;

	class ChessFigure {
	public:
		ChessFigure(swe::ChessBoard& chessBoard, swe::SpriteHandler& spriteHandler, sf::Sprite figureSprite, bool essential, swe::FigureIndex type, swe::Color color, int row, int col);

		// pure virtuals
		virtual std::vector<std::pair<int, bool>>	getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool const withIsKingThreatened = true) const = 0;
		

		// virtuals
		virtual void				draw(sf::RenderWindow& window, sf::Vector2f const pos);
		virtual std::vector<int>	getAttackSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board) const;		
		virtual bool				isKingThreatened(int const orgRow, int const orgCol, int const row, int const col) const;		
		virtual void				setCheck(bool const value);

		
		// methods
		void	initPossibleSteps();
		void	showPossibleSteps(sf::RenderWindow& window);
		bool	move(int const row, int const col, bool const force = false, char const promotion = ' ', bool const lastMove = true);
		void	scale(sf::Vector2f const scaleFactor);
		bool	checkEnd(swe::Color const color) const;


		// getter
		bool				getSelected() const;
		swe::FigureIndex	getType() const;
		swe::Color			getColor() const;
		bool				getFirstMove() const;
		float				getHeight() const;
		int					getRow() const;
		int					getCol() const;


		// setter
		void setFirstMove(bool const value);
		void setSelected(bool const value);


	protected:
		swe::ChessBoard&		mChessBoard;
		swe::SpriteHandler&		mSpriteHandler;
		sf::Sprite				mFigureSprite;

		bool								mEssential;
		swe::FigureIndex					mType;
		swe::Color							mColor;
		bool								mFirstMove;
		bool								mSelected;
		int									mRow;
		int									mCol;
		std::vector<std::pair<int, bool>>	mCurPossibleSteps;

		// protected methods
		void checkSpecialRules(int const row, int const col, bool const isAttack);
		
	};
}
