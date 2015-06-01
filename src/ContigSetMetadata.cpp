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

#include "pbbam/dataset/ContigSetMetadata.h"
#include <exception>
using namespace PacBio;
using namespace PacBio::BAM;
using namespace std;

namespace PacBio {
namespace BAM {
namespace internal {

// empty, "null" components

static
const ContigsMetadata& NullContigs(void)
{
    static const ContigsMetadata empty;
    return empty;
}

} // namespace internal
} // namespace BAM
} // namespace PacBio

// ----------------------------------
// ContigMetadata implementation
// ----------------------------------

ContigMetadata::ContigMetadata(void)
    : internal::DataSetElement("Contig") { }

const string& ContigMetadata::Digest(void) const
{ return FetchChildText("Digest"); }

ContigMetadata& ContigMetadata::Digest(const std::string& digest)
{ SetChildText("Digest", digest); return *this; }

const string& ContigMetadata::Length(void) const
{ return FetchChildText("Length"); }

ContigMetadata& ContigMetadata::Length(const std::string& length)
{ SetChildText("Length", length); return *this; }

// ----------------------------------
// ContigsMetadata implementation
// ----------------------------------

ContigsMetadata::ContigsMetadata(void)
    : internal::DataSetListElement<ContigMetadata>("Contigs")
{ }

ContigsMetadata& ContigsMetadata::AddContig(const ContigMetadata& contig)
{ AddChild(contig); return *this; }

ContigsMetadata& ContigsMetadata::RemoveContig(const ContigMetadata& contig)
{ RemoveChild(contig); return *this; }

// ----------------------------------
// ContigSetMetadata implementation
// ----------------------------------

ContigSetMetadata::ContigSetMetadata(void)
    : DataSetMetadataBase()
{ }

const ContigsMetadata& ContigSetMetadata::Contigs(void) const
{
    try {
        return Child<ContigsMetadata>("Contigs");
    } catch (std::exception&) {
        return internal::NullContigs();
    }
}

ContigsMetadata& ContigSetMetadata::Contigs(void)
{
    if (!HasChild("Contigs"))
        AddChild(internal::NullContigs());
    return Child<ContigsMetadata>("Contigs");
}
