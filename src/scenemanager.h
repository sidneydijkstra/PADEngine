/// @file scenemanager.h
/// @brief Standalone header providing Buffer functionality.
/// @author Naomi Poort
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SCENEMANAGER_CLASS
#define SCENEMANAGER_CLASS

#include "scene.h"
#include <map>

/// @brief Class describing a SceneManager, which stores all the scenes by name and order.
class SceneManager {
public:
	/// @brief Static get instance function, SceneManager is a singelton because we only need one instance.
	/// @return A pointer to SceneManager.
	static SceneManager* getInstance();
	/// @brief Static function to delete and cleanup the SceneManager.
	void deleteInstance();

	/// @brief Delete a Scene by name.
	/// @param name Name of Scene.
	void deleteScene(std::string name);

	/// @brief Add a Scene.
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

	/// @brief The deconstructor for the SceneManager class.
	~SceneManager();
private:
	/// @brief The constructor for the SceneManager class.
	SceneManager();

	Scene* _currentScene; ///< @brief Current Scene pointer of SceneManager.

	std::map <std::string, Scene*> _scenes; ///< @brief A std::map of Scene pointers arranged by name.
};
#endif
