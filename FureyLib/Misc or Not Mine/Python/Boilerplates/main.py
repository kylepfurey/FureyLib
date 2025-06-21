# .py
# Program Main Entry Point Script

import sys
import string
import types
import typing


def main(args: list[str]) -> int:
    """Entry point of the program."""
    print("Hello, Dinner!")

    # New code here

    return 0


# Starts the application.
if __name__ == "__main__":
    code: int = main(sys.argv)
    print("\n\nProgram exited with code " + str(code) + ".\n")
    sys.exit(code)
