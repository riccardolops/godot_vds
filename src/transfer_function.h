#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/gradient_texture1_d.hpp>

using namespace godot;

class TransferFunction : public Resource {
    GDCLASS(TransferFunction, Resource);

private:
    Ref<GradientTexture1D> gradient_color;
    Ref<GradientTexture1D> gradient_alpha;

protected:
    static void _bind_methods();

public:
    void set_gradient_color(const Ref<GradientTexture1D> &value);
    Ref<GradientTexture1D> get_gradient_color() const;

    void set_gradient_alpha(const Ref<GradientTexture1D> &value);
    Ref<GradientTexture1D> get_gradient_alpha() const;
};

#endif // TRANSFER_FUNCTION_H
