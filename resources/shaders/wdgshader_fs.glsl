#version 460 core

struct LightInfo {
    vec4 color;           // Base color of light
    vec4 position;        // w=1 for point, w=0 for directional
    vec4 diffuse;         // Diffuse intensity
    vec4 specular;        // Specular intensity
    vec4 ambient;         // Ambient intensity
    vec3 attenuation;     // x = constant, y = linear, z = quadratic
    bool is_spot;         // Spotlight flag
    vec3 direction;       // Spotlight direction (normalized)
    float cutoff;         // Cosine of cutoff angle
    float exponent;       // Spotlight exponent
};

const int MAX_LIGHTS = 8;
const vec3 GLOBAL_AMBIENT = vec3(0.1, 0.1, 0.1);

layout(location = 0) in vec3 frag_position;
layout(location = 1) in vec3 frag_normal;
layout(location = 2) in vec2 vTextCoord;

uniform vec4 color;
uniform int nlights;
uniform LightInfo lights[MAX_LIGHTS];
uniform int hasTexture;
uniform sampler2D ourTexture;
uniform vec3 camPos; // Needed for specular

layout(location = 0) out vec4 frag_color;

vec3 compute_light_intensity(LightInfo light, vec3 frag_pos, vec3 frag_normal)
{
    vec3 frag2light;
    float att = 1.0;

    // Determine light direction
    if (light.position.w == 0.0) {
        // Directional light
        frag2light = normalize(light.position.xyz);
    } else {
        // Point light
        vec3 light_position = light.position.xyz / light.position.w;
        frag2light = normalize(light_position - frag_pos);
        float dist = length(light_position - frag_pos);
        att = 1.0 / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist);
    }

    // Diffuse
    float diff = max(dot(frag_normal, frag2light), 0.0);
    vec3 diffuse = diff * light.diffuse.rgb;

    // Specular (Phong)
    vec3 viewDir = normalize(camPos - frag_pos);
    vec3 reflectDir = reflect(-frag2light, frag_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Consider making shininess a uniform
    vec3 specular = spec * light.specular.rgb;

    // Ambient
    vec3 ambient = light.ambient.rgb;

    vec3 intensity = att * (ambient + diffuse + specular);

    // Spotlight
    if (light.is_spot) {
        float spotFactor = max(dot(-frag2light, normalize(light.direction)), 0.0);
        if (spotFactor > light.cutoff) {
            spotFactor = pow(spotFactor, light.exponent);
            intensity *= spotFactor;
        } else {
            intensity = vec3(0.0);
        }
    }

    return intensity;
}

void main()
{
    vec3 normal = normalize(frag_normal);
    vec3 frag_light = vec3(0.0);

    for (int i = 0; i < nlights; i++) {
        frag_light += compute_light_intensity(lights[i], frag_position, normal);
    }

    frag_light += GLOBAL_AMBIENT;
    // Apply color and optional texture
    if (hasTexture == 1) {
        frag_color = vec4(clamp(color.rgb * texture(ourTexture, vTextCoord).rgb * frag_light, 0.0, 1.0), color.a);
    } else {
       frag_color = vec4(clamp(color.rgb * frag_light, 0.0, 1.0), color.a);
        
    }
}