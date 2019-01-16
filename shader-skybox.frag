#version 330 core
// This is a sample fragment shader.

//Original
struct Light{
    int light_mode;
    vec3 light_color;
    vec3 light_pos;
    vec3 light_dir;
    float cons_att;
    float linear_att;
    float quad_att;
    float cutoff_angle;
    float exponent;
};

struct Material{
    int object_mode;
    vec3 color_diff;
    vec3 color_spec;
    vec3 color_ambi;
};

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
//in float sampleExtraOutput;
in vec3 TexCoords;

//uniform vec3 viewPos;
//uniform Light light;
//uniform Material material;
//uniform int rendermode;
uniform samplerCube skybox;
// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;
vec3 doLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main()
{
    color = texture(skybox, TexCoords);
}

