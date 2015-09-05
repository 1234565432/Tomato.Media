//
// Tomato Media Core
// ��־����
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#pragma once
#include "common.h"
#include "IAppender.h"
#include <vector>

DEFINE_NS_CORE_INTERN

// ��־����
class LoggingConfiguration
{
public:
	LoggingConfiguration(){}

	static LoggingConfiguration& Current();

	LoggingConfiguration(LoggingConfiguration&) = delete;
	LoggingConfiguration& operator=(LoggingConfiguration&) = delete;

	const std::vector<std::shared_ptr<IAppender>> GetAppenders() const noexcept { return appenders; }
	void AddAppender(std::shared_ptr<IAppender>&& appender);
private:
	std::vector<std::shared_ptr<IAppender>> appenders;
};

END_NS_CORE_INTERN