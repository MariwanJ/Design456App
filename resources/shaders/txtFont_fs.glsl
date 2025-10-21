#version 460 core


in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 textColor;


void main() {
    float d = texture(image, TexCoords).r;
    float aaf= fwidth(d);
    float alpha = smoothstep(0.15-aaf, 0.15+aaf,d);
    FragColor = vec4(textColor, alpha);

}