@tool

@icon("res://addons/volumetric_importer/icons/VolumeRenderedObject.svg")

class_name VolumeRenderedObject
extends MeshInstance3D
## A brief description of the class's role and functionality.
##
## The description of the script, what it can do,
## and any further detail.

enum RenderMode {
    MaximumIntensityProjection,
    DirectVolume,
    Isosurface
}

enum LightSource {
    ActiveCamera,
    SceneMainLight
}

var volume_material: ShaderMaterial

var noise_texture: NoiseTexture2D = NoiseTexture2D.new()

@export var dataset: VolumeDataset:
    get:
        return dataset
    set(value):
        dataset = value
        var data = dataset.get_data()
        volume_material.set_shader_parameter("volumeDataSampler", data)
        volume_material.set_shader_parameter("volumeGradientSampler", dataset.get_gradient())
        volume_material.set_shader_parameter("_TextureSize", Vector3i(data.get_width(), data.get_height(), data.get_depth())) # TODO: Check if this is still needed
        scale = dataset.get_scale()
        quaternion = dataset.get_rotation()
        
@export var transfer_function: TransferFunction:
    get:
        return transfer_function
    set(value):
        transfer_function = value
        volume_material.set_shader_parameter("transferfunctionSamplerColor", transfer_function.gradient_color)
        volume_material.set_shader_parameter("transferfunctionSamplerAlpha", transfer_function.gradient_alpha)
        volume_material.set_shader_parameter("useTransferFunction2D", false)
        

@export var render_mode: RenderMode = RenderMode.MaximumIntensityProjection:
    get:
        return render_mode
    set(value):
        render_mode = value
        volume_material.set_shader_parameter("MODE", render_mode)


@export_custom(PROPERTY_HINT_RANGE, "0.0,1.0") var visibility_window: Vector2 = Vector2(0.001, 1.0):
    get:
        return visibility_window
    set(value):
        visibility_window = Vector2(clamp(value.x, 0.0, value.y), clamp(value.y, value.x, 1.0))
        volume_material.set_shader_parameter("_MinVal", visibility_window.x)
        volume_material.set_shader_parameter("_MaxVal", visibility_window.y)

@export_custom(PROPERTY_HINT_RANGE, "0.0,1.0") var gradient_lighting_threshold: Vector2 = Vector2(0.02, 0.15):
    get:
        return gradient_lighting_threshold
    set(value):
        gradient_lighting_threshold = Vector2(clamp(value.x, 0.0, value.y), clamp(value.y, value.x, 1.0))
        volume_material.set_shader_parameter("_LightingGradientThresholdStart", gradient_lighting_threshold.x)
        volume_material.set_shader_parameter("_LightingGradientThresholdEnd", gradient_lighting_threshold.y)

@export_range(0.0, 1.0) var min_gradient: float = 0.01:
    get:
        return min_gradient
    set(value):
        min_gradient = value
        volume_material.set_shader_parameter("_MinGradient", min_gradient)

@export var ray_termination: bool = false:
    get:
        return ray_termination
    set(value):
        ray_termination = value
        volume_material.set_shader_parameter("earlyRayTermination", ray_termination)

@export var cubic_interpolation: bool = false:
    get:
        return cubic_interpolation
    set(value):
        cubic_interpolation = value
        volume_material.set_shader_parameter("cubicInterpolation", cubic_interpolation)

@export var lighting_enabled: bool = false:
    get:
        return lighting_enabled
    set(value):
        lighting_enabled = value
        volume_material.set_shader_parameter("useLighting", lighting_enabled)

@export var light_source: LightSource = LightSource.ActiveCamera:
    get:
        return light_source
    set(value):
        light_source = value
        volume_material.set_shader_parameter("useMainLight", light_source==1)

# Called when the node enters the scene tree for the first time.
func _ready():
    noise_texture.height = 512
    noise_texture.width = 512
    noise_texture.noise = FastNoiseLite.new()
    mesh = BoxMesh.new()
    mesh.flip_faces = true
    volume_material = ResourceLoader.load("res://addons/volumetric_importer/materials/raymarch_material.tres").duplicate() as Material
    transfer_function = ResourceLoader.load("res://addons/volumetric_importer/materials/default_tf.tres").duplicate() as TransferFunction
    volume_material.set_shader_parameter("noiseSampler", noise_texture)
    volume_material.set_shader_parameter("MODE", render_mode)
    volume_material.set_shader_parameter("_MinVal", visibility_window.x)
    volume_material.set_shader_parameter("_MaxVal", visibility_window.y)
    volume_material.set_shader_parameter("_LightingGradientThresholdStart", gradient_lighting_threshold.x)
    volume_material.set_shader_parameter("_LightingGradientThresholdEnd", gradient_lighting_threshold.y)
    volume_material.set_shader_parameter("_MinGradient", min_gradient)
    volume_material.set_shader_parameter("earlyRayTermination", ray_termination)
    volume_material.set_shader_parameter("cubicInterpolation", cubic_interpolation)
    volume_material.set_shader_parameter("useLighting", lighting_enabled)
    volume_material.set_shader_parameter("useMainLight", light_source==1)
    mesh.surface_set_material(0, volume_material)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float):
    pass
