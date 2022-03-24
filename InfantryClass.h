/*
	Infantry
*/

#pragma once

#include <FootClass.h>
#include <InfantryTypeClass.h>

class NOVTABLE InfantryClass : public FootClass
{
public:
	static const AbstractType AbsID = AbstractType::Infantry;

	//Static
	static constexpr constant_ptr<DynamicVectorClass<InfantryClass*>, 0xA83DE8u> const Array{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~InfantryClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//FootClass
	virtual bool ApproachTarget(bool bSomething) override JMP_THIS(0x522340);

	//InfantryClass
	virtual bool IsDeployed() const R0;
	virtual bool PlayAnim(DoType index, bool force = false, bool randomStartFrame = false) R0; //0x51D6F0 `InfantryClass::Do_Action

	bool IsDoingDeploy()
		{ JMP_THIS(0x522510); }

	void UnslaveMe();
	void RemoveMe_FromGunnerTransport();

	void ForceHarvest() const
		{ JMP_THIS(0x522D00); }

	bool IsHarvesting() const
		{ JMP_THIS(0x522FC0); }

	//Constructor
	InfantryClass(InfantryTypeClass* pType, HouseClass* pOwner) noexcept
		: InfantryClass(noinit_t())
	{ JMP_THIS(0x517A50); }

protected:
	explicit __forceinline InfantryClass(noinit_t) noexcept
		: FootClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	InfantryTypeClass* Type;
	DoType SequenceAnim; //which is currently playing
	TimerStruct unknown_Timer_6C8;
	DWORD          PanicDurationLeft; // set in ReceiveDamage on panicky units
	bool           PermanentBerzerk; // set by script action, not cleared anywhere
	bool           Technician;
	bool           unknown_bool_6DA;
	bool           Crawling;
	bool           unknown_bool_6DC;
	bool           unknown_bool_6DD;
	DWORD          unknown_6E0;
	bool           ShouldDeploy;
	int            unknown_int_6E8;
	PROTECTED_PROPERTY(DWORD, unused_6EC); //??
};
