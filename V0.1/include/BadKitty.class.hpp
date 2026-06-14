#include "Core.class.hpp"

typedef struct {
	std::string output_file = "a.out";
}	t_options;

class BadKitty
{
	private:
		BadKitty() {};
		~BadKitty() {};

		static std::string transpile(const std::vector<t_code> &code);

		//built-ins implementation
		static std::string println(const std::vector<std::string> &args);
		static std::string print(const std::vector<std::string> &args);
		static std::string eprintln(const std::vector<std::string> &args);
		static std::string eprint(const std::vector<std::string> &args);
	public:
		static bool	compile(const std::vector<std::string> &source_files, const t_options &options = {});
};
