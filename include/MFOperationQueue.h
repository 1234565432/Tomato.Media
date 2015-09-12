//
// Tomato Music
// Media Foundation ��������
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2014-10-30
#pragma once
#include "common.h"
#include "WorkerQueueProvider.h"
#include <concurrent_queue.h>
#include <functional>
#include <atomic>

DEFINE_NS_CORE

// ��������
template<class TOperation>
// Media Foundation ��������
class MFOperationQueue final : public std::enable_shared_from_this<MFOperationQueue<TOperation>>
{
public:
	template<typename TDispatcher>
	MFOperationQueue(TDispatcher&& dispatcher)
		:dispatcher(std::forward<TDispatcher>(dispatcher))
	{

	}

	void SetWorkerQueue(WorkerQueueProvider& provider)
	{
		std::weak_ptr<MFOperationQueue> weak(shared_from_this());
		invoker = provider.CreateWorkerThread([weak]
		{
			if (auto me = weak.lock())
				me->OnProcessOperation();
		});
	}

	// �������
	template<class T>
	void Enqueue(T&& operation)
	{
		if (!invoker) ThrowIfFailed(E_NOT_VALID_STATE);
		operations.push(std::forward<T>(operation));
		ActiveInvoker();
	}
private:
	void OnProcessOperation()
	{
		try
		{
			TOperation operation;
			while (operations.try_pop(operation))
				dispatcher(operation);
			invokerActive.store(false, std::memory_order_release);
		}
		catch (...)
		{
			invokerActive.store(false, std::memory_order_release);
			throw;
		}
	}

	void ActiveInvoker()
	{
		bool expect = false;
		if (invokerActive.compare_exchange_strong(expect, true))
			invoker->Execute();
	}
private:
	std::shared_ptr<WorkerThread> invoker;
	std::function<void(TOperation&)> dispatcher;
	concurrency::concurrent_queue<TOperation> operations;
	std::atomic<bool> invokerActive = false;
};

END_NS_CORE