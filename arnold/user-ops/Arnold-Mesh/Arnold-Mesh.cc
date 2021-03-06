// ----------------------------------------------------------------------------
//
// Arnold-Mesh.cc
//
// Copyright (c) 2011 Exotic Matter AB.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of Exotic Matter AB nor its contributors may be used to
//   endorse or promote products derived from this software without specific
//   prior written permission.
//
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
//    LIMITED TO,  THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS
//    FOR  A  PARTICULAR  PURPOSE  ARE DISCLAIMED.  IN NO EVENT SHALL THE
//    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//    BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS  OR  SERVICES;
//    LOSS OF USE,  DATA,  OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER
//    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,  STRICT
//    LIABILITY,  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN
//    ANY  WAY OUT OF THE USE OF  THIS SOFTWARE,  EVEN IF ADVISED OF  THE
//    POSSIBILITY OF SUCH DAMAGE.
//
// ----------------------------------------------------------------------------
// Naiad Graph API
#include <NgBodyOp.h>
#include <NbAi.h>

class Arnold_Mesh : public Ng::BodyOp
{
public:
    Arnold_Mesh(const Nb::String& name)
        : Ng::BodyOp(name) {  }
// ----------------------------------------------------------------------------
    virtual Nb::String
    typeName() const
    { return "Arnold-Mesh"; }
// ----------------------------------------------------------------------------
    virtual void
    stepAdmittedBody(Nb::Body*             body,
                     Ng::NelContext&       nelContext,
                     const Nb::TimeBundle& tb)
    {
        const Nb::String bodyNameList = param1s("Body Names")->eval(tb);
        if(body->name().listed_in(bodyNameList)){

            //What type Arnold should render the body as
            NbAi::setProp<Nb::ValueBase::StringType>(body, "type", "Mesh");


            //Node name
            NbAi::setProp<Nb::ValueBase::StringType>(
                    body, "name", param1s("Node Name")->eval(tb));

            //Shader that can be found in the template ASS file
            //(see Arnold-Render or Arnold-ASS-Write)
            NbAi::setProp<Nb::ValueBase::StringType>(
                    body, "shader", param1s("Shader")->eval(tb));

            //Solid shadows or not?
            Nb::String opaque = "0";
            if (Nb::String("On") == param1e("Opaque")->eval(tb))
                opaque = "1";
            NbAi::setProp<Nb::ValueBase::IntType>(body, "opaque", opaque);

#ifndef NDEBUG
            std::cerr<< "Adding Arnold properties for " << body->name() << "\n"
            << "\tYype: " << body->prop1s("type")->eval(tb) << "\n"
            << "\tNode name: " << body->prop1s("name")->eval(tb) << "\n"
            << "\tShader: " << body->prop1s("shader")->eval(tb) << "\n"
            << "\tOpaque: " << body->prop1i("opaque")->eval(tb) << std::endl;
#endif
        }
    }
};

// ----------------------------------------------------------------------------

extern "C" {

NI_EXPORT bool
BeginPlugin(NtForeignFactory* factory)
{
    NiSetForeignFactory(factory);
    return true;
}

// -----------------------------------------------------------------------------
   
NI_EXPORT bool
EndPlugin(NtForeignFactory* factory)
{
    return true;
}

// -----------------------------------------------------------------------------

NI_EXPORT Nb::Object*
UserOpAlloc(const NtCString type, const NtCString name)
{
    return new Arnold_Mesh(name);
}

}

// ----------------------------------------------------------------------------
