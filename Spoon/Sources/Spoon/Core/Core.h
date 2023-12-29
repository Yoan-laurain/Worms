#pragma once
#ifdef SN_BUILD_DLL
	#define SPOON_API __declspec(dllexport)
	#define OBJECT_API SPOON_API
#else
	#define SPOON_API __declspec(dllimport)
	#define OBJECT_API
#endif // SN_BUILD_DLL

using uint64 = unsigned __int64;
using uint32 = unsigned int;
using int32 = signed int;

struct FColor;

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define NONCOPYABLE(TypeName) \
	TypeName(TypeName&&) = delete; \
	TypeName(const TypeName&) = delete; \
	TypeName& operator=(const TypeName&) = delete; \
	TypeName& operator=(TypeName&&) = delete;

