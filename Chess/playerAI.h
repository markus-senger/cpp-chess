#pragma once

#include "player.h"

namespace swe {
	class PlayerAI : public Player {
	public:
		PlayerAI(swe::Color color, bool turn, swe::ChessBoard& board) : Player(color, turn, board) {}

		bool turn() override {
			return true;
		}

	private:
	};
}