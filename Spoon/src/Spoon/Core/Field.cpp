#include "Field.h"
#include <snpch.h>

class Field;

class FieldClass
{
	NONCOPYABLE(FieldClass)

	std::string Name;
	uint64 Id;
	FieldClass* SuperClass;
	Field* DefaultObject;

public:

	FieldClass() {};

	std::string GetName() const { return Name; }

	uint64 GetId() const { return Id; }

	FieldClass* GetSuperClass() const { return SuperClass; }

	Field* GetDefaultObject() const { return DefaultObject; }

};