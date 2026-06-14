#include "Core.structs.hpp"

class KitsuCore
{
	private:
		// Static class 
		KitsuCore() {};
		~KitsuCore() {};
		
		// Utils
		static std::vector<t_token>		tokenize(const std::string &source);
	public:
		static t_code					get_code(const std::string &source);
};
