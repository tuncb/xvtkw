from conans import ConanFile

class XVTKWTesterConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "boost/1.66.0@conan/stable",
        "stringconversion/0.2.0@tuncb/pangea",
        "rapidxml/1.13@tuncb/pangea"
    )

    generators = "cmake_multi"