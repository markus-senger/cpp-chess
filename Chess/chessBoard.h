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

	private:
		swe::ChessGame& mChessGame;
		swe::Button mButtonBack;
		std::array<std::shared_ptr<swe::ChessFigure>, 64> chessBoard{};

		void drawHeader(sf::RenderWindow& window);
	};
}