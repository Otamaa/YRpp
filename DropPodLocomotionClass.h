#pragma once
#include <LocomotionClass.h>

enum DropPodDirType : BYTE
{
	DPOD_DIR_NE,
	DPOD_DIR_NW,
	DPOD_DIR_SE,
	DPOD_DIR_SW,
};

class __declspec(uuid("4A582745-9839-11d1-B709-00A024DDAFD1")) DropPodLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	// TODO stub virtuals implementations

	//Destructor
	virtual ~DropPodLocomotionClass() RX;

	//Constructor
	DropPodLocomotionClass()
		: DropPodLocomotionClass(noinit_t())
	{ JMP_THIS(0x4B5AB0); }

protected:
	explicit __forceinline DropPodLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DropPodDirType DroppodDir;
	CoordStruct CoordDest;
	void* Piggybackee;
};

static_assert(sizeof(DropPodLocomotionClass) == 0x30);