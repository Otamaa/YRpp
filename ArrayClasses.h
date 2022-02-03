#pragma once

#include <Memory.h>

#include <algorithm>


//========================================================================
//=== VectorClass ========================================================
//========================================================================

template <typename T>
class VectorClass
{
public:
	// the hidden element count messes with alignment. only applies to align 8, 16, ...
	static_assert(!needs_vector_delete<T>::value || (__alignof(T) <= 4), "Alignment of T needs to be less than or equal to 4.");

	constexpr VectorClass() noexcept = default;

	explicit VectorClass(int capacity, T* pMem = nullptr) {
		if(capacity != 0) {
			this->Capacity = capacity;

			if(pMem) {
				this->Items = pMem;
			} else {
				this->Items = GameCreateArray<T>(static_cast<size_t>(capacity));
				this->IsAllocated = true;
			}
		}
	}

	VectorClass(const VectorClass &other) {
		if(other.Capacity > 0) {
			this->Items = GameCreateArray<T>(static_cast<size_t>(other.Capacity));
			this->IsAllocated = true;
			this->Capacity = other.Capacity;
			for(auto i = 0; i < other.Capacity; ++i) {
				this->Items[i] = other.Items[i];
			}
		}
	}

	VectorClass(VectorClass &&other) noexcept :
		Items(other.Items),
		Capacity(other.Capacity),
		IsInitialized(other.IsInitialized),
		IsAllocated(std::exchange(other.IsAllocated, false))
	{ }

	virtual ~VectorClass() noexcept {
		if(this->IsAllocated) {
			GameDeleteArray(this->Items, static_cast<size_t>(this->Capacity));
		}
	}

	VectorClass& operator = (const VectorClass &other) {
		VectorClass(other).Swap(*this);
		return *this;
	}

	VectorClass& operator = (VectorClass &&other) noexcept {
		VectorClass(std::move(other)).Swap(*this);
		return *this;
	}

	virtual bool operator == (const VectorClass &other) const {
		if(this->Capacity != other.Capacity) {
			return false;
		}

		for(auto i = 0; i < this->Capacity; ++i) {
			if(this->Items[i] == other.Items[i]) {
				continue; // kapow! don't rewrite this to != unless you know why you're doing it
			}
			return false;
		}

		return true;
	}

	bool operator != (const VectorClass &other) const {
		return !(*this == other);
	}

	virtual bool SetCapacity(int capacity, T* pMem = nullptr) {
		if(capacity != 0) {
			this->IsInitialized = false;

			bool bMustAllocate = (pMem == nullptr);
			if(!pMem) {
				pMem = GameCreateArray<T>(static_cast<size_t>(capacity));
			}

			this->IsInitialized = true;

			if(!pMem) {
				return false;
			}

			if(this->Items) {
				auto n = (capacity < this->Capacity) ? capacity : this->Capacity;
				for(auto i = 0; i < n; ++i) {
					pMem[i] = std::move_if_noexcept(this->Items[i]);
				}

				if(this->IsAllocated) {
					GameDeleteArray(this->Items, static_cast<size_t>(this->Capacity));
					this->Items = nullptr;
				}
			}

			this->IsAllocated = bMustAllocate;
			this->Items = pMem;
			this->Capacity = capacity;
		} else {
			Clear();
		}
		return true;
	}

	virtual void Clear() {
		VectorClass(std::move(*this));
		this->Items = nullptr;
		this->Capacity = 0;
	}

	virtual int FindItemIndex(const T& item) const {
		if(!this->IsInitialized) {
			return 0;
		}

		for(auto i = 0; i < this->Capacity; ++i) {
			if(this->Items[i] == item) {
				return i;
			}
		}

		return -1;
	}

	virtual int GetItemIndex(const T* pItem) const final {
		if(!this->IsInitialized) {
			return 0;
		}

		return pItem - this->Items;
	}

	virtual T GetItem(int i) const final {
		return this->Items[i];
	}

	T& operator [] (int i) {
		return this->Items[i];
	}

	const T& operator [] (int i) const {
		return this->Items[i];
	}

