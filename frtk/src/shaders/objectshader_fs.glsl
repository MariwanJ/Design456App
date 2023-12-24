
#version 460 core

struct LightInfo {
    vec4 color;
    vec4 position;         //
    vec4 diffuse;          //
    vec4 specular;         //
    vec4 ambient;          //Light intensity
    vec3 attenuation;      //
    bool is_spot;          //
    vec3 direction;        //
    float cutoff;          //
    float exponent;        //
};

const int MAX_LIGHTS = 8;  //only 8 lights are allowed as a node in the application,change it if you need more
const int NUM_COLORS = 2; //check this value
const vec3 GLOBAL_AMBIENT = vec3(0.1, 0.1, 0.1);

layout (location=0) in vec3 frag_position;
layout (location=1) in vec3 frag_normal;
layout (location=2) in vec3 frag_sm_position;
layout (location=3) in vec2 vTextCoord;

uniform vec4 color;
uniform int nlights;
uniform LightInfo lights[MAX_LIGHTS];
uniform int sm_light;

uniform sampler2D ourTexture;
uniform int hasTexture;


layout (location=0) out vec4 frag_color;


vec3 compute_light_intensity(LightInfo light, int id, vec3 frag_normal_)
{
    vec3 light_position = light.position.xyz/ light.position.w;
    float dist = length(light_position - frag_position);
    float att = 1 / (light.attenuation.x + light.attenuation.y * dist  + light.attenuation.y * dist * dist);

    vec3 frag2light = normalize(light_position - frag_position);
    float diff = max(dot(frag_normal_, frag2light), 0);
    vec3 intensity = att * vec3(light.ambient + diff * light.diffuse +light.specular);

    if (light.is_spot) {
        float kspot = max(dot(-frag2light, light.direction), 0);
        if (kspot > light.cutoff) {
            kspot = pow(kspot, light.exponent);
            return kspot * intensity;
        }
        return vec3(0, 0, 0);
    }
	
    return (intensity);
}

void main ()
{
	int textureActive=hasTexture;
    vec3 frag_normal_n = normalize(frag_normal);
    vec3 frag_light = vec3(0, 0, 0);
    for (int i = 0; i < nlights; i++) {
        frag_light += compute_light_intensity(lights[i], i, frag_normal_n);
    }
    frag_light += GLOBAL_AMBIENT;
	frag_light = (frag_light * NUM_COLORS) / NUM_COLORS; //floor make it worse

	// Use sampling form texture if we use texture otherwise we use the original color calculation	
	if (textureActive==1){
		frag_color=vec4((color * texture2D(ourTexture,vTextCoord)).rgb, 1.0);
		}
	else{
		frag_color =  vec4(color.rgb * frag_light, color.a);
	//frag_color = vec4(color.rgb * frag_light*frag_normal, color.a);//TEST THIS
	}
 
}