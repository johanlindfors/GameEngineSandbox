precision mediump float;

varying vec2 TexCoords;
uniform sampler2D screenTexture;

void main()
{
    // No postprocessing
    gl_FragColor = texture2D(screenTexture, TexCoords);

    // Invert colors
    //gl_FragColor = vec4(vec3(1.0 - texture2D(screenTexture, TexCoord)), 1.0);

    // Grayscale
    // gl_FragColor = texture2D(screenTexture, TexCoords);
    // float average = 0.2126 * gl_FragColor.r + 0.7152 * gl_FragColor.g + 0.0722 * gl_FragColor.b;
    // gl_FragColor = vec4(average, average, average, 1.0);
}