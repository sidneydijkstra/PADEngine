#include "shaderdemo.h"

ShaderDemo::ShaderDemo(std::string _name) : Scene(_name) {
    this->_renderPass = new RenderPass();

    // normal shader data
    MaterialData mat_custom{};
    mat_custom.name = "mat_custom";
    mat_custom.vertexPath = "shaders/vert_custom.spv";
    mat_custom.fragmentPath = "shaders/frag_custom.spv";
    mat_custom.renderPass = _renderPass;

    // custom shader data -> optional
    mat_custom.customShader = true;

    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    std::array<VkDescriptorSetLayoutBinding, 1> bindings = { uboLayoutBinding };

    mat_custom.descriptorLayout = bindings.data();
    mat_custom.descriptorLayoutSize = 1;

    std::array<VkDescriptorPoolSize, 1> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(SwapChainHandler::getInstance()->getSwapChainImagesSize());

    mat_custom.descriptorPool = poolSizes.data();
    mat_custom.descriptorPoolSize = 1;

    MaterialManager::getInstance()->load(mat_custom);

    _plane = new Canvas();
    this->addChild(_plane);
}

void ShaderDemo::update() {
	this->getCamera()->move3D(5.0f);

	if (Input::getKeyDown(KeyCode::Q))
		SceneManager::getInstance()->setCurrentScene("light_demo");
	if (Input::getKeyDown(KeyCode::E))
		SceneManager::getInstance()->setCurrentScene("light_demo");
}

ShaderDemo::~ShaderDemo() {
    delete _plane;
    delete _renderPass;
}
