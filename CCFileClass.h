#pragma once

#include <GeneralDefinitions.h>
#include <YRAllocator.h>
#include <YRPPCore.h>
#include <GenericList.h>

enum class FileAccessMode : unsigned int {
	None = 0,
	Read = 1,
	Write = 2,
	ReadWrite = Read | Write
};

enum class FileSeekMode : unsigned int {
	Set = 0, // SEEK_SET
	Current = 1, // SEEK_CUR
	End = 2 // SEEK_END
};

enum class FileAccessType : unsigned int
{
	Closed = 0,       // Default state, file close.
	Read = 1,         // Open for reading access.
	Write = 2,        // Open for writing access.
	ReadWrite = 3,   // Combination of reading and writing access.
	Append = 4       // When writing, it will keep the existing data
				 // and set the file pointer to the end of the
				  // existing data.
};

enum FileErrorType : int
{
	/**
	 *  This is a duplicate of the error numbers. The error handler for the
	 *  RawFileClass handles these errors. If the error routine is overridden
	 *  and additional errors are defined, then use numbers starting with 100.
	 *  Note that these errors here are listed in numerical order. These errors
	 *  are defined in the standard header file <errno.h>.
	 */
	FILE_ERROR_ZERO = 0,                    // Non-error.
	FILE_ERROR_PERM = EPERM,                // Operation not permitted.
	FILE_ERROR_NOENT = ENOENT,              // No such file or directory.
	FILE_ERROR_SRCH = ESRCH,                // No such process.
	FILE_ERROR_INTR = EINTR,                // Interrupted function call.
	FILE_ERROR_IO = EIO,                    // Input/output error.
	FILE_ERROR_NXIO = ENXIO,                // No such device or address.
	FILE_ERROR_2BIG = E2BIG,                // Argument list too long.
	FILE_ERROR_NOEXEC = ENOEXEC,            // Exec format error.
	FILE_ERROR_BADF = EBADF,                // Bad file descriptor.
	FILE_ERROR_CHILD = ECHILD,              // No child processes.
	FILE_ERROR_AGAIN = EAGAIN,              // Resource temporarily unavailable.
	FILE_ERROR_NOMEM = ENOMEM,              // Not enough space/cannot allocate memory.
	FILE_ERROR_ACCES = EACCES,              // Permission denied.
	FILE_ERROR_FAULT = EFAULT,              // Bad address.
	FILE_ERROR_BUSY = EBUSY,                // Device or resource busy.
	FILE_ERROR_EXIST = EEXIST,              // File exists.
	FILE_ERROR_XDEV = EXDEV,                // Improper link.
	FILE_ERROR_NODEV = ENODEV,              // No such device.
	FILE_ERROR_NOTDIR = ENOTDIR,            // Not a directory.
	FILE_ERROR_ISDIR = EISDIR,              // Is a directory.
	FILE_ERROR_INVAL = EINVAL,              // Invalid argument.
	FILE_ERROR_NFILE = ENFILE,              // Too many open files in system.
	FILE_ERROR_MFILE = EMFILE,              // Too many open files.
	FILE_ERROR_NOTTY = ENOTTY,              // Inappropriate I/O control operation.
	FILE_ERROR_FBIG = EFBIG,                // File too large.
	FILE_ERROR_NOSPC = ENOSPC,              // No space left on device.
	FILE_ERROR_SPIPE = ESPIPE,              // Invalid seek.
	FILE_ERROR_ROFS = EROFS,                // Read-only filesystem.
	FILE_ERROR_MLINK = EMLINK,              // Too many links.
	FILE_ERROR_PIPE = EPIPE,                // Broken pipe.
	FILE_ERROR_DOM = EDOM,                  // Mathematics argument out of domain of function.
	FILE_ERROR_RANGE = ERANGE,              // Result too large.
	FILE_ERROR_DEADLK = EDEADLK,            // Resource deadlock avoided.
	FILE_ERROR_NAMETOOLONG = ENAMETOOLONG,  // Filename too long.
	FILE_ERROR_NOLCK = ENOLCK,              // No locks available.
	FILE_ERROR_NOSYS = ENOSYS,              // Function not implemented.
	FILE_ERROR_NOTEMPTY = ENOTEMPTY,        // Directory not empty.
	FILE_ERROR_ILSEQ = EILSEQ,              // Invalid or incomplete multibyte or wide character.
};

