#pragma once

#include <windows.h>
#include <atlbase.h>
#include <GeneralDefinitions.h>
#include <CoordStruct.h>
#include <unknwn.h>
#include <comdef.h>

DECLARE_INTERFACE_IID_(ISwizzle , IUnknown, "5FF0CA70-8B12-11D1-B708-00A024DDAFD1")
{
	virtual HRESULT __stdcall Reset() PURE;
	virtual HRESULT __stdcall Swizzle(void** pointer) PURE;
	virtual HRESULT __stdcall Fetch_Swizzle_ID(void* pointer, long* id) const PURE;
	virtual HRESULT __stdcall Here_I_Am(long id, void* pointer) PURE;
	virtual HRESULT __stdcall Save_Interface(IStream* stream, IUnknown* pointer) PURE;
	virtual HRESULT __stdcall Load_Interface(IStream* stream, GUID* riid, void** pointer) PURE;
	virtual HRESULT __stdcall Get_Save_Size(int* size) const PURE;
};

DECLARE_INTERFACE_IID_(IApplication , IUnknown, "96F02EC3-6FE8-11D1-B6FD-00A024DDAFD1")
{
	virtual HRESULT __stdcall FullName(BSTR* retval) PURE;
	virtual HRESULT __stdcall Name(BSTR* retval) PURE;
	virtual HRESULT __stdcall Quit() PURE;
	virtual HRESULT __stdcall ScenarioName(BSTR* retval) PURE;
	virtual HRESULT __stdcall FrameCount(long* retval) PURE;
	virtual HRESULT __stdcall Swizzle_Interface(ISwizzle** pVal) PURE;
};

__interface INoticeSource
{
	virtual void __stdcall INoticeSource_Unknown() PURE;
};

__interface INoticeSink
{
	virtual bool __stdcall INoticeSink_Unknown(DWORD dwUnknown) PURE;
};

DECLARE_INTERFACE_IID_(IAIHouse, IUnknown, "96F02EC4-6FE8-11D1-B6FD-00A024DDAFD1")
{
	virtual void __stdcall Link_House(void* unknown) const PURE;
	virtual void __stdcall AI(int* unknown) PURE;
};

DECLARE_INTERFACE_IID_(IRTTITypeInfo , IUnknown , "170DAC82-12E4-11D2-8175-006008055BB5")
{
	virtual AbstractType __stdcall What_Am_I() const PURE;
	virtual int __stdcall Fetch_ID() const PURE;
	virtual void __stdcall Create_ID() PURE;
};

DECLARE_INTERFACE_IID_(IHouse, IUnknown, "941582E0-86DA-11D1-B706-00A024DDAFD1")
{
	virtual long __stdcall				ID_Number() const PURE;
	virtual BSTR __stdcall				Name() const PURE;
	virtual IApplication* __stdcall		Get_Application() PURE;
	virtual long __stdcall				Available_Money() const PURE;
	virtual long __stdcall				Available_Storage() const PURE;
	virtual long __stdcall				Power_Output() const PURE;
	virtual long __stdcall				Power_Drain() const PURE;
	virtual long __stdcall				Category_Quantity(Category category) const PURE;
	virtual long __stdcall				Category_Power(Category category) const PURE;
	virtual CellStruct __stdcall		Base_Center() const PURE;
	virtual HRESULT __stdcall			Fire_Sale() const PURE;
	virtual HRESULT __stdcall			All_To_Hunt() PURE;
};

DECLARE_INTERFACE_IID_(IPublicHouse, IUnknown, "CAACF210-86E3-11D1-B706-00A024DDAFD1")
{
	virtual long __stdcall			ID_Number() const PURE;
	virtual BSTR __stdcall			Name() const PURE;
	virtual long __stdcall			Apparent_Category_Quantity(Category category) const PURE;
	virtual long __stdcall			Apparent_Category_Power(Category category) const PURE;
	virtual CellStruct __stdcall	Apparent_Base_Center() const PURE;
	virtual bool __stdcall			Is_Powered() const PURE;
};

DECLARE_INTERFACE_IID_(IGameMap, IUnknown, "96F02EC7-6FE8-11D1-B6FD-00A024DDAFD1")
{
	virtual long __stdcall Is_Visible(CellStruct cell) PURE;
};

__interface ILinkStream : IUnknown
{
	virtual HRESULT __stdcall Link_Stream(IUnknown* stream) PURE;
	virtual HRESULT __stdcall Unlink_Stream(IUnknown** stream) PURE;
};

DECLARE_INTERFACE_IID_(IFlyControl, IUnknown, "820F501C-4F39-11D2-9B70-00104B972FE8")
{
	virtual int __stdcall Landing_Altitude() PURE;
	virtual int __stdcall Landing_Direction() PURE;
	virtual long __stdcall Is_Loaded() PURE;
	virtual long __stdcall Is_Strafe() PURE;
	virtual long __stdcall Is_Fighter() PURE;
	virtual long __stdcall Is_Locked() PURE;
};

