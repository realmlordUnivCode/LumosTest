#pragma once
#include "Core/DataStructures/TDArray.h"
#include "Core/Function.h"

namespace Lumos
{
    struct DeletionQueue
    {
        TDArray<Function<void()>> Deletors;

        template <typename F>
        void PushFunction(F&& function)
        {
            ASSERT(sizeof(F) < 200, "Lambda too large");
            Deletors.PushBack(function);
        }

        void Flush()
        {
            for(auto& deleteFunc : Deletors)
            {
                deleteFunc();
            }

            Deletors.Clear();
        }
    };
}
