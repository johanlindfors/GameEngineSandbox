#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D screenTexture;

void main()
{
    // No postprocessing
    FragColor = texture(screenTexture, TexCoords);

    // Invert colors
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    // Grayscale
    // FragColor = texture(screenTexture, TexCoords);
    // float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    // FragColor = vec4(average, average, average, 1.0);
}