#include "generate_histogram_texture.h"

Ref<ImageTexture> GenerateHistogramTexture(Ref<VolumeDataset> dataset) {
    TypedArray<Image> data = dataset->get_data()->get_data();
    float _min_value = std::numeric_limits<float>::max();
    float _max_value = std::numeric_limits<float>::lowest();
    for (int i = 0; i < data.size(); i++) {
        Ref<Image> slice = data[i];
        if (slice.is_null()) continue;

        Vector2i size = slice->get_size();

        for (int y = 0; y < size.y; ++y) {
            for (int x = 0; x < size.x; ++x) {
                float value = slice->get_pixel(x, y).r; // Assuming single-channel format
                _min_value = std::min(_min_value, value);
                _max_value = std::max(_max_value, value);
            }
        }
    }
    float _value_range = _max_value - _min_value;
    if (_value_range == 0) return Ref<ImageTexture>(); // Avoid division by zero

    int _n_frequencies = std::min((int)_value_range, 1024);
    int *_frequencies = new int[_n_frequencies]();
    int maxFreq = 0;
    float valRangeRecip = 1.0f / (_min_value - _max_value);
    for (int i = 0; i < data.size(); i++) {
        Ref<Image> slice = data[i];
        if (slice.is_null()) continue;

        Vector2i size = slice->get_size();

        for (int y = 0; y < size.y; ++y) {
            for (int x = 0; x < size.x; ++x) {
                float value = slice->get_pixel(x, y).r;
                int bin_index = (int)(((value - _min_value) / _value_range) * (_n_frequencies - 1));
                _frequencies[bin_index]++;
                maxFreq = std::max(maxFreq, _frequencies[bin_index]);
            }
        }
    }

    float *samples = new float[_n_frequencies];
    for (int i = 0; i < _n_frequencies; i++) {
        samples[i] = (maxFreq > 0) ? log10f((float)_frequencies[i]) / log10f((float)maxFreq) : 0.0f;
    }

    PackedByteArray _byteArray;
    _byteArray.resize(_n_frequencies * sizeof(float));
    uint8_t *_byteArray_ptr = _byteArray.ptrw();
    memcpy(_byteArray_ptr, samples, _n_frequencies * sizeof(float));
    Ref<Image> histogram_image = Image::create_from_data(_n_frequencies, 1, false, Image::Format::FORMAT_RF, _byteArray);
    return ImageTexture::create_from_image(histogram_image);
}