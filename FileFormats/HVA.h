#ifndef HVA_H_
#define HVA_H_

class CCFileClass;

class MotLib {
public:
	DWORD f_0;
	DWORD f_4;
	DWORD f_8;
	void* f_C;

	MotLib(CCFileClass *Source)
		JMP_THIS(0x5BD570);

	~MotLib()
		JMP_THIS(0x5BD5A0);

	signed int ReadFile(CCFileClass *ccFile)
		JMP_THIS(0x5BD5C0);
};

#endif
