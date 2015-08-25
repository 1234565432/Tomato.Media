//
// Tomato Media
// Media Foundation PresentationTimeSource ʵ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-22
//
#pragma once
#include "common.h"
#include <mfidl.h>
#include <chrono>

DEFINE_NS_MEDIA

///<summary>Media Foundation PresentationTimeSource ʵ��</summary>
class MFPresentationTimeSource final : public WRL::RuntimeClass<WRL::RuntimeClassFlags<
	WRL::ClassicCom>, IMFPresentationTimeSource>
{
public:
	MFPresentationTimeSource();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP GetClockCharacteristics(DWORD * pdwCharacteristics) override;
	STDMETHODIMP GetCorrelatedTime(DWORD dwReserved, LONGLONG * pllClockTime, MFTIME * phnsSystemTime) override;
	STDMETHODIMP GetContinuityKey(DWORD * pdwContinuityKey) override;
	STDMETHODIMP GetState(DWORD dwReserved, MFCLOCK_STATE * peClockState) override;
	STDMETHODIMP GetProperties(MFCLOCK_PROPERTIES * pClockProperties) override;
	STDMETHODIMP GetUnderlyingClock(IMFClock ** ppClock) override;
private:
};

END_NS_MEDIA