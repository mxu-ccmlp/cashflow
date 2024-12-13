from setuptools import setup
import os
import re

# Read the version from version.py
def get_version():
    version_file = os.path.join(os.path.dirname(__file__), "version.py")
    with open(version_file) as f:
        match = re.search(r'__version__ = ["\'](.+)["\']', f.read())
        if match:
            return match.group(1)
        raise RuntimeError("Unable to find version string.")

setup(
    name="cfengines",
    version=get_version(),
    packages=["cfengines"],
)
