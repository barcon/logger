#ifndef LOGGER_BASE_HPP_
#define LOGGER_BASE_HPP_

#include "logger_types.hpp"
#include "logger_formatter.hpp"
#include "logger_sink.hpp"
#include "logger_record.hpp"

namespace logger
{
	class ILogger {
	public:
		virtual ~ILogger() = default;

		virtual void Log(const Severity& severity, const String& header, const String& message) const = 0;
		virtual void AddSink(ISinkPtr sink) = 0;
	};

	LoggerPtr CreateLogger(ISinkPtr sink);
		
	class Logger : public ILogger, public std::enable_shared_from_this<Logger>
	{
	public:
		virtual ~Logger() = default;

		static LoggerPtr Create();
		LoggerPtr GetPtr();
		ConstLoggerPtr GetPtr() const;
			
		void Log(const Severity& severity, const String& header, const String& message) const override;
		void AddSink(ISinkPtr sink) override;
			
	protected:
		Logger() = default;

		Sinks sinks_;
	};
		
	ILoggerPtr GetDefaultLogger();

	template<typename... Args> void Info(const String& header, const String& message) {
		GetDefaultLogger()->Log(severity_info, header, message);
	};	
	template<typename... Args> void Trace(const String& header, const String& message) {
		GetDefaultLogger()->Log(severity_trace, header, message);
	};	
	template<typename... Args> void Warning(const String& header, const String& message, Args... args) {
		GetDefaultLogger()->Log(severity_warning, header, message);
	};
	template<typename... Args> void Debug(const String& header, const String& message, Args... args) {
		GetDefaultLogger()->Log(severity_debug, header, message);
	};	
	template<typename... Args> void Error(const String& header, const String& message, Args... args) {
		GetDefaultLogger()->Log(severity_error, header, message);
	};	
	template<typename... Args> void Fatal(const String& header, const String& message, Args... args) {
		GetDefaultLogger()->Log(severity_fatal, header, message);
	};	
}

#endif

//utils::string::Format(message, args...)