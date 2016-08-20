#ifndef COLOR_H
#define COLOR_H

class Color
{
    public:
        Color();

    public:
        //Creates an RGB colour from HSV input.
        static Color HSVToRGB(float H, float S, float V);
        static Color HSVToRGB(float H, float S, float V, bool hdr);
        //Linearly interpolates between colors a and b by t.
        static Color lerp( Color a, Color b, float t );
        //Calculates the hue, saturation and value of an RGB input color.
        static void RGBToHSV(Color rgbColor, float* H, float* S, float* V);

    public:
        //Static: defines known colors

    public:
        int r;
        int g;
        int b;
        int a;
        float greyscale;

        //Can be methods
        Color* gamma;
        Color* linear;
        int maxColorComponent();

        //Allows to access color components using index [0, 1, 2, 3] as in RGBA
        int* data;
};

#endif // COLOR_H
