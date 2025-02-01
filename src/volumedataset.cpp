#include "volumedataset.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void VolumeDataset::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_data", "data"), &VolumeDataset::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &VolumeDataset::get_data);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "ImageTexture3D"), "set_data", "get_data");

    ClassDB::bind_method(D_METHOD("set_gradient", "gradient"), &VolumeDataset::set_gradient);
    ClassDB::bind_method(D_METHOD("get_gradient"), &VolumeDataset::get_gradient);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient", PROPERTY_HINT_RESOURCE_TYPE, "ImageTexture3D"), "set_gradient", "get_gradient");

    ClassDB::bind_method(D_METHOD("set_scale", "scale"), &VolumeDataset::set_scale);
    ClassDB::bind_method(D_METHOD("get_scale"), &VolumeDataset::get_scale);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "scale"), "set_scale", "get_scale");

    ClassDB::bind_method(D_METHOD("set_rotation", "rotation"), &VolumeDataset::set_rotation);
    ClassDB::bind_method(D_METHOD("get_rotation"), &VolumeDataset::get_rotation);
    ADD_PROPERTY(PropertyInfo(Variant::QUATERNION, "rotation"), "set_rotation", "get_rotation");
}
