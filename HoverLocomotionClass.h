#pragma once
#include <LocomotionClass.h>

class NOVTABLE __declspec(uuid("4A582742-9839-11d1-B709-00A024DDAFD1")) HoverLocomotionClass : public LocomotionClass
{
public:

	//Destructor
	virtual ~HoverLocomotionClass() RX;

	//HoverLocomotionClass

	//Constructor
	HoverLocomotionClass()
		: HoverLocomotionClass(noinit_t())
	{ JMP_THIS(0x513C20); }

protected:
	explicit __forceinline HoverLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct MovingDestination;
	CoordStruct CoordHeadTo;
	FacingStruct Facing;
	double __Height;
	double __Accel;
	double __Boost;
	double __Gravity_HoverDampen;
	bool _being_shoved68;
	int _shove_rand6C;
	bool _BeignPushed;
	int _unk74;

};

static_assert(sizeof(HoverLocomotionClass) == 0x78);