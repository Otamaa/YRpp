#pragma once
#include <LocomotionClass.h>

class __declspec(uuid("55D141B8-DB94-11d1-AC98-006008055BB5")) MechLocomotionClass : public LocomotionClass
{
public:

	//Destructor
	virtual ~MechLocomotionClass() RX;

	//MechLocomotionClass

	//Constructor
	MechLocomotionClass()
		: MechLocomotionClass(noinit_t())
	{ JMP_THIS(0x5AFEF0);}

protected:
	explicit __forceinline MechLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct MovingDestination;
	CoordStruct CoordHeadTo;
	bool IsMoving;
};

static_assert(sizeof(MechLocomotionClass) == 0x34);