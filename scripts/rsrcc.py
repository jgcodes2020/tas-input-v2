#!/usr/bin/python3
from argparse import ArgumentParser, Action
from pathlib import Path
import re
import hashlib

class PathAction(Action):
    def __call__(self, parser, namespace, values, option_string) -> None:
        setattr(namespace, self.dest, Path(values));

parser = ArgumentParser(description="Compile resources to C++ source code.")

parser.add_argument("src", action=PathAction)
parser.add_argument("sym")
parser.add_argument("--namespace", "-n", dest="ns", default="")
parser.add_argument("--output", "-o", dest="dst", action=PathAction, default=Path("out.rsrc.hpp"))

args = parser.parse_args()
del parser

# MAIN SCRIPT
# ==============

IDENTIFIER_REGEX = re.compile(r"^[A-Za-z_]\w*$")
NAMESPACE_REGEX = re.compile(r"^[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*$")

print(repr(args))

# Ensure validity of identifiers
if len(args.ns) != 0:
    assert re.match(NAMESPACE_REGEX, args.ns) is not None
assert re.match(IDENTIFIER_REGEX, args.sym) is not None

NS_BEGIN = "" if len(args.ns) == 0 else f"namespace {args.ns} {{"
NS_END = "" if len(args.ns) == 0 else "}"

ID_HASH = hashlib.sha256(f"{args.ns}{args.sym}".encode('utf-8')).hexdigest().upper()

FILE_HEADER = f"""\
#ifndef RESOURCE_{ID_HASH}
#define RESOURCE_{ID_HASH}
#include <string>
{NS_BEGIN}
namespace {{
using namespace std::string_literals;
const inline static std::string {args.sym} = R"<!resource!>(\
"""

FILE_FOOTER = f"""\
)<!resource!>"s;
}}
{NS_END}
#endif
"""

with open(args.src, "r") as sf, open(args.dst, "w") as df:
    print(FILE_HEADER, end="", file=df)
    for line in sf:
        df.write(line)
    print(FILE_FOOTER, end="", file=df)