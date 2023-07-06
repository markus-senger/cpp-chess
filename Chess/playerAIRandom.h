#pragma once

#include "player.h"

#include <random>

namespace swe {
	class PlayerAIRandom : public Player {
	public:
		PlayerAIRandom(swe::Color color, bool turn, swe::ChessBoard& board) : Player(color, true, turn, board) {}

		bool turn() override {
			if (mTurn) {
				std::vector<std::shared_ptr<swe::ChessFigure>> nonNullEntries;
				nonNullEntries.reserve(mBoard.getBoardWithFigures().size());

				std::copy_if(mBoard.getBoardWithFigures().begin(), mBoard.getBoardWithFigures().end(), std::back_inserter(nonNullEntries),
					[this](const std::shared_ptr<swe::ChessFigure>& entry) {
						return entry != nullptr && entry->getColor() == mColor && entry->getPossibleSteps(mBoard.getBoardWithFigures()).size() > 0;
					});

				std::random_device rd;
				std::mt19937 rng(rd());
				std::uniform_int_distribution<size_t> dist(0, nonNullEntries.size() - 1);
				size_t randomIndex = dist(rng);
				std::shared_ptr<swe::ChessFigure> randomFigure = nonNullEntries[randomIndex];
				randomFigure->initPossibleSteps();

				auto possibleMoves = randomFigure->getPossibleSteps(mBoard.getBoardWithFigures());
				std::uniform_int_distribution<size_t> distMoves(0, possibleMoves.size() - 1);
				randomIndex = distMoves(rng);
				int idx = possibleMoves[randomIndex].first;
				randomFigure->move(calcRowFromIdx(idx), calcColFromIdx(idx));

				return true;
			}
			return false;
		}
	};
}