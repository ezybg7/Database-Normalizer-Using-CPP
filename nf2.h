#ifndef NF2_H
#define NF2_H

#include "nf1.h"
#include "header.h"
#include "output.h"

//Check if it is in 1NF before operating
Table convertTo2NF(vector<Table> input)
{
    for(const Table* i: input)
    {
        if(!is1NF(i))
            i = convertTo1NF(i);
    }

    //Extract primary key and non-key attributes
    vector<string> primaryKey = inputTable.keys;
    vector<string> nonKeyAttributes;
    for (const auto &attribute : inputTable.attributes)
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