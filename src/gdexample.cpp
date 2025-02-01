#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include "volumedataset.h"

using namespace godot;

void GDExample::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_dataset", "dataset"), &GDExample::set_dataset);
  ClassDB::bind_method(D_METHOD("get_dataset"), &GDExample::get_dataset);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dataset", PROPERTY_HINT_RESOURCE_TYPE, "VolumeDataset"), "set_dataset", "get_dataset");
}

GDExample::GDExample() {
  // Initialize any variables here.
  time_passed = 0.0;
}

GDExample::~GDExample() {
  // Add your cleanup here.
}

void GDExample::_process(double delta) {
  time_passed += delta;

  Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)),
                                 10.0 + (10.0 * cos(time_passed * 1.5)));

  set_position(new_position);
}

void GDExample::set_dataset(const Ref<VolumeDataset> &p_dataset) {
  dataset = p_dataset;
}

Ref<VolumeDataset> GDExample::get_dataset() const {
  return dataset;
}
