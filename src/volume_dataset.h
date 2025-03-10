#ifndef VOLUME_DATASET_H
#define VOLUME_DATASET_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/image_texture3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/quaternion.hpp>

using namespace godot;

class VolumeDataset : public Resource {
    GDCLASS(VolumeDataset, Resource)

private:
    Vector3 scale = Vector3(1.0, 1.0, 1.0);
    Quaternion rotation = Quaternion(0.0, 0.0, 0.0, 1.0);
    Ref<ImageTexture3D> volume_texture;
    Ref<ImageTexture3D> gradient_texture;

protected:
    static void _bind_methods();

public:
    void set_data(const Ref<ImageTexture3D> &p_data) { volume_texture = p_data; }
    Ref<ImageTexture3D> get_data() const { return volume_texture; }

    void set_gradient(const Ref<ImageTexture3D> &p_gradient) { gradient_texture = p_gradient; }
    Ref<ImageTexture3D> get_gradient() const { return gradient_texture; }

    void set_scale(const Vector3 &p_scale) { scale = p_scale; }
    Vector3 get_scale() const { return scale; }

    void set_rotation(const Quaternion &p_rotation) { rotation = p_rotation; }
    Quaternion get_rotation() const { return rotation; }
};

#endif // VOLUME_DATASET_H
