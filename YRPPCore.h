#pragma once

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

// the most basic globals
#include <Fundamentals.h>

//Syringe interaction header - also includes <windows.h>
#include <Syringe.h>

//Assembly macros
#include <ASMMacros.h>

#include <Memory.h>

#include <wchar.h>
#include <cstdio>

//Avoid default CTOR trick
#define DECLARE_PROPERTY(type,name)\
union{\
	type name; \
	char __##name[sizeof(type)]; \
}

#define DECLARE_PROPERTY_ARRAY(type,name,cnt)\
union{\
	type name[cnt]; \
	char __##name[sizeof(type) * cnt]; \
}

//Not gettable/settable members
#define PROTECTED_PROPERTY(type,name)\
	protected:\
		type name; \
	public:

#define PRIVATE_PROPERTY(type,name)\
	private:\
		type name; \
	public:
/*
Operation: The Cleansing

These two replace a function's implementation.

R0 is used for functions which return a numeric value or a pointer.
RX is for functions without a return type.
Functions that return struct instances will have to be written manually.

I chose short names to keep things clean.

Example usage:
virtual int foo(int bar) R0;
virtual void alla(double malla) RX;
*/

#define R0 {return 0;}
#define RX {}
#define RT(type) {return type();}

#define NOVTABLE __declspec(novtable)
#define NOINLINE __declspec(noinline)
#define UNUSED __pragma(warning(suppress : 4100 4101))
#define NORETURN __declspec(noreturn)
#define NOTHROW __declspec(nothrow)
#define SELECTANY __declspec(selectany)
#define NAKED __declspec(naked)
#define ALIGN(val) __declspec(align(val))

#define SIZE_OF(typ, id) sizeof(((typ *)0)->id)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define elif else if
#define SAFE_RELEASE(ptr) {if(ptr) delete[] ptr;}

#define __has_builtin(x) 0
#define __has_attribute(x) 0

#define STRINGIZE_HELPER(str) #str
#define STRINGIZE(str) STRINGIZE_HELPER(str)
#define STRINGIZE_JOIN(str1, str2) STRINGIZE_HELPER(str1 ## str2)

#define MakeString(M, L) M(L)
#define $Line MakeString(STRINGIZE, __LINE__)
#define Reminder __FILE__ "(" $Line ") : Reminder: "
#define STRING2(x) #x
#define STRING(x) STRING2(x)

#define WRITE_LE_UINT16(p, value) ((p)[0] = ((value) & 0xFF), (p)[1] = (((value) >> 8) & 0xFF))
#define WRITE_LE_UINT32(p, value) ((p)[0] = ((value) & 0xFF), (p)[1] = (((value) >> 8) & 0xFF), (p)[2] = (((value) >> 16) & 0xFF), (p)[3] = (((value) >> 24) & 0xFF))
#define READ_LE_UINT16(p) ((uint16_t)(p)[0] | ((uint16_t)(p)[1] << 8))
#define READ_LE_UINT32(p) ((uint32_t)(p)[0] | ((uint32_t)(p)[1] << 8) | ((uint32_t)(p)[2] << 16) | ((uint32_t)(p)[3] << 24))
#define GETBYTE(x, n)    (*((uint8_t*)&(x)+n))
#define GETSBYTE(x, n)   (*((int8_t*)&(x)+n))

#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define VA_NARGS2(...) ((int)(sizeof((int[]){ __VA_ARGS__ })/sizeof(int)))

#define LOCO_CLSID(_name,_addrs) static constexpr reference<CLSID const, _addrs> const _name {};

#define COMPILE_TIME_SIZEOF(t) template<int s> struct SIZEOF_ ## t ## _IS; \
struct foo { \
int a,b; \
}; \
SIZEOF_ ## t ## _IS<sizeof(t)> SIZEOF_ ## t ## _IS;

#define VTABLE_SET(item, addr) ((int*)item)[0] = addr
#define VTABLE_GET(item) (((int*)item)[0])

struct noinit_t final {};
