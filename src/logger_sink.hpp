#ifndef LOGGER_SINK_HPP_
#define LOGGER_SINK_HPP_

#include "logger_types.hpp"
#include <mutex>

namespace logger{
	namespace sink{

		class Base{
		public:
			virtual ~Base() = default;

			virtual void Write(record::ConstPtr record) = 0;
			virtual void SetFormatter(formatter::ConstPtr formatter) = 0;
		protected:
			Base() = default;		
		};

		StdOutPtr CreateStdOut(formatter::ConstPtr formatter);
		
		class StdOut : public Base, public std::enable_shared_from_this<StdOut> {
		public:
			virtual ~StdOut() = default;
			
			static StdOutPtr Create();
			StdOutPtr GetPtr();
			ConstStdOutPtr GetPtr() const;

			void Write(record::ConstPtr record) override;
			void SetFormatter(formatter::ConstPtr formatter) override;
			
		protected:
			StdOut() = default;
			
			formatter::ConstPtr formatter_{nullptr};
			
			static std::mutex mutex_;
		};
		
		Ptr GetDefault();		
	}
}

#endif