//--------------------------------------------------------------------
//Abstract File class
//--------------------------------------------------------------------
class NOVTABLE FileClass
{
public:
	//Destructor
	virtual	~FileClass() RX;
	//FileClass
	virtual const char* GetFileName() const = 0;
	virtual const char* SetFileName(const char* pFileName) = 0;
	virtual BOOL CreateFile() = 0;
	virtual BOOL DeleteFile() = 0;
	virtual bool Exists(bool writeShared = false) = 0;
	virtual bool HasHandle() = 0;
	virtual bool Open(FileAccessMode access) = 0;
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) = 0;
	virtual int ReadBytes(void* pBuffer, int nNumBytes) = 0; //Returns number of bytes read.
	virtual off_t Seek(off_t offset, FileSeekMode seek) = 0;
	virtual off_t GetFileSize() = 0;
	virtual int WriteBytes(void* pBuffer, int nNumBytes) = 0; //Returns number of bytes written.
	virtual void Close() = 0;
	virtual LONG GetFileTime() R0; //LoWORD = FatTime, HiWORD = FatDate
	virtual bool SetFileTime(LONG FileTime) R0;
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) = 0;

	static void* __fastcall ReadWholeFile(FileClass* pFile)
	{ JMP_STD(0x4A3890); }

	void* ReadWholeFile()
	{ return ReadWholeFile(this); }

	template <typename T>
	bool Read(T& obj, int size = sizeof(T)) {
		return this->ReadBytes(&obj, size) == size;
	}

	template <typename T>
	bool Write(T& obj, int size = sizeof(T)) {
		return this->WriteBytes(&obj, size) == size;
	}

protected:
	explicit __forceinline FileClass(noinit_t)
	{ }

	//Properties

public:
	bool SkipCDCheck;
private:
	BYTE padding_5[3];
};

//--------------------------------------------------------------------
//Files in the game directory
//--------------------------------------------------------------------
class NOVTABLE RawFileClass : public FileClass
{
public:
	//Destructor
	virtual ~RawFileClass() {JMP_THIS(0x65CA00);}

	//FileClass
	virtual const char* GetFileName() const override { JMP_THIS(0x401940); }
	virtual const char* SetFileName(const char* pFileName) override {JMP_THIS(0x65CAC0);}
	virtual BOOL CreateFile() override { JMP_THIS(0x65D150); }
	virtual BOOL DeleteFile() override { JMP_THIS(0x65D190); }
	virtual bool Exists(bool writeShared = false) override { JMP_THIS(0x65CBF0); }
	virtual bool HasHandle() override { JMP_THIS(0x65D420); }
	virtual bool Open(FileAccessMode access) override {JMP_THIS(0x65CB50);}
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override {JMP_THIS(0x65CB30);}
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x65CCE0); }
	virtual off_t Seek(off_t offset, FileSeekMode seek) override { JMP_THIS(0x65CF00); }
	virtual off_t GetFileSize() override { JMP_THIS(0x65D0D0); }
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x65CDD0); }
	virtual void Close() override { JMP_THIS(0x65CCA0); }
	virtual LONG GetFileTime() override { JMP_THIS(0x65D1F0); }
	virtual bool SetFileTime(LONG date_time) override { JMP_THIS(0x65D240); }
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) override RX;

    void Bias(int nOffset , int nLength)
	{ JMP_THIS(0x65D2B0); }

	DWORD Raw_Seek(int nPos ,LONG nDir)
	{ JMP_THIS(0x65D320); }

	//Constructor
	RawFileClass(const char* pFileName)
		: RawFileClass(noinit_t())
	{ JMP_THIS(0x65CA80); }

protected:
	explicit __forceinline RawFileClass(noinit_t)
		: FileClass(noinit_t())
	{ }

	//Properties

public:
	FileAccessMode FileAccess;
	int FilePointer;
	int FileSize;
	HANDLE Handle;
	const char* FileName;
	short unknown_short_1C;	//FatTime?
	short unknown_short_1E;	//FatDate?
	bool FileNameAllocated;
private:
	BYTE padding_21[3];
};

//--------------------------------------------------------------------
//Files that get buffered in some way?
//--------------------------------------------------------------------
class NOVTABLE BufferIOFileClass : public RawFileClass
{
public:
	//Destructor
	virtual ~BufferIOFileClass() { JMP_THIS(0x431B80); }

