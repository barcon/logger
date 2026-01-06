#include "logger_sink.hpp"
#include "logger_formatter.hpp"
#include "logger_record.hpp"

namespace logger {
	std::mutex StdOutSink::mutex_{};

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
		String output;

		std::lock_guard<std::mutex> lock(mutex_);
		output = (*formatter_)(record);

		std::cout << output << "\n";
	}
	void StdOutSink::SetFormatter(IFormatterPtr formatter) {
		if (formatter != nullptr) {
			std::lock_guard<std::mutex> lock(mutex_);
			formatter_ = formatter;
		}
	}

	ISinkPtr GetDefaultSink() {
		static auto res = CreateStdOutSink(GetDefaultFormatter());
		return res;
	}
}