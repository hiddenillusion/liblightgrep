/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <boost/program_options.hpp>
#include <scope/testrunner.h>

#include "test_search_data.h"

namespace po = boost::program_options;

int main(int argc, char** argv) {
  po::options_description desc("Allowed Options");

  desc.add_options()
    ("help,h", "print help")
    ("test", "run unit tests (same as test command)")
    ("long-test", "run long test")
    ("debug", "print debuging info")
    ;

  po::options_description opts;
  opts.add(desc);

  po::variables_map optsMap;
  po::store(po::command_line_parser(argc, argv).options(opts).run(), optsMap);
  po::notify(optsMap);

  try {
    if (optsMap.count("help")) {
      std::cerr << desc << std::endl;
    }
    else if (optsMap.count("test")) {
      return scope::DefaultRun(std::cout, argc, argv) ? 0 : 1;
    }
    else if (optsMap.count("long-test")) {
      longTest();
    }
    else {
      // this should be impossible
      std::cerr << "Unrecognized command. Use --help for list of options."
                << std::endl;
      return 1;
    }
  }
  catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    return 1;
  }
  return 0;
}
