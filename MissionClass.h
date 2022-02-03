/*
	Base class for all game objects with missions (yeah... not many).
*/

#pragma once

#include <ObjectClass.h>

class CCINIClass;

class MissionControlClass
{
	public:
		static MissionControlClass* Array()
			{ return reinterpret_cast<MissionControlClass*>(0xA8E3A8); }

		static const char** Names()
			{ return reinterpret_cast<const char**>(0x816CAC); }

		static MissionControlClass* __fastcall Find(const char* pName)
			{ JMP_STD(0x5B3910); }

		static Mission __fastcall FindIndex(const char* pName)
			{ JMP_STD(0x5B3910); }

		static const char* __fastcall FindName(const Mission& index)
			{ JMP_STD(0x5B3740); }

		MissionControlClass()
			{ JMP_THIS(0x5B3700); }

		int Normal_Delay() const { return static_cast<int>(TICKS_PER_MINUTE * Rate); }
		int AA_Delay() const { return static_cast<int>(TICKS_PER_MINUTE * AARate); }

		void LoadFromINI(CCINIClass* pINI)
			{ JMP_THIS(0x5B3760); }

public:
		int ArrayIndex; //MissionType
		bool NoThreat;
		bool Zombie;
		bool Recruitable;
		bool Paralyzed;
		bool Retaliate;
		bool Scatter;
		double Rate; //default 0.016
		double AARate; //default 0.016
};

static_assert(sizeof(MissionControlClass) == 0x20);

class NOVTABLE MissionClass : public ObjectClass
{
public:
	//Destructor
	virtual ~MissionClass() { /* ~ObjectClass() */ }

	//MissionClass
	virtual bool QueueMission(Mission mission, bool start_mission) R0; //assign
	virtual bool NextMission() R0;//commence
	virtual void ForceMission(Mission mission) RX;

	virtual void Override_Mission(Mission mission, AbstractClass* tarcom = nullptr, AbstractClass* navcom = nullptr) RX; //Vt_1F4
	virtual bool Mission_Revert() R0; //Restore_Mission
	virtual bool Mission_Overriden() const R0;//vt_1FC
	virtual bool Ready_To_Commence() const R0; //200

	virtual int Mission_Sleep() R0;
	virtual int Mission_Harmless() R0;
	virtual int Mission_Ambush() R0;
	virtual int Mission_Attack() R0;
	virtual int Mission_Capture() R0;
	virtual int Mission_Eaten() R0;
	virtual int Mission_Guard() R0;
	virtual int Mission_AreaGuard() R0;
	virtual int Mission_Harvest() R0;
	virtual int Mission_Hunt() R0;
	virtual int Mission_Move() R0;
	virtual int Mission_Retreat() R0;
	virtual int Mission_Return() R0;
	virtual int Mission_Stop() R0;
	virtual int Mission_Unload() R0;
	virtual int Mission_Enter() R0;
	virtual int Mission_Construction() R0;
	virtual int Mission_Selling() R0;
	virtual int Mission_Repair() R0;
	virtual int Mission_Missile() R0;
	virtual int Mission_Open() R0;
	virtual int Mission_Rescue() R0;
	virtual int Mission_Patrol() R0;
	virtual int Mission_ParaDropApproach() R0;
	virtual int Mission_ParaDropOverfly() R0;
	virtual int Mission_Wait() R0;
	virtual int Mission_SpyPlaneApproach() R0;
	virtual int Mission_SpyPlaneOverfly() R0;

	static bool __fastcall IsRecruitableMission(Mission mission) { JMP_STD(0x5B36E0); }

	void Shorten_Mission_Timer() { UpdateTimer = 0; }
	MissionControlClass* GetCurrentMissionControl() const { JMP_THIS(0x5B3A00); }
	bool HasSuspendedMission() const { JMP_THIS(0x5B3A10); }
	int MissionTime() const { JMP_THIS(0x5B3A20); }
	Mission GetMission() const { JMP_THIS(0x5B3040); }

	//Constructor
	MissionClass() noexcept
		: MissionClass(noinit_t())
	{ THISCALL(0x5B2DA0); }

protected:
	explicit __forceinline MissionClass(noinit_t) noexcept
		: ObjectClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	Mission  CurrentMission;
	Mission  SuspendedMission; //B0
	Mission  QueuedMission;
	bool     AssignmentState; //B8
	int      MissionStatus;
	int      CurrentMissionStartTime;	//in frames
	DWORD    unknown_C4;
	TimerStruct UpdateTimer;
};

static_assert(sizeof(MissionClass) == 0xD4);