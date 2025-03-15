using System;
using System.Runtime.InteropServices;
using Godot;

using itk.simple;

namespace VolumetricRendering;

public partial class SITKImporter : Node
{
    private itk.simple.Image image;

    public void load(string path)
    {
        ImageFileReader reader = new();
        reader.SetImageIO("NrrdImageIO");
        reader.SetFileName(path);
        image = reader.Execute();
        image = SimpleITK.DICOMOrient(image, "LPS");
        image = SimpleITK.Cast(image, PixelIDValueEnum.sitkFloat32);
    }

    public Vector3I getDimensions()
    {
        VectorUInt32 size = image.GetSize();
        return new Vector3I((int)size[0], (int)size[1], (int)size[2]);
    }

    public float[] getByteArray()
    {
        VectorUInt32 size = image.GetSize();
        int length = (int)size[0] * (int)size[1] * (int)size[2];
        IntPtr imgBuffer = image.GetBufferAsFloat();
        float[] buffer = new float[length];
        Marshal.Copy(imgBuffer, buffer, 0, length);
        return buffer;
    }

    public Vector3 getSpacing()
    {
        VectorDouble spacing = image.GetSpacing();
        return new Vector3((float)spacing[0], (float)spacing[1], (float)spacing[2]);
    }
}