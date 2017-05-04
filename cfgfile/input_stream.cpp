
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2016 Igor Mironchik

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
#include <QtConfFile/private/InputStream>

// Qt include.
#include <QtCore/QTextStream>


namespace QtConfFile {

static const QChar c_carriageReturn = QChar( '\n' );
static const QChar c_lineFeed = QChar( '\r' );

//
// InputStream::InputStreamPrivate
//

class InputStream::InputStreamPrivate {
public:
	InputStreamPrivate( QIODevice * dev, QTextCodec * codec,
		const QString & fileName )
		:	m_stream( dev )
		,	m_lineNumber( 1 )
		,	m_columnNumber( 1 )
		,	m_fileName( fileName )
	{
		m_stream.setCodec( codec );
	}

	bool isNewLine( QChar & ch )
	{
		if( ch == c_carriageReturn )
			return true;
		else if( ch == c_lineFeed )
		{
			QChar nextChar = 0x00;
			m_stream >> nextChar;

			if( nextChar == c_carriageReturn )
			{
				ch == nextChar;

				return true;
			}
			else
			{
				m_returnedChar = nextChar;

				return true;
			}
		}
		else
			return false;
	}

	QTextStream m_stream;
	qint64 m_lineNumber;
	qint64 m_columnNumber;
	QString m_fileName;
	QChar m_returnedChar;
}; // struct InputStream::InputStreamPrivate


//
// InputStream
//

InputStream::InputStream( QIODevice * dev, QTextCodec * codec,
	const QString & fileName )
	:	d( new InputStreamPrivate( dev, codec, fileName ) )
{
}

InputStream::~InputStream()
{
}

QChar
InputStream::get()
{
	++d->m_columnNumber;

	if( !d->m_returnedChar.isNull() )
	{
		QChar ch = d->m_returnedChar;

		d->m_returnedChar = QChar();

		if( d->isNewLine( ch ) )
		{
			++d->m_lineNumber;
			d->m_columnNumber = 1;
		}

		return ch;
	}

	QChar ch = 0x00;

	d->m_stream >> ch;

	if( d->isNewLine( ch ) )
	{
		++d->m_lineNumber;
		d->m_columnNumber = 1;
	}

	return ch;
}

void
InputStream::putBack( QChar ch )
{
	--d->m_columnNumber;

	if( ch == c_carriageReturn || ch == c_lineFeed )
		--d->m_lineNumber;

	d->m_returnedChar = ch;
}

qint64
InputStream::lineNumber() const
{
	return d->m_lineNumber;
}

qint64
InputStream::columnNumber() const
{
	return d->m_columnNumber;
}

bool
InputStream::atEnd() const
{
	if( d->m_returnedChar.isNull() )
		return d->m_stream.atEnd();
	else
		return false;
}

const QString &
InputStream::fileName() const
{
	return d->m_fileName;
}

} /* namespace QtConfFile */
