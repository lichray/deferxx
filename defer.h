/*-
 * Copyright (c) 2012, 2014 Zhihao Yuan.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _STDEX_DEFER_H
#define _STDEX_DEFER_H

#include <utility>

#define defer(...)						\
	auto STDEX_NAMELNO__(_stdex_defer_, __LINE__) =		\
	stdex::make_guard([&]{ __VA_ARGS__; });
#define namely(name)						\
	; auto& name = STDEX_NAMELNO__(_stdex_defer_, __LINE__)
#define STDEX_NAMELNO__(name, lno)	STDEX_CAT__(name, lno)
#define STDEX_CAT__(a, b)		a ## b

namespace stdex
{

template <typename Func>
struct scope_guard
{
	explicit scope_guard(Func&& on_exit) :
		on_exit_(std::move(on_exit)),
		enabled_(true)
	{}

	scope_guard(scope_guard const&) = delete;
	scope_guard& operator=(scope_guard const&) = delete;

	scope_guard(scope_guard&& other) :
		on_exit_(std::move(other.on_exit_)),
		enabled_(other.enabled_)
	{
		other.enabled_ = false;
	}

	~scope_guard() noexcept
	{
		if (enabled_)
			on_exit_();
	}

	void dismiss()
	{
		enabled_ = false;
	}

private:
	Func on_exit_;
	bool enabled_;
};

template <typename Func>
auto make_guard(Func&& f) -> scope_guard<Func>
{
	return scope_guard<Func>(std::forward<Func>(f));
}

}

#endif