	bool Reserve(int capacity) {
		if(!this->IsInitialized) {
			return false;
		}

		if(this->Capacity >= capacity) {
			return true;
		}

		return SetCapacity(capacity, nullptr);
	}

	void Swap(VectorClass& other) noexcept {
		using std::swap;
		swap(this->Items, other.Items);
		swap(this->Capacity, other.Capacity);
		swap(this->IsInitialized, other.IsInitialized);
		swap(this->IsAllocated, other.IsAllocated);
	}

	T* Items{ nullptr };
	int Capacity{ 0 };
	bool IsInitialized{ true };
	bool IsAllocated{ false };
};

//========================================================================
//=== DynamicVectorClass =================================================
//========================================================================

template <typename T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	constexpr DynamicVectorClass() noexcept = default;

	explicit DynamicVectorClass(int capacity, T* pMem = nullptr)
		: VectorClass<T>(capacity, pMem)
	{ }

	DynamicVectorClass(const DynamicVectorClass &other) {
		if(other.Capacity > 0) {
			this->Items = GameCreateArray<T>(static_cast<size_t>(other.Capacity));
			this->IsAllocated = true;
			this->Capacity = other.Capacity;
			this->Count = other.Count;
			this->CapacityIncrement = other.CapacityIncrement;
			for(auto i = 0; i < other.Count; ++i) {
				this->Items[i] = other.Items[i];
			}
		}
	}

	DynamicVectorClass(DynamicVectorClass &&other) noexcept
		: VectorClass<T>(std::move(other)), Count(other.Count),
		CapacityIncrement(other.CapacityIncrement)
	{ }

	DynamicVectorClass& operator = (const DynamicVectorClass &other) {
		DynamicVectorClass(other).Swap(*this);
		return *this;
	}

	DynamicVectorClass& operator = (DynamicVectorClass &&other) noexcept {
		DynamicVectorClass(std::move(other)).Swap(*this);
		return *this;
	}

	virtual bool SetCapacity(int capacity, T* pMem = nullptr) override {
		bool bRet = VectorClass<T>::SetCapacity(capacity, pMem);

		if(this->Capacity < this->Count) {
			this->Count = this->Capacity;
		}

		return bRet;
	}

	virtual void Clear() override {
		VectorClass<T>::Clear();
		this->Count = 0;
	}

	virtual int FindItemIndex(const T& item) const override final {
		if(!this->IsInitialized) {
			return 0;
		}

		for(int i = 0; i < this->Count; i++) {
			if(this->Items[i] == item) {
				return i;
			}
		}

		return -1;
	}

	bool ValidIndex(int index) const {
		return static_cast<unsigned int>(index) < static_cast<unsigned int>(this->Count);
	}

	T GetItemOrDefault(int i) const {
		return this->GetItemOrDefault(i, T());
	}

	T GetItemOrDefault(int i, T def) const {
		if(this->ValidIndex(i)) {
			return this->Items[i];
		}
		return def;
	}

	T* begin() const {
		//if(!this->IsInitialized) {
		//	return nullptr;
		//}
		return &this->Items[0];
	}

	T* end() const {
		//if(!this->IsInitialized) {
		//	return nullptr;
		//}
		return &this->Items[this->Count];
	}

	bool AddItem(T item) {
		if(this->Count >= this->Capacity) {
			if(!this->IsAllocated && this->Capacity != 0) {
				return false;
			}

			if(this->CapacityIncrement <= 0) {
				return false;
			}

			if(!this->SetCapacity(this->Capacity + this->CapacityIncrement, nullptr)) {
				return false;
			}
		}

		this->Items[Count++] = std::move(item);
		return true;
	}

	bool AddHead(const T& item)
	{
		if (this->Count >= this->Capacity)
		{
			if (!this->IsAllocated && this->Capacity != 0)
			{
				return false;
			}

			if (this->CapacityIncrement <= 0)
			{
				return false;
			}

			if (!this->SetCapacity(this->Capacity + this->CapacityIncrement, nullptr))
			{
				return false;
			}
		}

		if (Count > 0)
			std::memmove(&(*this)[1], &(*this)[0], Count * sizeof(T));

		(*this)[0] = item;
		++Count;

		return true;
	}

	bool AddUnique(const T &item) {
		int idx = this->FindItemIndex(item);
		return idx < 0 && this->AddItem(item);
	}

	bool RemoveItem(int index) {
		if(!this->ValidIndex(index)) {
			return false;
		}

		--this->Count;
		for(int i = index; i < this->Count; ++i) {
			this->Items[i] = std::move_if_noexcept(this->Items[i + 1]);
		}

		return true;
	}

	bool Remove(const T &item) {
		int idx = this->FindItemIndex(item);
		return idx >= 0 && this->RemoveItem(idx);
	}

	void Swap(DynamicVectorClass& other) noexcept {
		VectorClass<T>::Swap(other);
		using std::swap;
		swap(this->Count, other.Count);
		swap(this->CapacityIncrement, other.CapacityIncrement);
	}

	int Count{ 0 };
	int CapacityIncrement{ 10 };
};

