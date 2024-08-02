#include "file.hxx"

#include <format>
#include <fstream>
#include "excp.hxx"

using namespace std;

string Essentials::File::read(const filesystem::path& file)
{
	ifstream in;

	in.exceptions(ifstream::badbit | ifstream::failbit);

	try {
		in.open(file);

		return string{
			istreambuf_iterator<char>(in),
			istreambuf_iterator<char>()
		};
	}
	catch (ios_base::failure& ex) {
		throw Excp::RuntimeExcp{format("读文件 {} 失败：{}。", file.generic_string(), ex.what())};
	}
}
