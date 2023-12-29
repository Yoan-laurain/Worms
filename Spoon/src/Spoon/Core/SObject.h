#pragma once
#include "Core.h"
#include <string>
#include <typeinfo>

class IReflecatble
{
public:
	virtual std::string GetClassName() const = 0;

	virtual size_t GetClassId() const = 0;
};

// To be honest C'est chat GPT qui là fait
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

	unsigned long long GetUniqueId() const { return UniqueId; }

private:

	unsigned long long UniqueId;

};

