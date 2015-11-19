
//
//  ofxBase64.cpp
//
//  Created by nausea on 3/9/15.
//
//  This is a wrapper around René Nyffenegger's base64 encoding/decoding class, so this source code follows his own original copyright note:
/*Copyright (C) 2004-2008 René Nyffenegger
 
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
 */

#include "ofxBase64.h"

ofxBase64::ofxBase64(){
    base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
}

bool ofxBase64::is_base64(unsigned char c){
    return (isalnum(c) || (c == '+') || (c == '/'));
}

string ofxBase64::encode(const unsigned char *bytes_to_encode, unsigned int in_len){
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
}

string ofxBase64::decode(const std::string &encoded_string){
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}

string ofxBase64::encode(ofImage *img){
    unsigned char * pix = img->getPixels();
    int iW = (int)img->getWidth();
    int iH = (int)img->getHeight();
    int nC = img->getPixelsRef().getNumChannels();
    return encode(pix, nC*iW*iH);
}

ofPixels ofxBase64::decode(string encoded_string, int w , int h, int nc){
    ofPixels rPix;
    string sPix = decode(encoded_string);
    unsigned char * pix = (unsigned char *)sPix.c_str();
    rPix.setFromPixels(pix, w, h, nc);
    return rPix;
}

void ofxBase64::savePixelsToXml(ofxXmlSettings * xml, ofPixels * pix, string tagName){
	unsigned char * data = pix->getPixels();
	int ww = (int)pix->getWidth();
	int hh = (int)pix->getHeight();
	int nc = pix->getNumChannels();
	string sPix = encode(data, nc*ww*hh);
	xml->addTag(tagName);
	xml->addAttribute(tagName, "w", ww, 0);
	xml->addAttribute(tagName, "h", hh, 0);
	xml->addAttribute(tagName, "c", nc, 0);
	xml->setValue(tagName, sPix, 0);
}

ofPixels ofxBase64::loadPixelsFromXml(ofxXmlSettings * xml, string tagName, int tagId){
	ofPixels pix;
	if(xml->tagExists(tagName, tagId)){
		int ww = xml->getAttribute(tagName, "w", 0, tagId);
		int hh = xml->getAttribute(tagName, "h", 0, tagId);
		int nc = xml->getAttribute(tagName, "c", 1, tagId);
		int totP = ww*hh*nc;
		string s64 = xml->getValue(tagName, "0", tagId);
		pix = decode(s64, ww, hh, nc);
	}
	return pix;
}