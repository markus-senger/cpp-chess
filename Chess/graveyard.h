#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "color.h"
#include "utils.h"

namespace swe {
	class Graveyard {
	public:
		void draw(sf::RenderWindow& window, int boardWidth, int boardHeight) {
			int i = 0;
			for(auto figure : mWhiteFigures) {
				figure->draw(window, sf::Vector2f(boardWidth - GRAVEYARD_BOARD_WIDTH_OFFSET_WHITE_PX,
					boardHeight - GRAVEYARD_BOARD_HEIGHT_OFFSET_PX - (figure->getHeight() - GRAVEYARD_FIGURE_HEIGHT_OFFSET_PX) * GRAVEYARD_SCALEFAKTOR * i));
				i++;
			}

			i = 0;
			for (auto figure : mBlackFigures) {
				figure->draw(window, sf::Vector2f(boardWidth + GRAVEYARD_BOARD_WIDTH_OFFSET_BLACK_PX,
					boardHeight - GRAVEYARD_BOARD_HEIGHT_OFFSET_PX - (figure->getHeight() - GRAVEYARD_FIGURE_HEIGHT_OFFSET_PX) * GRAVEYARD_SCALEFAKTOR * i));
				i++;
			}
		}

		void add(std::shared_ptr<swe::ChessFigure> chessFigure, swe::Color color) {
			chessFigure->scale(sf::Vector2f(GRAVEYARD_SCALEFAKTOR, GRAVEYARD_SCALEFAKTOR));
			if (color == swe::Color::black) mBlackFigures.push_back(chessFigure);
			else if (color == swe::Color::white) mWhiteFigures.push_back(chessFigure);
		}

		void clear() {
			mWhiteFigures.clear();
			mBlackFigures.clear();
		}

	private:
		std::vector<std::shared_ptr<swe::ChessFigure>> mWhiteFigures{};
		std::vector<std::shared_ptr<swe::ChessFigure>> mBlackFigures{};
	};
}
