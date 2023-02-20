#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
// Gets the color of the lights from the main function
uniform vec4 keyLightColor;
uniform vec4 fillLightColor;
// Gets the position of the lights from the main function
uniform vec3 keyLightPos;
uniform vec3 fillLightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
	// ambient light
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 keyLightDirection = normalize(keyLightPos - crntPos);
	vec3 fillLightDirection = normalize(fillLightPos - crntPos);
	float keyDiffuse = max(dot(normal, keyLightDirection), 0.0f);
	float fillDiffuse = max(dot(normal, fillLightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-keyLightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// outputs final color
	FragColor = texture(tex0, texCoord) * (keyLightColor * (keyDiffuse + ambient + specular)) + (fillLightColor * (fillDiffuse + ambient + specular));
}