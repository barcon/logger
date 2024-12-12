#ifndef LOGGER_RECORD_HPP_
#define LOGGER_RECORD_HPP_

#include "logger_types.hpp"

namespace logger{
	namespace record{
		Ptr Create(const Severity& severity, const String& header, const String& message);
		
		class Base : public std::enable_shared_from_this<Base> {
		public:
			virtual ~Base() = default;

			static Ptr Create(const Severity& severity, const String& header, const String& message);
			Ptr GetPtr();
			ConstPtr GetPtr() const;
			
			const String& GetHeader() const;
			const Date& GetDate() const;
			const Severity& GetSeverity() const;
			const String& GetMessage() const;
			const ThreadID& GetThreadID() const;

		protected:
			Base() = default;
			
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
}

#endif