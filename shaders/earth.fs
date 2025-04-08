#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D sphereTexture;
uniform sampler2D cloudTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    // ambient
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.4;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = ambient + diffuse + specular;

    // textures
    vec3 baseColor = texture(sphereTexture, TexCoord).rgb;
    vec4 cloudColor = texture(cloudTexture, TexCoord);
    
    vec3 finalColor = mix(baseColor, cloudColor.rgb, cloudColor.r);


    FragColor = vec4(finalColor * lighting, 1.0);
}
