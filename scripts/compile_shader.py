import argparse
import logging
import os
import subprocess
import typing

from .logger_configuration import *

here = os.path.dirname(__file__)
root = f"{here}/.."


class CompileShader:
    def __init__(
            self,
            sourceDirectory: str,
            outputDirectory: str,
            compilerPath: str,
            outputExtension: str = "bin",
            errorAction: typing.Literal["abort", None] = ""
    ):
        self.compiler = compilerPath
        self.sourceDir = sourceDirectory
        self.outputDir = outputDirectory
        self.outputExt = outputExtension
        self.errorAction = errorAction

        self.logger = logging.getLogger("Compile Shader")
        _logger_handler = logging.StreamHandler()
        _logger_handler.setFormatter(ColoredFormatter())
        self.logger.setLevel(logging.DEBUG)

        self.logger.info(f"Using compiler: {self.compiler}")

    def compile_file(self, path: str) -> bool:
        rel = os.path.relpath(path, self.sourceDir)
        src = os.path.abspath(path)
        dst = os.path.abspath(f"{self.outputDir}/{rel}.{self.outputExt}")

        os.makedirs(os.path.dirname(dst), exist_ok=True)

        self.logger.info(f"Compile: {os.path.relpath(src, root)} -> {os.path.relpath(dst, root)}")
        success = subprocess.run([self.compiler, "--target-env=opengl", src, "-o", dst]).returncode == 0
        if not success:
            self.logger.error("-> Failed")

        return success

    def compile_dir(self, path: str) -> (int, int):
        self.logger.info(f"Search: {os.path.relpath(path, root)}")

        success = 0
        fail = 0

        for file in os.listdir(path):
            p = os.path.join(path, file)
            if os.path.isdir(p):
                result = self.compile_dir(p)
                success += result[0]
                fail += result[1]
            else:
                if self.compile_file(p):
                    success += 1
                else:
                    fail += 1

        return success, fail


def configure_parser():
    _parser = argparse.ArgumentParser()

    _parser.add_argument("-s", "--source", dest="source", action="store")
    _parser.add_argument("-o", "--output", dest="output", action="store")
    _parser.add_argument("-c", "--compiler", dest="compiler", action="store")
    _parser.add_argument("-e", "--extension", dest="extension", action="store", default="bin")
    return _parser


def main():
    configure_logging()

    parser = configure_parser()
    args = parser.parse_args()

    if not args.source:
        logging.critical("--source(-s) is not set, aborting")
        exit(-1)
    if not args.output:
        logging.critical("--output(-o) is not set, aborting")
        exit(-1)
    if not args.compiler:
        logging.critical("--compiler(-c) is not set, aborting")
        exit(-1)

    result = CompileShader(
        sourceDirectory=args.source,
        outputDirectory=args.output,
        outputExtension=args.extension,
        compilerPath=args.compiler
    ).compile_dir(args.source)

    logging.info(f"[Result] Success {result[0]} / Fail {result[1]} of Total {sum(result)} files ({result[0] / sum(result) * 100}%)")


if __name__ == '__main__':
    main()
