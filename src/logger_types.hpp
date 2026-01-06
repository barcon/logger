#ifndef LOGGER_TYPES_HPP_
#define LOGGER_TYPES_HPP_

#include "utils.hpp"
#include <memory>
#include <thread>

namespace logger
{
	using Date = utils::Date;
	using String = utils::String;
	using ThreadID = std::thread::id;

	using Severity = std::size_t;
	static const Severity severity_info		= 0;
	static const Severity severity_trace	= 1;
	static const Severity severity_warning	= 2;
	static const Severity severity_debug	= 3;
	static const Severity severity_error	= 4;
	static const Severity severity_fatal	= 5;

	class ILogger;
	using ILoggerPtr = std::shared_ptr<ILogger>;
	using ConstILoggerPtr = std::shared_ptr<const ILogger>;
	
	class Logger;
	using LoggerPtr = std::shared_ptr<Logger>;
	using ConstLoggerPtr = std::shared_ptr<const Logger>;

	class IFormatter;
	using IFormatterPtr = std::shared_ptr<IFormatter>;
	using ConsIFormattertPtr = std::shared_ptr<const IFormatter>;

	class Formatter;
	using FormatterPtr = std::shared_ptr<Formatter>;
	using ConstFormatterPtr = std::shared_ptr<const Formatter>;

	class IRecord;
	using IRecordPtr = std::shared_ptr<IRecord>;
	using ConstIRecordPtr = std::shared_ptr<const IRecord>;

	class Record;
	using RecordPtr = std::shared_ptr<Record>;
	using ConstRecordPtr = std::shared_ptr<const Record>;

	class ISink;
	using ISinkPtr = std::shared_ptr<ISink>;
	using ConstISinkPtr = std::shared_ptr<const ISink>;

	class StdOutSink;
	using StdOutSinkPtr = std::shared_ptr<StdOutSink>;
	using ConstStdOutSinkPtr = std::shared_ptr<const StdOutSink>;
	
	using Sinks = std::vector<ISinkPtr>;
}

#endif