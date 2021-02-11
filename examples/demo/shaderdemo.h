
#ifndef SHADERDEMO_CLASS
#define SHADERDEMO_CLASS

#include "scene.h"
#include "entity.h"
#include "scenemanager.h"

struct DataBuffer {
	glm::vec2 center;
	glm::vec2 zoom;
	int maxIts;
};

class ShaderDemo : public Scene {
	public:
		ShaderDemo(std::string _name);
		~ShaderDemo();
		
		void update() override;
	private:
		RenderPass* _renderPass;
		Entity* _plane;
};

class Canvas : public Entity {
	public:
		Canvas() : Entity() {
			this->_type = EntityType::CUSTOM;
			this->getMesh()->loadShape(MeshType::PLANE);
			this->getMaterial()->setMaterial("mat_custom");
			this->setupDescriptorSets();

			_buffer = new UniformBuffer<DataBuffer>();
			zoom.x = 1.0f;
			zoom.y = 1.0f;
			center.x = 0.5f;
			center.y = 0.5f;
			maxIts = 1000;
		};
		~Canvas() {
			delete _buffer;
		};

		void update() override {
			if (Input::getMouseScrollDelta().second >= 1.0f) { // out
				center.y += map(Input::getMousePosition().first, 0, Config::WIDTH, -1.0f, 1.0f) / zoom.x;
				center.x += map(Input::getMousePosition().second, 0, Config::HEIGHT, -1.0f, 1.0f) / zoom.y;
				zoom.x /= 0.5f;
				zoom.y /= 0.5f;
			}
			else if (Input::getMouseScrollDelta().second <= -1.0f) { // int
				center.y += map(Input::getMousePosition().first, 0, Config::WIDTH, -1.0f, 1.0f) / zoom.x;
				center.x += map(Input::getMousePosition().second, 0, Config::HEIGHT, -1.0f, 1.0f) / zoom.y;
				zoom.x *= 0.5f;
				zoom.y *= 0.5f;
			}

			maxIts = Input::getKeyDown(KeyCode::A) ? maxIts - 1000 : Input::getKeyDown(KeyCode::D) ? maxIts + 1000 : maxIts;
		};

		void updateDescriptors(int _index) override {
			this->getUniformBuffer()->updateDescriptor(_index, _descriptorSets[_index], 0);

			this->_buffer->updateBuffer(_index, DataBuffer{ center, glm::vec2(zoom), maxIts });
			this->_buffer->updateDescriptor(_index, _descriptorSets[_index], 1);
		};

		float map(float value, float min1, float max1, float min2, float max2) {
			float perc = (value - min1) / (max1 - min1);
			return perc * (max2 - min2) + min2;
		};

	private:
		UniformBuffer<DataBuffer>* _buffer;
		glm::vec2 center;
		glm::vec2 zoom;
		int maxIts;
};

#endif