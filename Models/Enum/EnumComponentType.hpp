#pragma once
#ifndef ENUM_COMPONENT_TYPE_HPP
#define ENUM_COMPONENT_TYPE_HPP

enum class ComponentType : int
{
	NONE = -1,
	MESH,
	INPUT,
	SCRIPT,
	TRANSFORM,
	CAMERA,
	LIGHT
};

#endif