from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.files import copy
from os.path import join

class Recipe(ConanFile):
    name = "bactery-flow"
    version = "0.1"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    description = "This project uses genetic algorithms to create captivating real-time animations"
    url = "https://github.com/adidvar/bactery-flow"

    exports_sources = "*"

    def layout(self):
        self.folders.generators = "conan"
        self.folders.build = "build"

    def requirements(self):
        self.requires("sfml/2.6.2", options={"graphics": True, "window": True, "audio": False, "network": False})
        self.requires("eigen/3.4.0")

    def build_requirements(self):
        self.test_requires("catch2/3.7.1")

    def build(self):
        cmake = CMake(self)
        self.output.info(f"Configuring CMake from source folder: {self.source_folder}")
        self.output.info(f"Building into binary folder: {self.build_folder}")
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "bactery-flow*", src=self.build_folder, dst=join(self.package_folder, "bin"), keep_path=False)

        for dep in self.dependencies.values():
            if dep.cpp_info.bindirs:
                for bindir in dep.cpp_info.bindirs:
                    copy(self, "*.dll", src=bindir, dst=join(self.package_folder, "bin"), keep_path=False)
                    copy(self, "*.so", src=bindir, dst=join(self.package_folder, "bin"), keep_path=False)
                    copy(self, "*.dylib", src=bindir, dst=join(self.package_folder, "bin"), keep_path=False)

    def package_info(self):
        self.cpp_info.bindirs.append(join(self.package_folder, "bin"))