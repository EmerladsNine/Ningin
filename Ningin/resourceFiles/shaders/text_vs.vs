layout (location = 0) in vec2 vertex; // <vec2 pos>

out VS_OUT {
    vec2 TexCoords;
    flat int index;
}data;

layout (std140) uniform Matrix
{
    mat4 projection;
};

// uniform mat4 Transforms[MAX_MATRICES];

uniform vec2 lettersPositions[MAX_MATRICES];
uniform mat4 baseModel;
uniform float scale;

void main()
{
    vec3 translation = vec3(lettersPositions[gl_InstanceID], 0.0); // Move by (x, y, 0)
    mat4 translationMatrix = mat4(1.0); // Start with an identity matrix
    translationMatrix[3] = vec4(translation, 1.0); // Set translation in the last column

    mat4 scalingMatrix = mat4(1.0); 
    scalingMatrix[0][0] = scale;
    scalingMatrix[1][1] = scale;
    scalingMatrix[2][2] = 1.0;

    mat4 letterModel =  baseModel * translationMatrix * scalingMatrix;

    gl_Position = projection * letterModel * vec4(vertex.xy, 0.0, 1.0);
    data.index = gl_InstanceID;
    data.TexCoords = vertex.xy;
}
