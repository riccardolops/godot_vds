#ifndef GENERATE_HISTOGRAM_TEXTURE_H
#define GENERATE_HISTOGRAM_TEXTURE_H

#include "volume_dataset.h"
#include <godot_cpp/classes/image_texture.hpp>

using namespace godot;

Ref<ImageTexture> GenerateHistogramTexture(Ref<VolumeDataset> dataset);

#endif // GENERATE_HISTOGRAM_TEXTURE_H