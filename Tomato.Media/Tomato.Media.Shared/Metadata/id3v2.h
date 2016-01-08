//
// Tomato Media
// ID3v2 ������Ϣ
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-04-03
#pragma once
#include "MediaMetadata.h"
#include "ID3V2Frame.h"
#include <ppltasks.h>
#include <mfidl.h>

DEFINE_NS_MEDIA_INTERN

///<summary>ID3v2 ��־</summary>
enum class ID3V2Flags : byte
{
	// Unsynchronisation
	Unsynchronisation = 1 << 7,
	// ��չͷ��
	ExtendedHeader = 1 << 6,
	// ������;
	Experimental = 1 << 5
};

DEFINE_ENUM_FLAG_OPERATORS(ID3V2Flags);

///<summary>ID3v2.3 ������Ϣ</summary>
class ID3V2Meta
{
public:
	ID3V2Meta();

	///<summary>�Ƿ��ȡ�ɹ�</summary>
	bool IsGood() const noexcept;
	///<summary>��ȡ������Ϣ</summary>
	///<param name="framePredicate">�����֡����</param>
	///<return>�Ƿ��ȡ�ɹ�</return>
	concurrency::task<bool> Read(IMFByteStream* byteStream, const std::function<bool(const ID3V2FrameKind&)>& framePredicate = [](const ID3V2FrameKind&) {return true; });
	///<summary>��ȡ����������Ϣ</summary>
	static concurrency::task<bool> ReadBriefMetadata(IMFByteStream* byteStream, std::shared_ptr<MediaMetadataContainer> container);
	///<summary>��ȡ���⸽����Ϣ</summary>
	static concurrency::task<bool> ReadExtraMetadata(IMFByteStream* byteStream, std::shared_ptr<MediaMetadataContainer> container);

	template<class T>
	const T* GetFrame(const ID3V2FrameKind& kind) const noexcept
	{
		static_assert(std::is_base_of<ID3V2Frame, T>::value, "T ������֡���͡�");

		auto it = frames.find(kind);
		if (it != frames.end())
			return (T*)it->second.get();
		return nullptr;
	}

	template<class T>
	void ForEachFrame(const ID3V2FrameKind& kind, std::function<bool(const T*)> handler) const
	{
		static_assert(std::is_base_of<ID3V2Frame, T>::value, "T ������֡���͡�");

		auto matches = frames.equal_range(kind);
		for (auto it = matches.first; it != matches.second; ++it)
		{
			if (handler((T*)it->second.get()))
				break;
		}
	}

	template<class T>
	void ForEachFrame(const ID3V2FrameKind& kind, std::function<bool(T*)> handler)
	{
		static_assert(std::is_base_of<ID3V2Frame, T>::value, "T ������֡���͡�");

		auto matches = frames.equal_range(kind);
		for (auto it = matches.first; it != matches.second; ++it)
		{
			if (handler((T*)it->second.get()))
				break;
		}
	}

	const ID3V2FrameSingleText* GetSingleTextFrame(const ID3V2FrameKind& kind) const noexcept
	{
		return GetFrame<ID3V2FrameSingleText>(kind);
	}

	std::wstring GetTextOrEmpty(const ID3V2FrameKind& kind)
	{
		auto frame = GetSingleTextFrame(kind);
		if (frame)
			return frame->GetText();
		return std::wstring();
	}
private:
	///<summary>��ȡ֡</summary>
	///<return>�Ƿ����</return>
	bool ReadFrame(Core::BinaryReader<byte*>& reader, const std::function<bool(const ID3V2FrameKind&)>& framePredicate);
private:
	bool valid;						// ��ȡ�ɹ�
	byte reversion;					// �޶��汾��
	ID3V2Flags flags;				// ��־
	uint32_t restLength;			// ͷ�����ⳤ��
	std::unordered_multimap<ID3V2FrameKind, std::unique_ptr<ID3V2Frame>> frames;	// ֡
};

END_NS_MEDIA_INTERN