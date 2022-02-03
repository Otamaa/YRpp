// Memory allocation handler

#pragma once

#include <YRPPCore.h>
#include <Memory.h>

class Buffer
{
public:
	Buffer(char *ptr, int size = 0)
	{ JMP_THIS(0x43AD00); }

	Buffer(void *ptr = nullptr, int size = 0)
	{ JMP_THIS(0x43AD40); }

	Buffer(const void * ptr, int size = 0)
	{ JMP_THIS(0x43AD80); }

	Buffer(int size)
	{ JMP_THIS(0x43ADC0); }

	Buffer(const Buffer & buffer)
	{ JMP_THIS(0x43ADF0); }

	~Buffer()
	{ JMP_THIS(0x43AE50); }

	Buffer & operator = (const Buffer & buffer)
	{ JMP_THIS(0x43AE10); }

	Buffer& operator = (Buffer&& other) noexcept
	{
		*this = other;
		auto const allocated = other.IsAllocated;
		other.IsAllocated = false;
		this->IsAllocated = allocated;
		return *this;
	}

	operator void * () const { return BufferPtr; }
	operator char * () const { return (char *)BufferPtr; }

	void Reset() { JMP_THIS(0x43AE80); }
	void * Get_Buffer() const { return BufferPtr; }
	long Get_Size() const { return Size; }
	bool Is_Valid() const { return BufferPtr != nullptr; }

protected:
	void * BufferPtr;
	long Size;
	bool IsAllocated;
};

class MemoryBuffer
{
public:
	constexpr MemoryBuffer() noexcept = default;

	explicit MemoryBuffer(int size) noexcept
		: MemoryBuffer(nullptr, size)
	{ }

	MemoryBuffer(void* pBuffer, int size) noexcept
		: Buffer(pBuffer), Size(size)
	{
		if(!this->Buffer && this->Size > 0) {
			this->Buffer = YRMemory::Allocate(static_cast<size_t>(size));
			this->Allocated = true;
		}
	}

	constexpr MemoryBuffer(MemoryBuffer const& other) noexcept
		: Buffer(other.Buffer), Size(other.Size)
	{ }

	MemoryBuffer(MemoryBuffer&& other) noexcept
		: Buffer(other.Buffer), Size(other.Size), Allocated(other.Allocated)
	{
		other.Allocated = false;
	}

	~MemoryBuffer() noexcept
	{
		if(this->Allocated) {
			YRMemory::Deallocate(this->Buffer);
		}
	}

	operator void * () const { return Buffer; }
	operator char * () const { return (char *)Buffer; }

	MemoryBuffer& operator = (MemoryBuffer const& other) noexcept
	{
		if(this != &other) {
			MemoryBuffer tmp(static_cast<MemoryBuffer&&>(*this));
			this->Buffer = other.Buffer;
			this->Size = other.Size;
		}

		return *this;
	}

	MemoryBuffer& operator = (MemoryBuffer&& other) noexcept
	{
		*this = other;
		auto const allocated = other.Allocated;
		other.Allocated = false;
		this->Allocated = allocated;
		return *this;
	}

	void Clear() noexcept
	{
		MemoryBuffer tmp(static_cast<MemoryBuffer&&>(*this));
		this->Buffer = nullptr;
		this->Size = 0;
	}

	void * Get_Buffer() const { return Buffer; }
	long Get_Size() const { return Size; }
	bool Is_Valid() const { return Buffer != nullptr; }

public:
	void* Buffer{ nullptr };
	int Size{ 0 };
	bool Allocated{ false };
};