//========================================================================
//=== TypeList ===========================================================
//========================================================================

template <typename T>
class TypeList : public DynamicVectorClass<T>
{
public:
	constexpr TypeList() noexcept = default;

	explicit TypeList(int capacity, T* pMem = nullptr)
		: DynamicVectorClass(capacity, pMem)
	{ }

	TypeList(const TypeList &other)
		: DynamicVectorClass(other), unknown_18(other.unknown_18)
	{ }

	TypeList(TypeList &&other) noexcept
		: DynamicVectorClass(std::move(other)), unknown_18(other.unknown_18)
	{ }

	TypeList& operator = (const TypeList &other) {
		TypeList(other).Swap(*this);
		return *this;
	}

	TypeList& operator = (TypeList &&other) noexcept {
		TypeList(std::move(other)).Swap(*this);
		return *this;
	}

	void Swap(TypeList& other) noexcept {
		DynamicVectorClass::Swap(other);
		using std::swap;
		swap(this->unknown_18, other.unknown_18);
	}

	int unknown_18{ 0 };
};

//========================================================================
//=== CounterClass =======================================================
//========================================================================

class CounterClass : public VectorClass<int>
{
public:
	constexpr CounterClass() noexcept = default;

	CounterClass(const CounterClass& other)
		: VectorClass(other), Total(other.Total)
	{ }

	CounterClass(CounterClass &&other) noexcept
		: VectorClass(std::move(other)), Total(other.Total)
	{ }

	CounterClass& operator = (const CounterClass &other) {
		CounterClass(other).Swap(*this);
		return *this;
	}

	CounterClass& operator = (CounterClass &&other) noexcept {
		CounterClass(std::move(other)).Swap(*this);
		return *this;
	}

	virtual void Clear() override {
		for(int i = 0; i < this->Capacity; ++i) {
			this->Items[i] = 0;
		}

		this->Total = 0;
	}

	int GetTotal() const {
		return this->Total;
	}

	bool EnsureItem(int index) {
		if(index < this->Capacity) {
			return true;
		}

		int count = this->Capacity;
		if(this->SetCapacity(index + 10, nullptr)) {
			for(auto i = count; i < this->Capacity; ++i) {
				this->Items[i] = 0;
			}
			return true;
		}

		return false;
	}

	int operator[] (int index) const {
		return this->GetItemCount(index);
	}

	int GetItemCount(int index) {
		return this->EnsureItem(index) ? this->Items[index] : 0;
	}

	int GetItemCount(int index) const {
		return (index < this->Capacity) ? this->Items[index] : 0;
	}

	int Increment(int index) {
		if(this->EnsureItem(index)) {
			++this->Total;
			return ++this->Items[index];
		}
		return 0;
	}

	int Decrement(int index) {
		if(this->EnsureItem(index)) {
			--this->Total;
			return --this->Items[index];
		}
		return 0;
	}

	void Swap(CounterClass& other) noexcept {
		VectorClass::Swap(other);
		using std::swap;
		swap(this->Total, other.Total);
	}

	int Total{ 0 };
};

template<typename T, int N>
class TArray
{
public:
    inline TArray() {}

    inline TArray(T val)
    {
        for (int i = 0; i < N; ++i)
            Data[i] = val;
    }

