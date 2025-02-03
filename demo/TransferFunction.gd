class_name TransferFunction
extends Resource

@export var gradient_color: GradientTexture1D:
    get:
        return gradient_color
    set(value):
        gradient_color = value
        emit_changed()
@export var gradient_alpha: GradientTexture1D:
    get:
        return gradient_alpha
    set(value):
        gradient_alpha = value
        emit_changed()
