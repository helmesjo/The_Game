#pragma once

#include <ctime>

class HTimer
{
public:
	HTimer();

	void	Start();
	double	Stop();
	double	GetElapsedTime();

private:
	clock_t	m_Start;
	clock_t	m_End;
	double	m_ElapsedTime;
};