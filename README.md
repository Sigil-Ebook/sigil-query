 Sigil-Query for Sigil's version of Google's Gumbo HTML5 Parser
=======================================================================

 A C++ library that provides jQuery-like selectors for Google's Gumbo-Parser
 as used in Sigil:

 * https://github.com/Sigil-Ebook/Sigil
 * https://github.com/Sigil-Ebook/sigil-gumbo

 Hard Fork of: "gumbo-query" https://github.com/lazytiger/gumbo-query

 With modifications to work with Sigil's internal version of 
 gumbo which has many bugs fixed, speed-ups, and support for both 
 xhtml5 and html5.

 Many query related bugs have been tracked down and fixed for nth and type
 based pseudo classes and support has been added for :lang() and :root selectors.

 A test data set and querytester code is included to help track down any remaining
 issues.

 The Selector engine is an implementation based on cascadia.


License
=======
 
 Sigil-Query is available under the MIT License as follows:

 
   The MIT License (MIT)
   Copyright (c) 2021 Kevin B. Hendricks, Stratford, Ontario Canada
   Copyright (c) 2015 baimashi.com. 
   Copyright (c) 2011 Andy Balholm. All rights reserved.
 
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
 
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 


Build
=====

Sigil-Query uses CMake (version 3.0 or later) to build in a crossplatform manner
on Windows, MacOS and Linux.  The key is to build completely outside
the source repo.

The commands for Linux and MacOS are very similar.  The MacOS build commands are
presented below:

    mkdir build
    cd build
    cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.12 -DCMAKE_BUILD_TYPE=Release \\
          -DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/ \\
          ../sigil-query/
    make -j4



Testing
=======
To run the querytester from the build directory:

    cd querytest
    ./querytester PATH_TO_TEST_DATA_FILE

The test data file can be found in:
    

The test data is a compilation of my own testcases along with modified versions of 
the test data sets from the following two sites:

* https://github.com/TechnikEmpire/GQ/tests
    - Available under an MIT License

* http://tools.css3.info/selectors-test/test.html
    - The CSS Selector compatibility testsuite was the winning entry of the
      CSS3.info summer contest 2006. Created by Niels Leenheer, 
      http://rakaz.nl/. All testcases are licensed 
      under a BSD-like license. 
