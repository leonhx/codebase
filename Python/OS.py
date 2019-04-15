"""
Utilities about OS.
"""


import sys
import os
from datetime import datetime


def we_are_frozen():
    """Whether all of the modules are built-in to the interpreter,
    e.g., by py2exe
    """
    return hasattr(sys, "frozen")


def current_path():
    """Get the path of the current executed file"""
    encoding = sys.getfilesystemencoding()
    if we_are_frozen():
        return os.path.dirname(unicode(sys.executable, encoding))
    return os.path.dirname(unicode(__file__, encoding))


def path_modified_time(path):
    """Get las modified time of a specific path"""
    return datetime.fromtimestamp(os.path.getmtime(path))
