#pragma once

#include "Component.h"

class RTCComponent : public Component
{
public:
	RTCComponent(const char* _name) : Component(_name) {}
	virtual void OnFrame() {};
};