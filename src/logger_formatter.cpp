#include "logger_formatter.hpp"
#include "logger_record.hpp"

namespace logger {
	FormatterPtr CreateFormatter() {
		auto res = Formatter::Create();

		return res;
	}

	FormatterPtr Formatter::Create() {
		class MakeSharedEnabler : public Formatter {};

		auto res = std::make_shared<MakeSharedEnabler>();

		return res;
	}
	FormatterPtr Formatter::GetPtr() {
		return this->shared_from_this();
	}
	ConstFormatterPtr Formatter::GetPtr() const {
		return const_cast<Formatter*>(this)->GetPtr();
	}

	String Formatter::operator()(IRecordPtr record) const {
		return utils::string::Format("{}{}{}: {}\n", FormatDate(record->GetDate()), FormatHeader(record->GetHeader()), FormatSeverity(record->GetSeverity()), record->GetMessage());
	}
	String Formatter::FormatDate(const Date& date) const {
		return utils::string::Format("[{:4}/{:2}/{:2} {:2}:{:2}:{:06.3f}]", date.years, date.months, date.days, date.hours, date.minutes, date.seconds);
	}
	String Formatter::FormatHeader(const String& header) const {
		return utils::string::Format("[{}]", header);
	}
	String Formatter::FormatSeverity(const Severity& severity) const {
		return utils::string::Format("[{}]", severityText[severity]);
	}

	IFormatterPtr GetDefaultFormatter() {
		static auto res = CreateFormatter();
		return res;
	}
}