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
 
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "../LUT.h"
 
using namespace std;

//1D LUT Table Data
const float LUT1D_XDATA[_1D_XSIZE_] = { _1D_XDATA_ };
const float LUT1D_ZDATA[_1D_ZSIZE_] = { _1D_ZDATA_ };

const float LUT1D_TESTDATA_IN[_1D_NUMTESTPTS_] = { _1D_TESTDATA_IN_ };
const float LUT1D_TESTDATA_OUT[_1D_NUMTESTPTS_] = { _1D_TESTDATA_OUT_ };

//Instantiate a LUT1D
LUT1D<_1D_XSIZE_> Tbl1D(LUT1D_XDATA,LUT1D_ZDATA);

//2D LUT Table Data
const float LUT2D_XDATA[_2D_XSIZE_] = { _2D_XDATA_ };
const float LUT2D_YDATA[_2D_YSIZE_] = { _2D_YDATA_ };
const float LUT2D_ZDATA[_2D_YSIZE_][_2D_XSIZE_] = { _2D_ZDATA_ };

const float LUT2D_TESTDATA_IN1[_2D_NUMTESTPTS_] = { _2D_TESTDATA_IN1_ };
const float LUT2D_TESTDATA_IN2[_2D_NUMTESTPTS_] = { _2D_TESTDATA_IN2_ };
const float LUT2D_TESTDATA_OUT[_2D_NUMTESTPTS_] = { _2D_TESTDATA_OUT_ };

//Instantiate a LUTD
LUT2D<_2D_YSIZE_,_2D_XSIZE_> Tbl2D(LUT2D_XDATA,LUT2D_YDATA, LUT2D_ZDATA);
 
int main(int argc, char* argv[]){
	
	//Test the 1D LUT
	cout << "-LUT1D---------------------------" <<endl;
	int numFails = 0;
	for(int i=0;i<_1D_NUMTESTPTS_;i++){
		float result = Tbl1D.lookup(LUT1D_TESTDATA_IN[i] );
		cout << "[" << i << "]" << "\tIN: " << LUT1D_TESTDATA_IN[i] << "\tEXPECTED: " << LUT1D_TESTDATA_OUT[i] << "\tRESULT: " << result << "\tP/F: ";
		if(fabs(LUT1D_TESTDATA_OUT[i]-result)<0.001){
			cout << "PASS" <<endl;
		}else{
			cout << "FAIL!!!" << endl;
			numFails = numFails+1;
		}
	}
	
	cout << endl << "Number of Failures:" << numFails << endl << endl;
	
	
	//Test the 1D LUT
	cout << "-LUT2D---------------------------" <<endl;
	numFails = 0;
	for(int i=0;i<_1D_NUMTESTPTS_;i++){
		float result = Tbl2D.lookup(LUT2D_TESTDATA_IN1[i], LUT2D_TESTDATA_IN2[i] );
		cout << "[" << i << "]" << "\tIN1: " << LUT2D_TESTDATA_IN1[i]  << "\tIN2: " << LUT2D_TESTDATA_IN2[i] << "\tEXPECTED: " << LUT2D_TESTDATA_OUT[i] << "\tRESULT: " << result << "\tP/F: ";
		if(fabs(LUT2D_TESTDATA_OUT[i]-result)<0.001){
			cout << "PASS" <<endl;
		}else{
			cout << "FAIL!!!" << endl;
			numFails = numFails+1;
		}
	}
	
	cout << endl << "Number of Failures:" << numFails << endl << endl;
 }