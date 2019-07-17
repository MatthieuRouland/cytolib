/*
 * in_polygon.hpp
 *
 *  Created on: May 8, 2019
 *      Author: wjiang2
 */

#ifndef INST_INCLUDE_CYTOLIB_IN_POLYGON_HPP_
#define INST_INCLUDE_CYTOLIB_IN_POLYGON_HPP_

#include "datatype.hpp"
#include <vector>

#include <algorithm>
using namespace std;

typedef vector<unsigned> INDICE_TYPE;
namespace cytolib
{
struct POINT
{
//	this struct is the same as coordinate but without pb member functions so that flowCore doesn't need to depend on pb

	EVENT_DATA_TYPE x,y;
	POINT(EVENT_DATA_TYPE _x,EVENT_DATA_TYPE _y){x=_x;y=_y;};
	POINT(){};
};

void in_polygon(EVENT_DATA_TYPE * xdata, EVENT_DATA_TYPE * ydata, const vector<POINT> & vertices, INDICE_TYPE & parentInd, bool is_negated, INDICE_TYPE &res);
}

#endif /* INST_INCLUDE_CYTOLIB_IN_POLYGON_HPP_ */
