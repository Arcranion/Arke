import argparse
import base64
import datetime
import logging
import os.path
import time

import jinja2
from jinja2 import Environment, BaseLoader

from scripts.logger_configuration import *


class GenerateShaderHeader:
    def __init__(
            self,
            binaries_dir: str | None = None,
            generated_dir: str | None = None,
            generator_template_path: str | None = None,
            header_extension: str = "h"
    ):
        self.binaries_dir = binaries_dir
        self.generated_dir = generated_dir
        self.generator_template_path = generator_template_path
        self.header_extension = header_extension

        self.logger = logging.getLogger("Generate Shader Header")
        _logger_handler = logging.StreamHandler()
        _logger_handler.setFormatter(ColoredFormatter())

        if generator_template_path is not None:
            self.generator_template = self.load_template()

    def load_template(self, template_path: str | None = None):
        if template_path is None:
            template_path = self.generator_template_path

        with open(template_path, "r") as file:
            content = file.read()
            return Environment(loader=BaseLoader()).from_string(content)

    def generate(self, path_binary: str, path_output: str, path_template: str | None = None):
        self.logger.info(f"Generate: {os.path.relpath(path_binary)} -> {os.path.relpath(path_output)}")

        if path_template is None:
            template = self.generator_template
        else:
            with open(path_template, "r") as template_file:
                template_content = template_file.read()
                template = Environment(loader=BaseLoader()).from_string(template_content)

        with open(path_binary, "rb") as src_file:
            src_data = src_file.read()

        os.makedirs(os.path.dirname(path_output), exist_ok=True)

        encoded_data = base64.b64encode(src_data).decode('ascii')

        # The path is like "dir/filename.vert.spv", so we should remove .spv binary extension and do splitext again
        shader_source_ext = os.path.splitext((os.path.splitext(path_binary)[:-1])[0])[1].removeprefix(".")
        shader_type_matches = {
            "vert": "vertex",
            "frag": "fragment",
            "tesc": "tesscontrol",
            "tese": "tesseval",
            "geom": "geometry",
            "comp": "compute"
        }

        shader_type = shader_type_matches[shader_source_ext]

        (_, filename) = os.path.split(path_binary)
        shader_name = filename.split(".", 1)[0]

        rendered = template.render(
            content_encoded=encoded_data,
            filename=filename,
            src_rel=os.path.relpath(path_binary, ".").replace("\\", "/"),
            out_rel=os.path.relpath(path_output, ".").replace("\\", "/"),
            src_abs=os.path.abspath(path_binary),
            out_abs=os.path.abspath(path_output),
            shader_name=shader_name,
            shader_type=shader_type,

            utcnow=datetime.datetime.utcnow,
            unixnow=round(time.time() * 1000)
        )

        with open(path_output, "w") as out_file:
            out_file.write(rendered)

    def generate_recurse(self, path: str | None = None):
        """
        :param path: directory to search files and generate headers
        :return: List of tuples of source and generated header path
        """
        if path is None:
            path = self.binaries_dir

        self.logger.info(f"Search: {os.path.relpath(path)}")

        generated = []
        for file in os.listdir(path):
            p = os.path.join(path, file)
            absolute = os.path.abspath(p)
            if os.path.isdir(p):
                generated.extend(self.generate_recurse(p))
            else:
                bin_relative = os.path.relpath(p, self.binaries_dir)
                out = os.path.join(self.generated_dir, bin_relative) + f".{self.header_extension}"
                out_absolute = os.path.abspath(out)

                self.generate(p, out)
                generated.append((absolute, out_absolute))
        return generated

    pass


def configure_parser():
    _parser = argparse.ArgumentParser()

    _parser.add_argument("-b", "--binary", dest="binary", action="store")
    _parser.add_argument("-o", "--output", dest="output", action="store")
    _parser.add_argument("-t", "--template", dest="template", action="store")

    return _parser


def main():
    configure_logging()

    parser = configure_parser()
    args = parser.parse_args()

    if not args.binary:
        logging.critical("--binary(-b) is not set, aborting")
        exit(-1)
    if not args.output:
        logging.critical("--output(-o) is not set, aborting")
        exit(-1)
    if not args.template:
        logging.critical("--template(-t) is not set, aborting")
        exit(-1)

    GenerateShaderHeader().generate(args.binary, args.output, args.template)


if __name__ == '__main__':
    main()
