#ifndef SCENEMANAGER_CLASS
#define SCENEMANAGER_CLASS

#include "scene.h"
#include <map>

class SceneManager {
public:
	static SceneManager* getInstance();

	void deleteScene(std::string name);
	void addScene(Scene* scene);

	Scene* getScene(std::string name);
	Scene* getCurrentScene() { return _currentScene; }
	void setCurrentScene(Scene* scene);
	
	void deleteInstance();
	~SceneManager();

private:
	SceneManager();

	Scene* _currentScene;

	std::map <std::string, Scene*> _scenes;
};
#endif
