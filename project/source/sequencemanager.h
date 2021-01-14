#include <cstdint>

#ifndef SEQUENCEMANAGER_CLASS
#define SEQUENCEMANAGER_CLASS

#include "renderer.h"
#include "scene.h"
#include "input.h"

#include <vector>

class SequenceManager {
	public:
		SequenceManager();
		~SequenceManager();

		void draw(Scene* _scene);

		Renderer* getRenderer();

		void setFramebufferResized();
	private:
		Renderer* _renderer;

		float rotSpeed = 10.0f;

		uint32_t getImageIndex();

		void recreate();
		void setupSyncObjects();
		void updateScene(Scene* _scene, int _imageIndex);
		void updateSequence(const VkCommandBuffer _commandBuffer, const uint32_t _imageIndex);

		std::vector<VkSemaphore> _imageAvailableSemaphores;
		std::vector<VkSemaphore> _renderFinishedSemaphores;
		std::vector<VkFence> _inFlightFences;
		std::vector<VkFence> _imagesInFlight;
		size_t _currentFrame = 0;
		bool _framebufferResized = false;

		const int MAX_FRAMES_IN_FLIGHT = 2;
};
#endif