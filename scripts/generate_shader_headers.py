import argparse
import logging
import os
import shutil
import subprocess

from scripts.generate_shader_header import GenerateShaderHeader
from .compile_shader import *
from .logger_configuration import *


def configure_parser():
    _parser = argparse.ArgumentParser()

    _parser.add_argument("-b", "--binaries", dest="binaries", action="store")
    _parser.add_argument("-o", "--output", dest="output", action="store")
    _parser.add_argument("-t", "--template", dest="template", action="store")
    _parser.add_argument("-c", "--clean", dest="clean", action="store_true")

    return _parser


def generate_shader_headers(path_binaries: str, path_output: str, path_template: str):
    GenerateShaderHeader(path_binaries, path_output, path_template).generate_recurse()
    pass


def main():
    configure_logging()

    parser = configure_parser()
    args = parser.parse_args()

    if not args.binaries:
        logging.critical("--binaries(-b) is not set, aborting")
        exit(-1)
    if not args.output:
        logging.critical("--output(-o) is not set, aborting")
        exit(-1)
    if not args.template:
        logging.critical("--template(-t) is not set, aborting")
        exit(-1)

    if args.clean:
        logging.info("--clean(-c) option enabled, cleaning the output directory")
        if os.path.exists(args.output) and os.path.isdir(args.output):
            shutil.rmtree(args.output)

    generate_shader_headers(args.binaries, args.output, args.template)


if __name__ == '__main__':
    main()
