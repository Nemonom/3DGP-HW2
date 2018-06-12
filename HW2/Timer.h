#pragma once
const ULONG MAX_SAMPLE_COUNT = 50;

class CGameTimer
{
public:
	CGameTimer();
	~CGameTimer();

	void Tick(float fLockFPS = 0.0f);// �������Ӹ��� ȣ��
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0)const;
	float GetTimeElapsed()const;
	float GetTotalTime()const;

	//�������̳�..ȣȣ.
	void Start();//�޽��� ���� ������ ȣ��
	void Stop();//Ÿ�̸Ӹ� ���� �Ǵ� �簳�Ҷ� ȣ��.
	void Reset();//�޽��� ���� ������ ȣ���ؾ���

private:
	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale;
	float m_fTimeElapsed;

	__int64 m_nCurrentTime;
	__int64 m_nLastTime;

	//�������̳�..ȣȣ.
	__int64 m_nBaseTime;
	__int64 m_nPausedTime;
	__int64 m_nStopTime;

	bool m_bStopped;
	//�������̳�..ȣȣ.

	__int64 m_nPerformanceFrequency;

	float m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG m_nSampleCount;

	unsigned long m_nCurrentFrameRate;
	unsigned long m_nFramesPerSecond;
	float m_fFPSTimeElapsed;
};

