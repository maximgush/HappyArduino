#pragma once

#include "common.h"
#include "Utils\Array.h"

class Component;

class ComponentsContainer
{
public:
	static ComponentsContainer& Instance();

	void Init();
	void OnFrame();
	void AddComponent(Component* component);
	
	const CArray<Component*>& GetComponentsArray() const { return components; };
	short GetComponentsArraySize() const { return components.Size(); };
private:
	CArray<Component*> components;
	
	ComponentsContainer();
};


class Component
{
	char const* name;
public:
	Component(const char* _name);
	virtual const char * GetName();
	virtual void Init();
	virtual void OnFrame();
	
	struct KeyValue
	{
		String Key;
		String Value;
		
		KeyValue() : Key(""), Value("") {};
		KeyValue(String key, String value) : Key(key), Value(value){}
	};
	
	virtual void GetKeyValues(KeyValue *keyValues, short &size) { size = 0;};
};
