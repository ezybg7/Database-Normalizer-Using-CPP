#ifndef NF3_H
#define NF3_H

#include "header.h"
#include "output.h"

Table convertTo3NF(Table inputTable)
{
    if (!is1NF(inputTable))
    {
        return inputTable;
    }

    //Convert to 2NF
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

    unordered_map<string, Table> tables;

    for (const auto &attribute : nonKeyAttributes)
    {
        //Create a new table with primary key and the current attribute
        vector<string> tableAttributes = primaryKey;
        tableAttributes.push_back(attribute);
        Table newTable(tableAttributes, tableIn2NF.fundamentalDep, primaryKey, {});
        tables[attribute] = newTable;
    }

    //Add data into 3NF tables
    for (size_t i = 0; i < tableIn2NF.data[tableIn2NF.attributes[0]].size(); i++)
    {
        // Extract primary key values
        vector<string> keyValues;
        for (const auto &key : primaryKey)
        {
            keyValues.push_back(tableIn2NF.data[key][i]);
        }

        //Add non-key attribute values to respective 3NF tables
        for (const auto &attribute : nonKeyAttributes)
        {
            string value = tableIn2NF.data[attribute][i];
            vector<string> row = keyValues;
            row.push_back(value);
            tables[attribute].addRow(row);
        }
    }

    //Create a new 3NF table
    Table newTable(tableIn2NF.keys, tableIn2NF.fundamentalDep, tableIn2NF.keys, {});

    //Merge 3NF tables into the new table
    for (const auto &pair : tables)
    {
        newTable.mergeTable(pair.second);
    }

    return newTable;
}

#endif