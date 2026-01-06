#include "logger_base.hpp"

namespace logger {
	LoggerPtr CreateLogger(ISinkPtr sink){
		auto res = Logger::Create();
		
		res->AddSink(sink);

		return res;
	}

    LoggerPtr Logger::Create() {
      class MakeSharedEnabler: public Logger {};

      auto res = std::make_shared < MakeSharedEnabler > ();
	  
      return res;
    }
	LoggerPtr Logger::GetPtr() {
      return this->shared_from_this();
    }
    ConstLoggerPtr Logger::GetPtr() const {
      return const_cast<Logger*>(this)->GetPtr();
    }	

	void Logger::Log(const Severity& severity, const String& header, const String& message) const {
		auto record = CreateRecord(severity, header, message);	
		
		for(auto& it: sinks_){
			it->Write(record);
		}
	}
	void Logger::AddSink(ISinkPtr sink) {
		if(sink != nullptr) {
			sinks_.push_back(sink);
		}
	}
	
	ILoggerPtr GetDefaultLogger(){
		static auto res = CreateLogger(GetDefaultSink());
		return res;
	}
}