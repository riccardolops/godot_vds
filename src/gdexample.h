#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include "volumedataset.h"

namespace godot {
class GDExample : public Sprite2D {
  GDCLASS(GDExample, Sprite2D)

private:
  double time_passed;
  

protected:
  static void _bind_methods();

public:
  GDExample();
  ~GDExample();
  Ref<VolumeDataset> dataset;
  void set_dataset(const Ref<VolumeDataset> &p_dataset);
  Ref<VolumeDataset> get_dataset() const;
  void _process(double delta) override;
};

} // namespace godot

#endif
