from conan import ConanFile

class OofEngineRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("spdlog/1.11.0")
        self.requires("lz4/1.9.4")
