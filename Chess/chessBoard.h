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
		void draw(sf::RenderWindow& window);
		void handleEvent();
		void init(std::string const& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
		std::array<std::shared_ptr<swe::ChessFigure>, 64>& getBoardWithFigures();
		void setEnd(bool value, swe::Color winColor);
		swe::Graveyard& getGraveyard();

	private:
		swe::ChessGame& mChessGame;
		swe::Graveyard mGraveyard;
		std::array<std::shared_ptr<swe::ChessFigure>, CHESS_NUM_OF_FIELDS> mBoardWithFigures{};
		std::shared_ptr<ChessFigure> mSelectedFigure{};
	};
}