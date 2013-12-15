#include "HTimer.h"

HTimer::HTimer()
{
}
void HTimer::Start(){
	m_Start = clock();
}
double HTimer::Stop(){
	m_End = clock();
	m_ElapsedTime = (m_End - m_Start)/(CLOCKS_PER_SEC*0.001);
	return m_ElapsedTime;
}
double HTimer::GetElapsedTime()
{
	return m_ElapsedTime;
}
