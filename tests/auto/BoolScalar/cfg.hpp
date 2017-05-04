
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

#ifndef QTCONFFILE__TEST__BOOL_SCALAR__CFG_HPP__INCLUDED
#define QTCONFFILE__TEST__BOOL_SCALAR__CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>


//
// Configuration
//

/*!
	Configuration that will be loaded from file and savend into file.

	\verbatim
	{cfg
		{withTrue "true"}
		{withFalse "false"}
	}
	\endverbatim
*/
struct Configuration {
	Configuration();

	Configuration & operator = ( const Configuration & other );

	bool m_withTrue;
	bool m_withFalse;
}; // class Configuration


//
// TagConfiguration
//

/*!
	Tag with configuration:

	\verbatim
	{cfg
		{withTrue "true"}
		{withFalse "false"}
	}
	\endverbatim
*/
class TagConfiguration
	:	public QtConfFile::TagNoValue
{
public:
	//! For reading.
	TagConfiguration();
	//! For writing.
	explicit TagConfiguration( const Configuration & cfg );

	//! \return Configuration.
	Configuration
	configuration() const;

private:
	QtConfFile::TagScalar< bool > m_withTrue;
	QtConfFile::TagScalar< bool > m_withFalse;
}; // class TagConfiguration

#endif // QTCONFFILE__TEST__BOOL_SCALAR__CFG_HPP__INCLUDED
