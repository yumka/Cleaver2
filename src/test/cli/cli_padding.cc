//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
// Cleaver - A MultiMaterial Conforming Tetrahedral Meshing Library
//
// -- Cleaver-CLI Tests
//
// Primary Author: Brig Bagley (brig@sci.utah.edu)
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//  Copyright (C) 2014, Brig Bagley
//  Scientific Computing & Imaging Institute
//
//  University of Utah
//  //
//  //  Permission is  hereby  granted, free  of charge, to any person
//  //  obtaining a copy of this software and associated documentation
//  //  files  ( the "Software" ),  to  deal in  the  Software without
//  //  restriction, including  without limitation the rights to  use,
//  //  copy, modify,  merge, publish, distribute, sublicense,  and/or
//  //  sell copies of the Software, and to permit persons to whom the
//  //  Software is  furnished  to do  so,  subject  to  the following
//  //  conditions:
//  //
//  //  The above  copyright notice  and  this permission notice shall
//  //  be included  in  all copies  or  substantial  portions  of the
//  //  Software.
//  //
//  //  THE SOFTWARE IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY  OF ANY
//  //  KIND,  EXPRESS OR IMPLIED, INCLUDING  BUT NOT  LIMITED  TO THE
//  //  WARRANTIES   OF  MERCHANTABILITY,  FITNESS  FOR  A  PARTICULAR
//  //  PURPOSE AND NONINFRINGEMENT. IN NO EVENT  SHALL THE AUTHORS OR
//  //  COPYRIGHT HOLDERS  BE  LIABLE FOR  ANY CLAIM, DAMAGES OR OTHER
//  //  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  //  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//  //  USE OR OTHER DEALINGS IN THE SOFTWARE.
//  //-------------------------------------------------------------------
//  //-------------------------------------------------------------------
#include "cli_common.h"

// Tests scaling IO for CLI
TEST(CLIRegressionTests, Padding) {
  //make sure there is a command interpreter
  ASSERT_EQ(0,(int)!(std::system(NULL)));
  //setup the line that calls the command line interface
  std::string log = "padding_output.txt";
  std::string output = " > " + data_dir + log + " 2>&1";
  std::string option = " --padding 2 --write_background_mesh ";
  std::string line = (command + name + path + option + input + output);
  //make sure there was no error from the command line
  ASSERT_EQ(0, std::system(line.c_str()));
  //move the other generated files in the current dir to the test dir
  for(size_t i = 0; i < num_files; i++) {
    std::system(("mv " + files[i] + " " + data_dir).c_str());
  }
  //compare all of the related files
  EXPECT_NO_FATAL_FAILURE(compareNodeFiles(
        data_dir + "padding/output.node",
        data_dir + "output.node"));
  EXPECT_NO_FATAL_FAILURE(compareEleFiles(
        data_dir + "padding/output.ele",
        data_dir + "output.ele"));
  EXPECT_NO_FATAL_FAILURE(compareNodeFiles(
        data_dir + "padding/bgmesh.node",
        data_dir + "bgmesh.node"));
  EXPECT_NO_FATAL_FAILURE(compareEleFiles(
        data_dir + "padding/bgmesh.ele",
        data_dir + "bgmesh.ele"));
  //delete the output files from this test
  for(size_t i = 0; i < num_files; i++) {
    std::system(("rm " + data_dir + files[i]).c_str());
  }
  std::system(("rm " + data_dir + "output.info").c_str());
  std::system(("rm " + data_dir + "output.node").c_str());
  std::system(("rm " + data_dir + "output.ele").c_str());
  std::system(("rm " + data_dir + "bgmesh.ele").c_str());
  std::system(("rm " + data_dir + "bgmesh.node").c_str());
  std::system(("rm " + data_dir + log).c_str());
}
