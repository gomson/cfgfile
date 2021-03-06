
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2017 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// C++ include.
#include <fstream>

// UnitTest include.
#include <UnitTest/unit_test.hpp>

// test include.
#include "test.hpp"


cfg::vector_t load_config( const std::string & file_name )
{
	cfg::tag_vector_t< cfgfile::string_trait_t > read_tag;

	std::ifstream file( file_name );

	try {
		if( file.good() )
		{
			cfgfile::read_cfgfile( read_tag, file, file_name );

			file.close();
		}
	}
	catch( const cfgfile::exception_t<> & )
	{
		file.close();

		throw;
	}

	return read_tag.get_cfg();
}

void check_config( const cfg::vector_t & cfg )
{
	CHECK_CONDITION( cfg.vector().size() == 1 )
	CHECK_CONDITION( cfg.vector().at( 0 ).string_field() == "one" )
	CHECK_CONDITION( cfg.vector().at( 0 ).no_value_field() == true )
	CHECK_CONDITION( cfg.vector().at( 0 ).int_field().size() == 2 )
	CHECK_CONDITION( cfg.vector().at( 0 ).int_field().at( 0 ) == 100 )
	CHECK_CONDITION( cfg.vector().at( 0 ).int_field().at( 1 ) == 200 )
	CHECK_CONDITION( cfg.vector().at( 0 ).custom_field().m_value == 300 )
}


TEST( Generator, testAllIsOk )
{
	check_config( load_config( "test.cfg" ) );
} // testAllIsOk

int main()
{
	RUN_ALL_TESTS()

	return 0;
}
