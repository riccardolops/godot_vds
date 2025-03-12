#ifndef MOVABLE_BUTTON_H
#define MOVABLE_BUTTON_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

class MovableButton : public Button {
    GDCLASS(MovableButton, Button);

private:
    bool is_pressed = false;
    Vector2 original_position;
    Vector2 mouse_press_position;
    Vector2 min_position;
    Vector2 max_position;

    bool lock_vertical_movement = false;
    bool lock_horizontal_movement = false;
    bool lock_to_parent_rect = false;
    Vector2 lock_pivot = Vector2(0.0f, 0.0f);

protected:
    static void _bind_methods();

public:
    bool is_moving() const { return is_pressed; }

    void _gui_input(const Ref<InputEvent> &event);

    void set_lock_vertical_movement(bool lock) { lock_vertical_movement = lock; }
    bool get_lock_vertical_movement() const { return lock_vertical_movement; }

    void set_lock_horizontal_movement(bool lock) { lock_horizontal_movement = lock; }
    bool get_lock_horizontal_movement() const { return lock_horizontal_movement; }

    void set_lock_to_parent_rect(bool lock) { lock_to_parent_rect = lock; }
    bool get_lock_to_parent_rect() const { return lock_to_parent_rect; }

    void set_lock_pivot(Vector2 pivot) { lock_pivot = pivot; }
    Vector2 get_lock_pivot() const { return lock_pivot; }
};

#endif // MOVABLE_BUTTON_H
