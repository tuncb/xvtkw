from conans import ConanFile

class XVTKWConan(ConanFile):
    name = "xvtkw"
    version = "2.1.0"
    license = "https://www.apache.org/licenses/LICENSE-2.0"
    url = "https://github.com/tuncb/timetable"
    description = ("A library to write vtk and pvd files")
    requires = (
        "stringconversion/0.2.0@tuncb/pangea",
        "rapidxml/1.13@tuncb/pangea"
    )    

    def package(self):
        self.copy("*", dst="xvtkw", src="../projects/xvtkw/include/xvtkw")
    def package_info(self):
        self.cpp_info.includedirs = ['.']
