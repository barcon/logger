#include "logger_base.hpp"

namespace logger {
	Ptr Create(sink::Ptr sink){
		auto res = Base::Create();
		
		res->AddSink(sink);

		return res;
	}

    Ptr Base::Create() {
      class MakeSharedEnabler: public Base {};

      auto res = std::make_shared < MakeSharedEnabler > ();
	  
      return res;
    }
    Ptr Base::GetPtr() {
      return this->shared_from_this();
    }
    ConstPtr Base::GetPtr() const {
      return const_cast < Base * > (this)->GetPtr();
    }	

	void Base::Log(const Severity& severity, const String& header, const String& message) {
		auto event = record::Create(severity, header, message);	
		
		for(auto it: sinks_){
			it->Write(event);
		}
	}
	void Base::AddSink(sink::Ptr sink) {
		if(sink != nullptr) {
			sinks_.push_back(sink);
		}
	}
	
	Ptr GetDefault(){
		static auto res = Create(sink::GetDefault());
		return res;
	}
	

	
	/*void Trace(const String& header, const String& message) {
		GetDefault()->Log(logger::Severity::Trace, header, message);
	};
	void Warning(const String& header, const String& message) {
		GetDefault()->Log(logger::Severity::Warning, header, message);
	};
	void Debug(const String& header, const String& message) {
		GetDefault()->Log(logger::Severity::Debug, header, message);
	};
	void Error(const String& header, const String& message) {
		GetDefault()->Log(logger::Severity::Error, header, message);
	};	
	void Fatal(const String& header, const String& message) {
		GetDefault()->Log(logger::Severity::Fatal, header, message);
	};	*/

}