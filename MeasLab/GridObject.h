#pragma once
#ifndef  _GRID_OBJECT__ 
#define  _GRID_OBJECT__ 

#include "WaveFormMeasurement.h"
#include "Extensions.h"


namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace WaveFormMeasument;


	ref class GridObject
	{
	private:
		int _TNo;
		int _SNo;

		double _V_kV;
		double _V_Raw;
		double _ratio;

		double _V_kV_UUT;
		double _V_Raw_UUT;
		double _ratio_UUT;

		double _DMM_kV;
		double _UUT_kV;


	public:
		bool hasUUT;
		bool isPeak;
		property int SampleNo { int get() { return _SNo; } void set(int value) { _SNo = value; } }
		property int TestNo { int get() { return _TNo; } void set(int value) { _TNo = value; } }

		property double V_kV { double get() { return _V_kV; } void set(double value) { _V_kV = value; } }
		property double V_Raw { double get() { return _V_Raw;  }  void set(double value) { _V_Raw = value; } }
		property double Ratio { double get() { return _ratio; } void set(double value) { _ratio = value; } }
		property int V_kV_Mag { int get() { return Extensions::GetMagValue(_V_kV); }}
		property int V_Raw_Mag { int get() { return Extensions::GetMagValue(_V_Raw); }}
		property String^ STR_V_kV { String^ get() { return (V_kV_Mag >= 3) ? (_V_kV / 1000.0).ToString("F7") : _V_kV.ToString("F7"); }}
		property String^ STR_V_Raw { String^ get() { return (V_Raw_Mag >= 3) ? (_V_Raw / 1000.0).ToString("F7") : _V_Raw.ToString("F7"); }}

		property double V_kV_UUT { double get() { return _V_kV_UUT; } void set(double value) { _V_kV_UUT = value; } }
		property double V_Raw_UUT { double get() { return _V_Raw_UUT; }  void set(double value) { _V_Raw_UUT = value; } }
		property double Ratio_UUT { double get() { return _ratio_UUT; } void set(double value) { _ratio_UUT = value; } }

		property int V_kV_UUT_Mag { int get() { return Extensions::GetMagValue(_V_kV_UUT); }}
		property int V_Raw_UUT_Mag { int get() { return Extensions::GetMagValue(_V_Raw_UUT); }}
		property String^ STR_V_kV_UUT { String^ get() { return (V_kV_UUT_Mag >= 3) ? (_V_kV_UUT / 1000.0).ToString("F7") : _V_kV_UUT.ToString("F7"); }}
		property String^ STR_V_Raw_UUT { String^ get() { return (V_Raw_UUT_Mag >= 3) ? (_V_Raw_UUT / 1000.0).ToString("F7") : _V_Raw_UUT.ToString("F7"); }}

		property double ScaleFactor { double get() {
			if (V_Raw_UUT == 0) return 1.0;
			return (V_kV * _DMM_kV) / (V_Raw_UUT * _UUT_kV);
			}
		}

		GridObject() {
			_DMM_kV = 1.0;
			_UUT_kV = 1.0;
		}

		GridObject(WaveFormSample^ wfs, bool isUUT, int MeasType) {
			_DMM_kV = 1.0;
			_UUT_kV = 1.0;

			Update(wfs, isUUT, MeasType);
		}

		void Update(WaveFormSample^ wfs, bool isUUT, int MeasType)
		{
			if (!isUUT)
			{
				_SNo = wfs->SampleNo;
				switch (MeasType)
				{
				case 0:			//rms
					V_kV = wfs->Vrms;
					Ratio = wfs->Ratio;
					break;
				case 1:			//paek
					V_kV = wfs->VpeakRoot2;
					Ratio = wfs->Ratio_Peak;
					break;
				case 2:			//dc;
					V_kV = wfs->Vdc;
					Ratio = wfs->Ratio_DC;
					break;
				} 
				V_Raw = V_kV / Ratio;
			}
			else
			{
				_SNo = wfs->SampleNo;

				switch (MeasType)
				{
				case 0:			//rms
					V_kV_UUT = wfs->Vrms;
					Ratio_UUT = wfs->Ratio;
					break;
				case 1:			//peak;
					V_kV_UUT = wfs->VpeakRoot2;
					Ratio_UUT = wfs->Ratio_Peak;
					break;
				case 2:			//dc
					V_kV_UUT = wfs->Vdc;
					Ratio_UUT = wfs->Ratio_DC;
					break;
				}

				V_Raw_UUT = V_kV_UUT / Ratio_UUT;
			}

		}
		virtual String^ ToString() override sealed {
			return SampleNo.ToString() + MeasLab::G::DELIMETER +
				V_kV.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				V_Raw.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Ratio.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				V_kV_UUT.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				V_Raw_UUT.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Ratio_UUT.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER;
		}

	static String^ Headers(bool isPeak)
	{
		if (isPeak)
		{
			return L"No" + MeasLab::G::DELIMETER +
				L"Vpeak/√2 (kV)" + MeasLab::G::DELIMETER +
				L"Vpeak/√2 (V)" + MeasLab::G::DELIMETER +
				L"s.f. Vpeak" + MeasLab::G::DELIMETER +
				L"Vpeak/√2 (kV) (UUT)" + MeasLab::G::DELIMETER +
				L"Vpeak/√2 (V) (UUT)" + MeasLab::G::DELIMETER +
				L"s.f. Vpeak (UUT)" + MeasLab::G::DELIMETER;
		}
		else
		{

			return L"No" + MeasLab::G::DELIMETER +
				L"Vrms (kV)" + MeasLab::G::DELIMETER +
				L"Vrms (V)" + MeasLab::G::DELIMETER +
				L"s.f. Vrms" + MeasLab::G::DELIMETER +
				L"Vrms (kV) (UUT)" + MeasLab::G::DELIMETER +
				L"Vrms (V) (UUT)" + MeasLab::G::DELIMETER +
				L"s.f. Vrms (UUT)" + MeasLab::G::DELIMETER;
		}
	}
};

}

#endif // ! _GRID_OBJECT__ 
