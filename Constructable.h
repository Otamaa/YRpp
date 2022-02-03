#pragma once

#include <CoordStruct.h>
#include <AbstractClass.h>
#include <WeaponTypeClass.h>

class VoxLib;
class MotLib;
// these "Construcable" is copied from original place
// added more contructor for more usage , and to prevent virtualization of the new ctor
// that can cause broken vtable
struct ConstructableWeaponStruct
{
	WeaponTypeClass* WeaponType { nullptr };
	CoordStruct       FLH { CoordStruct::Empty };
	int               BarrelLength { 0 };
	int               BarrelThickness { 0 };
	bool              TurretLocked { false };

	ConstructableWeaponStruct() = default;
	~ConstructableWeaponStruct() = default;

	explicit ConstructableWeaponStruct(noinit_t) noexcept { }

	explicit ConstructableWeaponStruct
	(
		WeaponTypeClass* pWeapon
		, CoordStruct& nFLH
		, int nBarrelLength
		, int nBarrelThickness
		, bool bTurretLocked
	) noexcept :
		WeaponType(pWeapon),
		FLH(nFLH),
		BarrelLength(nBarrelLength),
		BarrelThickness(nBarrelThickness),
		TurretLocked(bTurretLocked)
	{ }

	bool operator == (const ConstructableWeaponStruct& pWeap) const
	{
		return
			!_strcmpi(WeaponType->get_ID(),pWeap.WeaponType->get_ID()) &&
			FLH == pWeap.FLH &&
			BarrelLength == pWeap.BarrelLength &&
			BarrelThickness == pWeap.BarrelThickness &&
			TurretLocked == pWeap.TurretLocked
			;
	}
};

struct ConstructableVoxelStruct
{
	VoxLib* VXL { nullptr };
	MotLib* HVA { nullptr };

	ConstructableVoxelStruct() = default;
	~ConstructableVoxelStruct() = default;

	explicit ConstructableVoxelStruct(noinit_t) noexcept { }

	explicit ConstructableVoxelStruct(VoxLib* pVox, MotLib* pMot) noexcept :
		VXL(pVox), HVA(pMot)
	{ }

	bool operator == (const ConstructableVoxelStruct& nOther) const
	{ return false; } // ?
};

struct ConstructableTurretControl
{
	int Travel { -1 };
	int CompressFrames { -1 };
	int RecoverFrames { -1 };
	int HoldFrames { -1 };

	ConstructableTurretControl() = default;
	~ConstructableTurretControl() = default;

	explicit ConstructableTurretControl(noinit_t) noexcept { }

	explicit ConstructableTurretControl
	(int nTravel, int nCompressFrames, int nRecoverFrames, int nHoldFrames) noexcept :
		Travel(nTravel), CompressFrames(nCompressFrames), RecoverFrames(nRecoverFrames), HoldFrames(nHoldFrames)
	{ }

	bool operator == (const ConstructableTurretControl& nOther) const
	{
		return Travel == nOther.Travel &&
			CompressFrames == nOther.CompressFrames &&
			RecoverFrames == nOther.RecoverFrames &&
			HoldFrames == nOther.HoldFrames;
	}
};

struct DamageGroup
{
	AbstractClass* Target { nullptr };
	int Distance { 0 };

	DamageGroup() = default;
   ~DamageGroup() = default;

   explicit DamageGroup(noinit_t) noexcept { }

   explicit DamageGroup(DamageGroup* pThat) noexcept :
		Target(pThat->Target), Distance(pThat->Distance)
	{ }

   explicit DamageGroup(AbstractClass* pTarget, int pDistance = 0) noexcept :
		Target(pTarget), Distance(pDistance)
	{ }

	bool operator == (const DamageGroup& nOther) const
	{
		return Target->_IsEqualTo(nOther.Target) &&
			Distance == nOther.Distance;
	}

};

static_assert(sizeof(DamageGroup) == 0x8u);