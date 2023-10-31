#ifndef NF2_H
#define NF2_H

#include "header.h"
#include "output.h"

//Check if it is in 1NF before operating
Table convertTo2NF(Table inputTable)
{
    if (!is1NF(inputTable))
    {
        return inputTable;
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

    unordered_map<string, Table> tables;

    for (const auto &attribute : nonKeyAttributes)
    {
        //Create a new table with primary key
        vector<string> tableAttributes = primaryKey;
        tableAttributes.push_back(attribute);
        Table newTable(tableAttributes, inputTable.fundamentalDep, primaryKey, {});
        tables[attribute] = newTable;
    }

    //Add data into 2NF tables
    for (size_t i = 0; i < inputTable.data[inputTable.attributes[0]].size(); i++)
    {
        vector<string> keyValues;
        for (const auto &key : primaryKey)
        {
            keyValues.push_back(inputTable.data[key][i]);
        }

        //Add non-key attribute values to respective 2NF tables
        for (const auto &attribute : nonKeyAttributes)
        {
            string value = inputTable.data[attribute][i];
            vector<string> row = keyValues;
            row.push_back(value);
            tables[attribute].addRow(row);
        }
    }

    //Create a new 2NF table
    Table newTable(inputTable.keys, inputTable.fundamentalDep, inputTable.keys, tables,inputTable.types);

    //Merge 2NF tables into the new table
    for (const auto &pair : tables)
    {
        newTable.mergeTable(pair.second);
    }

    return newTable;
}
#endif