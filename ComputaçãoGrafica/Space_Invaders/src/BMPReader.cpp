/*
 *  BMPReader.cpp
 *  SpotAndTiles
 *
 *  Created by brisson on 12/05/17.
 *  Copyright 2012 IST. All rights reserved.
 *
 */

#include "BMPReader.h"
#include <iostream>

#define STD_OFFSET 54

using std::ios;


BMPloader::BMPloader( const string filename)
{
	mImage = NULL;
	mWidth = mHeight = 0;
	mIsOK  = false;
	
	infile = new ifstream( filename.c_str(), ios::in | ios::binary);
	if ( !infile->fail() )
	{
		char ch1, ch2;
		infile->get( ch1); infile->get( ch2);
		if ( ch1 == 'B' && ch2 == 'M' )
		{
			unsigned int total = getLong();
			infile->seekg( 4, ios::cur);
			unsigned int offset = getLong();
			infile->seekg( 0, ios::end);
			unsigned int length = infile->tellg();
			if ( length == total && offset == STD_OFFSET )
			{
				infile->seekg( 18, ios::beg);
				unsigned int w = getLong();
				unsigned int h = getLong();
				infile->seekg( 2, ios::cur);
				unsigned int bitCount = getShort();
				unsigned int compression = getLong();
				unsigned int sizeImage = getLong();
				if ( bitCount == 24 && compression == 0 && 
					 ( sizeImage == 0 || sizeImage == (3*w*h) )  &&
					 (3*w*h+offset) <= length )
				{
					total = 3 * w * h;
					infile->seekg( offset, ios::beg);
					mImage = new char[ total];
					infile->read( mImage, total);
					if ( infile->gcount() == total )
					{
						mWidth  = w;
						mHeight = h;
						mIsOK   = true;
						char * ptr = mImage;
						for ( int i=0; i<(w*h); i++)
						{
							ch1      = *(ptr+2);
							*(ptr+2) = *ptr;
							*ptr     = ch1;
							ptr+=3;
						}
					}
				}
			}
		}
		infile->close();
	}
	delete infile;
}


BMPloader::~BMPloader()
{
	if ( mImage != NULL )
		delete mImage;
}


const unsigned int BMPloader::getShort()
{
	char ch1, ch2;
	infile->get( ch2); infile->get( ch1);
	return (ch1 & 0x00ff) * 256 + (ch2 & 0x00ff);
}


const unsigned int BMPloader::getLong()
{
	unsigned int low = getShort();
	return getShort() * 0x10000 + low;
}

