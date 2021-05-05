#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "TagComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "UUIDComponent.h"

namespace engine {
	typedef component::TagComponent			TagComponent;
	typedef component::UUIDComponent		UUIDComponent;
	typedef component::TransformComponent	TransformComponent;
	typedef component::MeshComponent		MeshComponent;
	typedef component::CameraComponent		CameraComponent;
}

#endif