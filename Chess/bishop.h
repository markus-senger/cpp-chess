#pragma once

#include <SFML/Graphics.hpp>
#include "chessFigure.h"

namespace swe {
	class Bishop : public ChessFigure {
	public:
		Bishop(swe::ChessBoard& chessBoard, sf::Sprite& spriteFigrue, sf::Sprite& spriteSelectedField, bool essential, int row, int col)
			: ChessFigure{ chessBoard, spriteFigrue, spriteSelectedField, essential, row, col } {

		}

		void showSteps() override {

		}

	private:

	};
}