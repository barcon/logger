#ifndef LOGGER_SINK_HPP_
#define LOGGER_SINK_HPP_

#include "logger_types.hpp"

namespace logger{
	class ISink {
	public:
		virtual ~ISink() = default;

		virtual void Write(IRecordPtr record) = 0;
		virtual void SetFormatter(IFormatterPtr formatter) = 0;
	};

	StdOutSinkPtr CreateStdOutSink(IFormatterPtr formatter);

	class StdOutSink : public ISink, public std::enable_shared_from_this<StdOutSink> {
	public:
		virtual ~StdOutSink() = default;

		static StdOutSinkPtr Create();
		StdOutSinkPtr GetPtr();
		ConstStdOutSinkPtr GetPtr() const;

		void Write(IRecordPtr record) override;
		void SetFormatter(IFormatterPtr formatter) override;

	protected:
		StdOutSink() = default;

		IFormatterPtr formatter_{ nullptr };
	};

	ISinkPtr GetDefaultSink();
}

#endif