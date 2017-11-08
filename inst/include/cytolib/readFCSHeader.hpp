/*
 * readFCSHeader.hpp
 *
 *  Created on: Sep 21, 2017
 *      Author: wjiang2
 */

#ifndef INST_INCLUDE_CYTOLIB_READFCSHEADER_HPP_
#define INST_INCLUDE_CYTOLIB_READFCSHEADER_HPP_

#include <fstream>
#include <cstring>
#include "global.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;


enum class TransformType {none, linearize, scale,linearize_with_PnG_scaling};
enum class endianType {big, small, mixed};
struct FCS_Header{
	float FCSversion;
	int textstart, textend, datastart, dataend, anastart, anaend, additional;
};

//typedef unordered_map <string, string> KEY_WORDS;
/**
 * this class mimic the map behavior so that the same code
 * can be used for both map and vector based container
 */
class vec_kw_constainer{
 typedef vector<pair <string, string>> KW_PAIR;
 KW_PAIR kw;
public:
 typedef KW_PAIR::iterator iterator;
 typedef KW_PAIR::const_iterator const_iterator;
 void resize(size_t n){kw.resize(n);}
 size_t size(){return kw.size();}
 KW_PAIR getPairs(){return kw;}
 iterator end(){return kw.end();}
 iterator begin(){return kw.begin();}
 iterator find(const string &key){
         return std::find_if(kw.begin(), kw.end(), [key](const pair<string, string> & p){return p.first == key;});
 }

 string & operator [](const string & key){
         iterator it = find(key);
         if(it==end())
         {
                 kw.push_back(pair<string, string>(key, ""));
                 return kw.back().second;
         }
         else
                 return it->second;
   }
 pair <string, string> & operator [](const int & n){
	 return kw[n];
 }
};


typedef vec_kw_constainer KEY_WORDS;

typedef float EVENT_DATA_TYPE;
typedef vector<EVENT_DATA_TYPE> EVENT_DATA_VEC;
typedef unique_ptr<EVENT_DATA_TYPE[] > EVENT_DATA_PTR;

/**
 * the struct that stores the FCS  header parse arguments
 */
struct FCS_READ_HEADER_PARAM{
	bool isEmptyKeyValue; //whether allow the keyword value to be empty. When true, then double delimiter will be considered as empty keyword value.
	bool ignoreTextOffset; //whether to ignore the offset recorded in the text segment of FCS
	int nDataset; // which data set to be parsed when multi-data segments are detected
	FCS_READ_HEADER_PARAM(){
		isEmptyKeyValue = false;
		ignoreTextOffset = false;
		nDataset = 1;
	};

};
/**
 * parameters parsed from keywords, but may be accessed frequently later thus saved as the copy
 * in this struct for fast and easy query
 */
struct cytoParam{
	string channel, marker;
	EVENT_DATA_TYPE min, max, PnG;
//	pair<EVENT_DATA_TYPE, EVENT_DATA_TYPE> PnE;//replace pair with simple array since it is not clear how to create compound type for pair
	EVENT_DATA_TYPE PnE[2];
	int PnB;

};
/**
 * parse the FCS header and Text segment
 *
 * @param in (input) the file stream object opened from FCS file
 * @param header (output) the FCS_Header object to store the result of FCS header
 * @param keys (output) the KEY_WORDS object to store parsed keywords
 * @param params (output) cytoParam container to store the parsed parameters
 * @param config (input) FCS_READ_HEADER_PARAM object gives the parsing arguments for header
 */
void readHeaderAndText(ifstream &in,FCS_Header & header, KEY_WORDS & keys, vector<cytoParam> & params, const FCS_READ_HEADER_PARAM & config);


#endif /* INST_INCLUDE_CYTOLIB_READFCSHEADER_HPP_ */
