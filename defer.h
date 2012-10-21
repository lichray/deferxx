/*-
 * Copyright (c) 2012 Zhihao Yuan.  All rights reserved.
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

#ifndef _DEFER_H
#define _DEFER_H 1

#include <functional>

#define defer(expr) \
	stdex::scope_guard __stdex_namelno(_DEFER_, __LINE__) ([&]{expr;})
#define __stdex_namelno(name, lno)	__stdex_cat(name, lno)
#define __stdex_cat(a, b)		a ## b

namespace stdex {

struct scope_guard {
	explicit scope_guard(std::function<void()> on_exit) :
		on_exit(on_exit), dismissed(false) {}
	scope_guard(scope_guard const&) = delete;
	scope_guard& operator=(scope_guard const&) = delete;
	
	~scope_guard() noexcept {
		if(!dismissed)
			on_exit();
	}
	
	void dismiss() {
		dismissed = true;
	}

private:
	std::function<void()> on_exit;
	bool dismissed;
};

}

#endif
