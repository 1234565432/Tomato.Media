//
// Tomato Media Core
// ��־����
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#include "pch.h"
#include "LoggingConfiguration.h"
#include "DebuggerAppender.h"

using namespace NS_CORE_INTERN;

LoggingConfiguration & LoggingConfiguration::Current()
{
	struct defaultConfiguration
	{
		LoggingConfiguration Configuration;

		defaultConfiguration()
		{
			Configuration.AddAppender(std::make_shared<DebuggerAppender>());
		}
	};

	static defaultConfiguration defaultConfig;
	return defaultConfig.Configuration;
}

void LoggingConfiguration::AddAppender(std::shared_ptr<IAppender>&& appender)
{
	appenders.emplace_back(std::move(appender));
}
