#if !defined __TINYAN_FFT__
#define __TINYAN_FFT__

class CFFT
{
public:
	CFFT();
	~CFFT();
	void End(void);

	void MakeTable(int n);
	void Calcu(int n, float* ar,float* ai);

private:
	BOOL m_tableFlag[32];
	float* m_cossinTable[32];

	int n2r(int n);
};

#endif
/*_*/
