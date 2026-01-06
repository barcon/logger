#ifndef LOGGER_FORMATTER_HPP_
#define LOGGER_FORMATTER_HPP_

#include "logger_types.hpp"
#include <vector>

namespace logger{
	static const std::vector<String> severityText{ "INFO", "TRACE", "WARN", "DEBUG", "ERROR", "FATAL" };

	class IFormatter {
	public:
		virtual ~IFormatter() = default;

		virtual String operator()(IRecordPtr record) const = 0;
	};

	FormatterPtr CreateFormatter();

	class Formatter : public IFormatter, public std::enable_shared_from_this<Formatter> {
	public:
		virtual ~Formatter() = default;

		static FormatterPtr Create();
		FormatterPtr GetPtr();
		ConstFormatterPtr GetPtr() const;

		String operator()(IRecordPtr record) const override;

	protected:
		Formatter() = default;

		String FormatDate(const Date& date) const;
		String FormatHeader(const String& header) const;
		String FormatSeverity(const Severity& severity) const;
	};

	IFormatterPtr GetDefaultFormatter();
}

#endif