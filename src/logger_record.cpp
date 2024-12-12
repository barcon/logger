#include "logger_record.hpp"

namespace logger {
  namespace record {
	  
    Ptr Create(const Severity& severity, const String& header, const String& message) {
      auto res = Base::Create(severity, header, message);

      return res;
    }

    Ptr Base::Create(const Severity& severity, const String& header, const String& message) {
      class MakeSharedEnabler: public Base {};

      auto res = std::make_shared < MakeSharedEnabler > ();

	  res->SetDate();	  
	  res->SetHeader(header);
	  res->SetSeverity(severity);  
	  res->SetMessage(message);
	  res->SetThreadID();	  
	  
      return res;
    }
    Ptr Base::GetPtr() {
      return this->shared_from_this();
    }
    ConstPtr Base::GetPtr() const {
      return const_cast < Base * > (this)->GetPtr();
    }

	const String& Base::GetHeader() const{
		return header_;
	}
	const Date& Base::GetDate() const{
		return date_;
	}
	const Severity& Base::GetSeverity() const{
		return severity_;
	}
	const String& Base::GetMessage() const{
		return message_;
	}
	const ThreadID& Base::GetThreadID() const{
		return threadID_;
	}

	void Base::SetHeader(const String& header){
		header_ = header;
	}	
	void Base::SetDate(){
		date_ = utils::GetDate();
	}
	void Base::SetSeverity(const Severity& severity){
		severity_ = severity;
	}
	void Base::SetMessage(const String& message){
		message_ = message;
	}
	void Base::SetThreadID(){
		threadID_ = std::this_thread::get_id();
	}
 
  }
}