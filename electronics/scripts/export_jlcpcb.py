#!/usr/bin/env python3

#   Copyright 2021 Scott Bezek and the splitflap contributors
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

import argparse
import logging
import os
import subprocess
import sys

electronics_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
repo_root = os.path.dirname(electronics_root)
sys.path.append(repo_root)

from util import file_util
from export_util import (
    versioned_file,
)

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)


def export_jlcpcb(schematic, pcb):
    schematic_file = os.path.abspath(schematic)
    pcb_file = os.path.abspath(pcb)

    output_dir = os.path.join(electronics_root, 'build', 'jlc')
    file_util.mkdir_p(output_dir)

    with versioned_file(pcb_file):
        subprocess.check_call([
            'kikit',
            'fab',
            'jlcpcb',
            '--assembly',
            '--schematic',
            schematic_file,
            pcb_file,
            output_dir,
        ])


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('schematic')
    parser.add_argument('pcb')
    args = parser.parse_args()
    export_jlcpcb(args.schematic, args.pcb)
