@tool
extends EditorImportPlugin

func _get_importer_name():
    return "volumetric_importer.sitk"

func _get_visible_name():
    return "VolumeDataset"

func _get_recognized_extensions():
    return ["nrrd", "nii.gz", "nii", "hdr", "img", "dcm", "dicom"]

func _get_save_extension():
    return "res"

func _get_resource_type():
    return "VolumeDataset"

func _get_preset_count():
    return 1

func _get_import_order():
    return 0

func _get_option_visibility(path, option, options):
    return true

func _get_preset_name(preset_index):
    return "Default"

func _get_import_options(path, preset_index):
    return [{"name": "my_option", "default_value": false}]

func _get_priority():
    return 1

func _import(source_file, save_path, options, platform_variants, gen_files):
    var loader_script = load("res://addons/sitkvolumetricimporter/SITKImporter.cs")
    
    var sitk_importer = loader_script.new()
    sitk_importer.load(ProjectSettings.globalize_path(source_file))
    var dataset := sitk_importer.getByteArray() as PackedFloat32Array
    var arr_dataset = Array(dataset)
    var minValue = arr_dataset.min()
    print(minValue)
    var maxValue = arr_dataset.max()
    print(maxValue)
    var range = maxValue - minValue;
    var n_frequencies = min(range, 1024)
    var frequencies = Array()
    frequencies.resize(n_frequencies)
    frequencies.fill(0)

    var dimensions := sitk_importer.getDimensions() as Vector3i
    print(dimensions)
    var spacing := sitk_importer.getSpacing() as Vector3

    var images_array := Array([], TYPE_OBJECT, "Image", null) as Array[Image]
    var gradient_array := Array([], TYPE_OBJECT, "Image", null) as Array[Image]
    
    var maxFrequency = 0
    for z in range(dimensions.z):
        var slice := Image.create_empty(dimensions.x, dimensions.y, false, Image.FORMAT_RF) as Image
        var gradient := Image.create_empty(dimensions.x, dimensions.y, false, Image.FORMAT_RGBAF) as Image
        for y in range(dimensions.y):
            for x in range(dimensions.x):
                var index = x + y * dimensions.x + z * dimensions.x * dimensions.y
                var value := dataset.get(index) as float
                var frequency_index := ((value - minValue) / range) * (n_frequencies - 1) as int
                frequencies[frequency_index] = frequencies[frequency_index] + 1
                maxFrequency = max(maxFrequency, frequencies[frequency_index])
                slice.set_pixel(x, y, Color((value - minValue) / range, 0, 0, 0))
                var x1 = (dataset.get(min(x + 1, dimensions.x - 1) + y * dimensions.x + z * dimensions.x * dimensions.y)) - minValue
                var x2 = (dataset.get(max(x - 1, 0) + y * dimensions.x + z * dimensions.x * dimensions.y)) - minValue
                var y1 = (dataset.get(x + min(y + 1, dimensions.y - 1) * dimensions.x + z * dimensions.x * dimensions.y)) - minValue
                var y2 = (dataset.get(x + max(y - 1, 0) * dimensions.x + z * dimensions.x * dimensions.y)) - minValue
                var z1 = (dataset.get(x + y * dimensions.x + min(z + 1, dimensions.z - 1) * dimensions.x * dimensions.y)) - minValue
                var z2 = (dataset.get(x + y * dimensions.x + max(z - 1, 0) * dimensions.x * dimensions.y)) - minValue
                gradient.set_pixel(x, y, Color((x2 - x1) / range, (y2 - y1) / range, (z2 - z1) / range, (value - minValue) / range))
        images_array.append(slice)
        gradient_array.append(gradient)
    
    var histogram_byteArray := PackedFloat32Array() as PackedFloat32Array
    for i in range(n_frequencies):
        histogram_byteArray.append((log(frequencies[i]) / log(10)) / (log(maxFrequency) / log(10)))        
    
    var volume_texture := ImageTexture3D.new() as ImageTexture3D
    var gradient_texture := ImageTexture3D.new() as ImageTexture3D
    volume_texture.create(Image.FORMAT_RF, dimensions.x, dimensions.y, dimensions.z, false, images_array)
    gradient_texture.create(Image.FORMAT_RGBAF, dimensions.x, dimensions.y, dimensions.z, false, gradient_array)
    var volume = VolumeDataset.new()
    volume.scale = Vector3(-(spacing.x * dimensions.x / 1000), (spacing.y * dimensions.y / 1000), -(spacing.z * dimensions.z / 1000))
    volume.rotation = Quaternion.from_euler(Vector3(deg_to_rad(90), 0, 0))
    volume.histogram = ImageTexture.create_from_image(Image.create_from_data(n_frequencies, 1, false, Image.FORMAT_RF, histogram_byteArray.to_byte_array()))
    volume.volume = volume_texture
    volume.gradient = gradient_texture

    var filename = save_path + "." + _get_save_extension()
    return ResourceSaver.save(volume, filename)
