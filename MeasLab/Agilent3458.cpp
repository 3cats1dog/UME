#include "Agilent3458.h"

using namespace AgilentDMM;
//using namespace Ivi::Visa::FormattedIO;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

bool Agilent3458::SendIDN( String^% _anwser) {
	if (isFake)
	{
		 _anwser = "Keysight 3548A, xxxxxxxx, y.yy";
		 return true; 
	}
	else
	{
		return SendCommand("ID?", _anwser);
	}
	return true;
}


bool Agilent3458::ChangeVoltageRange(VoltageRange range) {
	String^ ACDC = "DCV";
	if (meastype == MeasType::AC) ACDC = "ACV";
	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01:
		SendCommand(ACDC + " 0.1");
		break;
	case MeasLab::VoltageRange::VOLT_1:
		SendCommand(ACDC + " 1");
		break;
	case MeasLab::VoltageRange::VOLT_10:
		SendCommand(ACDC + " 10");
		break;
	case MeasLab::VoltageRange::VOLT_100:
		SendCommand(ACDC + " 100");
		break;
	case MeasLab::VoltageRange::VOLT_1000:
		SendCommand(ACDC + " 1000");
		break;
	case MeasLab::VoltageRange::AUTO:
		SendCommand(ACDC + " AUTO");
		break;
	default:
		break;
	}
	return true;
}

bool Agilent3458::GetTerminalSide()
{
	String^ termSide = "";
	bool sonuc= SendCommand("TERM?", termSide);
	//	0	OPEN
	// 	1	FRONT
	//  2	REAR
	//FRON or REAR
	//true or false;
	if (sonuc)
		TerminalSide = termSide->Contains("1");
	return sonuc;
}

bool Agilent3458::ChangeNPLC(double nplc)
{
	//50 Hz
	//NPLC0   => 25E-6	=> 500ns => 
	//NPLC0.5 => 500E-3 => 10ms => 
	//NPLC1   => 1		=> 20ms => 
	//NPLC10  => 10		=> 200ms => 
	//NPLC11  => 20		=> 200ms => 

	return true;
}


void Agilent3458::SetInitConfig() {
	SendCommand("END ALWAYS");
	SendCommand("TARM HOLD");
	SendCommand("DCV");
	SendCommand("TRIG AUTO");
	
 }

bool Agilent3458::ZInput()
{
	//ON => 10 MOhm fixed resistance
	//OFF => 10MOhm or 10GOHM depending voltage range;
	if (G::mySet->useFixedZInput)
	{
		SendCommand("FIXEDZ ON");
	}
	else
	{
		SendCommand("FIXEDZ OFF");
	}
	return true;
}

bool Agilent3458::PrepareLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
		SendCommand("PRESET NORM"); //!DINT FORMATS, TARM SYN, TRIG AUTO;
		//SendCommand("DISP OFF,***AC***"); //***GODS_ACVL***
		SendCommand("DISP ON"); 
		SendCommand("TARM HOLD");
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("TRIG AUTO");
		SendCommand("OFORMAT ASCII");
		SendCommand("TIMER 400E-3");    //500 ms of each reading;
		//SendCommand(String::Format("NRDGS {0} TIMER",1));
		SendCommand("TARM SGL");
		break;
	case MeasLab::MeasType::DC:
		SendCommand("PRESET NORM"); //!DINT FORMATS, TARM SYN, TRIG AUTO;
		//SendCommand("DISP OFF,***DC***"); //***GODS_ACVL***
		SendCommand("DISP ON"); 
		SendCommand("TARM HOLD");
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("TRIG AUTO");
		SendCommand("OFORMAT ASCII");
		SendCommand("TIMER 400E-3");    //500 ms of each reading;
		//SendCommand(String::Format("NRDGS {0} TIMER", 1));
		//SendCommand("TARM SGL");
		break;
	case MeasLab::MeasType::AC_DCSampling:
		SendCommand("PRESET FAST");	//!TARM SYN, TRIG AUTO, DINT FORMATS
		SendCommand("DISP OFF,***VLF***");
		SendCommand("TARM HOLD");
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("NPLC " + NPLC.ToString(MeasLab::G::invcul()));
		//SendCommand("APER 0.0049"); 
		//SendCommand("APER 0.049");
		SendCommand("MEM FIFO");
		SendCommand("OFORMAT DINT"); 
		SendCommand(String::Format("SWEEP {0},{1}", TIMER.ToString(MeasLab::G::invcul()), WaveFormSampleCount));
		//SendCommand("SWEEP 0.05,200");
		//SendCommand("SWEEP 0.01,200");
		// 
		// 
		//Change loop structure no need send first read in init section
		//SendCommand(String::Format("SWEEP {0},{1}", APER.ToString(MeasLab::G::invcul()), WaveFormSampleCount));
		//SendCommand("TARM SGL");
		ReadByteCount = WaveFormSampleCount * 4;	//double int
		break;
	default:
		break;
	}

	return true;
};

