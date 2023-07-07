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

		virtual std::vector<std::pair<int, bool>> getPossibleSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board, bool withIsKingThreatened = true) = 0;

		virtual bool isKingThreatened(int orgRow, int orgCol, int row, int col);

		void initPossibleSteps();

		void showPossibleSteps(sf::RenderWindow& window);

		virtual std::vector<int> getAttackSteps(std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> const& board);

		bool move(int row, int col, bool force = false, char promotion = ' ', bool lastMove = true);

		virtual void draw(sf::RenderWindow& window, sf::Vector2f pos);

		void scale(sf::Vector2f scaleFactor);

		void setSelected(bool value);

		virtual void setCheck(bool value);

		bool getSelected();

		swe::FigureIndex getType();

		swe::Color getColor();

		bool getFirstMove();

		void setFirstMove(bool value);

		float getHeight();

		int getRow();

		int getCol();

		bool checkEnd(swe::Color color);


	protected:
		swe::ChessBoard& mChessBoard;
		swe::SpriteHandler& mSpriteHandler;
		sf::Sprite mFigureSprite;

		bool mEssential;
		swe::FigureIndex mType;
		swe::Color mColor;
		bool mFirstMove;
		bool mSelected;
		int mRow;
		int mCol;
		std::vector<std::pair<int, bool>> mCurPossibleSteps;

		void checkSpecialRules(int row, int col, bool isAttack);
		
	};
}
