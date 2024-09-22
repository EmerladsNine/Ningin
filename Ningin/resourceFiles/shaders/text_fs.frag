out vec4 color;

in VS_OUT {
    vec2 TexCoords;
    flat int index;
}data_in;

uniform sampler2DArray text;
uniform int charsMap[MAX_MATRICES];
uniform vec4 TextColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, vec3(data_in.TexCoords.xy, charsMap[data_in.index])).r);
    color = TextColor * sampled;
}