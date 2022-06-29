#pragma once
#ifndef _WAVEFORM_SAMPLE_H_
#define _WAVEFORM_SAMPLE_H_



using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Xml::Serialization;

#include "WaveFormData.h";
namespace WaveFormMeasument {
	public ref class WaveFormSample
	{
	private:
		double _Vrms;
		double _Vpeak;
		double _Vpeakroot2;
		double _Vdc;
		int _SNo;
		String^ _etiket;
		double ROUNDMAX = 10000000;
	public:

		double Kademe; //{ get; set; }
		double NPLC; //{ get; set; }
		const double Freq = 50;
		double Vpeak;
		double Vptp;
		double Ratio;
		double Ratio_Peak;
		double Ratio_DC;
		int DataCount;

		double DecideDiff = 0.001;

		property int SampleNo { int get() { return _SNo; } void set(int value) { _SNo = value; } }
		//No Turncate
		//property double Vrms { double get() { return Math::Truncate(_Vrms * ROUNDMAX) / ROUNDMAX; } void set(double value) { _Vrms = value; } }
		//property double Vdc { double get() { return Math::Truncate(_Vdc * ROUNDMAX) / ROUNDMAX; } void set(double value) { _Vdc = value; } }
		//property double VpeakRoot2 { double get() { return Math::Truncate(_Vpeakroot2 * ROUNDMAX) / ROUNDMAX; }  void set(double value) { _Vpeakroot2 = value; } }
		property double Vrms { double get() { return _Vrms; } void set(double value) { _Vrms = value; } }
		property double Vdc { double get() { return _Vdc; } void set(double value) { _Vdc = value; } }
		property double VpeakRoot2 { double get() { return _Vpeakroot2; }  void set(double value) { _Vpeakroot2 = value; } }
		array<WaveFormData^>^ Data;


		//property double Ratio { double get() { return _ratio; } void set(double value) { _ratio = value; } }
		//property double Ratio_Peak { double get() { return _ratio_peak; } void set(double value) { _ratio_peak = value; } }
		//property int DataCount {  int  get() { if (Data == nullptr) return 0; return Data->Length; } }
		//property double Vpeak { double get() { return Math::Truncate(_Vpeak * 10000) / 10000; } void set(double value) { _Vpeak = value; }}
		//property String^ Etiket { String^ get() { return _etiket; } void set(String^ value) { _etiket = value; } }

		WaveFormSample(int _no, int size)
		{
			SampleNo = _no;
			Data = gcnew array<WaveFormData^>(size);
		}

		~WaveFormSample()
		{
			delete Data;
		}

		void CalculateRMS()
		{
			_Vrms = 0;
			DataCount = 0;
			if (Data != nullptr)
				DataCount = Data->Length;
			if (DataCount == 0) return;


			try
			{
				List<double>^ vrmsList = gcnew List<double>();
				 
				double dc = 0;
				double s = 0;
				int i;
				double maxValue = -9999999;
				double minValue = +9999999;
				//Calculate DC offset
				if (G::mySet->useDCOffset)
				{
					for (i = 0; i < Data->Length; i++)
					{
						dc += Data[i]->V;
					}
					dc = dc / Data->Length;
				}

				for (i = 0; i < Data->Length; i++)
				{
					if (maxValue < Data[i]->V) { maxValue = Data[i]->V; }
					if (minValue > Data[i]->V) { minValue = Data[i]->V; }
					//s += Data[i]->V * Data[i]->V;
					s += (Data[i]->V - dc) * (Data[i]->V - dc);
					vrmsList->Add(Math::Sqrt(s / (i + 1)));
				}
				Vrms = Math::Sqrt(s / Data->Length);
				Vdc = dc;
				//Find Peak
				Vpeak = maxValue;	// Data.Max(z = > z.V);
				Vptp = maxValue - minValue;
				VpeakRoot2 = Vptp / 2.0 / Math::Sqrt(2);

				//Now Add Scale Factor;

				Vrms *= Ratio;							// / 1000.0;					//Convert kV
				Vpeak *= Ratio_Peak;					// / 1000.0;			//Convert kV
				Vdc *= Ratio_DC;						// / 1000.0;				//Convert kV
				VpeakRoot2 *= Ratio_Peak;				// / 1000.0;      //Convert kV
				for (i = 0; i < Data->Length; i++)
				{
					Data[i]->V *= Ratio;				// / 1000.0;       //Convert kV
				}
			}
			catch (Exception^ ex)
			{


			}
		}

		bool isSameNumber(double v1, double v2)
		{
			return (Math::Abs(1.0 - v1 / v2) < DecideDiff);
			return true;
		}
		bool WaveFormComplete(int i, double fPoint, bool firstDir)
		{
			if (i == 0) return false;
			if (i >= DataCount - 1)
			{
				if (Data[i]->V > Data[i - 1]->V != firstDir) return false;
				return isSameNumber(Data[i]->V, fPoint);
			}
			else
			{
				if (Data[i + 1]->V > Data[i]->V != firstDir) return false;
				return isSameNumber(Data[i]->V, fPoint);
			}
		}

		void ResetDecideDiff()
		{
			 DecideDiff = 0.001;
		}

		void CalculateRMSMulti(int sampleForEachWave)
		{
			_Vrms = 0;
			DataCount = 0;
			if (Data != nullptr)
				DataCount = Data->Length;
			if (DataCount == 0) return;

			double sum = 0;
			int adet = 0;

			if (DataCount <= sampleForEachWave)
			{
				for (int i = 0; i < Data->Length; i++)
				{
					adet++;
					sum += Data[i]->V * Data[i]->V;
				}
				Vrms = Math::Sqrt(sum / adet);
			}
			else
			{
				List<double>^ rmsList = gcnew List<double>();
				double fPoint = Data[0]->V;
				bool firstDir = Data[1]->V > Data[0]->V;
				double Diff = Data[1]->V - Data[0]->V;



				for (int i = 0; i < Data->Length; i++)
				{
					adet++;
					sum += Data[i]->V * Data[i]->V;
					if (WaveFormComplete(i, fPoint, firstDir))
					{
						rmsList->Add(Math::Sqrt(sum / adet));
						sum = 0;
						adet = 0;
					}
				}

				if (rmsList->Count == 0)
				{
					//just pack every thing;
					DecideDiff += 0.001;
					if (DecideDiff > 0.15)
					{
						Vrms = Math::Sqrt(sum / adet);
					}
					else
					{
						return  CalculateRMSMulti(sampleForEachWave);
					}
				}
				else
				{
					double sumRMS = 0;
					for each (double d in rmsList) { sumRMS += d; }
					Vrms = sumRMS / rmsList->Count;

				}
			}



			double maxValue = -9999999;
			double minValue = +9999999;

			for (int i = 0; i < Data->Length; i++)
			{
				//Calculate peak, peak to peak
				if (maxValue < Data[i]->V) { maxValue = Data[i]->V; }
				if (minValue > Data[i]->V) { minValue = Data[i]->V; }
			}

			//Find Peak
			Vpeak = maxValue;	// Data.Max(z = > z.V);
			Vptp = maxValue - minValue;
			VpeakRoot2 = Vptp / 2.0 / Math::Sqrt(2);

			//Now Add Scale Factor;

			Vrms *= Ratio;							// / 1000.0;					//Convert kV
			Vpeak *= Ratio_Peak;					// / 1000.0;			//Convert kV
			VpeakRoot2 *= Ratio_Peak;				// / 1000.0;      //Convert kV
			for (int i = 0; i < Data->Length; i++)
			{
				Data[i]->V *= Ratio;				// / 1000.0;       //Convert kV
			}

		}

		virtual String^ ToString() override sealed {
			return SampleNo + MeasLab::G::DELIMETER +
				Ratio.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Ratio_Peak.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Ratio_DC.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Vrms.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				VpeakRoot2.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER +
				Vdc.ToString(MeasLab::G::trcul()) + MeasLab::G::DELIMETER;
		}
		static String^ Headers()
		{
			return L"No" + MeasLab::G::DELIMETER +
				L"s.f. Vrms" + MeasLab::G::DELIMETER +
				L"s.f. Vpeak" + MeasLab::G::DELIMETER +
				L"s.f. Vdc" + MeasLab::G::DELIMETER +
				L"Vrms (V)" + MeasLab::G::DELIMETER +
				L"Vpeak/√2 (V)" + MeasLab::G::DELIMETER +
				L"Vdc (V)" + MeasLab::G::DELIMETER;
		}
	};
}

#endif		//!_WAVEFORM_SAMPLE_H_