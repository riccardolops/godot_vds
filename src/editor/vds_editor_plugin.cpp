#include "vds_editor_plugin.h"
#include "volumedataset.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/file_access.hpp>

using namespace godot;

enum DataFormat
{
    Uint8,
    Int8,
    Uint16,
    Int16,
    Uint32,
    Int32
};

enum Endianness
{
    LittleEndian,
    BigEndian
};

void VDSImportPlugin::_bind_methods() {}

String VDSImportPlugin::_get_importer_name() const { return "volumetric_importer.raw"; }
String VDSImportPlugin::_get_visible_name() const { return "raw dataset"; }
PackedStringArray VDSImportPlugin::_get_recognized_extensions() const
{
    PackedStringArray extensions = PackedStringArray();
    extensions.append("raw");
    return extensions;
}
String VDSImportPlugin::_get_save_extension() const { return "res"; }
String VDSImportPlugin::_get_resource_type() const { return "VolumeDataset"; }
int VDSImportPlugin::_get_preset_count() const { return 1; }
String VDSImportPlugin::_get_preset_name(int preset_index) const { return "Default"; }
TypedArray<Dictionary> VDSImportPlugin::_get_import_options(const String &path, int p_idx) const
{
    TypedArray<Dictionary> options = TypedArray<Dictionary>();
    Dictionary option = Dictionary();
    option["name"] = "Dim x";
    option["default_value"] = 128;
    options.push_back(option);
    option["name"] = "Dim y";
    option["default_value"] = 256;
    options.push_back(option);
    option["name"] = "Dim z";
    option["default_value"] = 256;
    options.push_back(option);
    option["name"] = "Bytes to skip";
    option["default_value"] = 0;
    options.push_back(option);
    option["name"] = "Data format";
    option["default_value"] = DataFormat::Uint8;
    option["property_hint"] = PROPERTY_HINT_ENUM;
    option["property_hint_string"] = "Uint8,Int8,Uint16,Int16,Uint32,Int32";
    options.push_back(option);
    option["name"] = "Endianness";
    option["default_value"] = Endianness::LittleEndian;
    option["property_hint"] = PROPERTY_HINT_ENUM;
    option["property_hint_string"] = "LittleEndian,BigEndian";
    options.push_back(option);

    return options;
}

bool VDSImportPlugin::_get_option_visibility(const String &p_path, const StringName &p_option_name, const Dictionary &p_options) const
{
    return true;
}

Error VDSImportPlugin::_import(const String &source_file, const String &save_path, const Dictionary &options, const TypedArray<String> &platform_variants, const TypedArray<String> &gen_files) const
{
    Ref<FileAccess> file = FileAccess::open(source_file, FileAccess::READ);
    if (!file.is_valid())
    {
        return ERR_FILE_CANT_OPEN;
    }
    file->set_big_endian(options["Endianness"]);

    int dim_x = options["Dim x"];
    int dim_y = options["Dim y"];
    int dim_z = options["Dim z"];
    int bytes_to_skip = options["Bytes to skip"];

    int expected_size = dim_x * dim_y * dim_z * sizeof(uint8_t) + bytes_to_skip; // TODO: handle other data formats
    if (file->get_length() < expected_size)
    {
        return ERR_FILE_CORRUPT;
    }

    if (bytes_to_skip > 0)
    {
        file->seek(bytes_to_skip);
    }
    return OK;
}

void VDSEditorPlugin::_bind_methods() {}

void VDSEditorPlugin::_enter_tree()
{
    import_plugin.instantiate();
    add_import_plugin(import_plugin);
}

void VDSEditorPlugin::_exit_tree()
{
    remove_import_plugin(import_plugin);
    import_plugin.unref();
}