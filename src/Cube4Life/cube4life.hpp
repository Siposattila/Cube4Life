#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class Cube4Life {
public:
  void run();

private:
  GLFWwindow *mGLFWwindow = nullptr;
  const uint32_t mWindowWidth = 800;
  const uint32_t mWindowHeight = 600;

  VkInstance mVulkanInstance = nullptr;

  VkDebugUtilsMessengerEXT mVulkanDebugMessenger = nullptr;

  VkPhysicalDevice mVulkanPhysicalDevice = nullptr;
  VkDevice mVulkanDevice = nullptr;
  VkQueue mVulkanGraphicsQueue = nullptr;
  VkQueue mVulkanPresentGraphicsQueue = nullptr;

  VkSurfaceKHR mVulkanSurface = nullptr;

  VkSwapchainKHR mVulkanSwapChain = nullptr;
  std::vector<VkImage> mVulkanSwapChainImages;
  VkFormat mVulkanSwapChainImageFormat;
  VkExtent2D mVulkanSwapChainExtent;
  std::vector<VkImageView> mVulkanSwapChainImageViews;
  std::vector<VkFramebuffer> mVulkanSwapChainFramebuffers;

  VkRenderPass mVulkanRenderPass = nullptr;
  VkPipelineLayout mVulkanPipelineLayout = nullptr;
  VkPipeline graphicsPipeline = nullptr;

  VkCommandPool mVulkanCommandPool = nullptr;
  VkCommandBuffer mVulkanCommandBuffer = nullptr;

  VkSemaphore mVulkanImageAvailableSemaphore = nullptr;
  VkSemaphore mVulkanRenderFinishedSemaphore = nullptr;
  VkFence mVulkanInFlightFence = nullptr;

  void initWindow();
  void initVulkan();

  void createInstance();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  VkShaderModule createShaderModule(const std::vector<char> &code);
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffer();
  void createSyncObjects();

  void setupDevice();

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  void mainLoop();
  void cleanup();

  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  void setupDebugMessenger();
  std::vector<const char *> getRequiredExtensions();
  bool checkValidationLayerSupport();
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);

  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

  static std::vector<char> readFile(const std::string &filename);

  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  void drawFrame();
};
