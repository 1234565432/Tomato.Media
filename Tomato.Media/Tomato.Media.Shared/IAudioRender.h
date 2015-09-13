//
// Tomato Media
// ��Ƶ��Ⱦ���ӿ�
// 
// ���ߣ�SunnyCase 
// �������� 2015-09-04
#pragma once
#include "common.h"
#include <ppltasks.h>
#include "../../include/MFWorkerQueueProvider.h"
#include <functional>

DEFINE_NS_MEDIA
///<summary>��Ƶ��Ⱦ���ӿ�</summary>
struct DECLSPEC_UUID("9DB108BD-070C-4D5D-8C46-25C3CD782488") IAudioRender : public IUnknown
{
	virtual concurrency::task<void> Initialize() = 0;
	virtual void SetWorkerQueueProvider(Core::MFWorkerQueueProviderRef workerQueue) = 0;
	virtual void SetIsActive(bool value) = 0;
	// �����ṩ�����Ļص�
	// �ص����ͣ�size_t(byte* buffer, size_t bytesToRead) ����ʵ�ʶ�ȡ���ֽ���
	// Ҫ�󣺷�����
	virtual void SetProvideSampleCallback(std::function<size_t(byte*, size_t)>&& callback) = 0;
};

END_NS_MEDIA

// {9DB108BD-070C-4D5D-8C46-25C3CD782488}
EXTERN_GUID(MF_TM_AUDIORENDER_SERVICE,
	0x9db108bd, 0x70c, 0x4d5d, 0x8c, 0x46, 0x25, 0xc3, 0xcd, 0x78, 0x24, 0x88);