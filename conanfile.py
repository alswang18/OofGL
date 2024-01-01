from conan import ConanFile

class OofEngineRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("glfw/3.3.4")
        self.requires("glad/0.1.34")
