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
///
/// The Hierarchy class is designed after the Unity engine <a href=” https://riptutorial.com/unity3d/example/7478/parenting-and-children”>parenting and children</a> structure. 
/// It creates a link between the parent object and the child objects within the scene they are created in. When the parents position changes the child`s position is updated relative to its parent. 
/// For example, if the parent its global position, which means the position within the scene, is 1 on the x-axis and 1 on the y-axis and the child its position relative from its parent is 1 on the x-axis and 1 on the y-axis. 
/// The child`s global position is 2 on the x-axis and 2 on the y-axis. If we now change the parent its position to 2 on the x-axis and 2 on the y-axis. 
/// The child`s position updates automatically to 3 on the x-axis and 3 on the y-axis. 
/// This can come in handy when you want objects within your game linked, for example a player and his weapon. 
/// Since multiple object besides Entity needs this functionality like a the Camera and Scene.

class Hierarchy
{
public:
	/// @brief The constructor for the Hierarchy class.
	Hierarchy();
	/// @brief The deconstructor for the Hierarchy class.
	virtual ~Hierarchy();

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