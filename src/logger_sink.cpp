#include "logger_sink.hpp"
#include "logger_formatter.hpp"
#include "logger_record.hpp"

#include <syncstream>

namespace logger {

	StdOutSinkPtr CreateStdOutSink(IFormatterPtr formatter) {
		auto res = StdOutSink::Create();

		res->SetFormatter(formatter);

		return res;
	}

	StdOutSinkPtr StdOutSink::Create() {
		class MakeSharedEnabler : public StdOutSink {};

		auto res = std::make_shared < MakeSharedEnabler >();

		return res;
	}
	StdOutSinkPtr StdOutSink::GetPtr() {
		return this->shared_from_this();
	}
	ConstStdOutSinkPtr StdOutSink::GetPtr() const {
		return const_cast <StdOutSink*> (this)->GetPtr();
	}

	void StdOutSink::Write(IRecordPtr record) {
		std::osyncstream(std::cout) << (*formatter_)(record);
	}
	void StdOutSink::SetFormatter(IFormatterPtr formatter) {
		if(!formatter)
		{
			throw std::runtime_error("Formatter is nullptr");
		}

		formatter_ = formatter;
	}

	ISinkPtr GetDefaultSink() {
		static auto res = CreateStdOutSink(GetDefaultFormatter());
		return res;
	}
}