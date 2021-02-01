#ifndef SCENEMANAGER_CLASS
#define SCENEMANAGER_CLASS

#include "scene.h"
#include <map>

class SceneManager {
public:
	SceneManager* getInstance();

	Scene* createScene(string name);
	void addScene(Scene* scene);

	Scene* getScene(string name);
	Scene* getCurrentScene() { return _currentScene; }
	
	void deleteInstance();
	~SceneManager();

private:
	SceneManager();

	static SceneManager* _instance;
	Scene* _currentScene;

	std::map <std::string, Scene*> _scenes;
};
#endif
