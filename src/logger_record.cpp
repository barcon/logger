#include "logger_record.hpp"

namespace logger {
	RecordPtr CreateRecord(const Severity& severity, const String& header, const String& message) {
		auto res = Record::Create(severity, header, message);

		return res;
	}

	RecordPtr Record::Create(const Severity& severity, const String& header, const String& message) {
		class MakeSharedEnabler : public Record {};

		auto res = std::make_shared < MakeSharedEnabler >();

		res->SetDate();
		res->SetHeader(header);
		res->SetSeverity(severity);
		res->SetMessage(message);
		res->SetThreadID();

		return res;
	}
	RecordPtr Record::GetPtr() {
		return this->shared_from_this();
	}
	ConstRecordPtr Record::GetPtr() const {
		return const_cast <Record*> (this)->GetPtr();
	}

	const String& Record::GetHeader() const {
		return header_;
	}
	const Date& Record::GetDate() const {
		return date_;
	}
	const Severity& Record::GetSeverity() const {
		return severity_;
	}
	const String& Record::GetMessage() const {
		return message_;
	}
	const ThreadID& Record::GetThreadID() const {
		return threadID_;
	}

	void Record::SetHeader(const String& header) {
		header_ = header;
	}
	void Record::SetDate() {
		date_ = utils::GetDate();
	}
	void Record::SetSeverity(const Severity& severity) {
		severity_ = severity;
	}
	void Record::SetMessage(const String& message) {
		message_ = message;
	}
	void Record::SetThreadID() {
		threadID_ = std::this_thread::get_id();
	}
}