#include <boost/test/unit_test.hpp>
#include <xvtkw\VtuFile.h>
#include <xvtkw\PvdFile.h>

BOOST_AUTO_TEST_SUITE(vtu_file)

BOOST_AUTO_TEST_CASE(vtu_file_test_case) 
{
  xvtkw::VtuFile<float> vtu1(xvtkw::ByteOrder::LittleEndian);
  xvtkw::VtuFile<float> vtu2(xvtkw::ByteOrder::LittleEndian);

  vtu1.points.push_back(xvtkw::Point<float>(0.f, 0.f, 0.f));
  vtu1.points.push_back(xvtkw::Point<float>(10.f, 0.f, 0.f));
  vtu1.points.push_back(xvtkw::Point<float>(10.f, 10.f, 0.f));

  vtu1.cells.push_back(xvtkw::Cell(xvtkw::VtuCellType::VTK_LINE, { 0, 1 }));
  vtu1.cells.push_back(xvtkw::Cell(xvtkw::VtuCellType::VTK_LINE, { 1, 2 }));

  vtu2.points.push_back(xvtkw::Point<float>(0.f, 0.f, 0.f));
  vtu2.points.push_back(xvtkw::Point<float>(0.f, 10.f, 0.f));
  vtu2.points.push_back(xvtkw::Point<float>(10.f, 10.f, 0.f));
  
  vtu2.cells.push_back(xvtkw::Cell(xvtkw::VtuCellType::VTK_LINE, { 0, 1 }));
  vtu2.cells.push_back(xvtkw::Cell(xvtkw::VtuCellType::VTK_LINE, { 1, 2 }));

  xvtkw::DataSet cell_partitions_1(xvtkw::VtuType::Int32, 1, xvtkw::DataSetAttribute::Scalars);
  cell_partitions_1.add_to_data({ 1, 1 });
  vtu1.cell_datasets["Partition"] = std::move(cell_partitions_1);

  xvtkw::DataSet cell_partitions_1b(xvtkw::VtuType::Int32, 1, xvtkw::DataSetAttribute::Scalars);
  cell_partitions_1b.add_to_data({ 1, 1 });
  vtu1.cell_datasets["Partitionb"] = std::move(cell_partitions_1b);
  
  xvtkw::DataSet cell_partitions_2(xvtkw::VtuType::Int32, 1, xvtkw::DataSetAttribute::Scalars);
  cell_partitions_2.add_to_data({ 2, 2 });
  vtu2.cell_datasets["Partition"] = std::move(cell_partitions_2);

  xvtkw::DataSet cell_partitions_2b(xvtkw::VtuType::Int32, 1, xvtkw::DataSetAttribute::Scalars);
  cell_partitions_2b.add_to_data({ 2, 2 });
  vtu2.cell_datasets["Partitionb"] = std::move(cell_partitions_2b);

  xvtkw::DataSet point_displacements_1(xvtkw::VtuType::Float64, 3, xvtkw::DataSetAttribute::Vectors);
  point_displacements_1.add_to_data<double>({ 0, 0, 0, 0.5, 0, 0, 0.5, 0, 0 });
  vtu1.point_datasets["Displacements"] = std::move(point_displacements_1);
  
  xvtkw::DataSet point_displacements_2(xvtkw::VtuType::Float64, 3, xvtkw::DataSetAttribute::Vectors);
  point_displacements_2.add_to_data<double>({ 0, 0, 0, 0, 0, 0, 0.5, 0, 0 });
  vtu2.point_datasets["Displacements"] = std::move(point_displacements_2);

  xvtkw::to_file(vtu1, "d:\\temp\\vtu1.vtu");
  xvtkw::to_file(vtu2, "d:\\temp\\vtu2.vtu");

  xvtkw::PvdFile pvd(xvtkw::ByteOrder::LittleEndian);
  pvd.collection.push_back(xvtkw::PvdItem(0, 0, "d:\\temp\\vtu1.vtu"));
  pvd.collection.push_back(xvtkw::PvdItem(0, 1, "d:\\temp\\vtu2.vtu"));
  xvtkw::to_file(pvd, "d:\\temp\\vtu.pvd");
}


//BOOST_AUTO_TEST_CASE(vtu_file_test_case_double)
//{
//  xvtkw::vtu_file vtu;
//
//  std::array<double, 4> x_coord = { 0.0, 5.0, 0.0, 5.0 };
//  std::array<double, 4> y_coord = { 0.0, 0.0, 5.0, 5.0 };
//  std::array<double, 4> z_coord = { 0.0, 0.0, 0.0, 0.0 };
//
//  xvtkw::dataset<int, 1> point_partitions;
//  xvtkw::dataset<double, 3> point_coordinates;
//  point_partitions.name = "point_partitions";
//  for (size_t i = 0; i < 4; ++i) {
//    point_coordinates.data.push_back(x_coord[i]);
//    point_coordinates.data.push_back(y_coord[i]);
//    point_coordinates.data.push_back(z_coord[i]);
//    point_partitions.data.push_back(i);
//  }
//  vtu.point_coordinates = point_coordinates;
//  vtu.point_datasets.emplace_back(point_partitions);
//
//  std::array<int, 4> p1 = { 0, 1, 2, 3 };
//  std::array<int, 4> p2 = { 1, 2, 3, 0 };
//
//  xvtkw::dataset<int, 1> cell_partitions;
//  cell_partitions.name = "cell_partitions";
//  for (size_t i = 0; i < 4; ++i) {
//    vtu.cell_connectivity.data.push_back(p1[i]);
//    vtu.cell_connectivity.data.push_back(p2[i]);
//    vtu.cell_types.data.push_back(3);
//    vtu.cell_offsets.data.push_back((i + 1) * 2);
//    cell_partitions.data.push_back(i);
//  }
//  //vtu.cell_datasets.emplace_back(cell_partitions);
//
//  vtu.write("d:\\temp\\test_double.vtu");
//
//}

BOOST_AUTO_TEST_SUITE_END()