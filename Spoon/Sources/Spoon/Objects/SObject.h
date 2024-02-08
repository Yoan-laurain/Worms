#pragma once

#include "Core/Core.h"

#include <string>
#include <typeinfo>

class Widget;

class IReflecatble
{
public:
	virtual std::string GetClassName() const = 0;

	virtual size_t GetClassId() const = 0;
};

// To be honest C'est chat GPT qui là fait
// Je voulais pouvoir avoir la classe dans le quel il est crée pour que si je le stock dans une var du type parent
// Je puisse get la class child
#define GENERATE() \
	public: \
    virtual std::string GetClassName() const { \
        std::string mangledName = typeid(*this).name(); \
        size_t start = mangledName.find("class "); \
        if (start != std::string::npos) { \
            start += 6; \
            return mangledName.substr(start); \
        } \
        return mangledName; \
    } \
	virtual size_t GetClassId() const { return typeid(*this).hash_code(); }

// Object base. 
class SPOON_API SObject : public IReflecatble
{
	GENERATE()

public:
	
	SObject();

	virtual ~SObject();

	template <typename T = SObject>
	bool IsA() const
	{
		return static_cast<T>(this) != nullptr;
	}

	uint64 GetUniqueId() const { return UniqueId; }

private:

	uint64 UniqueId;

};