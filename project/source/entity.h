
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"

#include "resourcemanager.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"
#include "texture.h"

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
        Entity();
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

        Texture* texture() {
            return _texture;
        };

        std::vector<VkDescriptorSet> description() {
            return _descriptorSets;
        };

        virtual void recreate(int _index);

        glm::vec3 pos;
    protected:
        VertexBuffer* _vertexBuffer;
        IndexBuffer* _indexBuffer;
        UniformBuffer* _uniformBuffer;
        Texture* _texture;

        // TODO: good?
        VkDescriptorPool _pool;
        std::vector<VkDescriptorSet> _descriptorSets;
        virtual void setupDescriptorSets();
        virtual void updateDescriptorSets(int _index);
};
#endif