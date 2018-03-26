#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stringconversion/Fundamentals.h>
#include <xvtkw/InternalUtilities.h>
#include <xvtkw/VtuType.h>
#include <xvtkw/DataSet.h>

namespace xvtkw {

  namespace detail {

    std::string get_dataset_names(const std::unordered_map<std::string, DataSet>& ds, xvtkw::DataSetAttribute attr)
    {
      std::string names;
      for (auto&& pair : ds) {
        if (pair.second.attribute == attr) {
          names += pair.first + ",";
        }
      }
      if (!names.empty()) {
        names.pop_back(); // remove last comma character
      }
      return names;
    }

    void set_dataset_attributes(const std::unordered_map<std::string, DataSet>& ds, rapidxml::xml_document<>& doc, rapidxml::xml_node<char>* node)
    {
      auto set_attr = [&ds, &doc, &node](xvtkw::DataSetAttribute attr) {
        auto names = get_dataset_names(ds, attr);
        if (!names.empty()) {
          auto attr_name = std::to_string(attr);
          node->append_attribute(doc.allocate_attribute(doc.allocate_string(attr_name.c_str()), doc.allocate_string(names.c_str())));
        }
      };

      set_attr(DataSetAttribute::Normals);
      set_attr(DataSetAttribute::Scalars);
      set_attr(DataSetAttribute::TCoords);
      set_attr(DataSetAttribute::Tensors);
      set_attr(DataSetAttribute::Vectors);
    }
  }


  template <typename T> struct Point {
    Point(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z) {}
    T x;
    T y;
    T z;
  };


  enum class VtuCellType : int {
    VTK_EMPTY_CELL = 0,
    VTK_VERTEX = 1,
    VTK_POLY_VERTEX = 2,
    VTK_LINE = 3,
    VTK_POLY_LINE = 4,
    VTK_TRIANGLE = 5,
    VTK_TRIANGLE_STRIP = 6,
    VTK_POLYGON = 7,
    VTK_PIXEL = 8,
    VTK_QUAD = 9,
    VTK_TETRA = 10,
    VTK_VOXEL = 11,
    VTK_HEXAHEDRON = 12,
    VTK_WEDGE = 13,
    VTK_PYRAMID = 14,
    VTK_PENTAGONAL_PRISM = 15,
    VTK_HEXAGONAL_PRISM = 16,

    // Quadratic, isoparametric cells
    VTK_QUADRATIC_EDGE = 21,
    VTK_QUADRATIC_TRIANGLE = 22,
    VTK_QUADRATIC_QUAD = 23,
    VTK_QUADRATIC_POLYGON = 36,
    VTK_QUADRATIC_TETRA = 24,
    VTK_QUADRATIC_HEXAHEDRON = 25,
    VTK_QUADRATIC_WEDGE = 26,
    VTK_QUADRATIC_PYRAMID = 27,
    VTK_BIQUADRATIC_QUAD = 28,
    VTK_TRIQUADRATIC_HEXAHEDRON = 29,
    VTK_QUADRATIC_LINEAR_QUAD = 30,
    VTK_QUADRATIC_LINEAR_WEDGE = 31,
    VTK_BIQUADRATIC_QUADRATIC_WEDGE = 32,
    VTK_BIQUADRATIC_QUADRATIC_HEXAHEDRON = 33,
    VTK_BIQUADRATIC_TRIANGLE = 34,

    // Cubic, isoparametric cell
    VTK_CUBIC_LINE = 35,

    // Special class of cells formed by convex group of points
    VTK_CONVEX_POINT_SET = 41,

    // Polyhedron cell (consisting of polygonal faces)
    VTK_POLYHEDRON = 42,

    // Higher order cells in parametric form
    VTK_PARAMETRIC_CURVE = 51,
    VTK_PARAMETRIC_SURFACE = 52,
    VTK_PARAMETRIC_TRI_SURFACE = 53,
    VTK_PARAMETRIC_QUAD_SURFACE = 54,
    VTK_PARAMETRIC_TETRA_REGION = 55,
    VTK_PARAMETRIC_HEX_REGION = 56,

    // Higher order cells
    VTK_HIGHER_ORDER_EDGE = 60,
    VTK_HIGHER_ORDER_TRIANGLE = 61,
    VTK_HIGHER_ORDER_QUAD = 62,
    VTK_HIGHER_ORDER_POLYGON = 63,
    VTK_HIGHER_ORDER_TETRAHEDRON = 64,
    VTK_HIGHER_ORDER_WEDGE = 65,
    VTK_HIGHER_ORDER_PYRAMID = 66,
    VTK_HIGHER_ORDER_HEXAHEDRON = 67,
  };

