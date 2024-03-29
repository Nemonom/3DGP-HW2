#include "stdafx.h"
#include "Timer.h"
#include <timeapi.h>

CGameTimer::CGameTimer()
{
	if (::QueryPerformanceFrequency((LARGE_INTEGER *)&m_nPerformanceFrequency))
	{
		m_bHardwareHasPerformanceCounter = TRUE;
		::QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);
		m_fTimeScale = 1.0 / m_nPerformanceFrequency;
	}
	else
	{
		m_bHardwareHasPerformanceCounter = FALSE;
		m_nLastTime = ::timeGetTime();
		m_fTimeScale = 0.001f;
	}

	m_nSampleCount = 0;
	m_nCurrentFrameRate = 0;
	m_nFramesPerSecond = 0;
	m_fFPSTimeElapsed = 0.0f;
}


CGameTimer::~CGameTimer()
{
}

void CGameTimer::Tick(float fLockFPS)
{
	if (m_bHardwareHasPerformanceCounter)
	{
		::QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrentTime);
	}
	else
	{
		m_nCurrentTime = ::timeGetTime();
	}

	//마지막으로 이 함수를 호출한 이후 경과한시간을 계산.
	float fTimeElapsed = (m_nCurrentTime - m_nLastTime)*m_fTimeScale;

	if (fLockFPS > 0.0f)
	{
		//이 함수의 파라메터(fLockFPS)가 0보다 크면 이 시간만큼 호출한 함수를 기다리게 한다. 
		while (fTimeElapsed < (1.f / fLockFPS))
		{
			if (m_bHardwareHasPerformanceCounter)
			{
				::QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrentTime);
			}
			else
			{
				m_nCurrentTime = ::timeGetTime();
			}
			//마지막으로 이 함수를 호출한 이후 경과한 시간을 계산한다.
			fTimeElapsed = (m_nCurrentTime - m_nLastTime)*m_fTimeScale;
		}

	}

	//현재 시간을 m_nLastTime에 저장한다. 
	m_nLastTime = m_nCurrentTime;

	/* 마지막 프레임 처리 시간과 현재 프레임 처리 시간의 차이가 1초보다 작으면
	현재 프레임 처리 시간을 m_fFrameTime[0]에 저장한다. */
	if (fabsf(fTimeElapsed - m_fTimeElapsed) < 1.f)
	{
		::memmove(&m_fFrameTime[1], m_fFrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		m_fFrameTime[0] = fTimeElapsed;
		if (m_nSampleCount < MAX_SAMPLE_COUNT)m_nSampleCount++;
	}

	//초당 프레임 수를 1 증가시키고 현재 프레임 처리 시간을 누적하여 저장한다.
	m_nFramesPerSecond++;
	m_fFPSTimeElapsed += fTimeElapsed;
	if (m_fFPSTimeElapsed > 1.f)
	{
		m_nCurrentFrameRate = m_nFramesPerSecond;
		m_nFramesPerSecond = 0;
		m_fFPSTimeElapsed = 0.0f;
	}

	//누적된 프레임 처리 시간의 평균을 구하여 프레임 처리 시간을 구한다
	m_fTimeElapsed = 0.0f;
	for (ULONG i = 0; i < m_nSampleCount; i++)m_fTimeElapsed += m_fFrameTime[i];
	if (m_nSampleCount > 0)m_fTimeElapsed /= m_nSampleCount;

}

unsigned long CGameTimer::GetFrameRate(LPTSTR lpszString, int nCharacters)const
{
	if (lpszString)
	{
		_itow_s(m_nCurrentFrameRate, lpszString, nCharacters, 10);
		wcscat_s(lpszString, nCharacters, _T(" FPS)"));
	}
	return m_nCurrentFrameRate;
}

float CGameTimer::GetTimeElapsed()const
{
	return m_fTimeElapsed;
}

float CGameTimer::GetTotalTime()const
{
	if (m_bStopped)
		return (float(((m_nStopTime - m_nPausedTime) - m_nBaseTime)*m_fTimeScale));
	return
		(float(((m_nCurrentTime - m_nPausedTime) - m_nBaseTime)*m_fTimeScale));
}

void CGameTimer::Start()
{
	__int64 nPerformanceCounter;
	::QueryPerformanceCounter((LARGE_INTEGER*)&nPerformanceCounter);

	if (m_bStopped)
	{
		m_nPausedTime += (nPerformanceCounter - m_nStopTime);
		m_nLastTime = nPerformanceCounter;
		m_nStopTime = 0;
		m_bStopped = false;
	}
}

void CGameTimer::Stop()
{
	if (!m_bStopped)
	{
		__int64 currTime;
		::QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_nStopTime = currTime;
		m_bStopped = true;
	}
}

void CGameTimer::Reset()
{
	__int64 nPerformanceCounter;
	::QueryPerformanceCounter((LARGE_INTEGER*)&nPerformanceCounter);

	m_nBaseTime = nPerformanceCounter;
	m_nLastTime = nPerformanceCounter;
	m_nStopTime = 0;
	m_bStopped = false;
}
