/// @file entity.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef ENTITY_CLASS
#define ENTITY_CLASS

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
#include "color.h"

#include <iostream>
#include <vector>

/// @brief Class describing a Entity object, which stores all the information for a Entity.
class Entity : public Hierarchy {
    public:
        /// @brief The constructor for the Entity class.
        Entity();
        /// @brief The deconstructor for the Entity class.
        ~Entity();

        /// @brief Get UniformBuffer of the Entity, this buffer contains the model/view/projection.
        /// @return Pointer to UniformBuffer.
        UniformBuffer<UBOBufferObject>* getUniformBuffer();

        /// @brief Get Mesh of the Entity.
        /// @return Pointer to Mesh.
        Mesh* getMesh();

        /// @brief Get Texture of the Entity.
        /// @return Pointer to Texture.
        Texture* getTexture();

        /// @brief Get Material of the Entity.
        /// @return Pointer to Material.
        Material* getMaterial();

        /// @brief Get current VkDescriptorSet, final buffers for storing entity data.
        /// @param _index Current index.
        /// @return Reference of VkDescriptorSet.
        VkDescriptorSet& getDescriptorSet(int _index);

        /// @brief Recreate function of the Entity.
        /// @param _index Current index.
        virtual void recreate(int _index);

        /// @brief Update descriptors function to update the buffer data in VkDescriptorSet.
        /// @param _index Current index.
        void updateDescriptors(int _index);

        Vector3 position; ///< @brief Position of Entity.
        Vector3 rotation; ///< @brief Rotation of Entity.
        Vector3 scale; ///< @brief Scale of Entity.
        Color color; ///< @brief Color of Entity.
    protected:
        Mesh* _mesh; ///< @brief Mesh object pointer of Entity.
        UniformBuffer<UBOBufferObject>* _uniformBuffer; ///< @brief UniformBuffer object pointer of Entity.
        Texture* _texture; ///< @brief Texture object pointer of Entity.
        Material* _material; ///< @brief Material object pointer of Entity.

        std::vector<VkDescriptorSet> _descriptorSets; ///< @brief A std::vector<VkDescriptorSet> list of Entity.

        /// @brief Setup descriptor sets so they can contain entity data.
        void setupDescriptorSets();
};
#endif
