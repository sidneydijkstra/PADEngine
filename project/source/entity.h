
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"

#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"
#include "texturebuffer.h"

#include <iostream>
#include <vector>

#ifndef ENTITY_CLASS
#define ENTITY_CLASS

struct DescriptionData {
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
};

class Entity {
    public:
        Entity(VkInstance _instance, VkCommandPool _commandPool);
        ~Entity();

        VertexBuffer* vertex() {
            return _vertexBuffer;
        };

        IndexBuffer* index() {
            return _indexBuffer;
        };

        UniformBuffer* uniform() {
            return _uniformBuffer;
        };

        TextureBuffer* texture() {
            return _textureBuffer;
        };

        DescriptionData description() {
            return DescriptionData { _descriptorSetLayout, _descriptorPool, _descriptorSets };
        };

        void recreate() {
            _descriptorSets.clear();
            vkDestroyDescriptorPool(DeviceHandler::getInstance()->getLogicalDevice(), _descriptorPool, nullptr);
            vkDestroyDescriptorSetLayout(DeviceHandler::getInstance()->getLogicalDevice(), _descriptorSetLayout, nullptr);

            setupDescriptor();
            setupDescriptorSets();
        };

        glm::vec3 pos;
    private:
        VertexBuffer* _vertexBuffer;
        IndexBuffer* _indexBuffer;
        UniformBuffer* _uniformBuffer;
        TextureBuffer* _textureBuffer;

        // TODO: good?
        void setupDescriptor();
        void setupDescriptorSets();
        VkDescriptorSetLayout _descriptorSetLayout;
        VkDescriptorPool _descriptorPool;
        std::vector<VkDescriptorSet> _descriptorSets;
};
#endif