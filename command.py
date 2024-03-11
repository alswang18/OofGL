import os
import sys
import subprocess
import shutil


def generate_cmake_build(source_dir, build_dir, debug=True):
    # Ensure the build directory exists
    os.makedirs(build_dir, exist_ok=True)

    # Change directory to the build directory
    os.chdir(build_dir)

    # Generate CMake configuration
    cmake_args = ["cmake", source_dir]

    subprocess.run(cmake_args, check=True)

    # Build the project using default build tool (e.g., make, ninja)
    build_cmd = ["cmake", "--build", ".", "--config", "Debug" if debug else "Release"]
    subprocess.run(build_cmd, check=True)


def cmake_exists():
    try:
        subprocess.run(
            ["cmake", "--version"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True,
        )
        return True
    except subprocess.CalledProcessError:
        return False


def build(debug):
    print(f"Building {'debug' if debug else 'release'} version")
    if not cmake_exists():
        raise RuntimeError(
            "CMake is not installed cannot build the project. Please install CMake and try again."
        )

    # Get the current directory as the source directory
    source_dir = os.getcwd()

    # Define the build directory
    build_dir = os.path.join(os.getcwd(), "build/" + ("debug" if debug else "release"))

    # Check for -r flag to build release version
    if len(sys.argv) > 1 and ("-r" in sys.argv or "--release" in sys.argv):
        debug = False
    else:
        debug = True

    # Check for -c flag to clean the build directory
    if len(sys.argv) > 1 and ("-c" in sys.argv or "--clean" in sys.argv):
        force_delete_directory(build_dir)

    # Generate CMake build
    generate_cmake_build(source_dir, build_dir, debug=debug)


def force_delete_directory(directory):
    print("Deleting build directory and all its contents.")
    try:
        # run remove-Item build -force if on Windows
        if os.name == "nt":
            print(
                "Windows Detected. Running powershell `remove-item` command to remove build directory if it exists."
            )
            if os.path.exists(directory):
                subprocess.run(
                    ["powershell", "remove-item", directory, "-force -recurse"]
                )
        else:
            print(
                "Operating system not detected, using shutil.rmtree to remove build directory."
            )
            shutil.rmtree(directory, ignore_errors=True)
        print(
            f"Directory '{directory}' and all its contents have been successfully deleted."
        )
    except Exception as e:
        print(f"An error occurred while deleting directory '{directory}': {e}")


if __name__ == "__main__":
    command = ""
    if len(sys.argv) == 1:
        command = "build"
    else:
        command = sys.argv[1]

    if command == "build":
        if len(sys.argv) > 2 and "-r" in sys.argv:
            debug = False
        else:
            debug = True
        build(debug)
    elif command == "clean":
        build_dir = os.path.join(os.getcwd(), "build")
        force_delete_directory(build_dir)
    else:
        print("Unknown command")
        sys.exit(1)
