#pragma once

#include "player.h"

namespace swe {
	class PlayerHuman : public Player {
	public:
		PlayerHuman(swe::Color color, bool turn, swe::ChessBoard& board) : Player(color, false, turn, board, false) {}

		bool turn() override {
			if (mTurn && mBoard.handleEvent(mColor)) {
				mTurn = !mTurn;
				return true;
			}
			return false;
		}
	};
}