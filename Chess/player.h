#pragma once

#include "color.h"
#include "chessBoard.h"

namespace swe {
	class Player {
	public:
		Player(swe::Color color, bool isAi, bool turn, swe::ChessBoard& board, bool preparation) : 
			mColor{ color }, mIsAi{ isAi }, mTurn{ turn }, mBoard{ board }, mPreparation{ preparation } {}

		// ----- pure virtuals ---------------------------------------------------------------------------------

		virtual bool turn() = 0;


		// ----- virtuals ---------------------------------------------------------------------------------

		virtual void closeEngine() {}


		// ----- methods ---------------------------------------------------------------------------------

		bool isAi() const {
			return mIsAi;
		}


		// ----- getter ---------------------------------------------------------------------------------

		bool getTurn() const {
			return mTurn;
		}

		bool getPreparation() const {
			return mPreparation;
		}


		// ----- setter ---------------------------------------------------------------------------------

		void setTurn(bool const value) {
			mTurn = value;
		}

	protected:
		swe::ChessBoard& mBoard;
		swe::Color mColor;
		bool mIsAi;
		bool mTurn;
		bool mPreparation;
	};
}