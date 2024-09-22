#version 330 core
layout (location = 0) in vec2 vertex; // <vec2 pos>

out VS_OUT {
    vec2 TexCoords;
    flat int index;
}data;

layout (std140) uniform Matrix
{
    mat4 projection;
};

// uniform mat4 Transforms[100];

uniform vec2 LetterPositions[100];
uniform mat4 baseModel;
uniform floar scale;

void main()
{
    mat4 letterModel = baseModel;

    // do operations 

    gl_Position = projection  * letterModel * vec4(vertex.xy, 0.0, 1.0);
    data.index = gl_InstanceID;
    data.TexCoords = vertex.xy;
}