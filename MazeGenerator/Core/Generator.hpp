#pragma once

#include <fstream>

#include "Builder.hpp"

namespace mazegenerator
{
namespace core
{

class Generator
{
public:
    explicit Generator(const unsigned width,
                       const unsigned height,
                       const unsigned beginX,
                       const unsigned beginY,
                       const unsigned endX,
                       const unsigned endY);

    bool save(const char* filename);

private:
    void saveArea(std::ofstream& file) const;
    void saveHeader(std::ofstream& file) const;
    bool create();
    bool isEmpty(std::ofstream& file) const;

private:
    std::string m_header;
    std::string m_area;
    Builder m_builder;
};

}  // namespace core
}  // namespace mazegenerator
