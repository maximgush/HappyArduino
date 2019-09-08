#pragma once

#include "Component.h"

ComponentsContainer& ComponentsContainer::Instance()
{
	static ComponentsContainer instance;
	return instance;
}

void ComponentsContainer::Init()
{
	for (short i = 0; i < size; i++)
		components[i]->Init();
};

void ComponentsContainer::OnFrame()
{
	for (short i = 0; i < size; i++)
		components[i]->OnFrame();
};

void ComponentsContainer::AddComponent(Component* component)
{
	size++;
	components[size] = component;
}

Component::Component(const char* _name)
	: name(_name)
{
	ComponentsContainer::Instance().AddComponent(this);
}

const char * Component::GetName()
{
	return name;
};

void Component::Init()
{
}
void Component::OnFrame()
{
};
String Component::GetStatusHTML()
{
};