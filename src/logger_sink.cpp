#include "logger_sink.hpp"
#include "logger_formatter.hpp"
#include "logger_record.hpp"

namespace logger {
  namespace sink {
	
	std::mutex StdOut::mutex_{};	
	
	StdOutPtr CreateStdOut(formatter::ConstPtr formatter){
		auto res = StdOut::Create();
		
		res->SetFormatter(formatter);

		return res;
	}

    StdOutPtr StdOut::Create() {
      class MakeSharedEnabler: public StdOut {};

      auto res = std::make_shared < MakeSharedEnabler > ();
	  
      return res;
    }
    StdOutPtr StdOut::GetPtr() {
      return this->shared_from_this();
    }
    ConstStdOutPtr StdOut::GetPtr() const {
      return const_cast < StdOut * > (this)->GetPtr();
    }
	
	void StdOut::Write(record::ConstPtr record){
		String output;
		
		std::lock_guard<std::mutex> lock(mutex_);
		output = (*formatter_)(record);
		std::cout << output << std::flush;
	}
	void StdOut::SetFormatter(formatter::ConstPtr formatter){		
		if(formatter != nullptr){
			std::lock_guard<std::mutex> lock(mutex_);
			formatter_ = formatter;
		}
	}
	
	Ptr GetDefault(){
		static auto res = CreateStdOut(formatter::GetDefault());
		return res;
	}
  
  }
}