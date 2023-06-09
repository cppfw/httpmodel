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

#include "headers.hpp"

#include <array>

#include <utki/string.hpp>

using namespace httpmodel;

namespace {
const constexpr std::array<std::string_view, size_t(header::enum_size)> header_enum_to_string_mapping =
	{"Host", "Accept", "Content-Length", "Connection"};
} // namespace

std::string_view httpmodel::to_string(header h)
{
	ASSERT(size_t(h) < size_t(header::enum_size))
	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
	return header_enum_to_string_mapping[size_t(h)];
}

std::optional<std::string_view> headers::get(std::string_view name) const noexcept
{
	auto i = this->hdrs.find(name);
	if (i == this->hdrs.end()) {
		return {};
	}

	return utki::make_string_view(i->second);
}

std::optional<std::string_view> headers::get(header h) const noexcept
{
	return this->get(to_string(h));
}

void headers::put(std::string name, std::string value)
{
	this->hdrs.insert_or_assign(std::move(name), std::move(value));
}

void headers::put(header h, std::string value)
{
	this->put(std::string(to_string(h)), std::move(value));
}

void headers::append_to(std::vector<uint8_t>& buf) const
{
	for (const auto& h : this->hdrs) {
		std::copy(h.first.begin(), h.first.end(), std::back_inserter(buf));
		buf.push_back(':');
		buf.push_back(' ');
		std::copy(h.second.begin(), h.second.end(), std::back_inserter(buf));
		buf.push_back('\n');
	}
}