bool Agilent3458::PrepareNextLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		//SendCommand("INIT");
		//SendCommand(String::Format("NRDGS {0} TIMER", 1));
		SendCommand("TARM SGL");
		break;
	case MeasLab::MeasType::AC_DCSampling:
		//SendCommand("SWEEP 0.01,200");
		//AddLogText("PrepareNextLiveData" + Environment::NewLine);
		SendCommand("TARM SGL");
		break;
	}
	return true;
};


bool Agilent3458::ReadLiveData(String^% _rawdata) {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		if (isFake) {
			System::Threading::Thread::Sleep(200);
			Random^ random = gcnew Random();
			double data = 1;
			switch (range)
			{
			case MeasLab::VoltageRange::VOLT_01: data = 0.4515E-01;				break;
			case MeasLab::VoltageRange::VOLT_1:data = 8.4515E-01;				break;
			case MeasLab::VoltageRange::VOLT_10:data = 6.455E+00;				break;
			case MeasLab::VoltageRange::VOLT_100:data = 20.4515E-00;			break;
			case MeasLab::VoltageRange::VOLT_1000:data = 200.4515E-00;			break;
			}
			_rawdata = (data + random->NextDouble() / 100.0).ToString();
			//_rawdata += "\n" + (data + random->NextDouble() / 100.0).ToString();
			return true;
		}

		return SendCommand("", _rawdata);
		break;
	case MeasLab::MeasType::AC_DCSampling:
		if (isFake)
		{
			System::Threading::Thread::Sleep(600);
			_rawdata = CreateFakeWaveFormRawData(WaveFormSampleCount);		// WaveFormMeasument::WaveFormMeasurement::CreateFakeData(1000);
			return true;
		}
		else
		{
			ReadStatus();
			currentStatus = (STB_3458A)STBByte;
			if (currentStatus.HasFlag(STB_3458A::DataAvaliable))
			{
				VLFData = gcnew List<int>();
				bool keepReading = true;
				String^ compactData = "";
				while (keepReading)
				{  
					responseMode = CommMode::Binary;
					SendCommand("", compactData);
					//Convert data to general array;
					int i = 0;

					while (i < compactData->Length - 7)
					{
						String^ HexStr = compactData->Substring(i, 8);
						VLFData->Add(Convert::ToInt32(HexStr, 16));
						i += 8;
					}
					//while (i < answerbyte->Count - 4)
					//{
					//	String^ HexStr = answerbyte[i].ToString("X2") + answerbyte[i + 1].ToString("X2") + answerbyte[i + 2].ToString("X2") + answerbyte[i + 3].ToString("X2");
					//	VLFData->Add(Convert::ToInt32(HexStr, 16));
					//	i += 4;
					//}
					keepReading = false;
					//if (VLFData->Count < WaveFormSampleCount) keepReading = false;

				}
				responseMode = CommMode::ASCII;
				String^ scaleSTR = "1.0";
				SendCommand("ISCALE?", scaleSTR);
				double::TryParse(scaleSTR, ScaleCoeff);
				_rawdata = "";
				for (int k = 0; k < VLFData->Count; k++)
				{
					_rawdata += String::Format("{0},{1:F5}SECS", (VLFData[k] * ScaleCoeff).ToString("E8", G::invcul()), k) + Environment::NewLine;

				}
				return true;
			}
			return	false;
		}
		break;
	}
};

String^ Agilent3458::CreateFakeWaveFormRawData(int adet) {
	//+1.23456789E-03, +11.664SECS, +236RDNG,
	Random^ random = gcnew Random();
	String^ data = "";
	int startPhase = random->Next(360);
	double SampleCount = (double)WaveFormSampleCount;

	double baseVal = 1;
	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01: baseVal = 0.4515E-01;				break;
	case MeasLab::VoltageRange::VOLT_1:baseVal = 8.4515E-01;				break;
	case MeasLab::VoltageRange::VOLT_10:baseVal = 6.455E+00;				break;
	case MeasLab::VoltageRange::VOLT_100:baseVal = 20.4515E-00;			break;
	case MeasLab::VoltageRange::VOLT_1000:baseVal = 200.4515E-00;			break;
	}
	for (int i = startPhase; i < adet + startPhase; i++)
	{
		double sinV = Math::Sin(2 * Math::PI * i / WaveFormSampleCount);
		sinV += random->NextDouble() / 100.0;
		data += String::Format("{0},{1:F5}SECS", (sinV * baseVal).ToString("E8", G::invcul()), i) + Environment::NewLine;
	}
	return data;
}

