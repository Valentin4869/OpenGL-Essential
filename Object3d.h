#pragma once

enum VertexFormat {XY, XYZ, XYZ_XYZ_XY, XYZ_XY, XYZ_XYZ, XY_RGB, XYZ_RGB, XY_RGBA, XYZ_RGBA};

class Object3d{

public:
	glm::mat4 transform;
	VertexFormat vert_format;
	GLenum draw_mode;


};