DECLARE_INTERFACE_IID_(ILocomotion, IUnknown, "070F3290-9841-11D1-B709-00A024DDAFD1")
{
	virtual HRESULT __stdcall Link_To_Object(void* pointer) PURE; //Links object to locomotor.
	virtual bool __stdcall Is_Moving() PURE;	//Sees if object is moving.
	virtual CoordStruct* __stdcall Destination(CoordStruct* pcoord) PURE;	//Fetches destination coordinate.
	virtual CoordStruct* __stdcall Head_To_Coord(CoordStruct* pcoord) PURE; // Fetches immediate (next cell) destination coordinate.
	virtual Move __stdcall Can_Enter_Cell(CellStruct cell) PURE; //Determine if specific cell can be entered.
	virtual bool __stdcall Is_To_Have_Shadow() PURE;	//Should object cast a shadow?
	virtual Matrix3D __stdcall Draw_Matrix(int* key) PURE; //Fetch voxel draw matrix.
	virtual Matrix3D __stdcall Shadow_Matrix(int* key) PURE;	//Fetch shadow draw matrix.
	virtual Point2D* __stdcall Draw_Point(Point2D* pPoint) PURE;	//Draw point center location.
	virtual Point2D* __stdcall Shadow_Point(Point2D* pPoint) PURE;	//Shadow draw point center location.
	virtual VisualType __stdcall Visual_Character(VARIANT_BOOL unused) PURE;	//Visual character for drawing.
	virtual int __stdcall Z_Adjust() PURE;	//Z adjust control value.
	virtual ZGradient __stdcall Z_Gradient() PURE;	//Z gradient control value.
	virtual bool __stdcall Process() PURE;	//Process movement of object.]
	virtual void __stdcall Move_To(CoordStruct to) PURE;	//Instruct to move to location specified.
	virtual void __stdcall Stop_Moving() PURE;	//Stop moving at first opportunity.
	virtual void __stdcall Do_Turn(DirStruct coord) PURE;	//Try to face direction specified.
	virtual void __stdcall Unlimbo() PURE;	//Object is appearing in the world.
	virtual void __stdcall Tilt_Pitch_AI() PURE;	//Special tilting AI function.
	virtual bool __stdcall Power_On() PURE;	//Locomotor becomes powered.
	virtual bool __stdcall Power_Off() PURE;	//Locomotor loses power.
	virtual bool __stdcall Is_Powered() PURE;	//Is locomotor powered?
	virtual bool __stdcall Is_Ion_Sensitive() PURE;	//Is locomotor sensitive to ion storms?
	virtual bool __stdcall Push(DirStruct dir) PURE;	//Push object in direction specified.
	virtual bool __stdcall Shove(DirStruct dir) PURE;	//Shove object (with spin) in direction specified.
	virtual void __stdcall Force_Track(int track, CoordStruct coord) PURE;	//Force drive track -- special case only.
	virtual Layer __stdcall In_Which_Layer() PURE;	//What display layer is it located in.
	virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) PURE;	//Don't use this function.
	virtual void __stdcall Force_New_Slope(int ramp) PURE;	//Force a voxel unit to a given slope. Used in cratering.
	virtual bool __stdcall Is_Moving_Now() PURE;	//Is it actually moving across the ground this very second?
	virtual int __stdcall Apparent_Speed() PURE;	//Actual current speed of object expressed as leptons per game frame.
	virtual int __stdcall Drawing_Code() PURE;	//Special drawing feedback code (locomotor specific meaning)
	virtual FireError __stdcall Can_Fire() PURE;	//Queries if any locomotor specific state prevents the object from firing.
	virtual int __stdcall Get_Status() PURE;	//Queries the general state of the locomotor.
	virtual void __stdcall Acquire_Hunter_Seeker_Target() PURE;	//Forces a hunter seeker droid to find a target.
	virtual bool __stdcall Is_Surfacing() PURE;	//Is this object surfacing?
	virtual void __stdcall Mark_All_Occupation_Bits(int mark) PURE;	//Lifts all occupation bits associated with the object off the map
	virtual bool __stdcall Is_Moving_Here(CoordStruct to) PURE;	//Is this object in the process of moving into this coord.
	virtual bool __stdcall Will_Jump_Tracks() PURE;	//Will this object jump tracks?
	virtual bool __stdcall Is_Really_Moving_Now() PURE;	//Infantry moving query function
	virtual void __stdcall Stop_Movement_Animation() PURE;	//Falsifies the IsReallyMoving flag in WalkLocomotionClass
	virtual void __stdcall Clear_Coords() PURE;	//Unknown, must have been added after LOCOS.TLB was generated. -pd
	virtual void __stdcall Lock() PURE;	//Locks the locomotor from being deleted
	virtual void __stdcall Unlock() PURE;	//Unlocks the locomotor from being deleted
	virtual int __stdcall Get_Track_Number() PURE;	//Queries internal variables
	virtual int __stdcall Get_Track_Index() PURE;	//Queries internal variables
	virtual int __stdcall Get_Speed_Accum() PURE;	//Queries internal variables
};

_COM_SMARTPTR_TYPEDEF(ILocomotion, __uuidof(ILocomotion));

DECLARE_INTERFACE_IID_(IPiggyback, IUnknown, "92FEA800-A184-11D1-B70A-00A024DDAFD1")
//'Piggyback' one locomotor onto another.
{
	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) PURE;	//Piggybacks a locomotor onto this one.
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) PURE;	//End piggyback process and restore locomotor interface pointer.
	virtual bool __stdcall Is_Ok_To_End() PURE;	//Is it ok to end the piggyback process?
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) PURE;	//Fetches piggybacked locomotor class ID.
	virtual bool __stdcall Is_Piggybacking() PURE;	//Is it currently piggy backing another locomotor?
};

_COM_SMARTPTR_TYPEDEF(IPiggyback, __uuidof(IPiggyback));