    inline const int Size() const
    {
        return N;
    }

    inline T& operator [](int idx)
    {
        return Data[idx];
    }

    inline T operator [](int idx) const
    {
        return Data[idx];
    }

private:
    T Data[N];
};

template<typename T, const int size>
class ArrayHelper
{
public:
	operator T* () { return (T*)this; }
	operator const T* () const { return (T*)this; }
	T* operator&() { return (T*)this; }
	const T* operator&() const { return (T*)this; }
	T& operator[](int index) { return ((T*)this)[index]; }
	const T& operator[](int index) const { return ((T*)this)[index]; }

protected:
	char _dummy[size * sizeof(T)];
};

template<typename T, const int y, const int x>
class ArrayHelper2D
{
public:
	operator ArrayHelper<T, x>* () { return (ArrayHelper<T, x> *)this; }
	operator const ArrayHelper<T, x>* () const { return (ArrayHelper<T, x> *)this; }
	ArrayHelper<T, x>* operator&() { return (ArrayHelper<T, x> *)this; }
	const ArrayHelper<T, x>* operator&() const { return (ArrayHelper<T, x> *)this; }
	ArrayHelper<T, x>& operator[](int index) { return _dummy[index]; }
	const ArrayHelper<T, x>& operator[](int index) const { return _dummy[index]; }

protected:
	ArrayHelper<T, x> _dummy[y];
};

class BooleanVectorClass
{
public:
	BooleanVectorClass(unsigned size = 0, unsigned char* array = 0)
	{
		BitArray.SetCapacity(((size + (8 - 1)) / 8), array);
		LastIndex = -1;
		BitCount = size;
	}

	BooleanVectorClass(BooleanVectorClass const& vector)
	{
		LastIndex = -1;
		*this = vector;
	}

	// Assignment operator.
	BooleanVectorClass& operator =(BooleanVectorClass const& vector)
	{
		Fixup();
		Copy = vector.Copy;
		LastIndex = vector.LastIndex;
		BitArray = vector.BitArray;
		BitCount = vector.BitCount;
		return(*this);
	}

	// Equivalency operator.
	int operator == (BooleanVectorClass const& vector)
	{
		Fixup(LastIndex);
		return(BitCount == vector.BitCount && BitArray == vector.BitArray);

	}

	// Fetch number of boolean objects in vector.
	int Length() { return BitCount; };

	// Set all boolean values to false;
	void Reset();

	// Set all boolean values to true.
	void Set();

	// Resets vector to zero length (frees memory).
	void Clear()
	{
		Fixup();
		BitCount = 0;
		BitArray.Clear();
	}

	// Change size of this boolean vector.
	int Resize(unsigned size)
	{
		Fixup();

		if (size)
		{

			/*
			**	Record the previous bit count of the boolean vector. This is used
			**	to determine if the array has grown in size and thus clearing is
			**	necessary.
			*/
			int oldsize = BitCount;

			/*
			**	Actually resize the bit array. Since this is a bit packed array,
			**	there are 8 elements per byte (rounded up).
			*/
			int success = BitArray.SetCapacity(((size + (8 - 1)) / 8));

			/*
			**	Since there is no default constructor for bit packed integers, a manual
			**	clearing of the bits is required.
			*/
			BitCount = size;
			if (success && oldsize < (int)size)
			{
				for (int index = oldsize; index < (int)size; index++)
				{
					(*this)[index] = 0;
				}
			}

			return(success);
		}

		Clear();
		return(true);
	}

	// Fetch reference to specified index.
	bool const& operator[](int index) const
	{
		if (LastIndex != index) Fixup(index);
		return(Copy);
	};
	bool& operator[](int index)
	{
		if (LastIndex != index) Fixup(index);
		return(Copy);
	};

	// Quick check on boolean state.
	bool Is_True(int index) const;
;
	// Find first index that is false.
	int First_False() const;

	// Find first index that is true.
	int First_True() const;

private:
	void Fixup(int index = -1) const;

	int BitCount;
	bool Copy;
	int LastIndex;
	VectorClass<unsigned char> BitArray;
};

static_assert(sizeof(BooleanVectorClass) == 0x1C);

