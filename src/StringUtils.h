// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// Author: Derek Barnett

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <algorithm>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

namespace PacBio {
namespace BAM {
namespace internal {

inline std::string Int2String(const int x)
{
    char buffer[64];
    char* p = buffer;
    if (boost::spirit::karma::generate(p, boost::spirit::karma::int_, x)) {
        *p = 0;
        return std::string(buffer);
    }
    throw std::exception();
}

inline std::string MakeSamTag(const std::string& tag,
                              const std::string& value)
{
    return std::string('\t' + tag + ':' + value);
}

inline std::vector<std::string> Split(const std::string& line,
                                      const char delim = '\t')
{
    std::vector<std::string> tokens;
    std::stringstream lineStream(line);
    std::string token;
    while (std::getline(lineStream, token, delim))
        tokens.push_back(token);
    return tokens;
}

inline int String2Int(const std::string& str)
{
    int result;
    std::string::const_iterator i = str.begin();
    if (boost::spirit::qi::parse(i, str.end(), boost::spirit::qi::int_, result)) {
        if (i == str.end())
            return result;
    }
    throw std::exception();
}

} // namespace internal
} // namespace BAM
} // namespace PacBio

#endif // STRINGUTILS_H
