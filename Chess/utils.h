#pragma once

#include <SFML/Graphics.hpp> 

namespace swe {
	// generally
	const int			WINDOW_DEFAULT_WIDTH_PX							= 840;
	const int			WINDOW_DEFAULT_HEIGHT_PX						= 840;
	const int			CHESS_SIZE										= 8;
	const int			CHESS_NUM_OF_FIELDS								= CHESS_SIZE * CHESS_SIZE;
	const float			CHESS_FIELD_SIZE_PX								= 85.25f;
	const int			CHESS_BOARD_WITDH_OFFSET_PX						= 60;
	const int			CHESS_BOARD_HEIGHT_OFFSET_PX					= 55;
	const int			CHESS_BOARD_HEADER_SIZE_PX						= 50;
	const int			CHESS_NUM_DIFFERENT_FIGURES						= 6;

	// images
	const float			IMAGE_FIGURES_Y_OFFSET_FIRST_ROW_PX				= 0;
	const float			IMAGE_FIGURES_Y_OFFSET_SECOND_ROW_PX			= 107.5f;
	const float			IMAGE_FIGURES_WITDH_PX							= 99.2f;
	const float			IMAGE_FIGURES_HEIGHT_PX							= IMAGE_FIGURES_Y_OFFSET_SECOND_ROW_PX;

	// ui
	const int			TITLE_MENU_FIRST_ROW_OFFSET_FROM_CENTER_PX		= 150;
	const int			TITLE_MENU_SECOND_ROW_OFFSET_FROM_CENTER_PX		= 190;
	const int			BUTTON_MENU_FIRST_ROW_OFFSET_FROM_CENTER_PX		= -80;
	const int			BUTTON_MENU_SECOND_ROW_OFFSET_FROM_CENTER_PX	= 20;
	const int			BUTTON_MENU_THIRD_ROW_OFFSET_FROM_CENTER_PX		= 120;
	const sf::Vector2f	BACK_BUTTON_POSITION_V							= sf::Vector2f(50, 30);
	const sf::Vector2f	INFO_MOUSE_BUTTON_PRESS_V						= sf::Vector2f(WINDOW_DEFAULT_WIDTH_PX / 2, WINDOW_DEFAULT_HEIGHT_PX - 15);
	const sf::Vector2f	TURN_INFO_POSITION_V							= sf::Vector2f(310, 13);
	const int			POPUP_WINDOW_FIRST_ROW_OFFSET_FROM_CENTER_PX	= -50;
	const int			POPUP_WINDOW_THIRD_ROW_OFFSET_FROM_CENTER_PX	= 50;

	// move symbols
	const int			MOVE_SYMBOL_SELECTED_FIELD_OFFSET_PX			= 13;
	const int			MOVE_SYMBOL_ATTACK_FIELD_OFFSET_PX				= 3;
	const int			MOVE_SYMBOL_POSSIBLE_MOVE_OFFSET_PX				= 25;
	
	// num of possible moves
	const int			NUM_POSSIBLE_MOVES_KING							= 8;
	const int			NUM_POSSIBLE_MOVES_KNIGHT						= 8;

	// special rules	
	const int			START_ROW_NUM_FOR_WHITE_PAWN					= 6;
	const int			START_ROW_NUM_FOR_BLACK_PAWN					= 1;
	const int			NUM_OF_PROMOTION_OPTIONS						= 4;
	const int			PROMOTION_FIELD_OFFSET_X_PX						= 10;
	const int			PROMOTION_FIELD_OFFSET_Y_PX						= 35;
	const int			PROMOTION_FIELD_SPACE_BETWEEEN_PX				= 5;
	const int			PROMOTION_FIELD_FIGURE_OFFSET_X_PX				= 8;
	const int			PROMOTION_FIELD_FIGURE_OFFSET_Y_PX				= 3;
	const float			PROMOTION_FIELD_FIGURE_SCALE					= 0.6f;
	const int			ENPASSANT_ROW_WHITE								= 4;
	const int			ENPASSANT_ROW_BLACK								= 3;

	// graveyard
	const float			GRAVEYARD_SCALEFAKTOR							= 0.7f;
	const int			GRAVEYARD_BOARD_WIDTH_OFFSET_WHITE_PX			= 15;
	const int			GRAVEYARD_BOARD_WIDTH_OFFSET_BLACK_PX			= 25;
	const int			GRAVEYARD_BOARD_HEIGHT_OFFSET_PX				= 10;
	const int			GRAVEYARD_FIGURE_HEIGHT_OFFSET_PX				= 35;

	// generally
	static int convTo1D(int row, int col) {
		return (row * CHESS_SIZE) + col;
	}

	static int calcRowFromIdx(int idx) {
		return idx / CHESS_SIZE;
	}

	static int calcColFromIdx(int idx) {
		return idx % CHESS_SIZE;
	}

	static bool mouseOverFieldAccordingToIdx(sf::Vector2i mousePos, int idx) {
		return	mousePos.x > (calcColFromIdx(idx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX && 
			mousePos.x < (calcColFromIdx(idx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_WITDH_OFFSET_PX + CHESS_FIELD_SIZE_PX &&
			mousePos.y > (calcRowFromIdx(idx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX &&
			mousePos.y < (calcRowFromIdx(idx)) * CHESS_FIELD_SIZE_PX + CHESS_BOARD_HEIGHT_OFFSET_PX + CHESS_FIELD_SIZE_PX;
	}
}