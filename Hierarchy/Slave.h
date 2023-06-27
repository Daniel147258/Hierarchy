#pragma once

#include <libds/amt/implicit_sequence.h>
#include "libds/heap_monitor.h"

template<typename Block, typename Iterator>
class Slave
{
    using IS = ds::amt::ImplicitSequence<Block>;
public:
    IS& process_(Iterator beginN1, Iterator endN1, IS& out, std::function<bool(Block)> predikat)
    {
        while (beginN1 != endN1)
        {
            Block& pom = *beginN1;
            if (predikat(pom))
            {
                out.insertLast();
                out.access(out.size() - 1)->data_ = pom;
            }
            ++beginN1;
        }
        return out;
    };
};

