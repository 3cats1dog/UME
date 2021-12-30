#include "Agilent34410.h"

using namespace AgilentDMM;
//using namespace Ivi::Visa::FormattedIO;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;

bool Agilent3441x::SendIDN(String^% _anwser) {

	//	AGILENT TECHNOLOGIES, 34410A, <Serial Number>, f.ff - b.bb - aa - p
	//	AGILENT TECHNOLOGIES, 34411A, <Serial Number>, f.ff - b.bb - aa - p
	//	AGILENT TECHNOLOGIES, L4411A, <Serial Number>, f.ff - b.bb - aa - p
	//	f.ff = Firmware revision number
	//	b.bb = Boot kernel revision number
	//	aa = ASIC revision number
	//	p = Printed circuit board revision number
	if (isFake)
	{
		_anwser = "AGILENT TECHNOLOGIES, 34411A, 12548442, f.ff - b.bb - aa - p";
		return true;
	}
	else
	{
		return SendCommand("*IDN?", _anwser);
	}
}

void Agilent3441x::SetInitConfig() {

}

bool Agilent3441x::ChangeVoltageRange(VoltageRange range) {
	String^ ACDC = "DC";
	if (meastype == MeasType::AC) ACDC = "AC";
	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01:
		return		SendCommand("CONF:VOLT:" + ACDC + " 0.1");
		break;
	case MeasLab::VoltageRange::VOLT_1:
		return		SendCommand("CONF:VOLT:" + ACDC + " 1");
		break;
	case MeasLab::VoltageRange::VOLT_10:
		return		SendCommand("CONF:VOLT:" + ACDC + " 10");
		break;
	case MeasLab::VoltageRange::VOLT_100:
		return SendCommand("CONF:VOLT:" + ACDC + " 100");
		break;
	case MeasLab::VoltageRange::VOLT_1000:
		return		SendCommand("CONF:VOLT:" + ACDC + " 1000");
		break;
	case MeasLab::VoltageRange::AUTO:
		return	SendCommand("CONF:VOLT:" + ACDC + " AUTO");
		break;
	default:
		return false;
		break;
	}
}

bool Agilent3441x::GetTerminalSide()
{
	String^ cevap="";
	if (SendCommand("ROUT:TERM?", cevap))
	{
		//FRON or REAR
		//true or false;
		if (cevap->Contains("FRON")) TerminalSide = true;
		else TerminalSide = false;
		return true;
	}
	else { return false; }
}

bool Agilent3441x::ChangeNPLC(double nplc)
{
	switch (model)
	{
	case AgilentDMM::DMMModel::Model_34410:
		//	34410A: {0.006|0.02|0.06|0.2|1|2|10|100}
		//	MIN = 0.006 PLC,
		//	MAX = 100 PLC
		break;
	case AgilentDMM::DMMModel::Model_34411:
		//	34411A/L4411A: 	{0.001 | 0.002 | 0.006 | 0.02 | 0.06 | 0.2 | 1 | 2 | 10 | 100}
		//  MIN = 0.001 PLC,
		//	MAX = 100 PLC
		break;
	}
	return true;
}