template<class T, int COUNT, int FIRST = 0, int DEFAULT = FIRST>
class DynamicVectorArrayClass
{
public:
	static const int COUNT = COUNT;

	DynamicVectorArrayClass() : Active(DEFAULT) { }

	void Set_Active_Context(int active)
	{
		Active = active;
	}

	void Clear_All()
	{
		for (int i = FIRST; i < COUNT; ++i)
		{
			Clear(i);
		}
	}

	void Clear()
	{
		Clear(Active);
	}

	int Count() const
	{
		return Count(Active);
	}

	int Add(T const& object)
	{
		return Add(Active, object);
	}

	int Add_Head(T const& object)
	{
		return NULL;
		//return Add_Head(Active, object);
	}

	int Delete(T const& object)
	{
		return Delete(Active, object);
	}

	int Delete_All(T const& object)
	{
		int count = 0;
		for (int i = FIRST; i < COUNT; ++i)
		{
			count += Delete(i, object);
		}
		return count;
	}

	int Delete_All_Except(T const& object, int except)
	{
		int count = 0;
		for (int i = FIRST; i < COUNT; ++i)
		{
			if (except != i)
			{
				count += Delete(i, object);
			}
		}
		return count;
	}

	int Delete(int index)
	{
		return Delete(Active, index);
	}

	T& operator[](unsigned index)
	{
		return Collection[Active][index];
	}

	T const& operator[](unsigned index) const
	{
		return Collection[Active][index];
	}

	void Clear(int context)
	{
		Collection[context].Clear();
	}

	int Count(int context) const
	{
		return Collection[context].Count();
	}

	int Add(int context, T const& object)
	{
		return Collection[context].AddItem(object);
	}

	int Add_Unique(int context, T const& object)
	{
		return Collection[context].AddUnique(object);
	}

	int Add_Head(int context, T const& object)
	{
		return Collection[context].AddHead(object);
	}

	int Delete(int context, T const& object)
	{
		return Collection[context].Remove(object);
	}

	int Delete(int context, int index)
	{
		return Collection[context].RemoveItem(index);
	}

	DynamicVectorClass<T>& Raw()
	{
		return Collection[Active];
	}

	DynamicVectorClass<T>& Raw(int context)
	{
		return Collection[context];
	}

private:
	DynamicVectorClass<T> Collection[COUNT];
	int Active;
};

template<class T>
class SimpleVecClass
{
public:
	SimpleVecClass(unsigned size = 0) :
		Vector(nullptr), VectorMax(0)
	{
		if (size > 0)
		{
			Resize(size);
		}
	}

	virtual ~SimpleVecClass()
	{
		if (Vector != nullptr)
		{
			GameDeleteArray(Vector, static_cast<size_t>(VectorMax));
			Vector = nullptr;
			VectorMax = 0;
		}
	}

	virtual bool Resize(int newsize)
	{
		if (newsize == VectorMax)
		{ return true; }

		if (newsize > 0)
		{
			T* newptr = GameCreateArray<T>((size_t)newsize);

			if (Vector != nullptr)
			{
				int copycount = (newsize < VectorMax) ? newsize : VectorMax;
				std::memcpy(newptr, Vector, copycount * sizeof(T));

				GameDeleteArray(Vector, static_cast<size_t>(VectorMax));
				Vector = nullptr;
			}

			Vector = newptr;
			VectorMax = newsize;

		}
		else
		{
			VectorMax = 0;
			if (Vector != nullptr)
			{
				GameDeleteArray(Vector, static_cast<size_t>(VectorMax));
				Vector = nullptr;
			}
		}
		return true;
	}

	virtual bool Uninitialised_Grow(int newsize)
	{
		if (newsize <= VectorMax)
		{
			return true;
		}

		if (newsize > 0)
		{
			GameDeleteArray(Vector, static_cast<size_t>(VectorMax));
			Vector = GameCreateArray<T>((size_t)newsize);;
			VectorMax = newsize;
		}
		return true;
	}

	T& operator[](int index)
	{
		if (index > VectorMax)
			index = VectorMax;

		return Vector[index];
	}
	T const& operator[](int index) const
	{
		if (index > VectorMax)
			index = VectorMax;

		return Vector[index];
	}

