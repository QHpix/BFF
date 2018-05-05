#!/usr/bin/env python

import ptrace.debugger
import signal
import subprocess
import sys
from Handler import Handler

def main():
    child = subprocess.Popen(sys.argv[1], stdin=subprocess.PIPE)
    handler = Handler(child)
    handler.detectSyscalls()
    child.kill()
    child.wait()

if __name__ == "__main__":
    main()
