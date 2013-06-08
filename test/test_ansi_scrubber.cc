/**
 * Copyright (c) 2013, Timothy Stack
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * * Neither the name of Timothy Stack nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "ansi_scrubber.hh"

using namespace std;

int main(int argc, char *argv[])
{
    ansi_scrubber &as = ansi_scrubber::singleton();
    view_colors &vc = view_colors::singleton();
    string_attrs_t::iterator iter;
    string_attrs_t sa;
    string str_cp;

    str_cp = "Hello, World!";
    as.scrub_value(str_cp, sa);

    assert(str_cp == "Hello, World!");
    assert(sa.empty());

    str_cp = "Hello\x1b[44;m, \x1b[33;mWorld\x1b[0;m!";
    as.scrub_value(str_cp, sa);
    assert(str_cp == "Hello, World!");
    
    iter = sa.begin();
    assert(iter->second.find("style")->second.sa_int == vc.ansi_color_pair(0, 4));
    assert(iter->first.lr_start == 5);
    assert(iter->first.lr_end == 7);
    ++iter;
    assert(iter->second.find("style")->second.sa_int == vc.ansi_color_pair(3, 0));
    assert(iter->first.lr_start == 7);
    assert(iter->first.lr_end == 12);
}
