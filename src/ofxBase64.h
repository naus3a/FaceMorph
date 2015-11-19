//
//  ofxBase64.h
//
//
//  Created by enrico<nausea>viola on 3/9/15.
//
//  This is a wrapper around René Nyffenegger's base64 encoding/decoding class, so the basic encode/functions should be considered his own copyright.
//
/*Copyright (C) 2004-2008 René Nyffenegger
  Copyright (C) 2015 Enrico Viola
This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

René Nyffenegger rene.nyffenegger@adp-gmbh.ch
Enrico Viola enrico@augmentedrealityag.com
*/

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofxBase64{
public:
    ofxBase64();
    bool is_base64(unsigned char c);
    string encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    string encode(ofImage * img);
    string decode(std::string const& encoded_string);
    ofPixels decode(string encoded_string, int w, int h, int nc);
	void savePixelsToXml(ofxXmlSettings * xml, ofPixels * pix, string tagname="img");
	ofPixels loadPixelsFromXml(ofxXmlSettings * xml, string tagName="img", int tagId=0);
    string base64_chars;
};