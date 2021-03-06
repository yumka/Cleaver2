Cleaver2
========

Cleaver2 Release Source Code

This is the open-source repository for Cleaver2, a tetrahedral meshing tool. 
This distribution comes with both a command-line interface, and a GUI.

Aknowledgements
========

<h4>Cleaver - A MultiMaterial Tetrahedral Meshing Library and Application</h4>

The Cleaver Library is based on the 'Lattice Cleaving' algorithm:

<strong>Bronson J., Levine, J., Whitaker R., "Lattice Cleaving: Conforming Tetrahedral Meshes of Multimaterial Domains with Bounded Quality". Proceedings of the 21st International Meshing Roundtable (San Jose, CA, Oct 7-10, 2012)</strong>

The method is theoretically guaranteed to produce valid meshes with bounded dihedral angles, while still conforming to multimaterial material surfaces. Empirically these bounds have been shown to be significant.

Cleaver is an Open Source software project that is principally funded through the SCI Institute's NIH/NIGMS CIBC Center. Please use the following acknowledgment and send us references to any publications, presentations, or successful funding applications that make use of NIH/NIGMS CIBC software or data sets.

"This project was supported by the National Institute of General Medical Sciences of the National Institutes of Health under grant number P41GM103545."

<strong>Author: </strong> Jonathan Bronson<br/>
<strong>Contributor: </strong> Ross Whitaker<br/>
<strong>Contributor: </strong> Josh Levine<br/>
<strong>Contributor: </strong> Shankar Sastry<br/>
<strong>Developer: </strong> Brig Bagley<br/>

Building Cleaver2
========
Requirements: Git, CMake, Qt4 -OR- Qt5<br/>
Suggested:  QtCreator cross-platform IDE<br/>
We recommend building cleaver outside of the source tree. <br/>
From Cleaver2 directory:<br/>

<h4>Linux, OSX</h4>
<code>mkdir build</code><br/>
<code>cd build</code><br/>
<code>cmake ../src</code><br/>
<code>make</code><br/><br/>
NOTE: You may need to run ccmake ../src to set the locations of some of the components if your environment is not already set up. (e.g. Qt5Widgets_DIR="/usr/lib/Qt/5.3.0/gcc/lib/cmake/Qt5Widgets").

<h4>Windows</h4>
Additional requirements for GUI: glew (<link>http://glew.sourceforge.net/</link>) -OR- Qt5 and glext
(<link>http://sourceforge.net/projects/glextwin32/</link>)<br/>
From Developer Command Prompt: (e.g.  Visual Studio 10 (32bit)) <br/>

<code>mkdir build</code><br/>
<code>cd build</code><br/>
<code>cmake ../src</code><br/>
<code>nmake</code><br/>



NOTE: If you do not have your development environment paths set up, you can set them with cmake-gui, qt-creator, or pass library paths directly to command line like below:<br/>

<h5>For Qt 4</h5>
<code>cmake -G "NMake Makefiles" -DGLEW_LIBRARY="C:\glew\glew-1.10.0\lib\Release\Win32\glew32.lib" -DGLEW_INCLUDE_DIR="C:\glew\glew-1.10.0\include" -DQT_QMAKE_EXECUTABLE="C:\Qt\4.8.5\bin\qmake.exe" -DQT_VERSION="4" ..\src</code><br/>
<h5>For Qt 5</h5>
<code>cmake -G "NMake Makefiles" -DGLEXT_LIBRARY="C:\glext\glext\lib\glext.lib" -DGLEXT_INCLUDE_DIR="C:\glext\glext\include" -DQt5Widgets_DIR="c:\Qt\5.3.0\5.3\msvc2010_opengl\lib\cmake\Qt5Widgets" -DQt5OpenGL_DIR="c:\Qt\5.3.0\5.3\msvc2010_opengl\lib\cmake\Qt5OpenGL"  -DQT_VERSION="5" ..\src</code><br/>
<br/>

Using Cleaver2
========
Inside of your build directory:<br/>
<code>bin/cleaver-gui</code><br/>
Or, for the command line tool:<br/>
<code> bin/cleaver-cli --help</code><br/>
For a list of command line tool options.


    Command line flags:
      -h [ --help ]            display help message
      -v [ --verbose ]         enable verbose output
      --version                display version information
      --material_fields arg    material field paths
      --background_mesh arg    input background mesh
      --mesh_mode arg          background mesh mode
      --mesh_improve           improve background quality
      --alpha arg              initial alpha value
      --alpha_long arg         alpha long value for regular mesh_mode
      --alpha_short arg        alpha short value for regular mesh_mode
      --sizing_field arg       sizing field path
      --grading arg            sizing field grading
      --multiplier arg         sizing field multiplier
      --scale arg              sizing field scale
      --padding arg            volume padding
      --accelerate             use acceleration structure
      --write_background_mesh  write background mesh
      --strip_exterior         strip exterior tetrahedra
      --output_path arg        output path prefix
      --output_name arg        output mesh name
      --output_format arg      output mesh format
      --strict                 warnings become errors
Known Issues
========

 * On larger data sets with a potentially high number of quadruple points (> 3 material fields), some functions are not implemented that ensure valid tets and meshes, causing bad tets in the final output. This code is being implemented now for a future release.
 * The wind up order for tets may be incorrect for jacobian calculations. This may or may not be fixed in the future. There is a flag in the command line interface that re-orders vertices at the end of meshing if this is important for your output. 
