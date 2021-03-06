#pragma once
#include "CppUnitTest.h"
#include "PairTest.h"

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<ParamHandler>(const class ParamHandler& t) { return L"ParamHandler"; }
        }
    }
}