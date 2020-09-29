#include "core.h"

Core::Core() {

}

Core::~Core() {

}

void Core::run() {
    initWindow();

    initVulkan();
    loop();
    cleanup();
}

void Core::initVulkan() {
    this->createInstance();
    this->createSurface();

	_deviceHandler = new DeviceHandler(this->_instance, this->_surface);

	_deviceHandler->setupDevices();

	this->_physicalDevice = _deviceHandler->getPhysicalDevice();
	this->_device = _deviceHandler->getLogicalDevice();

	_deviceHandler->getDevicePresentQueue(_presentQueue);
	_deviceHandler->getDeviceGraphicsQueue(_graphicsQueue);

    //this->pickPhysicalDevice();
    //this->createLogicalDevice();

    _swapChainHandler = new SwapChainHandler(this->_instance, this->_surface, _deviceHandler);

    _swapChainHandler->setupSwapChain();
    this->_swapChain = _swapChainHandler->getSwapChain();

    //this->createSwapChain();
    //this->createImageView();

    this->createRenderPass();
	this->createGraphicsPipeline();

    this->createFramebuffers();
    this->createCommandPool();
    this->createCommandBuffers();
    this->createSyncObjects();
}

void Core::createInstance() {
    // check if validation layers ar available
    if (this->_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }else {
        std::cout << "validation layers requested and available!" << std::endl;
    }

    // create struck with information about vulkan, technically optional but it may provide some useful information to the driver in order to optimize our specific application
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "PADEngine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "No Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    // tell the Vulkan driver which global extensions and validation layers we want to use
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    // add validation layers
    if (this->_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(this->_validationLayers.size());
        createInfo.ppEnabledLayerNames = this->_validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    // create a vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan instance!");
    }else {
        std::cout << "created Vulkan instance!" << std::endl;
    }

    // check available vulkan extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // print available extensions
    /*std::cout << "available extensions:\n";

    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }*/
}