bool Agilent3441x::ZInput()
{
	// [SENSe:] VOLTage[:DC]:IMPedance:	 AUTO	{ OFF | 0 | ON | 1 }
	// [SENSe:] VOLTage[:DC]:IMPedance : AUTO?
	/*
	This command disables or enables the automatic input impedance mode for
	dc voltage measurements. Normally, the instrument's input resistance is
	fixed at 10 MΩ for all dc voltage measurements to minimize noise pickup. In
	the automatic input impedance mode ("AUTO ON"), the input impedance is
	automatically varied according to range. For the 100 mV, 1 V, and 10 V
	ranges the input impedance is automatically set to "HI-Z" (>10 GΩ) to
	reduce the effects of measurement loading errors on these lower ranges. For
	the 100 V and 1000 V ranges, the input impedance remains at 10 MΩ.
*/

	/*
	This command affects dc voltage measurements only.
	With "AUTO OFF" (default), the input impedance for dc voltage
	measurements is fixed at 10 MΩ for all ranges.
	With "AUTO ON", the input impedance for dc voltage measurements is
	automatically selected according to range. The impedance is set to "HI-Z"
	(>10 GΩ) for the 100 mV, 1 V, and 10 V ranges. The 100 V and 1000 V
	ranges remain at a 10 MΩ input impedance.
	The CONFigure and MEASure? commands automatically select "AUTO OFF"
	(fixed at 10 MΩ for all ranges).
	This setting is reset to the default (fixed, 10 MΩ) by the *RST and
	SYSTem:PRESet commands.
*/
	if (G::mySet->useFixedZInput)
	{
		SendCommand("VOLT:IMP:AUTO OFF");
	}
	else
	{
		SendCommand("VOLT:IMP:AUTO ON");
	}
	return true;
}

bool Agilent3441x::PrepareLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
		//SendCommand("DISP:TEXT '***AC***'"); //***GODS_ACVL***
		SendCommand("SYST:PRES");  //Preset;
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("FORMAT:DATA ASCII");
		if (peakType == PeakType::Peak)
		{
			SendCommand("VOLT:AC:PEAK:STAT ON");
			SendCommand("DISP:WIND2:TEXT:FEED \"VOLT:AC:PTP\"");
		}
		//SendCommand("INIT");
		break;
	case MeasLab::MeasType::DC:
		//SendCommand("DISP:TEXT '***DC***'"); //***GODS_ACVL***
		SendCommand("SYST:PRES");  //Preset;
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("FORMAT:DATA ASCII");
		if (peakType == PeakType::Peak)
		{
			SendCommand("VOLT:DC:PEAK:STAT ON");
			SendCommand("DISP:WIND2:TEXT:FEED \"VOLT:DC:PTP\"");
		}
		//SendCommand("INIT");
		break;
	case MeasLab::MeasType::AC_DCSampling:
		//SendCommand("DISP:TEXT '***VLF***'"); //***GODS_ACVL***
		SendCommand("SYST:PRES");  //Preset;
		ZInput();
		ChangeVoltageRange(range);
		SendCommand("VOLT:APER:ENAB ON");
		SendCommand(String::Format("VOLT:DC:APER {0}", APER.ToString(MeasLab::G::invcul())));
		SendCommand("FORMAT:DATA REAL");
		SendCommand(String::Format("SAMP:TIM {0}", APER.ToString(MeasLab::G::invcul())));
		SendCommand(String::Format("SAMP:COUN {0}", WaveFormSampleCount));
		ReadByteCount = WaveFormSampleCount * 16;	//double int
		break;
	default:
		break;
	}
	return true;
};

bool Agilent3441x::PrepareNextLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		SendCommand(String::Format("INIT; FETCH?"));
		break;

	//case MeasLab::MeasType::AC:
	//	SendCommand(String::Format("MEAS:VOLT:{0}?", "AC"));
	//	break;
	//case MeasLab::MeasType::DC:
	//	SendCommand(String::Format("MEAS:VOLT:{0}?", "DC"));
	//	break;
	case MeasLab::MeasType::AC_DCSampling:
		//SendCommand("INIT");
		//SendCommand("*WAI");
		//SendCommand("READ?");
		SendCommand("INIT; *WAI; READ?");

		break;
	}
	return true;
};

