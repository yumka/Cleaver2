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
TEST(CLIRegressionTests, MATLAB) {
  //make sure there is a command interpreter
  ASSERT_EQ(0,(int)!(std::system(NULL)));
  //setup the line that calls the command line interface
  std::string log = "matlab_output.txt";
  std::string output = " > " + data_dir + log + " 2>&1";
  std::string line = (command + name + path + 
      " --output_format matlab " + input + output);
  //make sure there was no error from the command line
  ASSERT_EQ(0, std::system(line.c_str()));
  //move the other generated files in the current dir to the test dir
  for(size_t i = 0; i < num_files; i++) {
    std::system(("mv " + files[i] + " " + data_dir).c_str());
  }
  line = "diff " + data_dir + "matlab/output.mat " 
    + data_dir +  "output.mat";
  ASSERT_EQ(0,std::system(line.c_str()));

  //delete the output files from this test
  for(size_t i = 0; i < num_files; i++) {
    std::system(("rm " + data_dir + files[i]).c_str());
  }
  std::system(("rm " + data_dir + "output.info").c_str());
  std::system(("rm " + data_dir + "output.mat").c_str());
  std::system(("rm " + data_dir + log).c_str());
}
