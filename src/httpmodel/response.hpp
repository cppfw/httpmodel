/*
MIT License

Copyright (c) 2023 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ================ LICENSE END ================ */

#pragma once

#include <vector>

#include "headers.hpp"
#include "http.hpp"
#include "request.hpp"

namespace httpmodel {

class response
{
public:
	explicit response() = default;

	response(const httpmodel::request& request);

	response(const httpmodel::request& request, httpmodel::status status);

	httpmodel::protocol protocol = httpmodel::protocol::http_1_0;

	httpmodel::status status = httpmodel::status::http_200_ok;

	std::string status_text;

	httpmodel::headers headers;

	std::vector<uint8_t> body;

	std::vector<uint8_t> to_bytes_no_body() const;

	std::vector<uint8_t> to_bytes() const;
};

} // namespace httpmodel
