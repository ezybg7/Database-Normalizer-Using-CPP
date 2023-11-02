#ifndef NF2_H
#define NF2_H

#include "nf1.h"
#include "header.h"
#include "output.h"

//Check if it is in 1NF before operating
vector<Table> convertTo2NF(Table inputTable)
{
    if(!is1NF(inputTable))
        inputTable = convertTo1NF(inputTable);
    

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