	int Length() const { return VectorMax; }

	void Zero_Memory()
	{
		if (Vector != nullptr)
		{
			std::memset(Vector, 0, VectorMax * sizeof(T));
		}
	}

protected:
	T* Vector;
	int VectorMax;
};

template<class T>
class SimpleDynVecClass : public SimpleVecClass<T>
{
	using SimpleVecClass<T>::Vector;
	using SimpleVecClass<T>::VectorMax;
	using SimpleVecClass<T>::Length;

public:
	SimpleDynVecClass(unsigned size = 0) :
		SimpleVecClass<T>(size),
		ActiveCount(0)
	{}

	virtual ~SimpleDynVecClass()
	{
		if (Vector != nullptr)
		{
			GameDeleteArray(Vector, (size_t)VectorMax);
			Vector = nullptr;
		}
	}

	virtual bool Resize(int newsize)
	{
		if (SimpleVecClass<T>::Resize(newsize))
		{
			if (Length() < ActiveCount)
			{
				ActiveCount = Length();
			}
			return true;
		}
		return false;
	}

	T& operator[](int index)
	{
		if (index > ActiveCount)
			index = ActiveCount;

		return Vector[index];
	}
	const T& operator[](int index) const
	{
		if (index > ActiveCount)
			index = ActiveCount;

		return Vector[index];
	}

	int Count() const { return (ActiveCount); }

	bool Add(const T& object, int new_size_hint = 0)
	{
		if (ActiveCount >= VectorMax)
		{
			if (!Grow(new_size_hint))
			{
				return false;
			}
		}

		(*this)[ActiveCount++] = object;
		return true;
	}

	T* Add_Multiple(int number_to_add)
	{
		int i = ActiveCount;
		ActiveCount += number_to_add;

		if (ActiveCount >= VectorMax)
		{
			Grow(ActiveCount);
		}

		return &Vector[i];
	}

	bool Delete(int index, bool allow_shrink = true)
	{
		if (index > ActiveCount)
			index = ActiveCount;

			if (index < (ActiveCount - 1))
			{
				std::memmove(&(Vector[index]), &(Vector[index + 1]), (ActiveCount - index - 1) * sizeof(T));
			}
		--ActiveCount;

		if (allow_shrink)
		{
			Shrink();
		}

		return true;
	}

	bool Delete(const T& object, bool allow_shrink = true)
	{
		int id = Find_Index(object);
		if (id != -1)
		{
			return Delete(id, allow_shrink);
		}
		return false;
	}

	bool Delete_Range(int start, int count, bool allow_shrink = true)
	{
		if (start < 0)
			start = 0;

		if (start > (ActiveCount - count))
			start = (ActiveCount - count);

		if (start < ActiveCount - count)
			std::memmove(&(Vector[start]), &(Vector[start + count]), (ActiveCount - start - count) * sizeof(T));

		ActiveCount -= count;

		if (allow_shrink)
			Shrink();

		return true;
	}

	void Delete_All(bool allow_shrink = true)
	{
		ActiveCount = 0;
		if (allow_shrink)
		{
			Shrink();
		}
	}

	T* begin() const
	{ return &this->Vector[0]; }

	T* end() const
	{ return &this->Vector[ActiveCount]; }

	bool Add_Unique(const T& item, int new_size_hint = 0)
	{
		int idx = this->Find_Index(item);
		return idx < 0 && this->Add(item, new_size_hint);
	}

protected:
	bool Grow(int new_size_hint)
	{
		int new_size = std::max(Length() + Length() / 4, Length() + 4);
		new_size = std::max(new_size, new_size_hint);

		return Resize(new_size);
	}

	bool Shrink()
	{
		// Shrink the array if it is wasting more than 25%.
		if (ActiveCount < VectorMax / 4)
		{
			return Resize(ActiveCount);
		}
		return true;
	}

	int Find_Index(const T& object)
	{
		for (int i = 0; i < Count(); ++i)
		{
			if ((*this)[i] == object)
			{
				return i;
			}
		}
		return -1;
	}

protected:
	int ActiveCount;
};