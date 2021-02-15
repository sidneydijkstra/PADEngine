
#ifndef SHADERDEMO_CLASS
#define SHADERDEMO_CLASS

#include "scene.h"
#include "entity.h"
#include "scenemanager.h"

struct DataBuffer {
	glm::dvec2 center;
	double zoom;
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
			zoom = 1.0f;
			lastMouse.x = 1.0f;
			lastMouse.y = 1.0f;
			center.x = 0.5f;
			center.y = 0.5f;
			maxIts = 1000;
		};

		~Canvas() {
			delete _buffer;
		};

		void update() override {
			if (Input::getMouseScrollDelta().second >= 1.0f) { // out
				center.y += map(Input::getMousePosition().first, 0, Config::WIDTH, -1.0f, 1.0f) / zoom;
				center.x += map(Input::getMousePosition().second, 0, Config::HEIGHT, -1.0f, 1.0f) / zoom;
				zoom /= 0.5f;
			}
			else if (Input::getMouseScrollDelta().second <= -1.0f) { // int
				center.y += map(Input::getMousePosition().first, 0, Config::WIDTH, -1.0f, 1.0f) / zoom;
				center.x += map(Input::getMousePosition().second, 0, Config::HEIGHT, -1.0f, 1.0f) / zoom;
				zoom *= 0.5f;
			}

			if (Input::getMouseButtonDown(0)) {
				lastMouse.x = Input::getMousePosition().first;
				lastMouse.y = Input::getMousePosition().second;
			}

			if (Input::getMouseButton(0)){
				center.y -= ((Input::getMousePosition().first - lastMouse.x) / zoom) / 100;
				center.x -= ((Input::getMousePosition().second - lastMouse.y) / zoom) / 100;
				lastMouse.x = Input::getMousePosition().first;
				lastMouse.y = Input::getMousePosition().second;
			}

			maxIts = Input::getKeyDown(KeyCode::A) ? maxIts - 1000 : Input::getKeyDown(KeyCode::D) ? maxIts + 1000 : maxIts;
		};

		void updateDescriptors(int _index) override {
			this->getUniformBuffer()->updateDescriptor(_index, _descriptorSets[_index], 0);

			this->_buffer->updateBuffer(_index, DataBuffer{ center, zoom, maxIts });
			this->_buffer->updateDescriptor(_index, _descriptorSets[_index], 1);
		};

		double map(double value, double min1, double max1, double min2, double max2) {
			double perc = (value - min1) / (max1 - min1);
			return perc * (max2 - min2) + min2;
		};

	private:
		UniformBuffer<DataBuffer>* _buffer;
		glm::dvec2 center;
		double zoom;
		glm::vec2 lastMouse;
		int maxIts;
};

#endif