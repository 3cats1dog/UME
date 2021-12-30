#include "KeithlyDMM.h"

using namespace KeithleyDMM;
//using namespace Ivi::Visa::FormattedIO;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;

void Keithley2700DMM::SetInitConfig() {
};
bool Keithley2700DMM::ChangeNPLC(double nplc) {
	if (meastype == MeasType::AC)
	{
		SendCommand(":VOLT:AC:DET:BAND " + SampleFreq.ToString("F0", G::invcul()));
		SendCommand(":SENS:VOLT:AC:NPLC " + nplc.ToString("F2", G::invcul()));
	}
	else
	{
		SendCommand(":SENS:VOLT:DC:NPLC " + nplc.ToString("F2", G::invcul()));
	}

	return true;
};
bool Keithley2700DMM::GetTerminalSide() {
	SendCommand("SYSTem:FRSWitch?");
	// 0 REAR
	// 1 FRONT
	return true;
};

bool Keithley2700DMM::GetLineFreq() {

	SendCommand("SYSTem:LFRequency?");
	return true;
}
bool Keithley2700DMM::ZInput() {
	return true;
};

bool Keithley2700DMM::ChangeVoltageRange(VoltageRange range) {
	String^ ACDC = "DC";
	if (meastype == MeasType::AC) ACDC = "AC";
	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01:
		SendCommand(":SENS:VOLT:" + ACDC + ":RANG 0.1");
		break;
	case MeasLab::VoltageRange::VOLT_1:
		SendCommand(":SENS:VOLT:" + ACDC + ":RANG 1");
		break;
	case MeasLab::VoltageRange::VOLT_10:
		SendCommand(":SENS:VOLT:" + ACDC + ":RANG 10");
		break;
	case MeasLab::VoltageRange::VOLT_100:
		SendCommand(":SENS:VOLT:" + ACDC + ":RANG 100");
		break;
	case MeasLab::VoltageRange::VOLT_1000:
		SendCommand(":SENS:VOLT:" + ACDC + ":RANG 1000");
		break;
	default:
		break;
	}

	return true;
};

bool Keithley2700DMM::SendIDN(String^% _anwser) {
	if (isFake)
	{
		_anwser = "Keitley 2700, xxxxxxx, yyyyy/zzz";
		return true;
	}
	else
	{
		return SendCommand("*IDN?", _anwser);
	}
};

bool Keithley2700DMM::PrepareLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:

		break;
	case MeasLab::MeasType::DC:

		break;
	case MeasLab::MeasType::AC_DCSampling:
		////For Keithley 20ms = 1 PLC (50Hz line freq)
		////Min aperture time for Keithley 200us / 0.01 NPLC (50Hz line freq)
		//// 
		////For example 0.01Hz freq; 100s/200us= 500000 sample for one waveform;
		////For example 0.1Hz freq; 10s/200us= 50000 sample for one waveform;
		////For example 1Hz freq; 1000ms/200us= 5000 sample for one waveform;
		////For example 50Hz freq; 20ms/200us= 100 sample for one waveform;
		//NPLC = 0.01;
		//WaveFormSampleCount = (int)(1.0 / SampleFreq / (0.0002));

		////but we want to fix apprx 1000 sample for each sample;
		//if (SampleFreq <= 0.04)
		//{
		//	NPLC = 1;
		//	WaveFormSampleCount = (int)(1.0 / SampleFreq / (0.020 / NPLC));
		//	//So fixed to max 1250-5000 sample varies from 0.01 Hz to 0.04Hz;
		//}

		////if waveform sample count is bigger than 1000 keep it simple;
		//if (WaveFormSampleCount > 1000)
		//{

		//}

		SendCommand("*RST");
		SendCommand(":TRAC:CLE");
		SendCommand(":INIT:CONT OFF");
		SendCommand(":ABORT");
		SendCommand(":TRIG:COUN 1");
		ChangeVoltageRange(range);			//SendCommand(":SENS:VOLT:DC:RANG " + liveData->Kademe.ToString("F0", G::invcul()));
		ChangeNPLC(NPLC);					// SendCommand(":SENS:VOLT:DC:NPLC " + liveData->NPLC.ToString("F2", G::invcul()));

		SendCommand(":DISP:ENAB OFF");
		SendCommand(":SYST:AZER:STAT OFF");
		SendCommand(":SENS:VOLT:DC:AVER OFF");
		SendCommand(":FORM ASC");
		SendCommand(":FORM:ELEM READ,TST,RNUM");
		//instrument.SendCommand(":FORM:ELEM READ, UNIT, TST,RNUM,CHAN,LIM");

		System::Threading::Thread::Sleep(300);
		SendCommand(":SAMP:COUN " + WaveFormSampleCount);
		SendCommand(":READ?");
		break;
	}
	return true;
};

bool Keithley2700DMM::PrepareNextLiveData() {
	SendCommand(":TRAC:CLE");
	SendCommand(":SAMP:COUN " + WaveFormSampleCount);
	SendCommand(":READ?");
	return true;
}
bool Keithley2700DMM::ReadLiveData(String^% _rawdata) {
	if (isFake)
	{
		_rawdata = CreateFakeWaveFormRawData(WaveFormSampleCount);		//  WaveFormMeasument::WaveFormMeasurement::CreateFakeData(1000);
		return true;
	}
	else
	{
		return	SendCommand(":TRAC:DATA?", _rawdata);
	}
};

String^ Keithley2700DMM::CreateFakeWaveFormRawData(int adet) {
	//+1.23456789E-03, +11.664SECS, +236RDNG,
	Random^ random = gcnew Random();
	String^ data = "";
	int startPhase = random->Next(360);
	double SampleCount = 50;
	if (G::mySet->NPLC == 0.01) SampleCount = 100;
	if (G::mySet->NPLC == 0.04) SampleCount = 25;

	for (int i = startPhase; i < adet + startPhase; i++)
	{
		double sinV = Math::Sin(2 * Math::PI * i / WaveFormSampleCount);
		sinV += random->NextDouble() / 100.0;
		data += String::Format("{0:e8},{1:F3}SECS,{2}RDNG", sinV, i, i) + Environment::NewLine;
	}
	return data; 
}

void Keithley2700DMM::CalculateParam() {
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
		WaveFormSampleCount = 1000;
		double APER_raw = WaveLengthSeconds / WaveFormSampleCount;
		APER_raw = Math::Floor(APER_raw / 200E-6) * 200E-6;


		if (APER_raw < 200E-06)
		{
			APER_raw = 200E-6;
			WaveFormSampleCount = WaveLengthSeconds / APER_raw;
		}

		APER = APER_raw;
		break;
	}

};

bool Keithley2700DMM::CheckDataReady() {
	if (isFake)
	{
		dataReady = true;
		return dataReady;
		//double waitMs = APER * WaveFormSampleCount * 1000.0;
		//System::Threading::Thread::Sleep(waitMs);
	}
	String^ OPCSTR = "";
	SendCommand("*OPC?", OPCSTR);
	if (OPCSTR == "1") dataReady = true;
	return dataReady;
}
void Keithley2700DMM::CheckError()
{
	ReadStatus();
	hasError = false;
}
void Keithley2700DMM::ReadError()
{
	SendCommand("SYST:ERR?", ErrorStr);
}

String^ Keithley2700DMM::ReturnSTB() {
	return "";
}