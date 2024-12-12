#ifndef LOGGER_TYPES_HPP_
#define LOGGER_TYPES_HPP_

#include "utils.hpp"
#include <memory>
#include <thread>

namespace logger
{
	using Date = utils::Date;
	using String = utils::String;
	using ThreadID = std::thread::id;

	enum class Severity
	{
		Info = 0,
		Trace = 1,
		Warning = 2,
		Debug = 3,
		Error = 4,
		Fatal = 5	
	};

	class Base;
	using Ptr = std::shared_ptr<Base>;
	using ConstPtr = std::shared_ptr<const Base>;
	
	namespace formatter
	{
		class Base;
		using Ptr = std::shared_ptr<Base>;
		using ConstPtr = std::shared_ptr<const Base>;
		
		class Basic;
		using BasicPtr = std::shared_ptr<Basic>;
		using ConstBasicPtr = std::shared_ptr<const Basic>;
	}

	namespace record
	{
		class Base;
		using Ptr = std::shared_ptr<Base>;
		using ConstPtr = std::shared_ptr<const Base>;
	}

	namespace sink
	{
		class Base;
		using Ptr = std::shared_ptr<Base>;
		using ConstPtr = std::shared_ptr<const Base>;
		
		class StdOut;
		using StdOutPtr = std::shared_ptr<StdOut>;
		using ConstStdOutPtr = std::shared_ptr<const StdOut>;
	}
	
	using Sinks = std::vector<sink::Ptr>;
}

#endif