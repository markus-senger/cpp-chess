#pragma once

#include "color.h"
#include "chessBoard.h"

namespace swe {
	class Player {
	public:
		Player(swe::Color color, bool isAi, bool turn, swe::ChessBoard& board, bool preparation) : 
			mColor{ color }, mIsAi{ isAi }, mTurn{ turn }, mBoard{ board }, mPreparation{ preparation } {}

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

		bool getPreparation() {
			return mPreparation;
		}

		virtual void closeEngine() {}

	protected:
		swe::Color mColor;
		bool mIsAi;
		bool mTurn;
		swe::ChessBoard& mBoard;
		bool mPreparation;
	};
}