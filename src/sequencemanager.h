/// @file sequencemanager.h
/// @brief Standalone header providing SequenceManager functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SEQUENCEMANAGER_CLASS
#define SEQUENCEMANAGER_CLASS

#include "renderer.h"
#include "scene.h"
#include "input.h"

#include <cstdint>
#include <vector>

/// @brief Class describing a SequenceManager, which handles the flow of the engine.
class SequenceManager {
	public:
		/// @brief The constructor for the SequenceManager class.
		SequenceManager();
		/// @brief The deconstructor for the SequenceManager class.
		~SequenceManager();

		/// @brief The draw function of SequenceManager.
		/// @param _scene The Scene to draw.
		void draw(Scene* _scene);

		/// @brief Get the Renderer.
		/// @return Pointer to Renderer.
		Renderer* getRenderer();

		/// @brief Set resize value to true, this means the window is resized.
		void setFramebufferResized();
	private:
		Renderer* _renderer; ///< @brief Renderer pointer of SequenceManager.

		/// @brief Get the image index.
		/// @return Current image index.
		uint32_t getImageIndex();

		/// @brief Recreate the SequenceManager.
		void recreate();

		/// @brief Setup sync objects.
		void setupSyncObjects();

		/// @brief Setup a scene.
		/// @param _scene Pointer to the Scene.
		/// @param _imageIndex Current image index.
		void updateScene(Scene* _scene, int _imageIndex);

		/// @brief Update the sequence.
		/// @param _commandBuffer VkCommandBuffer to use.
		/// @param _imageIndex Current image index.
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