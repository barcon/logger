#include "logger_formatter.hpp"
#include "logger_record.hpp"

namespace logger {
  namespace formatter {

    BasicPtr CreateBasic() {
      auto res = Basic::Create();
	
      return res;
    }

    BasicPtr Basic::Create() {
      class MakeSharedEnabler: public Basic {};

      auto res = std::make_shared < MakeSharedEnabler > ();
	  
      return res;
    }
    BasicPtr Basic::GetPtr() {
      return this->shared_from_this();
    }
    ConstBasicPtr Basic::GetPtr() const {
      return const_cast<Basic*>(this)->GetPtr();
    }
	
	String Basic::operator()(record::ConstPtr record) const{
		String str1 = FormatDate(record->GetDate());
		String str2 = FormatHeader(record->GetHeader());
		String str3 = FormatSeverity(record->GetSeverity());
		String str4 = FormatMessage(record->GetMessage());	

		return str1 + str2 + str3 + str4;
	}
	
	String Basic::FormatDate(const Date& date) const{
		String res;
		
		res = utils::string::Format("[%04d/%02d/%02d %02d:%02d:%06.3f]", date.years, date.months, date.days, date.hours, date.minutes, date.seconds);

		return res;
	}
	String Basic::FormatHeader(const String& header) const{
		String res = "["+ header + "]";	
		
		return res;
	}
	String Basic::FormatSeverity(const Severity& severity) const{		
		std::size_t index = static_cast<std::size_t>(severity);
		
		String res = "["+ severityText[index] + "]";	
		
		return res;
	}
	String Basic::FormatMessage(const String& message) const{
		String res;
		
		res += " " + message + "\n";
		return res;
	}
	
	Ptr GetDefault(){
		static auto res = CreateBasic();
		return res;
	}
  }
}