#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class King : public ChessFigure {
	public:
		King(swe::ChessBoard& chessBoard, sf::Sprite& spriteFigrue, sf::Sprite& spriteSelectedField, bool essential, int row, int col)
			: ChessFigure{ chessBoard, spriteFigrue, spriteSelectedField, essential, row, col } {

		}

		void showSteps() override {

		}

	private:

	};
}