bool Agilent3441x::ReadLiveData(String^% _rawdata) {
	String^ dataSTR = "";
	String^ peakSTR = "";
	String^ ACDC = "AC";

	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		if (isFake) {
			Random^ random = gcnew Random();
			double data = 1;
			switch (range)
			{
			case MeasLab::VoltageRange::VOLT_01: data = 0.4515E-01;				break;
			case MeasLab::VoltageRange::VOLT_1:data = 8.4515E-01;				break;
			case MeasLab::VoltageRange::VOLT_10:data = 6.455E+00;				break;
			case MeasLab::VoltageRange::VOLT_100:data = 20.4515E-01;			break;
			case MeasLab::VoltageRange::VOLT_1000:data = 200.4515E-01;			break;
			}
			_rawdata = (data + random->NextDouble() / 100.0).ToString();
			_rawdata += "\n" + (data + random->NextDouble() / 100.0).ToString();
			return true;
		}

		responseMode = CommMode::ASCII;
		if (meastype == MeasType::DC) { ACDC = "DC"; }

		SendCommand("", dataSTR);

		if (peakType == PeakType::Peak)
		{
			SendCommand(String::Format("FETC:VOLT:{0}:PTP?", meastype), peakSTR);
		}
		_rawdata = dataSTR + peakSTR;
		return	true;
		break;
	case MeasLab::MeasType::AC_DCSampling:
		if (isFake)
		{
			_rawdata = CreateFakeWaveFormRawData(WaveFormSampleCount);		// WaveFormMeasument::WaveFormMeasurement::CreateFakeData(1000);
			return true;
		}
		else
		{
			ReadStatus();
			currentStatus = (STB_3441x)STBByte;
			if (currentStatus.HasFlag(STB_3441x::DataAvaliable))
			{
				_rawdata = "";
				String^ compactData = "";
				SendCommand("", compactData);
				//Convert data to general array;
				int i = 0;
				for each (String^ str  in compactData->Trim()->Split(','))
				{
					_rawdata += String::Format("{0},{1}SECS", str, i) + Environment::NewLine;
				}
				return true;
			}
			return	false;
		}
		break;
	}
};



String^ Agilent3441x::CreateFakeWaveFormRawData(int adet) {
	//+1.23456789E-03, +11.664SECS, +236RDNG,
	Random^ random = gcnew Random();
	String^ data = "";
	int startPhase = random->Next(360);
	double SampleCount = (double)WaveFormSampleCount;


	for (int i = startPhase; i < adet  + startPhase; i++)
	{
		double sinV = Math::Sin(2 * Math::PI * i / WaveFormSampleCount);
		sinV += random->NextDouble() / 100.0;
		data += String::Format("{0:e8},{1:F5}SECS", sinV, i) + Environment::NewLine;
	}
	return data;
}

void Agilent3441x::CalculateParam() {
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
		WaveFormSampleCount = G::mySet->DesiredVLFCount;

		double Aper20us = 20E-6;
		double Aper40us = 40E-6;
		double Aper100us = 120E-6;		// 100E-6;
		double Aper03ms = 0.1E-3;		// 0.3E-3;
		double Aper1ms = 1.2E-3;		// 1E-3;
		double Aper3ms = 4.0E-3;		// 3E-3;
		double Aper20ms = 20E-3;
		double Aper40ms = 40E-3;
		double Aper200ms = 200E-3;
		double Aper2s = 2E-0;

		int DataCount1 = WaveFormSampleCount;
		double Aper1 = Aper20us;
		int DataCount2 = WaveFormSampleCount;
		double Aper2 = Aper20us;

		double Needed = 1 / SampleFreq / WaveFormSampleCount;

		if (Needed >= Aper2s)
		{
			Aper1 = Aper2s;
			Aper2 = Aper2s;
		}
		else if (Needed >= Aper200ms)
		{
			Aper1 = Aper200ms;
			Aper2 = Aper2s;
		}
		else if (Needed >= Aper40ms)
		{
			Aper1 = Aper40ms;
			Aper2 = Aper200ms;
		}
		else if (Needed >= Aper20ms)
		{
			Aper1 = Aper20ms;
			Aper2 = Aper40ms;
		}
		else if (Needed >= Aper3ms)
		{
			Aper1 = Aper3ms;
			Aper2 = Aper20ms;
		}
		else if (Needed >= Aper1ms)
		{
			Aper1 = Aper1ms;
			Aper2 = Aper3ms;
		}
		else if (Needed >= Aper03ms)
		{
			Aper1 = Aper03ms;
			Aper2 = Aper1ms;
		}
		else if (Needed >= Aper100us)
		{
			Aper1 = Aper100us;
			Aper2 = Aper03ms;
		}
		else if (Needed >= Aper40us)
		{
			Aper1 = Aper40us;
			Aper2 = Aper100us;
		}
		else if (Needed >= Aper20us)
		{
			Aper1 = Aper20us;
			Aper2 = Aper40us;
		}
		else
		{
			Aper1 = Aper20us;
			Aper2 = Aper20us;
		}
		DataCount1 = (int)(1 / SampleFreq / Aper1);
		DataCount2 = (int)(1 / SampleFreq / Aper2);

		//lblCalcInfo.Text = string.Format("APER: {0:E3} \r\nDATACOUNT: {1}\r\nAPER: {2:E3} \r\nDATACOUNT: {3}", Aper1, DataCount1, Aper2, DataCount2);

		WaveFormSampleCount = DataCount1;
		APER = Aper1;
		ApertureTime = APER;
		break;
	}

};

