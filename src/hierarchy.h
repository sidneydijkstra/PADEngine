/// @file hierarchy.h
/// @brief Standalone header providing Hierarchy functionality.
/// @author Naomi Poort
/// @version 1.0.0
/// @date 02/01/2021

#ifndef HIERARCHY_CLASS
#define HIERARCHY_CLASS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/// @brief Class describing a Hierarchy object, which stores all child -> parent logic.
class Hierarchy
{
public:
	/// @brief The constructor for the Hierarchy class.
	Hierarchy();
	/// @brief The deconstructor for the Hierarchy class.
	~Hierarchy();

	/// @brief Add child to Hierarchy.
	/// @param child Pointer to Hierarchy object.
	void addChild(Hierarchy* child);

	/// @brief Remove child to Hierarchy.
	/// @param child Pointer to Hierarchy object.
	void removeChild(Hierarchy* child);

	/// @brief Get parent of Hierarchy object.
	/// @return Pointer to Hierarchy object.
	Hierarchy* getParent() { return _parent; };

	/// @brief Get all children of Hierarchy object.
	/// @return std::vector with pointers to Hierarchy objects.
	std::vector<Hierarchy*> getChildren() { return _children; }

	int guid; ///< @brief Value of guid.

private:
	std::vector<Hierarchy*> _children; ///< @brief The std::vector containing Hierarchy pointers.
	Hierarchy* _parent; ///< @brief Hierarchy pointer containing parent.

	int _nextGuid; ///< @brief Value of next guid.
};

#endif