void Core::createSurface() {
    if (glfwCreateWindowSurface(this->_instance, this->_window, nullptr, &this->_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan surface instance!");
    }
    else {
        std::cout << "created Vulkan surface instance!" << std::endl;
    }
}

std::vector<char> Core::readFile(const std::string& _filename) {
	std::ifstream file(_filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

void Core::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = _swapChainHandler->getSwapChainImageFormat();
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(this->_device, &renderPassInfo, nullptr, &this->_renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }else {
        std::cout << "created render pass!" << std::endl;
    }
}

void Core::createGraphicsPipeline() {
	auto vertShaderCode = readFile("shaders/vert.spv");
	auto fragShaderCode = readFile("shaders/frag.spv");

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)_swapChainHandler->getSwapChainExtent().width;
    viewport.height = (float)_swapChainHandler->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = this->_swapChainHandler->getSwapChainExtent();

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH
    };

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = 2;
    dynamicState.pDynamicStates = dynamicStates;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

    if (vkCreatePipelineLayout(this->_device, &pipelineLayoutInfo, nullptr, &this->_pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }else {
        std::cout << "created pipeline layout!" << std::endl;
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;

    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr; // Optional

    pipelineInfo.layout = this->_pipelineLayout;
    pipelineInfo.renderPass = this->_renderPass;
    pipelineInfo.subpass = 0;

    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional

    if (vkCreateGraphicsPipelines(this->_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->_graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }else {
        std::cout << "created graphics pipeline!" << std::endl;
    }

    vkDestroyShaderModule(this->_device, fragShaderModule, nullptr);
    vkDestroyShaderModule(this->_device, vertShaderModule, nullptr);
}

VkShaderModule Core::createShaderModule(const std::vector<char>& _code) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = _code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(_code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(this->_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
    }else {
        std::cout << "created shader module!" << std::endl;
    }

	return shaderModule;
}

void Core::createFramebuffers() {
    this->_swapChainFramebuffers.resize(this->_swapChainHandler->getSwapChainImageViews().size());

    for (size_t i = 0; i < this->_swapChainHandler->getSwapChainImageViews().size(); i++) {
        VkImageView attachments[] = {
            this->_swapChainHandler->getSwapChainImageViews()[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = this->_renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = this->_swapChainHandler->getSwapChainExtent().width;
        framebufferInfo.height = this->_swapChainHandler->getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(this->_device, &framebufferInfo, nullptr, &this->_swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }else {
            std::cout << "\t- created framebuffer!" << std::endl;
        }
    }
}

void Core::createCommandPool() {
    QueueFamilyIndices queueFamilyIndices = _deviceHandler->findQueueFamilies(this->_physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(this->_device, &poolInfo, nullptr, &this->_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }else {
        std::cout << "created command pool!" << std::endl;
    }
}


void Core::createCommandBuffers() {
    this->_commandBuffers.resize(this->_swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = this->_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->_commandBuffers.size();

    if (vkAllocateCommandBuffers(this->_device, &allocInfo, this->_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }else {
        std::cout << "created command buffers!" << std::endl;
    }

    for (size_t i = 0; i < this->_commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(this->_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }else {
            std::cout << "\t- begin recording command buffer!" << std::endl;
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->_renderPass;
        renderPassInfo.framebuffer = this->_swapChainFramebuffers[i];

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = this->_swapChainHandler->getSwapChainExtent();

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(this->_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(this->_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, this->_graphicsPipeline);
        vkCmdDraw(this->_commandBuffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(this->_commandBuffers[i]);

        if (vkEndCommandBuffer(this->_commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }else {
            std::cout << "\t- recording command buffer!" << std::endl;
        }
    }
}

void Core::createSyncObjects() {
    this->_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    this->_imagesInFlight.resize(this->_swapChainHandler->getSwapChainImages().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(this->_device, &semaphoreInfo, nullptr, &this->_imageAvailableSemaphores[i]) != VK_SUCCESS || vkCreateSemaphore(this->_device, &semaphoreInfo, nullptr, &this->_renderFinishedSemaphores[i]) != VK_SUCCESS || vkCreateFence(this->_device, &fenceInfo, nullptr, &this->_inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }else {
            std::cout << "\t- created synchronization object for a frame!" << std::endl;
        }
    }
}

void Core::drawFrame() {
    vkWaitForFences(this->_device, 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(this->_device, this->_swapChain, UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->_device, 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    this->_imagesInFlight[imageIndex] = this->_inFlightFences[this->_currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { this->_imageAvailableSemaphores[this->_currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->_commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = { this->_renderFinishedSemaphores[this->_currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(this->_device, 1, &this->_inFlightFences[this->_currentFrame]);

    if (vkQueueSubmit(this->_graphicsQueue, 1, &submitInfo, this->_inFlightFences[this->_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { this->_swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueuePresentKHR(this->_presentQueue, &presentInfo);
    vkQueueWaitIdle(this->_presentQueue);
}

bool Core::checkValidationLayerSupport() {
    // get all validation layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // check if all the layers in _validationLayers exist in availableLayers
    for (const char* layerName : this->_validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

void Core::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = glfwCreateWindow(Config::WIDTH, Config::HEIGHT, "PAD-Engine", nullptr, nullptr);
}

void Core::loop() {
    while (!glfwWindowShouldClose(this->_window)) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(this->_device);
}

void Core::cleanup() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->_device, this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(this->_device, this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(this->_device, this->_inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(this->_device, this->_commandPool, nullptr);

    for (VkFramebuffer framebuffer : this->_swapChainFramebuffers) {
        vkDestroyFramebuffer(this->_device, framebuffer, nullptr);
    }

    vkDestroyPipeline(this->_device, this->_graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(this->_device, this->_pipelineLayout, nullptr);
    vkDestroyRenderPass(this->_device, this->_renderPass, nullptr);

    delete _swapChainHandler;
    delete _deviceHandler;

    vkDestroySurfaceKHR(this->_instance, this->_surface, nullptr);
    vkDestroyInstance(this->_instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}
