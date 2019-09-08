#pragma once

class Component;

class ComponentsContainer
{
public:
	static ComponentsContainer& Instance();

	void Init();
	void OnFrame();
	void AddComponent(Component* component);
	
private:
	short size;
	Component* components[25];
};

class Component
{
	char const* name;
public:
	Component(const char* _name);
	virtual const char * GetName();
	virtual void Init();
	virtual void OnFrame();
	virtual String GetStatusHTML();
};