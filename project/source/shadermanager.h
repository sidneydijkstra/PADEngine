
#ifndef SHADERMANAGER_CLASS
#define SHADERMANAGER_CLASS

#include "shaderstage.h"

#include <iostream>
#include <map>

class ShaderManager {
	public:
		ShaderManager();
		~ShaderManager();

		static ShaderManager* getInstance();
		static void deleteInsance();

		ShaderStage* getShaderStage(const char* _path, VkShaderStageFlagBits _stage);

	private:
		std::map<std::string, ShaderStage*> _shaderStages;
};
#endif