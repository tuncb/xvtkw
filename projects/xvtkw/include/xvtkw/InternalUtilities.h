#pragma once
#include <rapidxml/rapidxml_print.hpp>
#include <stringconversion/Fundamentals.h>
#include "ByteOrder.h"
#include <xvtkw/DataSet.h>

namespace xvtkw { namespace detail {

  rapidxml::xml_node<>* append_root(const std::string& type, ByteOrder order, rapidxml::xml_document<>& doc) {
    rapidxml::xml_node<>* root_node = doc.allocate_node(rapidxml::node_element, "VTKFile");
    root_node->append_attribute(doc.allocate_attribute("type", doc.allocate_string(type.c_str())));
    root_node->append_attribute(doc.allocate_attribute("version", "1.0"));
    root_node->append_attribute(doc.allocate_attribute("byte_order", doc.allocate_string(std::to_string(order).c_str())));
    doc.append_node(root_node);
    return root_node;
  }

  void write_xml_dataset(rapidxml::xml_node<>* root_node, const std::string& name, const xvtkw::DataSet& dataset)
  {
    auto& doc = *(root_node->document());

    rapidxml::xml_node<>* datanode = doc.allocate_node(rapidxml::node_element, "DataArray");
    root_node->append_node(datanode);
    datanode->append_attribute(doc.allocate_attribute("Name", doc.allocate_string(name.c_str(), name.size()), 4, name.size()));
    datanode->append_attribute(doc.allocate_attribute("type", doc.allocate_string(std::to_string(dataset.type).c_str()), 4, 0));
    datanode->append_attribute(doc.allocate_attribute("format", doc.allocate_string("ascii", 5), 6, 5));
    datanode->append_attribute(doc.allocate_attribute("NumberOfComponents", doc.allocate_string(stringconversion::to_string(dataset.num_components).c_str()), 18, 0));

    char* str = doc.allocate_string(dataset.data.c_str(), dataset.data.size());
    datanode->append_node(doc.allocate_node(rapidxml::node_data, "", str, 0, dataset.data.size()));
  }

} }