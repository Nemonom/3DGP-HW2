#pragma once
const ULONG MAX_SAMPLE_COUNT = 50;

class CGameTimer
{
public:
	CGameTimer();
	~CGameTimer();

	void Tick(float fLockFPS = 0.0f);// 매프레임마다 호출
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0)const;
	float GetTimeElapsed()const;
	float GetTotalTime()const;

	//빼놓으셨네..호호.
	void Start();//메시지 루프 이전에 호출
	void Stop();//타이머를 시작 또는 재개할때 호출.
	void Reset();//메시지 루프 이전에 호출해야함

private:
	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale;
	float m_fTimeElapsed;

	__int64 m_nCurrentTime;
	__int64 m_nLastTime;

	//빼놓으셨네..호호.
	__int64 m_nBaseTime;
	__int64 m_nPausedTime;
	__int64 m_nStopTime;

	bool m_bStopped;
	//빼놓으셨네..호호.

	__int64 m_nPerformanceFrequency;

	float m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG m_nSampleCount;

	unsigned long m_nCurrentFrameRate;
	unsigned long m_nFramesPerSecond;
	float m_fFPSTimeElapsed;
};

