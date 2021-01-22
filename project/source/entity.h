
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
#include "mesh.h"
#include "materialmanager.h"
#include "material.h"
#include "uniformbuffer.h"
#include "texture.h"
#include "hierarchy.h"
#include "vector3.h"

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

        UniformBuffer* uniform() {
            return _uniformBuffer;
        };

        Mesh* mesh() {
            return _mesh;
        };

        Texture* texture() {
            return _texture;
        };

        Material* getMaterial() {
            return _material;
        }

        void setMaterial(Material* _material) {
            this->_material->getDescriptor()->freePool(_pool);
            this->_material = _material;
            this->setupDescriptorSets();
        }

        std::vector<VkDescriptorSet> description() {
            return _descriptorSets;
        };

        virtual void recreate(int _index);

        Vector3& getPostion() { return _position; }
        void setPosition(Vector3 position) { _position = position; }
        Vector3& getRotation() { return _rotation; }
        void setRotation(Vector3 rotation) { _rotation = rotation; }
        Vector3& getScale() { return _scale; }
        void setScale(Vector3 scale) { _scale = scale; }
    protected:
        Vector3 _position = Vector3(0, 0, 0);
        Vector3 _rotation = Vector3(0, 0, 0);
        Vector3 _scale = Vector3(1, 1, 1);

        Mesh* _mesh;
        UniformBuffer* _uniformBuffer;
        Texture* _texture;
        Material* _material;

        // TODO: good?
        VkDescriptorPool _pool;
        std::vector<VkDescriptorSet> _descriptorSets;
        virtual void setupDescriptorSets();
        virtual void updateDescriptorSets(int _index);
};
#endif
