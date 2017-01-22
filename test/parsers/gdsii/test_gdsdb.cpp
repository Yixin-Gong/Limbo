/*************************************************************************
    > File Name: test_gdsdb.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 17 Jan 2017 10:12:44 PM CST
 ************************************************************************/

#include <iostream>
#include <limbo/parsers/gdsii/gdsdb/GdsIO.h>
#include <limbo/preprocessor/Msg.h>

int main(int argc, char** argv)
{
    limbo::GdsParser::GdsDB db; 
    if (argc > 2 && argc <= 4)
    {
        // test simple read and write
        limbo::GdsParser::GdsReader reader (db); 
        limboAssert(reader(argv[1]));

        for (std::vector<limbo::GdsParser::GdsCell>::const_iterator it = db.cells().begin(); it != db.cells().end(); ++it)
            std::cout << "cell: " << it->name() << std::endl; 

        // write 
        limbo::GdsParser::GdsWriter gw (db); 
        gw(argv[2]);

        std::cout << "4 arguments to test flatten: input gds, output gds, flat output gds, flat cell name" << std::endl;
    }
	else if (argc > 4)
    {
        // test flatten 
        limbo::GdsParser::GdsCell flatCell = db.extractCell(argv[4]);

        limbo::GdsParser::GdsDB flatDB; 
        flatDB.addCell(flatCell); 

        // write flatten cell 
        limbo::GdsParser::GdsWriter flatGw (flatDB); 
        flatGw(argv[3]);
    }
	else std::cout << "at least 4 arguments are required: input gds, output gds, flat output gds, flat cell name" << std::endl;

	return 0;
}