//
// Created by gunSlaveUnit on 28.05.2023.
//

#pragma once

#ifndef FEAR_QUEUE_FAMILY_INDICES_HPP
#define FEAR_QUEUE_FAMILY_INDICES_HPP

#include <optional>

#include <vulkan/vulkan.hpp>

#include "types.h"

namespace fear {

    /*
     * Information about indexes of required queues.
     * */
    struct QueueFamilyIndices {

        /*
         * Finds queue families that support the required operations.
         * */
        void find(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface);

        /*
        * Check indexes of all requested queues have a value.
        * */
        [[nodiscard]] bool is_available() const;

        std::optional<ufast32> graphics_family;
        std::optional<ufast32> present_surface_family;
    };

}

#endif //FEAR_QUEUE_FAMILY_INDICES_HPP
