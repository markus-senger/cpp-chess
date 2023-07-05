#pragma once

#include "color.h"
#include "chessBoard.h"

namespace swe {
	class Player {
	public:
		Player(swe::Color color, bool isAi, bool turn, swe::ChessBoard& board) : mColor{ color }, mIsAi{ isAi }, mTurn{ turn }, mBoard{ board } {}

		virtual bool turn() = 0;

		void setTurn(bool value) {
			mTurn = value;
		}

		bool getTurn() {
			return mTurn;
		}

		bool isAi() {
			return mIsAi;
		}

	protected:
		swe::Color mColor;
		bool mIsAi;
		bool mTurn;
		swe::ChessBoard& mBoard;
	};
}