#ifndef LOGGER_BASE_HPP_
#define LOGGER_BASE_HPP_

#include "logger_types.hpp"
#include "logger_formatter.hpp"
#include "logger_sink.hpp"
#include "logger_record.hpp"

namespace logger
{
	Ptr Create(sink::Ptr sink);
		
	class Base : public std::enable_shared_from_this<Base> 
	{
	public:
		virtual ~Base() = default;

		static Ptr Create();
		Ptr GetPtr();
		ConstPtr GetPtr() const;
			
		void Log(const Severity& severity, const String& header, const String& message);
		void AddSink(sink::Ptr sink);
			
	protected:
		Base() = default;

		Sinks sinks_;
	};
		
	Ptr GetDefault();	

	template<typename... Args> void Info(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Info, header, utils::string::Format(message, args...));
	};	
	template<typename... Args> void Trace(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Trace, header, utils::string::Format(message, args...));
	};	
	template<typename... Args> void Warning(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Warning, header, utils::string::Format(message, args...));
	};
	template<typename... Args> void Debug(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Debug, header, utils::string::Format(message, args...));
	};	
	template<typename... Args> void Error(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Error, header, utils::string::Format(message, args...));
	};	
		template<typename... Args> void Fatal(const String& header, const String& message, Args... args) {
		GetDefault()->Log(logger::Severity::Fatal, header, utils::string::Format(message, args...));
	};	
}

#endif