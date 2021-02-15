/// @file scenemanager.h
/// @brief Standalone header providing Scene management functionality.
/// @author Naomi Poort
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SCENEMANAGER_CLASS
#define SCENEMANAGER_CLASS

#include "scene.h"
#include <map>

/// @brief Class describing a SceneManager, which controls all Scenes added to the instance of itself.
///


class SceneManager {
public:
	/// @brief Static get instance function, SceneManager is a singelton because it is important to only have one instance of the SceneManager. This is importand because each instance of the SceneManager controls it's own scene's. So if you add Scene A to for example SceneManager A, SceneManager B does not own Scene A and can not acces it through the map: _scenes.  
	/// @return A pointer to SceneManager.
	static SceneManager* getInstance();

	/// @brief Static function to delete and cleanup the SceneManager.
	void deleteInstance();

	/// @brief Delete a Scene by name. This function finds the Scene in question by name from the map, then deletes the Scene's pointer and clears the reference in the map object: _scenes.
	/// @param name Name of Scene.
	void deleteScene(std::string name);

	/// @brief Add a Scene. Oppisite of the deleteScene(std::string name) function, the addScene function adds the given Scene pointer to the _scenes map object for later use in the SceneManager.
	/// @param scene Pointer to Scene.
	void addScene(Scene* scene);

	/// @brief Get a Scene by name.
	/// @param name Name of Scene.
	/// @return Pointer to Scene.
	Scene* getScene(std::string name);

	/// @brief Get current Scene.
	/// @return Pointer to Scene.
	Scene* getCurrentScene() { return _currentScene; }

	/// @brief Set current Scene.
	/// @param scene Pointer to Scene.
	void setCurrentScene(Scene* scene);

	/// @brief Set current Scene by name.
	/// @param name Name of scene.
	void setCurrentScene(const char* name);

	/// @brief The deconstructor for the SceneManager class. Here all objects created in the SceneManager class are deleted when the SceneManager is deleted.
	~SceneManager();
private:
	/// @brief The constructor for the SceneManager class. Here all the variables that need to be initialized are initialized to their default values.
	SceneManager();

	Scene* _currentScene; ///< @brief Current Scene pointer of SceneManager.

	std::map <std::string, Scene*> _scenes; ///< @brief A std::map of Scene pointers arranged by name.
};
#endif
