//
// Created by gunSlaveUnit on 28.05.2023.
//

#include "queue_family_indices.hpp"

namespace fear {
    void QueueFamilyIndices::find(const VkPhysicalDevice &physical_device) {
        ufast32 queue_family_count{0};
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

        std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

        int graphics_family_index{0};
        for (const auto &queue_family: queue_families) {
            if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                graphics_family = graphics_family_index;

            if (is_available()) break;

            ++graphics_family_index;
        }
    }

    bool QueueFamilyIndices::is_available() const {
        return graphics_family.has_value();
    }
}