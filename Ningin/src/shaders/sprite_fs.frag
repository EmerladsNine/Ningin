#version 330 core

in vec2 TexCoords; // Texture coordinates passed from the vertex shader
out vec4 FragColor; // Final color output of the fragment shader.

uniform sampler2D sprite;
uniform vec4 TintingColor; // Color used for tinting.
uniform bool useTint;

void main()
{
    vec4 textureColor = texture(sprite, TexCoords); // Samples the color from the texture.
    FragColor = useTint ? TintingColor * textureColor : textureColor;
}
