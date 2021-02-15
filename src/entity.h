/// @file entity.h
/// @brief Standalone header providing Entity functionality. An Entity object is designed to serve as renderable objects in the scene. This can serve as the different objects needed for your game, like the main character or enemies. 
/// @author Sidney Dijkstra, Naomi Poort
/// @version 1.0.0
/// @date 09/02/2021

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

namespace pad {

/// @brief Enum describing the type of an Entity, this way we know how to render a Entity.
enum class EntityType {
    ENTITY,
    LIGHT,
    CUSTOM
};

/// @brief Class describing a Entity object, which stores all the information for a Entity. Entity inherrits from the Hierarchy class to add the parent-child functionality.
///
/// The entity class contains all the information and functionality needed to easily create game objects within the Scene.
/// These entities can contain meshes to add models, textures, shaders and more. The Entity also stores data like the position, rotation and scale of the object within the scene. 
/// From this class object like a Player, a weapon and more can be created in the games Scene.

class Entity : public Hierarchy {
    public:
        /// @brief The constructor for the Entity class. Here all variables are initialized and set to their default values.
        Entity();
        /// @brief The deconstructor for the Entity class. In the destructor all objects created in the Entity class are deleted from memory.
        virtual ~Entity();

        /// @brief Get UniformBuffer of the Entity, this buffer contains the model/view/projection.
        /// @return Pointer to UniformBuffer.
        UniformBuffer<UBOBufferObject>* getUniformBuffer();

        /// @brief Get EntityType of the Entity.
        /// @return Reference of EntityType.
        EntityType getType();

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

        /// @brief Main update function of the Entity.
        virtual void update();

        /// @brief Recreate function of the Entity.
        /// @param _index Current index.
        virtual void recreate(int _index);

        /// @brief Update descriptors function to update the buffer data in VkDescriptorSet.
        /// @param _index Current index.
        virtual void updateDescriptors(int _index);

        Vector3 position; ///< @brief Position of Entity in the Scene.
        Vector3 rotation; ///< @brief Rotation of Entity in the Scene.
        Vector3 scale; ///< @brief Scale of Entity.
        Color color; ///< @brief Color of Entity.
    protected:
        EntityType _type; ///< @brief Mesh object EntityType.

        Mesh* _mesh; ///< @brief Mesh object pointer of Entity.
        UniformBuffer<UBOBufferObject>* _uniformBuffer; ///< @brief UniformBuffer object pointer of Entity.
        Texture* _texture; ///< @brief Texture object pointer of Entity.
        Material* _material; ///< @brief Material object pointer of Entity.

        std::vector<VkDescriptorSet> _descriptorSets; ///< @brief A std::vector<VkDescriptorSet> list of Entity.

        /// @brief Setup descriptor sets so they can contain entity data.
        void setupDescriptorSets();
};

}

#endif
