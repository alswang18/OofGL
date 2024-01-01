import subprocess
from sys import platform
def RunConan(build_type):
    subprocess.run((
        'conan', 'install', '.', 
        '--build', 'missing', 
        '--output-folder=./dependencies', 
        f'--settings=build_type={build_type}'
    ))

def RunPremake(action):
    subprocess.run((
        'premake5', action
    ))

if __name__ == "__main__":
    RunConan("Debug")
    RunConan("Release")
    if platform == "win32":
        RunPremake("vs2022")
    elif platform == "darwin":
        RunPremake("xcode4")
    else:
        raise Exception(f"Unsupported platform {platform}")