	//FileClass
	virtual const char* GetFileName() const override R0;
	virtual const char* SetFileName(const char* pFileName) override { JMP_THIS(0x431E80); }
	virtual BOOL CreateFile() override R0;
	virtual BOOL DeleteFile() override R0;
	virtual bool Exists(bool writeShared = false) override { JMP_THIS(0x431F10); }
	virtual bool HasHandle() override { JMP_THIS(0x431F30); }
	virtual bool Open(FileAccessMode access) override { JMP_THIS(0x431F70); }
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override { JMP_THIS(0x431F50); }
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x4322A0); }
	virtual off_t Seek(off_t offset, FileSeekMode seek) override { JMP_THIS(0x4324B0); }
	virtual off_t GetFileSize() override { JMP_THIS(0x4325A0); }
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x432050); }
	virtual void Close() override { JMP_THIS(0x4325C0); }
	virtual LONG GetFileTime() override R0;
	virtual bool SetFileTime(LONG date_time) override R0;
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) override RX;

	bool Cache(int size, void* pBuffer)
	{ JMP_THIS(0x431BC0); }

	void Free()
	{ JMP_THIS(0x431D90); }

	bool Commit()
	{ JMP_THIS(0x431DD0); }

	//Constructor
	BufferIOFileClass()
		: BufferIOFileClass(noinit_t())
	{ JMP_THIS(0x431B20); }

	BufferIOFileClass(const char* pFilename)
		: BufferIOFileClass(noinit_t())
	{ JMP_THIS(0x431A30); }

protected:
	explicit __forceinline BufferIOFileClass(noinit_t)
		: RawFileClass(noinit_t())
	{ }

	//Properties

public:
	bool IsAllocated;
	bool IsOpen;
	bool IsDiskOpen;
	bool IsCached;
	bool IsChanged;
	bool UseBuffer;
	DWORD BufferRights;
	DWORD BufferPtr;
	DWORD BufferedSize;
	DWORD BufferPos;
	DWORD BufferFilePos;
	DWORD BufferChangeBeg;
	DWORD BufferChangeEnd;
	DWORD FileSize;
	DWORD FilePos;
	DWORD TrueFileStart;
};

//--------------------------------------------------------------------
//Files on a CD?
//--------------------------------------------------------------------
class NOVTABLE CDFileClass : public BufferIOFileClass
{
public:
	//Destructor
	virtual ~CDFileClass() { JMP_THIS(0x535A60); }
	//FileClass
	virtual const char* GetFileName() const override R0;
	virtual const char* SetFileName(const char* pFileName) override { JMP_THIS(0x47AE10); }
	virtual BOOL CreateFile() override R0;
	virtual BOOL DeleteFile() override R0;
	virtual bool Exists(bool writeShared = false) override R0;
	virtual bool HasHandle() override R0;
	virtual bool Open(FileAccessMode access) override { JMP_THIS(0x47AAB0); }
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override { JMP_THIS(0x47AF10); }
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override R0;
	virtual off_t Seek(off_t offset, FileSeekMode seek) override R0;
	virtual off_t GetFileSize() override R0;
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override R0;
	virtual void Close() override RX;
	virtual LONG GetFileTime() override R0;
	virtual bool SetFileTime(LONG date_time) override R0;
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) override RX;

	static void __fastcall Refresh()
	{ JMP_STD(0x47AAC0); }

	static bool __fastcall SetPath(const char* pPath)
	{ JMP_STD(0x47AB10); }

	static void __fastcall AddPath(const char* pPath)
	{ JMP_STD(0x47AD50); }

	static void __fastcall SetCDDrive(int nDriveNumber)
	{ JMP_STD(0x47ADA0); }

	static HRESULT __fastcall Clear()
	{ JMP_STD(0x47ADA0); }

	//Constructor
	CDFileClass()
		: CDFileClass(noinit_t())
	{ JMP_THIS(0x47AA30); }

	CDFileClass(const char* pFilename)
		: CDFileClass(noinit_t())
	{ JMP_THIS(0x47A9D0); }

	CDFileClass(wchar_t* pWideFilename)
		: CDFileClass(noinit_t())
	{ JMP_THIS(0x47AA00); }

