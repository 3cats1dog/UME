#pragma once
#pragma once
#ifndef _Results_H_
#define _Results_H_




using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Xml::Serialization;
 
#include "Global.h";

namespace WaveFormMeasument {
	
	
	public ref class sfResults
	{
	private:
		int _no;
		double _uut;
		double	_uut_s;
		double _ref;
		double _ref_s;
	public:
		property double v_UUT { double get() { return _uut; } void set(double value) { _uut = value; } }
		property  double sf_UUT { double get() { return _uut_s; } void set(double value) { _uut_s = value; } }
		property double v_REF { double get() { return _ref; } void set(double value) { _ref = value; } }
		property  double sf_REF { double get() { return _ref_s; } void set(double value) { _ref_s = value; } }

		property  int No { int get() { return _no; } void set(int value) { _no = value; } }
		sfResults() {

		}



	};

#endif