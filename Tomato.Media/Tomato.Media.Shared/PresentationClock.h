//
// Tomato Media
// ����ʱ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-07
//
#pragma once
#include "common.h"
#include <mfidl.h>

DEFINE_NS_MEDIA

///<summary>����ʱ��</summary>
///<remarks>ʵ�� IUnknown ��������з�������֤�̰߳�ȫ��</remarks>
class PresentationClock : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::ClassicCom>, IMFPresentationClock>
{
public:
	PresentationClock();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP GetClockCharacteristics(DWORD * pdwCharacteristics) override;
	STDMETHODIMP GetCorrelatedTime(DWORD dwReserved, LONGLONG * pllClockTime, MFTIME * phnsSystemTime) override;
	STDMETHODIMP GetContinuityKey(DWORD * pdwContinuityKey) override;
	STDMETHODIMP GetState(DWORD dwReserved, MFCLOCK_STATE * peClockState) override;
	STDMETHODIMP GetProperties(MFCLOCK_PROPERTIES * pClockProperties) override;
	STDMETHODIMP SetTimeSource(IMFPresentationTimeSource * pTimeSource) override;
	STDMETHODIMP GetTimeSource(IMFPresentationTimeSource ** ppTimeSource) override;
	STDMETHODIMP GetTime(MFTIME * phnsClockTime) override;
	STDMETHODIMP AddClockStateSink(IMFClockStateSink * pStateSink) override;
	STDMETHODIMP RemoveClockStateSink(IMFClockStateSink * pStateSink) override;
	STDMETHODIMP Start(LONGLONG llClockStartOffset) override;
	STDMETHODIMP Stop(void) override;
	STDMETHODIMP Pause(void) override;
private:
	WRL::ComPtr<IMFClock> clock;
	WRL::ComPtr<IMFClockStateSink> clockStateSink;
	std::vector<WRL::ComPtr<IMFClockStateSink>> clockStateSinks;
	unsigned __int64 frequency = 0;
};

///<summary>������ high_resolution_clock Ϊ�ڲ� clock �ĳ���ʱ��</summary>
WRL::ComPtr<IMFPresentationClock> CreateHighResolutionPresentationClock();

END_NS_MEDIA