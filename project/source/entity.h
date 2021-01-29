
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
#include "storagebuffer.h"
#include "uniformbuffer.h"
#include "texture.h"
#include "hierarchy.h"
#include "vector3.h"
#include "color.h"

#include <iostream>
#include <vector>

#ifndef ENTITY_CLASS
#define ENTITY_CLASS

struct DescriptionData {
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
};

class Entity : public Hierarchy {
    public:
        Entity();
        ~Entity();

        UniformBuffer* getUniformBuffer();
        StorageBuffer* getColorBuffer();
        Mesh* getMesh();
        Texture* getTexture();
        Material* getMaterial();
        void setMaterial(const char* _name);

        std::vector<VkDescriptorSet> description();

        virtual void recreate(int _index);

        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
        Color color;
    protected:
        Mesh* _mesh;
        UniformBuffer* _uniformBuffer;
        StorageBuffer* _colorBuffer;
        Texture* _texture;
        Material* _material;

        // TODO: good?
        VkDescriptorPool _pool;
        std::vector<VkDescriptorSet> _descriptorSets;
        virtual void setupDescriptorSets();
        virtual void updateDescriptorSets(int _index);
};
#endif
