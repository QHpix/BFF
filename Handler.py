#!/usr/bin/python

# This is the Handler class
# Usage: Handler(child)

class Handler():
    _child = None
    def __init__(self, child):
        self._child = _child
        _bff_debugger = ptrace.debugger.PtraceDebugger()
        print("Attaching the running process %s" % pid)
        _process = bff_debugger.addProcess(pid, False)

    def detectSyscalls(self):
        while 1:
                _process.singleStep()
                _process.waitSignals(signal.SIGTRAP)
                if _process.readBytes(_process.getregs().rip, 2) == "\x0f\x05":
                    print "SYSCALL DETECTED"
