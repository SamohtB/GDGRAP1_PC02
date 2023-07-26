#version 330 core 

out vec4 FragColor; //pixel color

uniform sampler2D tex0;

uniform vec3 pointLightPos;
uniform vec3 pointLightColor;
uniform vec3 pointAmbientColor;
uniform float pointAmbientStr;
uniform float pointSpecStr;
uniform float pointSpecPhong;
uniform float pointIntensity;

uniform vec3 direction;
uniform vec3 dirLightColor;
uniform vec3 dirAmbientColor;
uniform float dirAmbientStr;
uniform float dirSpecStr;
uniform float dirSpecPhong;
uniform float dirIntensity;

uniform vec3 cameraPos;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

void main()
{
	//Calculate Point Light
	vec3 pointNormal = normalize(normCoord);
	vec3 pointLightDir = normalize(pointLightPos - fragPos);
	
	float pointDiff = max(dot(pointNormal, pointLightDir), 0.0);
	vec3 pointDiffuse = pointDiff * pointLightColor;

	vec3 pointAmbientCol = pointAmbientColor * pointAmbientStr;

	vec3 pointViewDir = normalize(cameraPos - fragPos);
	vec3 pointReflectDir = reflect(-pointLightDir, pointNormal);

	float pointSpec = pow(max(dot(pointReflectDir, pointViewDir), 0.1), pointSpecPhong);
	vec3 pointSpecColor = pointSpec * pointSpecStr * pointLightColor;

	float pointDistance = distance(pointLightPos, fragPos);
	float pointIntensity = pointIntensity * (1.0 / (pointDistance * pointDistance));

	vec3 pointLightResult = vec3(pointSpecColor + pointDiffuse + pointAmbientCol) * pointIntensity;

	//Calculate Directional Light
	vec3 dirNormal = normalize(normCoord);
	vec3 dirLightDir = direction;
	
	float dirDiff = max(dot(dirNormal, dirLightDir), 0.0);
	vec3 dirDiffuse = dirDiff * dirLightColor;

	vec3 dirAmbientCol = dirAmbientColor * dirAmbientStr;

	vec3 dirViewDir = normalize(cameraPos - fragPos);
	vec3 dirReflectDir = reflect(-dirLightDir, dirNormal);

	float dirSpec = pow(max(dot(dirReflectDir, dirViewDir), 0.1), dirSpecPhong);
	vec3 dirSpecColor = dirSpec * dirSpecStr * dirLightColor;

	float dirIntensity = dirIntensity;

	vec3 directionalLightResult = vec3(dirSpecColor + dirDiffuse + dirAmbientCol) * dirIntensity;

	FragColor = vec4(pointLightResult + directionalLightResult, 1.0) * texture(tex0, texCoord);
}