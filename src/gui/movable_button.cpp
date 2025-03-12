#include "movable_button.h"

void MovableButton::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_moving"), &MovableButton::is_moving);

    ClassDB::bind_method(D_METHOD("set_lock_vertical_movement", "lock"), &MovableButton::set_lock_vertical_movement);
    ClassDB::bind_method(D_METHOD("get_lock_vertical_movement"), &MovableButton::get_lock_vertical_movement);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "lock_vertical_movement"), "set_lock_vertical_movement", "get_lock_vertical_movement");

    ClassDB::bind_method(D_METHOD("set_lock_horizontal_movement", "lock"), &MovableButton::set_lock_horizontal_movement);
    ClassDB::bind_method(D_METHOD("get_lock_horizontal_movement"), &MovableButton::get_lock_horizontal_movement);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "lock_horizontal_movement"), "set_lock_horizontal_movement", "get_lock_horizontal_movement");

    ClassDB::bind_method(D_METHOD("set_lock_to_parent_rect", "lock"), &MovableButton::set_lock_to_parent_rect);
    ClassDB::bind_method(D_METHOD("get_lock_to_parent_rect"), &MovableButton::get_lock_to_parent_rect);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "lock_to_parent_rect"), "set_lock_to_parent_rect", "get_lock_to_parent_rect");

    ClassDB::bind_method(D_METHOD("set_lock_pivot", "pivot"), &MovableButton::set_lock_pivot);
    ClassDB::bind_method(D_METHOD("get_lock_pivot"), &MovableButton::get_lock_pivot);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "lock_pivot", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_lock_pivot", "get_lock_pivot");
}

void MovableButton::_gui_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseButton> mouse_button_event = event;
    Ref<InputEventMouseMotion> mouse_motion_event = event;

    if (mouse_button_event.is_valid() && mouse_button_event->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) {
        if (mouse_button_event->is_pressed()) {
            is_pressed = true;
            mouse_press_position = mouse_button_event->get_global_position();
            original_position = get_global_position();
            
            Control *parent = Object::cast_to<Control>(get_parent());
            if (parent && lock_to_parent_rect) {
                Rect2 parent_rect = parent->get_rect();
                min_position = parent_rect.position - lock_pivot * get_size();
                max_position = parent_rect.position + parent_rect.size - get_size() + lock_pivot * get_size();
            }
        } else {
            is_pressed = false;
        }
    }

    if (mouse_motion_event.is_valid() && is_pressed) {
        Vector2 offset = mouse_motion_event->get_global_position() - mouse_press_position;
        Vector2 new_position = original_position + Vector2(
            lock_horizontal_movement ? 0.0f : offset.x,
            lock_vertical_movement ? 0.0f : offset.y
        );

        if (lock_to_parent_rect) {
            new_position = new_position.clamp(min_position, max_position);
        }

        set_global_position(new_position);
    }
}
