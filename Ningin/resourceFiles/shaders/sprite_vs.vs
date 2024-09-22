layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model; // a matrix used to adjust the position, rotation, and scale of the object

// note that we're omitting the view matrix;
// the view never changes so we basically have an identity view matrix and can therefore omit it.

layout (std140) uniform Matrix
{
    mat4 projection;
};

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
