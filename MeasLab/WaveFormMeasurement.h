#pragma once

#ifdef _WAVEFORMMEAS_H_

#endif // _WAVEFORMMEAS_H_


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Xml::Serialization;

#include "WaveFormSample.h";
 

namespace WaveFormMeasument {

	public ref  class LogChangeEventArgs : EventArgs
	{
	public:

		String^ Text;	// { get; set; }
		LogChangeEventArgs(String^ txt) { Text = txt; }
	};

	public delegate void LogChangeEventHandler(Object^, LogChangeEventArgs^);

	public enum class LogType :int
	{
		cmd = 0,
		answer = 1,
	};


	public ref class WaveFormMeasurement
	{
	public:
		 
		List<WaveFormSample^ >^ waves;
		String^ Etiket;	// { get; set; }
		double Kademe;	//{ get; set; }
		double Ratio;	//{ get; set; }
		double Ratio_Peak;	//{ get; set; }
		double Ratio_DC;	//{ get; set; }
		double NPLC;	//{ get; set; }
		int WaveCount;	//{ get; set; }
		int measType;
		int sampleForEachWave;

		//property int sampleForEachWave { int get() { return (int)(1.0 / NPLC); } };
		property int totalSampleCount { int  get() { return sampleForEachWave * WaveCount; } };
		property int toltalMsForTest { int  get() { return WaveCount * 20; } };// 1 wave 20ms


		WaveFormMeasurement()
		{
			waves = gcnew List<WaveFormSample^>();
		}
		void ReadResults(String^ rawData)
		{
			switch (measType)
			{
			case 0:		//MeasLab::MeasType::AC:
				ReadResults_Single(rawData);
				break;
			case 1:		//MeasLab::MeasType::DC:
				ReadResults_Single(rawData);
				break;
			case 2:		//MeasLab::MeasType::AC_DCSampling:
				ReadResults_WaveForm(rawData);
				break;
			default:
				break;
			}
		}

		void ReadResults_Enter(double readedRMS, double readedPeak, bool ACorDC)	//String^ rawData,
		{
			double _V = 0;
			double  _Vpeak = 0;
			double _Vdc = 0;
			int _N;
			if (ACorDC)
			{
				_V = readedRMS;
			}
			else
			{
				_Vdc = readedRMS;
			}
			_Vpeak = readedPeak;
			////Create all waveform
			//array<String^>^ lines = rawData->Split('\n');
			////First value Vrms or Vdc, second value is Vpeak;
			//if (ACorDC)
			//{
			//	double::TryParse(lines[0], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _V);
			//}
			//else
			//{
			//	double::TryParse(lines[0], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _Vdc);
			//}
			//if (lines->Length > 1)
			//{
			//	double::TryParse(lines[1], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _Vpeak);
			//	//_Vpeak /= 2.0;		//convert peak to peak to peak
			//}

			waves->Clear();
			for (int i = 0; i < WaveCount; i++) {
				WaveFormSample^ wfs = gcnew WaveFormSample(i + 1, sampleForEachWave);
				wfs->Kademe = Kademe;
				wfs->NPLC = NPLC;
				wfs->Ratio = Ratio;
				wfs->Ratio_Peak = Ratio_Peak;
				wfs->Ratio_DC = Ratio_DC;
				wfs->Vrms = _V;									//*Ratio;
				wfs->Vdc = _Vdc;
				wfs->VpeakRoot2 = _Vpeak;  
				waves->Add(wfs);
			}
		}
		static String^ CreateFakeData_Keithley(int adet)
		{
			//+1.23456789E-03, +11.664SECS, +236RDNG,
			Random^ random = gcnew Random();
			String^ data = "";
			int startPhase = random->Next(360);
			double SampleCount = 50;
			if (G::mySet->NPLC == 0.01) SampleCount = 100;
			if (G::mySet->NPLC == 0.04) SampleCount = 25;

			for (int i = startPhase; i < adet + startPhase; i++)
			{
				double sinV = Math::Sin(2 * Math::PI * i / 50);
				sinV += random->NextDouble() / 100.0;
				data += String::Format("{0:e8},{1:F3}SECS,{2}RDNG", sinV, i, i) + Environment::NewLine;
			}
			return data;
		}
		virtual String^ ToString() override sealed {
			return "Test";
		}
	private:
		void ReadResults_Single(String^ rawData) {
			//Create all waveform
			array<String^>^ lines = rawData->Split('\n');
			//First value Vrms or Vdc, second value is Vpeak;
			double _V = 0;
			double  _Vpeak = 0;
			double _Vdc = 0;
			int _N;
			double::TryParse(lines[0], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _V);
			if (lines->Length > 1)
			{
				double::TryParse(lines[1], System::Globalization::NumberStyles::Any, MeasLab::G::invcul(), _Vpeak);
				_Vpeak /= 2.0;		//convert peak to peak to peak
			}
			//double divider = showAskV ? 1000.0 : 1.0;
			waves->Clear();
			for (int i = 0; i < WaveCount; i++) {
				WaveFormSample^ wfs = gcnew WaveFormSample(i + 1, sampleForEachWave);
				wfs->Kademe = Kademe;
				wfs->NPLC = NPLC;
				wfs->Ratio = Ratio;
				wfs->Ratio_Peak = Ratio_Peak;
				wfs->Ratio_DC = Ratio_DC;
				wfs->Vrms = _V * Ratio;
				wfs->VpeakRoot2 = _Vpeak * Ratio_Peak / Math::Sqrt(2);
				wfs->Vdc = _V * Ratio_DC;
				//wfs->Vrms /= divider;			//convert to kV
				//wfs->VpeakRoot2 /= divider;		//convert to kV
				waves->Add(wfs);
			}
		}
 
		void ReadResults_WaveForm(String^ rawData)
		{
			//Create all waveform
			array<String^>^ lines = rawData->Split('\n');
			waves->Clear();
			for (int i = 0; i < WaveCount; i++) {
				WaveFormSample^ wfs = gcnew WaveFormSample(i + 1, sampleForEachWave);
				//wfs->Etiket = Etiket;
				wfs->Kademe = Kademe;
				wfs->NPLC = NPLC;
				wfs->Ratio = Ratio;
				wfs->Ratio_Peak = Ratio_Peak;
				wfs->Ratio_DC = Ratio_DC;
				waves->Add(wfs);
			}

			int wfsIndex = 0;
			int dataIndex = 0;
			int totalLineCount = 0;
			for (int i = 0; i < lines->Length; i++)
			{
				if (lines[i]->Length > 0)
				{
					totalLineCount++;
				}
			}

			if (totalLineCount < totalSampleCount)
			{
				//Bir hata var, az veri toplamışız???
				//throw  gcnew Exception(L"veri sayısı hatalı!!!");
				waves[wfsIndex]->Data = gcnew array<WaveFormData^>(totalLineCount);
			}

			for (int i = 0; i < lines->Length; i++)
			{
				if (lines[i]->Length > 0)
				{
					waves[wfsIndex]->Data[i] = gcnew WaveFormData(lines[i], dataIndex);
					dataIndex++;
					if (dataIndex >= sampleForEachWave) {
						//waves[wfsIndex]->CalculateRMS();    // Calculate peak, rms etc;
						wfsIndex++;                         // Refer new wave;
						dataIndex = 0;                      // Reset counter
					}
					if (wfsIndex >= WaveCount)
					{
						break;
					}
				}
			}

			//Veri Genel yapısı
			//+1.23456789E-03, +11.664SECS, +236RDNG,

		}

	};
}

#define _WAVEFORMMEAS_H_
