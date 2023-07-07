#pragma once

#include <string>

namespace swe {
	enum class Color {
		none, black, white
	};

    static std::string colorToString(Color const value)
    {
        switch (value)
        {
            case Color::none:
                return "none";
            case Color::black:
                return "black";
            case Color::white:
                return "white";
            default:
                return "Unknown";
        }
    }
}