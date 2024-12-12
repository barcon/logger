#ifndef LOGGER_FORMATTER_HPP_
#define LOGGER_FORMATTER_HPP_

#include "logger_types.hpp"

#include <vector>

namespace logger{
	namespace formatter{
		
		static const std::vector<String> severityText{ "INFO", "TRACE", "WARN", "DEBUG", "ERROR", "FATAL" };
		
		class Base{
		public:
			virtual ~Base() = default;

			virtual String operator()(record::ConstPtr record) const = 0;	

		protected:
			Base() = default;		
		};

		BasicPtr CreateBasic();	

		class Basic : public Base, public std::enable_shared_from_this<Basic> {
		public:
			virtual ~Basic() = default;
			
			static BasicPtr Create();
			BasicPtr GetPtr();
			ConstBasicPtr GetPtr() const;

			String operator()(record::ConstPtr record) const override;			
			
		protected:
			Basic() = default;
			
			String FormatDate(const Date& date) const;
			String FormatHeader(const String& header) const;
			String FormatSeverity(const Severity& severity) const;
			String FormatMessage(const String& message) const;
			
			String separator_{" "};		
		};
		
		Ptr GetDefault();
	}
}

#endif