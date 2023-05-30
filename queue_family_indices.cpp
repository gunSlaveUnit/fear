//
// Created by gunSlaveUnit on 28.05.2023.
//

#include "queue_family_indices.hpp"

namespace fear {
    void QueueFamilyIndices::find(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface) {
        ufast32 queue_family_count{0};
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

        std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

        int family_index{0};
        for (const auto &queue_family: queue_families) {
            if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                graphics_family = family_index;

            VkBool32 is_device_present_images_surface = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, family_index, surface,
                                                 &is_device_present_images_surface);

            if (is_device_present_images_surface) present_surface_family = family_index;

            if (is_available()) break;

            ++family_index;
        }
    }

    bool QueueFamilyIndices::is_available() const {
        return graphics_family.has_value() && present_surface_family.has_value();
    }
}