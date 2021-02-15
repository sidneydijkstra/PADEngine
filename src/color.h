/// @file color.h
/// @brief Standalone header providing Color functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef COLOR_CLASS
#define COLOR_CLASS

#include <cstdint>
#include <cmath>
#include <iostream>

//namespace pad {

/// @brief Struct describing a Color object, for using rgba colors.
///
/// In the Color struct the value`s for each separate color red, green, blue and the alpha value are stored. 
/// The color its value range from 0 to 255, just like normal RGBA color pickers.

	struct Color {

		uint8_t r; ///< @brief the red value of the Color
		uint8_t g; ///< @brief the green value of the Color
		uint8_t b; ///< @brief the blue value of the Color
		uint8_t a; ///< @brief the alpha value of the Color

		/// @brief The constructor for the Color class.
		Color() {
			r = 255;
			g = 255;
			b = 255;
			a = 255;
		}

		/// @brief The constructor for the Color class.
		/// @param _r The red value.
		/// @param _g The green value.
		/// @param _b The blue value.
		/// @param _a The alpha value.
		Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		/// @brief The constructor for the Color class.
		/// @param _r The red value.
		/// @param _g The green value.
		/// @param _b The blue value.
		Color(uint8_t _r, uint8_t _g, uint8_t _b) {
			r = _r;
			g = _g;
			b = _b;
			a = 255;
		}

		/// @brief Logic for lerping a color from a to b.
		/// @param _c1 Start value of color.
		/// @param _c2 End value of color.
		/// @param _amount Lerp amount/speed.
		/// @return The next color to change to.
		static Color lerpColor(Color _c1, Color _c2, float _amount) {
			if (_amount < 0) { _amount = 0; }
			if (_amount > 1) { _amount = 1; }

			uint8_t rn = floor(_c1.r + (_c2.r - _c1.r) * _amount);
			uint8_t gn = floor(_c1.g + (_c2.g - _c1.g) * _amount);
			uint8_t bn = floor(_c1.b + (_c2.b - _c1.b) * _amount);
			uint8_t an = floor(_c1.a + (_c2.a - _c1.a) * _amount);

			return Color(rn, gn, bn, an);
		}

		/// @brief Logic for translating Color to std::string
		/// @return The rgba values in std::string format.
		std::string toString() {
			return "{ " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + " }";
		}

		/// @brief Operator overitor for convertion to glm::vec3.
		/// @return The rgba values in glm::vec3 format.
		operator glm::vec3() const {
			return glm::vec3(r / 255, g / 255, b / 255);
		}

		/// @brief Operator overitor for convertion to glm::vec4.
		/// @return The rgba values in glm::vec4 format.
		operator glm::vec4() const {
			return glm::vec4(r / 255, g / 255, b / 255, a / 255);
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

//}

#endif