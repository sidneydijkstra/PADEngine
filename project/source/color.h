
#ifndef COLOR_CLASS
#define COLOR_CLASS

#include <cstdint>
#include <cmath>
#include <iostream>

struct Color {

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Color() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	Color(uint8_t _r, uint8_t _g, uint8_t _b) {
		r = _r;
		g = _g;
		b = _b;
		a = 255;
	}

	static Color lerpColor(Color _c1, Color _c2, float _amount) {
		if (_amount < 0) { _amount = 0; }
		if (_amount > 1) { _amount = 1; }

		uint8_t rn = floor(_c1.r + (_c2.r - _c1.r) * _amount);
		uint8_t gn = floor(_c1.g + (_c2.g - _c1.g) * _amount);
		uint8_t bn = floor(_c1.b + (_c2.b - _c1.b) * _amount);
		uint8_t an = floor(_c1.a + (_c2.a - _c1.a) * _amount);

		return Color(rn, gn, bn, an);
	}

	std::string toString() {
		return "{ " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + " }";
	}

	operator glm::vec3() const {
		return glm::vec3(r/255, g/255, b/255);
	}

	operator glm::vec4() const {
		return glm::vec4(r/255, g/255, b/255, a/255);
	}

};

#define BLACK   Color(0,   0,   0,   255) ///< @brief color black
#define GRAY    Color(127, 127, 127, 255) ///< @brief color gray
#define RED     Color(255, 0,   0,   255) ///< @brief color red
#define ORANGE  Color(255, 127, 0,   255) ///< @brief color orange
#define YELLOW  Color(255, 255, 0,   255) ///< @brief color yellow
#define GREEN   Color(0,   255, 0,   255) ///< @brief color green
#define CYAN    Color(0,   255, 255, 255) ///< @brief color cyan
#define BLUE    Color(0,   0,   255, 255) ///< @brief color blue
#define MAGENTA Color(255, 0,   255, 255) ///< @brief color magenta
#define PINK    Color(255, 127, 255, 255) ///< @brief color pink
#define WHITE   Color(255, 255, 255, 255) ///< @brief color white

#endif