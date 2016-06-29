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
 
#ifndef _LUT_H
#define _LUT_H

#include <stdlib.h>

/**************************
*	LUT1D
**************************/
template< size_t N>
class LUT1D{
  private:
    float _xvals[N];
    float _zvals[N];
    int _count;
	
  public:
	//Constructor
	LUT1D(float xvals[N], float zvals[N]){
		//Copy the X data
		_count = N;
		for(int i=0; i<N; i++){
			_xvals[i] = xvals[i];
			_zvals[i] = zvals[i];
		}
	};
	
	//Constructor - Constant Float Data
	LUT1D(const float xvals[N],const float zvals[N]){
		//Copy the X data
		_count = N;
		for(int i=0; i<N; i++){
			_xvals[i] = xvals[i];
			_zvals[i] = zvals[i];
		}
	};
	
	//Lookup Algoritm
	float lookup(float xval){
		  if( xval <= _xvals[0]){
			 return _zvals[0]; 
		  }else{
			if( xval >= _xvals[_count-1]){
			  return _zvals[_count-1];
			}else{
			  // In the Middel of Table, interpolate to find value.
			  int ix = 0;
			  for ( ix = 0; ix < _count - 1 ; ix++ )
			  {
				  //Find the location we are in the table.
				  if( (xval >= _xvals[ix]) && (xval < _xvals[ix+1])){
					  break;
				  }
			  }
			  
			  //Interpolate z value
			  return ((xval - _xvals[ix])*((_zvals[ix+1] - _zvals[ix])/(_xvals[ix+1]-_xvals[ix])) + _zvals[ix]);
			}
		  }
	};
};


/**************************
*	LUT2D
**************************/
template<size_t M,size_t N>
class LUT2D{
  private:
    float _xvals[N];
    float _yvals[M];
    float _zvals[M][N];
    int _countx;
    int _county;
	
  public:
	//Constructor
	LUT2D(float xvals[N], float yvals[M], float zvals[M][N]){
		_countx = N;
		_county = M;
		
		//Copy the X data
		for(int i=0; i<N; i++){
			_xvals[i] = xvals[i];
		}
		
		//Copy the Y data
		for(int i=0; i<M; i++){
			_yvals[i] = yvals[i];
		}

		//float zvals_temp[leny*lenx];
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				_zvals[j][i] = zvals[j][i] ;
			}
		}
	};
	
	//Constructor - Constant Float Data
	LUT2D( const float xvals[N], const float yvals[M], const float zvals[M][N]){
		_countx = N;
		_county = M;
		
		//Copy the X data
		for(int i=0; i<N; i++){
			_xvals[i] = xvals[i];
		}
		
		//Copy the Y data
		for(int i=0; i<M; i++){
			_yvals[i] = yvals[i];
		}

		//float zvals_temp[leny*lenx];
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				_zvals[j][i] = zvals[j][i] ;
			}
		}
	};
	
	//Lookup Algoritm
    float lookup(float xval, float yval){
		int xi_lower = 0;
		int xi_upper = 0;
		int yi_lower = 0;
		int yi_upper = 0;
		
		//Bound X
		if( xval <= _xvals[0]){
			xval = _xvals[0];
			if(_countx > 1){
				xi_lower = 0; 
				xi_upper = 1;
			}else{
				xi_lower = 0; 
				xi_upper = 0;
			}
		}else if(xval >= _xvals[_countx-1]){
			xval = _xvals[_countx-1];
			if(_countx > 1){
				xi_lower = _countx-2;
				xi_upper = _countx-1;
			}else{
				xi_lower = _countx-1; 
				xi_upper = _countx-1;
			}
		}else{
		  // In the Middel of Table, interpolate to find value.
		  int ix = 0;
		  for ( ix = 0; ix < _countx - 1 ; ix++ )
		  {
			  //Find the location we are in the table.
			  if( (xval >= _xvals[ix]) && (xval < _xvals[ix+1])){
				  xi_lower = ix;
				  xi_upper = ix+1;
				  break;
			  }
		  }
		}
		
		//Bound Y
		if( yval <= _yvals[0]){
			yval = _yvals[0];
			if(_county > 1){
				yi_lower = 0; 
				yi_upper = 1;
			}else{
				yi_lower = 0; 
				yi_upper = 0;
			}
		}else if(yval >= _yvals[_county-1]){
			yval = _yvals[_county-1];
			if(_county > 1){
				yi_lower = _county-2;
				yi_upper = _county-1;
			}else{
				yi_lower = _county-1; 
				yi_upper = _county-1;
			}
		}else{
		  // In the Middel of Table, interpolate to find value.
		  int iy = 0;
		  for ( iy = 0; iy < _county - 1 ; iy++ )
		  {
			  //Find the location we are in the table.
			  if( (yval >= _yvals[iy]) && (yval < _yvals[iy+1])){
				  yi_lower = iy;
				  yi_upper = iy+1;
				  break;
			  }
		  }
		}
		
		//Lookup Z values
		float z11 = _zvals[yi_lower][xi_lower];
		float z12 = _zvals[yi_lower][xi_upper];
		float z21 = _zvals[yi_upper][xi_lower];
		float z22 = _zvals[yi_upper][xi_upper];
		
		//Interpolate along the X axis
		float z1x = z11 + (xval-_xvals[xi_lower])*(z12-z11)/(_xvals[xi_upper]-_xvals[xi_lower]);
		float z2x = z21 + (xval-_xvals[xi_lower])*(z22-z21)/(_xvals[xi_upper]-_xvals[xi_lower]);
		
		//Interpolate along y axis
		float z = z1x + (yval - _yvals[yi_lower])*(z2x-z1x)/(_yvals[yi_upper]-_yvals[yi_lower]);
		
		//Return Interpolated Value
		return z;
	};
};

#endif
