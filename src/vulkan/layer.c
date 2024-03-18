#include <string.h>
#include <vulkan/vulkan.h>
#include "layer.h"

int check_layer_support(const char **layers, uint32_t layer_count) {
    uint32_t count;
    vkEnumerateInstanceLayerProperties(&count, NULL);
    VkLayerProperties properties[count];
    vkEnumerateInstanceLayerProperties(&count, properties);

    for (size_t i = 0; i < layer_count; i++) {
        int layer_found = 0;
        for (size_t j = 0; j < count; j++) {
            if (!strcmp(layers[i], properties[j].layerName)) {
                layer_found = 1;
                break;
            }
        }

        if (!layer_found) {
            return 0;
        }
    }

    return 1;
}
