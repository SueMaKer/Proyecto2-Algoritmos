#pragma once
#include <string>
#include "Universe.hpp"

class CSVReader {
public:
    // Carga planetas y sistemas desde archivo CSV
    static bool loadUniverseFromCSV(const std::string& filename, Universe& universe);
};