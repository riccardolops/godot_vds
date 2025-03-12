#include "transfer_function_editor_plugin.h"

#define RL ResourceLoader::get_singleton()

///////////////////////

TransferFunctionEditor::TransferFunctionEditor() {
    Label *label = memnew(Label);
    label->set_text("Transfer Function Editor");
    add_child(label);

    HFlowContainer *toolbar = memnew(HFlowContainer);
    add_child(toolbar);

    Button *save_button = memnew(Button);
    save_button->set_text("Save");
    toolbar->add_child(save_button);

    toolbar->add_child(memnew(VSeparator));

    Button *load_button = memnew(Button);
    load_button->set_text("Load");
    toolbar->add_child(load_button);


    Panel *alpha_panel = memnew(Panel);
    Panel *colour_panel = memnew(Panel);
    alpha_panel->set_focus_mode(FOCUS_ALL);
    alpha_panel->set_custom_minimum_size(Size2(0, 200) * EDSCALE);
	add_child(alpha_panel);
    _histogram_texture_rect = memnew(TextureRect);
    ERR_FAIL_COND(!RL->exists("res://addons/godotvolumetricrendering/shaders/TransferFunctionEditor.gdshader"));
    Ref<ShaderMaterial> _histogram_material;
    _histogram_material.instantiate();
    _histogram_material->set_shader(RL->load("res://addons/godotvolumetricrendering/shaders/TransferFunctionEditor.gdshader"));
    _histogram_texture_rect->set_material(_histogram_material);
    _histogram_texture_rect->set_anchors_preset(PRESET_FULL_RECT);
    alpha_panel->add_child(_histogram_texture_rect);

    colour_panel->set_custom_minimum_size(Size2(0, 60) * EDSCALE);
    add_child(colour_panel);
    _palette_texture_rect = memnew(TextureRect);
    _palette_texture_rect->set_anchors_preset(PRESET_FULL_RECT);
    colour_panel->add_child(_palette_texture_rect);
}

void TransferFunctionEditor::set_transfer_function(Ref<TransferFunction> p_tf) {
    _transfer_function = p_tf;
    transfer_function_changed();
    if (!_transfer_function->is_connected("changed", callable_mp(this, &TransferFunctionEditor::transfer_function_changed))) {
        _transfer_function->connect("changed", callable_mp(this, &TransferFunctionEditor::transfer_function_changed));
    }
}

void TransferFunctionEditor::transfer_function_changed() {
    ((Ref<ShaderMaterial>)_histogram_texture_rect->get_material())->set_shader_parameter("tf_tex_colour", _transfer_function->get_gradient_color());
    ((Ref<ShaderMaterial>)_histogram_texture_rect->get_material())->set_shader_parameter("tf_tex_alpha", _transfer_function->get_gradient_alpha());
    _histogram_texture_rect->set_texture(_transfer_function->get_histogram_texture());
    _palette_texture_rect->set_texture(_transfer_function->get_gradient_color());
}

///////////////////////

void EditorInspectorPluginTransferFunction::_bind_methods() {}

bool EditorInspectorPluginTransferFunction::_can_handle(Object *p_object) const {
    return p_object != nullptr && Object::cast_to<TransferFunction>(p_object) != nullptr;
}

void EditorInspectorPluginTransferFunction::_parse_begin(Object *p_object) {
    TransferFunction *tf = static_cast<TransferFunction *>(p_object);
    ERR_FAIL_NULL(tf);
    Ref<TransferFunction> tf_ref(tf);

    TransferFunctionEditor *editor = memnew(TransferFunctionEditor);
    editor->set_transfer_function(tf_ref);
    add_custom_control(editor);
}