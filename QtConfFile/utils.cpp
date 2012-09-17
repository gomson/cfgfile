
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>
#include <QtConfFile/private/Parser>
#include <QtConfFile/private/InputStream>

// Qt include.
#include <QtCore/QFile>
#include <QtCore/QTextStream>


namespace QtConfFile {

//
// readQtConfFile
//

void
readQtConfFile( Tag & tag, const QString & fileName, QTextCodec * codec )
{
	QFile file( fileName );

	if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		throw Exception( QString( "Couldn't open file: \"%1\"" )
			.arg( fileName ) );

	try {
		InputStream stream( &file, codec, fileName );

		Parser parser( tag, stream );

		parser.parse();

		file.close();
	}
	catch( ... )
	{
		file.close();

		throw;
	}
}


//
// writeQtConfFile
//

void
writeQtConfFile( const Tag & tag, const QString & fileName, QTextCodec * codec )
{
	QFile file( fileName );

	if( !file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) )
		throw Exception( QString( "Couldn't open file: \"%1\"" )
			.arg( fileName ) );

	try {
		QString content = tag.print();

		QTextStream stream( &file );
		stream.setCodec( codec );

		stream << content;

		file.close();
	}
	catch( ... )
	{
		file.close();

		throw;
	}
}

} /* namespace QtConfFile */
