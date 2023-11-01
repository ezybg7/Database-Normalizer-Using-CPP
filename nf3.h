#ifndef NF3_H
#define NF3_H

#include "header.h"
#include "output.h"
#include "nf1.h"
#include "nf2.h"

Table convertTo3NF(Table inputTable)
{
    for(const Table* i: input)
    {
        if(!is1NF(i))
            i = convertTo1NF(i);
    }

    Table tableIn2NF = convertTo2NF(inputTable);

    // Extract primary key and non-key attributes
    vector<string> primaryKey = tableIn2NF.keys;
    vector<string> nonKeyAttributes;
    for (const auto &attribute : tableIn2NF.attributes)
    {
        if (find(primaryKey.begin(), primaryKey.end(), attribute) == primaryKey.end())
        {
            nonKeyAttributes.push_back(attribute);
        }
    }
    vector<Table> result;

    return result;

}

#endif