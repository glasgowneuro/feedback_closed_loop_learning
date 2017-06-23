class Bandpass;

#ifndef _Bandpass
#define _Bandpass

#include <assert.h>

class Bandpass {
public:
	/**
	 * Constructor
	 **/
	Bandpass();
	
	/**
	 * Filter
	 **/
	double filter(double v);

	/**
	 * Calculates the coefficients
	 * The frequency is the normalized frequency in the range [0..0.5].
	 **/
	void calcPolesZeros(double f,double r);

	/**
	 * sets the filter parameters
	 **/
	void setParameters(double frequency, double Qfactor);

	/**
	 * Generates an acsii file with the impulse response of the filter.
	 **/
	void impulse(char* name);

	/**
	 * normalization
	 **/
	double norm;

	void calcNorm(double f);

	/**
	 * Generates an ASCII file with the transfer function
	 **/
	void transfer(char* name);

	/**
	 * Gets the actual output of the filter. Same as the return value
	 * of the function "filter()".
	 **/
	double getActualOutput() {return actualOutput;};

	/**
	 * The coefficients of the denominator of H(z)
	 **/
	double denominator0;
	double denominator1;
	double denominator2;

	/**
	 * The coefficients of the enumerator of H(z)
	 **/
	double enumerator0;
	double enumerator1;
	double enumerator2;

	/**
	 * Delay lines for the IIR-Filter
	 **/
	double buffer0;
	double buffer1;
	double buffer2;

	/**
	 * The actual output of the filter (the return value of the filter()
	 * function).
	 **/
	double actualOutput;
};

#endif