  struct Cell {
    Cell(VtuCellType cell_type, std::initializer_list<int> list) : type(cell_type), point_positions(list) {}
    Cell(VtuCellType cell_type, std::vector<int>& vec) : type(cell_type), point_positions(vec) {}
    template <typename Iter> 
    Cell(VtuCellType cell_type, Iter b, Iter e) : type(cell_type), point_positions(b, e) {}

    VtuCellType type;
    std::vector<int> point_positions;
  };

  template <typename T> struct VtuFile
  {
    explicit VtuFile(xvtkw::ByteOrder _byte_order) : byte_order(_byte_order) {}
    std::vector<Point<T>> points;
    std::vector<Cell> cells;
    std::unordered_map<std::string, DataSet> point_datasets;
    std::unordered_map<std::string, DataSet> cell_datasets;
    xvtkw::ByteOrder byte_order;
  };

  template <typename T> void to_file(const VtuFile<T>& vtu, const std::string& filename)
  {
    rapidxml::xml_document<> doc;
    // root node
    auto&& root_node = detail::append_root("UnstructuredGrid", vtu.byte_order, doc);
    // Unstructured Grid node
    auto&& us_grid = doc.allocate_node(rapidxml::node_element, "UnstructuredGrid");
    root_node->append_node(us_grid);
    // Piece node
    rapidxml::xml_node<>* piece_node = doc.allocate_node(rapidxml::node_element, "Piece");
    root_node->first_node("UnstructuredGrid")->append_node(piece_node);
    piece_node->append_attribute(doc.allocate_attribute("NumberOfPoints", doc.allocate_string(stringconversion::to_string(vtu.points.size()).c_str())));
    piece_node->append_attribute(doc.allocate_attribute("NumberOfCells", doc.allocate_string(stringconversion::to_string(vtu.cells.size()).c_str())));

    // write point data
    rapidxml::xml_node<>* points_node = doc.allocate_node(rapidxml::node_element, "Points");
    piece_node->append_node(points_node);
    DataSet points(type_to_vtk_type<T>(), 3, DataSetAttribute::None);
    for (auto&& point : vtu.points) {
      points.add_to_data(point.x);
      points.add_to_data(point.y);
      points.add_to_data(point.z);
    }
    xvtkw::detail::write_xml_dataset(points_node, "", points);
    //write cell data
    rapidxml::xml_node<>* cell_node = doc.allocate_node(rapidxml::node_element, "Cells");
    piece_node->append_node(cell_node);
    DataSet cell_connectivity(VtuType::Int32, 1, DataSetAttribute::None);
    DataSet cell_offsets(VtuType::Int32, 1, DataSetAttribute::None);
    DataSet cell_types(VtuType::UInt8, 1, DataSetAttribute::None);
    int offset = 0;
    for (auto&& cell : vtu.cells) {
      cell_types.add_to_data((int)cell.type);
      for (auto point_pos : cell.point_positions) cell_connectivity.add_to_data(point_pos);
      offset += cell.point_positions.size();
      cell_offsets.add_to_data(offset);
    }
    xvtkw::detail::write_xml_dataset(cell_node, "connectivity", cell_connectivity);
    xvtkw::detail::write_xml_dataset(cell_node, "offsets", cell_offsets);
    xvtkw::detail::write_xml_dataset(cell_node, "types", cell_types);

    // write point datasets
    auto p_node = doc.allocate_node(rapidxml::node_element, "PointData");
    detail::set_dataset_attributes(vtu.point_datasets, doc, p_node);
    piece_node->append_node(p_node);
    for(auto&& pair : vtu.point_datasets) {
      xvtkw::detail::write_xml_dataset(p_node,pair.first, pair.second);
    }
    // write cell datasets
    auto c_node = doc.allocate_node(rapidxml::node_element, "CellData");
    detail::set_dataset_attributes(vtu.cell_datasets, doc, c_node);
    piece_node->append_node(c_node);
    for (auto&& pair : vtu.cell_datasets) {
      xvtkw::detail::write_xml_dataset(c_node, pair.first, pair.second);
    }

    std::ofstream file;
    file.open(filename.c_str(), std::ios::trunc | std::ios::out);
    file << doc;
  }



}