/*
 *        File: LUT.cpp
 *      Author: Nick Dodds <Nick1787@gmail.com>
 * Description: 1D and 2D Lookup Tables
 *				No Extrapolation outside tables bounds
 *				Linear interpolation between points
 * ----------------------------------------------------------------
 *    Revision:
 *		09172015 - NRD - Initial Version
 * ----------------------------------------------------------------
 */
 
#include "LUT.h"
#include <iostream>

using namespace std;

const float LUT1D_XDATA[2] = {0,10};
const float LUT1D_ZDATA[2] = {5,10};

const float LUT2D_XDATA[2] = {0,10};
const float LUT2D_YDATA[2] = {0,10};
const float LUT2D_ZDATA[2][2] = {{5,10},{10,15}};

//Instantiate a LUT1D
LUT1D<2> Tbl1D(LUT1D_XDATA,LUT1D_ZDATA);
LUT2D<2,2> Tbl2D(LUT2D_XDATA,LUT2D_YDATA,LUT2D_ZDATA);

int main(){
	
	cout << endl;
	cout << "1D Lookup -1: " << Tbl1D.lookup(-1) << endl;
	cout << "1D Lookup  5: " << Tbl1D.lookup(5) << endl;
	cout << "1D Lookup 11: " << Tbl1D.lookup(11) << endl << endl;
	
	cout << "2D Lookup -1, -1: " << Tbl2D.lookup(-1,-1) << endl;
	cout << "1D Lookup -1,  5: " << Tbl2D.lookup(-1,5) << endl;
	cout << "1D Lookup  5, -1: " << Tbl2D.lookup(5,-1) << endl;
	cout << "1D Lookup  5,  5: " << Tbl2D.lookup(5,5) << endl;
	cout << "1D Lookup  5, 11: " << Tbl2D.lookup(5,11) << endl;
	cout << "1D Lookup  11, 5: " << Tbl2D.lookup(11,5) << endl;
	cout << "1D Lookup  11,11: " << Tbl2D.lookup(11,11) << endl;
	
	return 0;
}