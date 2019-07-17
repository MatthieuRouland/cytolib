/*
 * compensation.hpp
 *
 *  Created on: Apr 8, 2016
 *      Author: wjiang2
 */

#ifndef INCLUDE_COMPENSATION_HPP_
#define INCLUDE_COMPENSATION_HPP_

#include "transformation.hpp"

namespace cytolib
{
class compensation{
public:
	string cid;
	string prefix;
	string suffix;
	string name;
	string comment;// store "Acquisition-defined" when the spillOver matrix is not supplied and cid==-1
	vector<string> marker;
	vector<double> spillOver;
	compensation(){};
	/**
	 * constructor from the existing spillover matrix
	 * @spillover arma:mat representing a col-major matrix
	 * @_markers string vector
	 */
	compensation(mat spillMat, vector<string> _markers);
	/**
	 * convert spillover matrix from row-majored std::vector
	 * to col-majored arma::ma
	 * @return
	 */
	mat get_spillover_mat ()const;
	void update_channels(const CHANNEL_MAP & chnl_map);
	void convertToPb(pb::COMP & comp_pb);
	compensation(const pb::COMP & comp_pb);
	bool empty() const{return marker.size() == 0;}
};

};

#endif /* INCLUDE_COMPENSATION_HPP_ */
