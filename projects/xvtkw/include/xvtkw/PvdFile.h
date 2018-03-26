#pragma once
#include <vector>
#include <fstream>
#include <rapidxml\rapidxml_print.hpp>
#include <stringconversion/Fundamentals.h>
#include <xvtkw\ByteOrder.h>

namespace xvtkw {

struct PvdItem
{
  PvdItem(float a_timestep, int a_part, std::string a_filename) : timestep(a_timestep), part(a_part), filename(std::move(a_filename)) {}
  float timestep;
  int part;
  std::string filename;
};


struct PvdFile {
  PvdFile(xvtkw::ByteOrder _byte_order) : byte_order(_byte_order) {}
  xvtkw::ByteOrder byte_order;
  std::vector<PvdItem> collection;
};

void to_file(const PvdFile& pvd, const std::string& filename)
{
  rapidxml::xml_document<> doc;

  auto&& root_node = detail::append_root("Collection", pvd.byte_order, doc);

  auto collection_node = doc.allocate_node(rapidxml::node_element, "Collection");
  root_node->append_node(collection_node);

  for (auto&& item : pvd.collection) {
    auto node = doc.allocate_node(rapidxml::node_element, "DataSet");
    node->append_attribute(doc.allocate_attribute("timestep", doc.allocate_string(stringconversion::to_string(item.timestep).c_str())));
    node->append_attribute(doc.allocate_attribute("part", doc.allocate_string(stringconversion::to_string(item.part).c_str())));
    node->append_attribute(doc.allocate_attribute("file", item.filename.c_str()));
    collection_node->append_node(node);
  }

  std::ofstream file;
  file.open(filename.c_str(), std::ios::trunc | std::ios::out);
  file << doc;
}

}