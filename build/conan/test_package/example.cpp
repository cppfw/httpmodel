#include <httpmodel/request.hpp>

int main(int argc, const char** argv){
	httpmodel::request req;

	req.method = httpmodel::method::get;
	req.url.path.push_back("dir1");

	req.headers.put("hdr1", "val1");

	std::cout << "http headers = " << req.headers.get("hdr1").value() << std::endl;
}
