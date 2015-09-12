//
// Tomato Media Codec
// Codec ������
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-06
#include "pch.h"
#include "CodecManager.h"
#include "ByteStreamHandlers/OggByteStreamHandler.h"
#include "Transforms/TheoraDecoderTransform.h"

using namespace NS_MEDIA_CODEC;
using namespace WRL;
using namespace Windows::Foundation;

ActivatableClass(CodecManager);

HRESULT CodecManager::RuntimeClassInitialize()
{
	try
	{
		Wrappers::HStringReference mediaExtensionManagerClassName(RuntimeClass_Windows_Media_MediaExtensionManager);
		ThrowIfFailed(ActivateInstance(mediaExtensionManagerClassName.Get(), &mediaExtensionManager));
	}
	CATCH_ALL();
	return S_OK;
}

template<class T>
void RegisterByteStreamHandler(ABI::Windows::Media::IMediaExtensionManager* mediaExtensionManager)
{
	Wrappers::HStringReference className(T::InternalGetRuntimeClassName());
	for (auto&& item : T::RegisterInfos)
	{
		Wrappers::HStringReference fileExtension(item.FileExtension);
		Wrappers::HStringReference mimeType(item.MimeType);

		ThrowIfFailed(mediaExtensionManager->RegisterByteStreamHandler(className.Get(),
			fileExtension.Get(), mimeType.Get()));
	}
}

template<class T>
void RegisterVideoDecoderTransform(ABI::Windows::Media::IMediaExtensionManager* mediaExtensionManager)
{
	Wrappers::HStringReference className(T::InternalGetRuntimeClassName());
	for (auto&& item : T::RegisterInfos)
	{
		ThrowIfFailed(mediaExtensionManager->RegisterVideoDecoder(className.Get(),
			item.InputSubType, item.OutputSubType));
	}
}

HRESULT CodecManager::RegisterDefaultCodecs(void)
{
	try
	{
		RegisterByteStreamHandler<OggByteStreamHandler>(mediaExtensionManager.Get());
		RegisterVideoDecoderTransform<TheoraDecoderTransform>(mediaExtensionManager.Get());
	}
	CATCH_ALL();
	return S_OK;
}
