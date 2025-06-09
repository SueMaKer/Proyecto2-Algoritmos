#pragma once
#include <string>
#include "Universe.hpp"

class CSVReader {
public:
    
    static bool loadUniverseFromCSV(const std::string& filename, Universe& universe);
};