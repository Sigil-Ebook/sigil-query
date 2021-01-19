/**********************************************************************************
 **
 **  This file is part of SigilQuery for Gumbo
 **
 **  A C++ library that provides jQuery-like selectors for Google's Gumbo-Parser.
 **  Selector engine is an implementation based on cascadia.
 **
 **
 **  The MIT License (MIT)
 **  Copyright (c) 2021 Kevin B. Hendricks, Stratford, Ontario Canada
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "query/CDocument.h"
#include "query/CSelection.h"
#include "query/CNode.h"


static const char USEP = '\x1f'; // ascii unit separator 
static const char RSEP = '\x1e'; // ascii record separator

enum {
      TESTNO, SELECT, XMATCHES, PAGE, FIELDSIZE
} datafields;

// forward declarations
bool file_exists(const char *filename);
std::vector<std::string> splitstr(const char marker, const std::string &source, const bool keep_empty = false);


bool file_exists(const char *filename)
{
    std::ifstream file_input(filename);

    if(file_input.is_open())
    {
        file_input.close();
        return true;
    }
    
    file_input.close();
    return false;
}


std::vector<std::string> splitstr(const char marker, const std::string &source, const bool keep_empty)
{
    std::vector<std::string> res;
    std::string s(source);
    int sp = s.find(marker, 0);
        
    while(sp != std::string::npos) {
        if (sp != 0 || keep_empty) res.push_back(s.substr(0,sp));
        s.erase(0,sp+1);
        sp = s.find(marker, 0);
    }
        
    if (s != "" || keep_empty) res.push_back(s);
    return res;
}


// Application entry point
int main(int argc, char *argv[])
{

	if (argc <=  1)
    {
        std::cout << "Error did not specify path to test data file." << std::endl;
		return -1;
    }

    std::string testfile = argv[1];
	if(!file_exists(argv[1]))
	{
        std::cout << "The file \"" << testfile << "\" does not exist." << std::endl;
		return -1;
	}

    std::ifstream data_input(testfile.c_str(),std::ios::binary);
    if(data_input.bad())
	{
        std::cout << "The file \"" << testfile << "\" could not be read from." << std::endl;
		return -1;
	}

    int cnt = 0;
    int failed = 0;
    int passed = 0;
    int parser_errors = 0;
            
    while(data_input.good())
    {
        std::string arec;
        // read in the a data record and skip the newline immediately after the record separator
        // those newlines are present to keep the file easily viewed and hand editable
        getline(data_input, arec, RSEP);
        data_input.ignore(1);
        if (data_input.eof() || (!arec.empty() && arec[0]=='!') ) continue;
        
        std::vector<std::string> fields = splitstr(USEP, arec, true);
        if (fields.size() != FIELDSIZE)
        {
            std::cout << "Error in test data at record: " << cnt << " incorrect number of data fields read." << std::endl;
            data_input.close();
            return -1;
        }

        cnt++;

        int testno = std::stoi(fields[TESTNO]);
        int em = std::stoi(fields[XMATCHES]);
        std::string sel = fields[SELECT];
        std::string page = fields[PAGE];

        CDocument doc(page);
        CSelection c = doc.find(sel);
        // first check for query parser errors
        if (c.parseError())
        {
            parser_errors++;
            std::cout << "Test: " << testno << " parser error." << std::endl;
            std::cout << "    Selector: " << sel << std::endl;
            std::cout << "    XMatches: " << em << std::endl;
            std::cout << "    Page:     " << page << std::endl;
        }
        else
        {
            bool hasfails = false;                
            for (int i=0; i < c.nodeNum(); i++)
            {
                CNode aNode = c.nodeAt(i);
                std::string text = "--";
                if (aNode.valid()) text = aNode.ownText();
                hasfails = hasfails || (text.find("FAIL") != std::string::npos);
            }
            
            if (em == c.nodeNum() && !hasfails)
            {
                passed++;
                std::cout << "Test: " << testno << " passed." << std::endl;
                for (int i=0; i < c.nodeNum(); i++)
                {
                    CNode aNode = c.nodeAt(i);
                    std::string text = "--";
                    if (aNode.valid()) text = aNode.ownText();
                    std::cout << "    Text:    " << text << std::endl;
                }
            }
            else
            {
                failed++;
                std::cout << "Test: " << testno << " **failed**." << std::endl;
                std::cout << "    Selector: " << sel << std::endl;
                std::cout << "    XMatches: " << em << std::endl;
                std::cout << "    Found:    " << c.nodeNum() << std::endl;
                for (int i=0; i < c.nodeNum(); i++)
                {
                    CNode aNode = c.nodeAt(i);
                    std::string tag = aNode.tag();
                    
                    std::string text = "--";
                    if (aNode.valid()) text = aNode.ownText();
                    std::cout << "    Tag:     " << aNode.tag() << std::endl;
                    std::cout << "    Text:    " << text << std::endl;
                }
                
            std::cout << "    Page:     " << page << std::endl;
            }
        }
    }
    data_input.close();
    std::cout << "\n\nTest Summary  " << std::endl;
    std::cout << "    Tests run:    " << cnt << std::endl;
    std::cout << "    Tests passed: " << passed << std::endl;
    std::cout << "    Tests failed: " << failed << std::endl;
    std::cout << "    Tests errors: " << parser_errors << std::endl;
    
    return 0;
}
