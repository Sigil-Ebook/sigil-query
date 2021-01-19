/**********************************************************************************
 **
 **  SigilQuery for Gumbo
 **
 **  A C++ library that provides jQuery-like selectors for Google's Gumbo-Parser.
 **  Selector engine is an implementation based on cascadia.
 **
 **  Based on: "gumbo-query" https://github.com/lazytiger/gumbo-query
 **  With bug fixes, extensions and improvements
 **
 **  The MIT License (MIT)
 **  Copyright (c) 2021 Kevin B. Hendricks, Stratford, Ontario Canada
 **  Copyright (c) 2015 baimashi.com. 
 **  Copyright (c) 2011 Andy Balholm. All rights reserved.
 **
 **
 **  Permission is hereby granted, free of charge, to any person obtaining a copy
 **  of this software and associated documentation files (the "Software"), to deal
 **  in the Software without restriction, including without limitation the rights
 **  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 **  copies of the Software, and to permit persons to whom the Software is
 **  furnished to do so, subject to the following conditions:
 **
 **  The above copyright notice and this permission notice shall be included in
 **  all copies or substantial portions of the Software.
 **
 **  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 **  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 **  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 **  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 **  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 **  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 **  THE SOFTWARE.
 **
 **********************************************************************************/

#ifndef CQUERYUTIL_H_
#define CQUERYUTIL_H_

#include "gumbo/gumbo.h"
#include "gumbo/gumbo_edit.h"

#include <string>
#include <vector>

class CQueryUtil
{
    public:

        static std::string tolower(std::string s);

        static std::vector<GumboNode*> unionNodes(std::vector<GumboNode*> aNodes1,
                std::vector<GumboNode*> aNode2);

        static bool nodeExists(std::vector<GumboNode*> aNodes, GumboNode* apNode);

        static std::string nodeText(GumboNode* apNode);
    
        static std::string nodeOwnText(GumboNode* apNode);

    private:

        static void writeNodeText(GumboNode* apNode, std::string& aText);
    

};

#endif /* CQUERYUTIL_H_ */