void Agilent3458::CalculateParam() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC: 
		WaveFormSampleCount = 1;
		break;
	case MeasLab::MeasType::DC:
		WaveFormSampleCount = 1;
		break;
	case MeasLab::MeasType::AC_DCSampling:
		double WaveLengthSeconds = 1.0 / SampleFreq;
		if (SampleFreq >= 40)
		{
			WaveFormSampleCount = G::mySet->DesiredVLFCount2;;
		}
		else
		{
			WaveFormSampleCount = G::mySet->DesiredVLFCount;
		}

		TIMER = WaveLengthSeconds / WaveFormSampleCount;
		double APER_raw = TIMER / 2;// -0.00005;
		//if (SampleFreq < 0.05)
		//{
		//	APER_raw = TIMER - 0.1;
		//}
		//else
		//{

		//}

		if (APER_raw < 100E-9)
		{
			APER_raw = 100E-9;
			TIMER = APER_raw;
			WaveFormSampleCount = WaveLengthSeconds / TIMER;
		}

		APER_raw = Math::Floor(APER_raw / 100E-9) * 100E-9;
		 

		//if  (APER_raw < 500E-09)
		//{
		//	APER_raw = 500E-9;
		//	WaveFormSampleCount = WaveLengthSeconds / APER_raw;
		//}

		APER = APER_raw;
		ApertureTime = APER;
		break;
	}
};

bool Agilent3458::GetLineFreq() {

	SendCommand("SYSTem:LFRequency?");
	return true;
}

bool Agilent3458::CheckDataReady() {
	if (isFake)
	{
		dataReady = true;
		return dataReady;
		//double waitMs = APER * WaveFormSampleCount * 1000.0;
		//System::Threading::Thread::Sleep(waitMs);
	}

	ReadStatus();
	currentStatus = (STB_3458A)STBByte;

	hasError = currentStatus.HasFlag(STB_3458A::Error);

	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		dataReady = currentStatus.HasFlag(STB_3458A::DataAvaliable);
		break;
	case MeasLab::MeasType::AC_DCSampling:
		dataReady = currentStatus.HasFlag(STB_3458A::ReadyFor);
		break;
	}

	return dataReady;
}

void Agilent3458::CheckError()
{
	ReadStatus();
	currentStatus = (STB_3458A)STBByte;
	hasError = currentStatus.HasFlag(STB_3458A::Error);
}

bool Agilent3458::ReadError()
{
	ErrorStr = "";
	String^ errStr = "";

	ReadStatus();
	currentStatus = (STB_3458A)STBByte;
	if (currentStatus.HasFlag(STB_3458A::DataAvaliable))
	{
		SendCommand("", errStr);
	}
	errStr = "";

	while (currentStatus.HasFlag(STB_3458A::Error))
	{
		SendCommand("ERRSTR?", errStr);
		if (errStr == "")
		{
			SendCommand("*RST");
			return false;
		}
		ErrorStr += errStr + Environment::NewLine;
		ReadStatus();
		currentStatus = (STB_3458A)STBByte;
	}
	hasError = false;
	return true;
}

String^ Agilent3458::ReturnSTB() {
	ReadStatus();
	currentStatus = (STB_3458A)STBByte;
	String^ txt = "3458A" + Environment::NewLine;;
	txt += "DataAvaliable:" + (currentStatus.HasFlag(STB_3458A::DataAvaliable) ? "1" : "0") + Environment::NewLine;
	txt += "Error:" + (currentStatus.HasFlag(STB_3458A::Error) ? "1" : "0") + Environment::NewLine;
	txt += "HiLoLimitExeeced:" + (currentStatus.HasFlag(STB_3458A::HiLoLimitExeeced) ? "1" : "0") + Environment::NewLine;
	txt += "PowerOn:" + (currentStatus.HasFlag(STB_3458A::PowerOn) ? "1" : "0") + Environment::NewLine;
	txt += "ReadyFor:" + (currentStatus.HasFlag(STB_3458A::ReadyFor) ? "1" : "0") + Environment::NewLine;
	txt += "ReadyOn:" + (currentStatus.HasFlag(STB_3458A::ReadyOn) ? "1" : "0") + Environment::NewLine;
	txt += "ServiceRequest:" + (currentStatus.HasFlag(STB_3458A::ServiceRequest) ? "1" : "0") + Environment::NewLine;
	txt += "SRQCmndExecuted:" + (currentStatus.HasFlag(STB_3458A::SRQCmndExecuted) ? "1" : "0") + Environment::NewLine;
	txt += "SubProgramExecuteComplete:" + (currentStatus.HasFlag(STB_3458A::SubProgramExecuteComplete) ? "1" : "0") + Environment::NewLine;
	return txt;

}
