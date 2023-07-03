#pragma once

#include "color.h"
#include "chessBoard.h"

namespace swe {
	class Player {
	public:
		Player(swe::Color color, bool turn, swe::ChessBoard& board) : mColor{ color }, mTurn{ turn }, mBoard{ board } {}

		virtual bool turn() = 0;

		void setTurn(bool value) {
			mTurn = value;
		}

		bool getTurn() {
			return mTurn;
		}

	protected:
		swe::Color mColor;
		bool mTurn;
		swe::ChessBoard& mBoard;
	};
}