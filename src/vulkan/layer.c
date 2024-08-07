#include <string.h>
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include "layer.h"

const char **_layers = NULL;
uint32_t _layer_count = 0;

ValidationLayers *check_layer_support(const char **layers, uint32_t layer_count) {
    if (layers == NULL && layer_count == 0) {
        if (_layers == NULL || _layer_count == 0) return NULL;
        ValidationLayers *p_layers = calloc(1, sizeof(ValidationLayers));
        p_layers->enabled_layers = _layers;
        p_layers->layer_count = _layer_count;
        return p_layers;
    }
    ValidationLayers *p_layers = calloc(1, sizeof(ValidationLayers));
    p_layers->enabled_layers = layers;
    p_layers->layer_count = layer_count;

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
            return NULL;
        }
    }

    _layers = p_layers->enabled_layers;
    _layer_count = p_layers->layer_count;

    return p_layers;
}
