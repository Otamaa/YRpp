/*
	File related stuff
*/

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <GeneralStructures.h>
#include <CCFileClass.h>
#include <CCINIClass.h>
#include <ConvertClass.h>

class DSurface;

//Voxel file stuff
//class VoxLib;	//VXL
//class MotLib;	//HVA

class MotLib {
public:
	DWORD f_0;
	DWORD f_4;
	DWORD f_8;
	void* f_C;

	MotLib(CCFileClass *Source)
		JMP_THIS(0x5BD570);

	~MotLib()
		JMP_THIS(0x5BD5A0);
};

class VoxLib {
public:
	DWORD f_0;
	DWORD f_4;
	DWORD f_8;
	DWORD f_C;
	DWORD f_10;
	DWORD f_14;
	DWORD f_18;

	VoxLib(CCFileClass *Source, DWORD dwUnk)
		JMP_THIS(0x755CD0);

	~VoxLib()
		JMP_THIS(0x755D10);
};

struct VoxelStruct
{
	VoxLib*	VXL;
	MotLib* HVA;
};

//SHP file stuff
struct SHPStruct
{
	WORD		unknown_0;
	short		Width;
	short		Height;
	short		Frames;
	DWORD		unknown_8;
	DWORD		unknown_C;
	//linked list of all SHPStructs
	SHPStruct*	Next;
	SHPStruct*	Prev;
};

//=== GLOBAL LINKED LIST OF ALL LOADED SHP FILES
// defined but not used
// static SHPStruct* SHPStruct_first=(SHPStruct*)0xB077B0;
//==============================================

class FileSystem
{
public:
	static void* __fastcall LoadFile(const char* pFileName, bool bLoadAsSHP)
		JMP_STD(0x5B40B0);

	static void* LoadFile(const char* pFileName)
		{ return LoadFile(pFileName, false); }

	static SHPStruct* LoadSHPFile(const char* pFileName)
		{ return (SHPStruct*)LoadFile(pFileName, true); }

	//I'm just making this up for easy palette loading
	static ConvertClass* LoadPALFile(const char* pFileName, DSurface* pSurface)
	{
		ColorStruct* pRawData = (ColorStruct*)LoadFile(pFileName, false);
		ColorStruct ColorData[0x100];

		for(int i = 0; i < 0x100; i++)
		{
			ColorData[i].R = pRawData[i].R << 2;
			ColorData[i].G = pRawData[i].G << 2;
			ColorData[i].B = pRawData[i].B << 2;
		}

		return new ConvertClass(
			ColorData,
			(ColorStruct*)0x885780,
			pSurface,
			0x35,
			0);
	}
};

#endif
