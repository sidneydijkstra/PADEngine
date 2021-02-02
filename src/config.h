/// @file config.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#include <cstdint>

#ifndef CONFIG_CLASS
#define CONFIG_CLASS


/// @brief Class holding config information.
class Config {
	public:
		static const uint32_t WIDTH = 800; ///< @brief The standart width of the window
		static const uint32_t HEIGHT = 600; ///< @brief The standart height of the window
};
#endif