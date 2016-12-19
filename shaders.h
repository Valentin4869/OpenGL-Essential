#pragma once


const GLchar* vertexSource =
    "#version 330 core\n"

    "in vec3 position;"
	"in vec3 color;"
	"in vec3 normal;"
	"in vec2 texCoord;"

	"uniform mat4 proj;"
	"uniform mat4 model;"
	"uniform mat4 view;"
	"uniform mat4 inv;"
	
	"out vec3 Normal;"
	"out vec3 FragPos;"
	"out vec3 vertex_color;"
	"out vec2 TexCoord;"

    "void main() {"
	
    "gl_Position = proj*view*model*vec4(position, 1.0);"
	"FragPos = vec3(model* vec4(position, 1.0f));"
	"Normal= mat3(transpose(inverse(model))) * normal;"
	"vertex_color=color;"
	"TexCoord= vec2(texCoord.x,-texCoord.y);"
    "}";

const GLchar* fragmentSource =
    "#version 330 core\n"
	"uniform vec3 Color;" //object color
	"uniform vec3 lightpos; "
	"uniform vec3 camerapos;"
	"uniform vec3 obj_pos;"
	"uniform bool lighting; " //lighting off/on
	"uniform bool color_from_vert;" //use vertex color, 1; use Color, 1
	"uniform bool tex;" //texture off/on
	"uniform bool particles;" //texture off/on
	"uniform sampler2D Texture;"

	"in vec2 TexCoord;"
	"in vec3 FragPos;"
	"in vec3 Normal;"
	"in vec3 vertex_color;"
	
    "out vec4 outColor;"
	
    "void main() {"

	"vec3 result;"
	"vec3 frag_color;"

		//color source
		"if (color_from_vert)" //from vertex color
		"{frag_color=vertex_color;}"
		"else if(tex)"
		"{frag_color=vec3(texture(Texture, TexCoord));}"
		"else"
		"{frag_color=Color;}"			//else, get color from object color variable

		//Other properties
		"if(lighting){"	//apply lighting?

  			"float ambientStrength = 0.3f;"
			"vec3 ambient = ambientStrength * frag_color;"

			"vec3 norm = normalize(Normal);"
			"vec3 lightDir = normalize(lightpos - FragPos);"
			"float diff = max(dot(norm, lightDir), 0.0f)*1.7 ;"
			"vec3 diffuse = diff * frag_color;"

			"float specularStrength = 0.7f;"
			"vec3 viewDir = normalize(camerapos - FragPos);"
			"vec3 reflectDir = reflect(-lightDir, norm);  "
			"float spec = pow(max(dot(viewDir, reflectDir), 0.0), 50)*diff;"
			//"float spec = sin(distance(FragPos,lightpos))*diff/1.f;"
	
  			"vec3 specular = specularStrength * spec* frag_color;  "
	
			" result = (ambient+ diffuse+specular) * frag_color;"
			"}"
			"else if (particles)"
			"{outColor=  vec4( pow(cos(distance(FragPos, obj_pos)), 0.7) )  ;}"
		"else"
		"{result=frag_color;}" //use solid color

		"if (!particles)"
"outColor=vec4(result,1.0f);"

	
    "}";

const GLchar* lightFragmentSource =
    "#version 330 core\n"
    "in vec3 vertex_color;"
	"uniform vec3 Color;"
	"uniform bool color_from_vert;"
	"out vec4 outColor;"
	
    "void main() {"
	"if(color_from_vert==true)"
	"outColor = vec4(vertex_color, 1.0f);"
	"else"
	"{outColor = vec4(Color, 1.0f);}"
    "}";

const GLchar* particleFragment =
    "#version 330 core\n"
	"uniform vec3 Color;"
	"out vec4 outColor;"
	
    "void main() {"
	

	"outColor = vec4(1.0f);"
    "}";
