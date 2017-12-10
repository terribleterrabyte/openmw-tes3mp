//
// Created by koncord on 04.03.17.
//

#include "Utils.hpp"

using namespace std;

static std::string lastErrorMessage = "unknown error";

const vector<string> Utils::split(const string &str, int delimiter)
{
    string buffer;
    vector<string> result;

    for (const auto &symb : str)
        if (symb != delimiter)
            buffer += symb;
        else if (!buffer.empty())
        {
            result.push_back(move(buffer));
            buffer.clear();
        }
    if (!buffer.empty())
        result.push_back(move(buffer));

    return result;
}

ESM::Cell Utils::getCellFromDescription(const std::string &cellDescription)
{
    ESM::Cell cell;
    cell.blank();

    static regex exteriorCellPattern("^(-?\\d+), (-?\\d+)$");
    smatch baseMatch;

    if (regex_match(cellDescription, baseMatch, exteriorCellPattern))
    {
        cell.mData.mFlags &= ~ESM::Cell::Interior;

        // The first sub match is the whole string, so check for a length of 3
        if (baseMatch.size() == 3)
        {
            cell.mData.mX = stoi(baseMatch[1].str());
            cell.mData.mY = stoi(baseMatch[2].str());
        }
    }
    else
    {
        cell.mData.mFlags |= ESM::Cell::Interior;
        cell.mName = cellDescription;
    }

    return cell;
}

const std::string Utils::getLastError()
{
    return lastErrorMessage;
}

void Utils::throwError(const std::string &errorMessage)
{
#ifdef _WIN32
    // Throwing exceptions makes them show up as "bad exception" on Windows with
    // our stacktracer, so record their intended error messages separately here
    // when possible
    lastErrorMessage = errorMessage;
#endif

    throw runtime_error(errorMessage);
}
