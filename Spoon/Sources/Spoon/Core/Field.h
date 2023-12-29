#pragma once
#include "Core.h"

class Field;

class FieldClass
{
	NONCOPYABLE(FieldClass)

	std::string Name;
	uint64 Id;
	FieldClass* SuperClass;
	Field* DefaultObject;

public:

	// Creat le constructeur avec tous les arguments par défaut

	FieldClass(std::string _name, uint64 _id, FieldClass* _superClass, Field* _defaultObject) : Name(_name), Id(_id), SuperClass(_superClass), DefaultObject(_defaultObject) {}

	std::string GetName() const { return Name; }

	uint64 GetId() const { return Id; }

	FieldClass* GetSuperClass() const { return SuperClass; }

	Field* GetDefaultObject() const { return DefaultObject; }

};