protected:
	explicit __forceinline CDFileClass(noinit_t)
		: BufferIOFileClass(noinit_t())
	{ }

	//Property

public:
	DWORD IsDisabled; //54
};

//--------------------------------------------------------------------
//Files in MIXes
//--------------------------------------------------------------------
class NOVTABLE CCFileClass : public CDFileClass
{
public:
	//Destructor
	virtual ~CCFileClass() { JMP_THIS(0x535A70); }

	//FileClass
	virtual const char* GetFileName() const override R0;
	virtual const char* SetFileName(const char* pFileName) override { JMP_THIS(0x473FC0); }
	virtual BOOL CreateFile() override R0;
	virtual BOOL DeleteFile() override R0;
	virtual bool Exists(bool writeShared = false) override { JMP_THIS(0x473C50); }
	virtual bool HasHandle() override { JMP_THIS(0x473CD0); }
	virtual bool Open(FileAccessMode access) override { JMP_THIS(0x473D10); }
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override { JMP_THIS(0x401980); }
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x473B10); }
	virtual off_t Seek(off_t offset, FileSeekMode seek) override { JMP_THIS(0x473BA0); }
	virtual off_t GetFileSize() override { JMP_THIS(0x473C00); }
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x473AE0); }
	virtual void Close() override { JMP_THIS(0x473CE0); }
	virtual LONG GetFileTime() override { JMP_THIS(0x473E50); }
	virtual bool SetFileTime(LONG date_time) override { JMP_THIS(0x473F00); }
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) override { JMP_THIS(0x473AB0); }

	//Constructor
	CCFileClass(const char* pFileName)
		: CCFileClass(noinit_t())
	{ JMP_THIS(0x4739F0); }

	CCFileClass()
		: CCFileClass(noinit_t())
	{ JMP_THIS(0x473A80); }

	CCFileClass(wchar_t* pWideName)
		: CCFileClass(noinit_t())
	{ JMP_THIS(0x473A30); }

protected:
	explicit __forceinline CCFileClass(noinit_t)
		: CDFileClass(noinit_t())
	{ }

	//Properties
public:
	MemoryBuffer Buffer;
	DWORD Position;	// unknown_64;
	DWORD Availablility;	// unknown_68;
};
static_assert(sizeof(CCFileClass) == 0x6C);

//--------------------------------------------------------------------
//Files in RAM
//--------------------------------------------------------------------
class RAMFileClass : public FileClass
{
public:
	virtual ~RAMFileClass() { JMP_THIS(0x65C2A0); }

	virtual const char* GetFileName() const override { JMP_THIS(0x65C550); }
	virtual const char* SetFileName(const char* pFileName) override { JMP_THIS(0x65C560); }
	virtual BOOL CreateFile() override { JMP_THIS(0x65C2E0); }
	virtual BOOL DeleteFile() override { JMP_THIS(0x65C300); }
	virtual bool Exists(bool writeShared = false) override { JMP_THIS(0x65C320); }
	virtual bool HasHandle() override { JMP_THIS(0x65C330); }
	virtual bool Open(FileAccessMode access) override { JMP_THIS(0x65C350); };
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override { JMP_THIS(0x65C340); }
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x65C3A0); }
	virtual off_t Seek(off_t offset, FileSeekMode seek) override { JMP_THIS(0x65C420); }
	virtual off_t GetFileSize() override { JMP_THIS(0x65C4A0); }
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override { JMP_THIS(0x65C4B0); }
	virtual void Close() override { JMP_THIS(0x65C540); }
	virtual LONG GetFileTime() override { JMP_THIS(0x65C570); }
	virtual bool SetFileTime(LONG date_time) override { JMP_THIS(0x65C580); }
	virtual void Error(FileErrorType error, bool can_retry = false, const char *filename = nullptr) override { JMP_THIS(0x65C590); }

	//Constructor
	RAMFileClass(void* pData, size_t nSize)
		: RAMFileClass(noinit_t())
	{ JMP_THIS(0x65C250); }

protected:
	explicit __forceinline RAMFileClass(noinit_t)
		: FileClass(noinit_t())
	{ }

private:
	char* Buffer;
	int MaxLength;
	int Length;
	int Offset;
	FileAccessType Access;
	bool IsOpen;
	bool IsAllocated;
};
