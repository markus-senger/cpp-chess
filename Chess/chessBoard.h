#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "button.h"
#include "chessFigure.h"

namespace swe {
	class ChessGame;

	class ChessBoard {
	public:
		ChessBoard(swe::ChessGame& chessGame);
		void draw(sf::RenderWindow& window);
		void handleEvent();
		void init(std::string const& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
		std::array<std::shared_ptr<swe::ChessFigure>, 64>& getBoardWithFigures();

	private:
		swe::ChessGame& mChessGame;
		swe::Button mButtonBack;
		std::array<std::shared_ptr<swe::ChessFigure>, 64> mBoardWithFigures{};
		std::shared_ptr<ChessFigure> mSelectedFigure{};

		void drawHeader(sf::RenderWindow& window);
	};
}