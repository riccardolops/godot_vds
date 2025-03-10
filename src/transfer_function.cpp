#include "transfer_function.h"

void TransferFunction::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_gradient_color", "value"), &TransferFunction::set_gradient_color);
    ClassDB::bind_method(D_METHOD("get_gradient_color"), &TransferFunction::get_gradient_color);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient_color", PROPERTY_HINT_RESOURCE_TYPE, "GradientTexture1D"), "set_gradient_color", "get_gradient_color");

    ClassDB::bind_method(D_METHOD("set_gradient_alpha", "value"), &TransferFunction::set_gradient_alpha);
    ClassDB::bind_method(D_METHOD("get_gradient_alpha"), &TransferFunction::get_gradient_alpha);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gradient_alpha", PROPERTY_HINT_RESOURCE_TYPE, "GradientTexture1D"), "set_gradient_alpha", "get_gradient_alpha");
}

void TransferFunction::set_gradient_color(const Ref<GradientTexture1D> &value) {
    gradient_color = value;
    emit_changed();
}

Ref<GradientTexture1D> TransferFunction::get_gradient_color() const {
    return gradient_color;
}

void TransferFunction::set_gradient_alpha(const Ref<GradientTexture1D> &value) {
    gradient_alpha = value;
    emit_changed();
}

Ref<GradientTexture1D> TransferFunction::get_gradient_alpha() const {
    return gradient_alpha;
}
