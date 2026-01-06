#ifndef LOGGER_RECORD_HPP_
#define LOGGER_RECORD_HPP_

#include "logger_types.hpp"

namespace logger{
	class IRecord {
	public:
		virtual ~IRecord() = default;

		virtual const String& GetHeader() const = 0;
		virtual const Date& GetDate() const = 0;
		virtual const Severity& GetSeverity() const = 0;
		virtual const String & GetMessage() const = 0;
		virtual const ThreadID& GetThreadID() const = 0;
	};

	RecordPtr CreateRecord(const Severity& severity, const String& header, const String& message);

	class Record : public IRecord, public std::enable_shared_from_this<Record> {
	public:
		virtual ~Record() = default;

		static RecordPtr Create(const Severity& severity, const String& header, const String& message);
		RecordPtr GetPtr();
		ConstRecordPtr GetPtr() const;

		const String& GetHeader() const override;
		const Date& GetDate() const override;
		const Severity& GetSeverity() const override;
		const String& GetMessage() const override;
		const ThreadID& GetThreadID() const override;

	protected:
		Record() = default;

		void SetHeader(const String& header);
		void SetDate();
		void SetSeverity(const Severity& severity);
		void SetMessage(const String& message);
		void SetThreadID();

		String header_{};
		Date date_{};
		Severity severity_{};
		String message_{};
		ThreadID threadID_{};
	};
}

#endif