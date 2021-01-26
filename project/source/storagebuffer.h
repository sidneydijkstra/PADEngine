
#ifndef STORAGEBUFFER_CLASS
#define STORAGEBUFFER_CLASS

#include "buffer.h"
#include "swapchainhandler.h"

struct StorageBufferData {
	glm::vec3 data;
};

class StorageBuffer : Buffer {
	public:
		StorageBuffer();
		~StorageBuffer();

		std::vector<VkBuffer> getBuffer();

		void updateBuffer(int _index, StorageBufferData _bufferData);
		void recreate();

	private:
		std::vector<VkBuffer> _buffers;
		std::vector<VkDeviceMemory> _buffersMemory;

		void setupBuffer();
};
#endif