bool Agilent3441x::GetLineFreq() {

	if (SendCommand("SYSTem:LFRequency?"))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Agilent3441x::CheckDataReady() {
	if (isFake)
	{
		dataReady = true;
		return dataReady;
		//double waitMs = APER * WaveFormSampleCount * 1000.0;
		//System::Threading::Thread::Sleep(waitMs);
	}

	ReadStatus();
	currentStatus = (STB_3441x)STBByte;

	hasError = currentStatus.HasFlag(STB_3441x::ErrorQueue);
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		dataReady = (currentStatus.HasFlag(STB_3441x::DataAvaliable));
		break;
	case MeasLab::MeasType::AC_DCSampling:
		dataReady = currentStatus.HasFlag(STB_3441x::DataAvaliable);
		break;
	}

	return dataReady;
}
void Agilent3441x::CheckError()
{
	ReadStatus();
	currentStatus = (STB_3441x)STBByte;
	hasError = currentStatus.HasFlag(STB_3441x::ErrorQueue);
}

bool Agilent3441x::ReadError()
{
	ErrorStr = "";
	String^ errStr = "";


	ReadStatus();
	currentStatus = (STB_3441x)STBByte;

	//Clear Current data;
	if (currentStatus.HasFlag(STB_3441x::DataAvaliable))
	{
		SendCommand("", errStr);
	}
	errStr = "";


	while (currentStatus.HasFlag(STB_3441x::ErrorQueue))
	{
		SendCommand("SYST:ERR?", errStr);
		if (errStr == "") {
			SendCommand("*RST");
			return false;
			break;
		}
		else
		{
			ErrorStr += errStr + Environment::NewLine;
			ReadStatus();
			currentStatus = (STB_3441x)STBByte;
		}
	}
	hasError = false;
	return true;
}
String^ Agilent3441x::ReturnSTB() {
	ReadStatus();
	currentStatus = (STB_3441x)STBByte;
	String^ txt = "34411" + Environment::NewLine;;
	txt += "DataAvaliable:" + (currentStatus.HasFlag(STB_3441x::DataAvaliable) ? "1" : "0") + Environment::NewLine;
	txt += "Error:" + (currentStatus.HasFlag(STB_3441x::ErrorQueue) ? "1" : "0") + Environment::NewLine;
	txt += "ESESummary:" + (currentStatus.HasFlag(STB_3441x::ESESummary) ? "1" : "0") + Environment::NewLine;
	txt += "QDSummary:" + (currentStatus.HasFlag(STB_3441x::QDSummary) ? "1" : "0") + Environment::NewLine;
	txt += "SORSummary:" + (currentStatus.HasFlag(STB_3441x::SORSummary) ? "1" : "0") + Environment::NewLine;
	txt += "SRESummary:" + (currentStatus.HasFlag(STB_3441x::SRESummary) ? "1" : "0") + Environment::NewLine;
	return txt;
}
