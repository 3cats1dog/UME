#pragma once
#ifndef _WAVEFORMDATA_H_
#define _WAVEFORMDATA_H_




using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Xml::Serialization;

#include "Global.h";

namespace WaveFormMeasument {

	public ref class WaveFormData
	{
	private:
		double _T;
		double _V;
		double _No;
	public:
		property double T { double get() { return _T; } void set(double value) { _T = value; } }
		property  double V { double get() { return _V; } void set(double value) { _V = value; } }
		property  int No { int get() { return _No; } void set(int value) { _No = value; } }
		WaveFormData()
		{

		}

		WaveFormData(double _v, int _n)
		{
			V = _v; No = _n;
		}
		WaveFormData(double _v, int _n, double _t)
		{
			V = _v; No = _n; T = _t;
		}
		WaveFormData(String^ line, int _no)
		{
			//Veri Genel yapısı
			//+1.23456789E-03, +11.664SECS, +236RDNG,
			array<String^>^ parts = line->Split(',');
			double _V, _T;
			int _N;
			double::TryParse(parts[0], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _V);
			if (parts->Length ==2)
			{
				double::TryParse(parts[1]->Replace("SECS", ""), System::Globalization::NumberStyles::Any, MeasLab::G::trcul(), _T);
			}
			if (parts->Length == 3)
			{
				int::TryParse(parts[2]->Replace("RDNG", ""), System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _N);
			}
			V = _V;
			T = _T;
			No = _N;
			No = _no;
		}
		virtual String^ ToString() override sealed {
			return String::Format("{1}{0}{2}{0}{3}{0}", MeasLab::G::DELIMETER, No, T.ToString("F5", MeasLab::G::trcul()), V.ToString("F5", MeasLab::G::trcul()));
		}
	};
}


#endif // !_WAVEFORMDATA_H_
