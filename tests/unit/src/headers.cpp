#include <tst/set.hpp>
#include <tst/check.hpp>

#include <httpmodel/headers.hpp>

using namespace std::string_view_literals;

namespace{
tst::set set("http__headers", [](tst::suite& suite){
    suite.add(
        "put_get",
        [](){
            httpmodel::headers h;

            h.put("Host", "blabla.com");

            tst::check(h.get("Host"), SL);
        }
    );

    suite.add<std::pair<httpmodel::header, std::string_view>>(
        "header_to_string_mapping",
        {
            {httpmodel::header::host, "Host"},
            {httpmodel::header::accept, "Accept"},
            {httpmodel::header::content_length, "Content-Length"},
            {httpmodel::header::connection, "Connection"sv}
        },
        [](const auto& p){
            auto str = httpmodel::to_string(p.first);
            tst::check_eq(str, p.second, SL);
        }
    );
});
}