//
// Tomato Media
// ���ɸ��ƻ���
// 
// ���ߣ�SunnyCase
// �������� 2015-08-16
#pragma once

struct TOMATO_CORE_API NonCopyable
{
	NonCopyable(){}
	NonCopyable(NonCopyable&) = delete;
	NonCopyable& operator=(NonCopyable&) = delete;
};