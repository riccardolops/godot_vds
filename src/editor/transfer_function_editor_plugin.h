#ifndef TRANSFER_FUNCTION_EDITOR_PLUGIN_H
#define TRANSFER_FUNCTION_EDITOR_PLUGIN_H

#include "transfer_function.h"
#include "../util/editor_scale.h"
#include <godot_cpp/classes/editor_inspector.hpp>
#include <godot_cpp/classes/editor_inspector_plugin.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_spin_slider.hpp>
#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/v_separator.hpp>
#include <godot_cpp/classes/scene_state.hpp>
#include <godot_cpp/classes/popup_panel.hpp>
#include <godot_cpp/classes/color_picker.hpp>
#include <godot_cpp/classes/editor_settings.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/gradient.hpp>
#include <godot_cpp/classes/editor_undo_redo_manager.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

class TransferFunctionEditor : public VBoxContainer {
	GDCLASS(TransferFunctionEditor, VBoxContainer);
public:
	TransferFunctionEditor();
	void set_transfer_function(Ref<TransferFunction> p_tf);
	
private:
	Ref<TransferFunction> _transfer_function;
	TextureRect *_histogram_texture_rect = nullptr;
	TextureRect *_palette_texture_rect = nullptr;
	static void _bind_methods() {};
	void transfer_function_changed();
	
};

class EditorInspectorPluginTransferFunction : public EditorInspectorPlugin {
    GDCLASS(EditorInspectorPluginTransferFunction, EditorInspectorPlugin);

public:
    virtual bool _can_handle(Object *p_object) const override;
    virtual void _parse_begin(Object *p_object) override;

protected:
	static void _bind_methods();
};

#endif // TRANSFER_FUNCTION_EDITOR_PLUGIN_H