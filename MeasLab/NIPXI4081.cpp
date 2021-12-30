#include "NIPXI4081.h"
//using namespace Ivi::Visa::FormattedIO;
using namespace NIDMM;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;


void NIPXI4081::Connect_PXI(String^ cnnstr ) {
	DmmSession = gcnew NIDmm(cnnstr, true, true);
	DmmSession->WaveformAcquisition->ReadWaveformCompleted += gcnew System::EventHandler<NationalInstruments::ModularInstruments::NIDmm::DmmMeasurementEventArgs<NationalInstruments::AnalogWaveform<double>^>^>(this, &NIPXI4081::WaveformAcquisition_ReadWaveformCompleted);
	PXI_Connected = true;
}

void NIPXI4081::DisConnect() {
	PXI_Connected = false;
	DmmSession->Close();
	delete DmmSession;
}

bool NIPXI4081::SendIDN(String^% _anwser) {
	if (isFake)
	{
		_anwser = "NI PIXe 4081, xxxxxxxx, y.yy";
		return true;
	}
	else
	{
		_anwser = String::Format("{0}, SN:{1}, Rev:", DmmSession->DriverIdentity->InstrumentModel, DmmSession->DriverIdentity->SerialNumber, DmmSession->DriverIdentity->Revision);
		return true;
		//return SendCommand("ID?", _anwser);
	}
	return true;
}

bool NIPXI4081::ChangeVoltageRange(VoltageRange range) {
	//String^ ACDC = "DCV";
	//if (meastype == MeasType::AC) ACDC = "ACV";
	DmmSession->AutoRange = DmmAuto::Off;
	double DRange = 1;
	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01:
		DmmSession->Range = 0.1;
		break;
	case MeasLab::VoltageRange::VOLT_1:
		DmmSession->Range = 1.0;
		break;
	case MeasLab::VoltageRange::VOLT_10:
		DmmSession->Range = 10.0;
		break;
	case MeasLab::VoltageRange::VOLT_100:
		DmmSession->Range = 100.0;
		break;
	case MeasLab::VoltageRange::VOLT_1000:
		DmmSession->Range = 1000.0;
		break;
	case MeasLab::VoltageRange::AUTO:
		DmmSession->AutoRange = DmmAuto::On;
		break;
	default:
		break;
	}

	switch (range)
	{
	case MeasLab::VoltageRange::VOLT_01:
	case MeasLab::VoltageRange::VOLT_1:
	case MeasLab::VoltageRange::VOLT_10:
		if (G::mySet->useFixedZInput)
		{
			DmmSession->InputResistance = MOHM10;
		}
		else
		{
			DmmSession->InputResistance = GOHM10;
		}
	case MeasLab::VoltageRange::VOLT_100:
	case MeasLab::VoltageRange::VOLT_1000:
		DmmSession->InputResistance = MOHM10;
		break;
	case MeasLab::VoltageRange::AUTO:
		break;
	}
	return true;
}

bool NIPXI4081::GetTerminalSide()
{
	TerminalSide = true;
	return true;
	//String^ termSide = "";
	//bool sonuc = SendCommand("TERM?", termSide);
	////	0	OPEN
	//// 	1	FRONT
	////  2	REAR
	////FRON or REAR
	////true or false;
	//if (sonuc)
	//	TerminalSide = termSide->Contains("1");
	//return sonuc;
}

bool NIPXI4081::ChangeNPLC(double nplc)
{
	//50 Hz
	//NPLC0   => 25E-6	=> 500ns => 
	//NPLC0.5 => 500E-3 => 10ms => 
	//NPLC1   => 1		=> 20ms => 
	//NPLC10  => 10		=> 200ms => 
	//NPLC11  => 20		=> 200ms => 

	return true;
}

void NIPXI4081::SetInitConfig() {
	SendCommand("END ALWAYS");
	SendCommand("TARM HOLD");
	SendCommand("DCV");
	SendCommand("TRIG AUTO");

}

bool NIPXI4081::ZInput()
{
	//     Gets or sets the input resistance of the instrument.
	//
	// Value:
	//     The supported values are 1.000000E+6 (1M Ohm), 1.000000E+7 (10M Ohm), and 1.000000E+10
	//     (input resistance greater than 10 G Ohm).

	//ON => 10 MOhm fixed resistance
	//OFF => 10MOhm or 10GOHM depending voltage range;


	//No device ability for fixed Empedans, it's controller by software;

	//if (G::mySet->useFixedZInput)
		//{
	//
	//	SendCommand("FIXEDZ ON");
	//}
	//else
		//{
		//	SendCommand("FIXEDZ OFF");
	//}
	return true;
}

bool NIPXI4081::PrepareLiveData() {
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
		measurementMode = DmmMeasurementFunction::ACVolts;
		ChangeVoltageRange(range);
		DmmSession->ConfigureMeasurementDigits(measurementMode, DmmSession->Range, 6.5);
		break;
	case MeasLab::MeasType::DC:
		measurementMode = DmmMeasurementFunction::DCVolts;
		ChangeVoltageRange(range);
		DmmSession->ConfigureMeasurementDigits(measurementMode, DmmSession->Range, 7.5);
		break;
	case MeasLab::MeasType::AC_DCSampling:
		measurementMode = DmmMeasurementFunction::WaveformVoltage;
		ChangeVoltageRange(range);
		DmmSession->ConfigureWaveformAcquisition(measurementMode, DmmSession->Range, rate, WaveFormSampleCount);
		break;
	default:
		break;
	}

	return true;
};

bool NIPXI4081::PrepareNextLiveData() {
	if (isFake) return true;
	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		//SendCommand("TARM SGL");
		break;
	case MeasLab::MeasType::AC_DCSampling:
		hasVLFComplete = false;
		DmmSession->WaveformAcquisition->ReadWaveformAsync(WaveFormSampleCount, NationalInstruments::PrecisionTimeSpan::MaxValue, nullptr);
		break;
	}
	return true;
};


bool NIPXI4081::ReadLiveData(String^% _rawdata) {
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
			case MeasLab::VoltageRange::VOLT_100:data = 20.4515E-01;			break;
			case MeasLab::VoltageRange::VOLT_1000:data = 200.4515E-01;			break;
			}
			_rawdata = (data + random->NextDouble() / 100.0).ToString();
			//_rawdata += "\n" + (data + random->NextDouble() / 100.0).ToString();
			return true;
		}
		_rawdata = (DmmSession->Measurement->Read()).ToString();
		return true;
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
			if (hasVLFComplete)
			{
				_rawdata = _rawDataBuffer;
				return true;
			}
			return false;
		}
		break;
	}
};

void NIPXI4081::WaveformAcquisition_ReadWaveformCompleted(Object^ sender, NationalInstruments::ModularInstruments::NIDmm::DmmMeasurementEventArgs<NationalInstruments::AnalogWaveform<double>^>^ e)
{
	NationalInstruments::AnalogWaveform<double>^ analogWaveform;
	_rawDataBuffer = "";
	try
	{
		analogWaveform = e->Reading;
		array<double>^ readingsBuffer = analogWaveform->GetRawData();

		for (int k = 0; k < analogWaveform->SampleCount; k++)
		{
			_rawDataBuffer += String::Format("{0:e8},{1:F5}SECS", readingsBuffer[k], k) + Environment::NewLine;

		}
	}
	catch (Exception^ exception)
	{
		//messageTextBox.Text = exception.Message;
	}
	hasVLFComplete = true;
}

String^ NIPXI4081::CreateFakeWaveFormRawData(int adet) {
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
	case MeasLab::VoltageRange::VOLT_100:baseVal = 20.4515E-01;			break;
	case MeasLab::VoltageRange::VOLT_1000:baseVal = 200.4515E-01;			break;
	}
	for (int i = startPhase; i < adet + startPhase; i++)
	{
		double sinV = Math::Sin(2 * Math::PI * i / WaveFormSampleCount);
		sinV += random->NextDouble() / 100.0;
		data += String::Format("{0:e8},{1:F5}SECS", sinV * baseVal, i) + Environment::NewLine;
	}
	return data;
}

void NIPXI4081::CalculateParam() {
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
		if (SampleFreq >= 50)
		{
			WaveFormSampleCount = G::mySet->DesiredVLFCount2;;
		}
		else
		{
			WaveFormSampleCount = G::mySet->DesiredVLFCount;
		}

		TIMER = WaveLengthSeconds / WaveFormSampleCount;
		rate = WaveFormSampleCount / WaveLengthSeconds;
		double APER_raw = TIMER / 2; 

		if (APER_raw < 100E-9)
		{
			APER_raw = 100E-9;
			TIMER = APER_raw;
			WaveFormSampleCount = WaveLengthSeconds / TIMER;
		}

		APER_raw = Math::Floor(APER_raw / 100E-9) * 100E-9;

		APER = APER_raw;
		ApertureTime = APER;
		break;
	}
};

bool NIPXI4081::GetLineFreq() {
	//SendCommand("SYSTem:LFRequency?");
	return true;
}

bool NIPXI4081::CheckDataReady() {
	if (isFake)
	{
		dataReady = true;
		return dataReady;
		//double waitMs = APER * WaveFormSampleCount * 1000.0;
		//System::Threading::Thread::Sleep(waitMs);
	}

	//ReadStatus();
	//currentStatus = (STB_4081)STBByte;

	//hasError = currentStatus.HasFlag(STB_4081::Error);

	switch (meastype)
	{
	case MeasLab::MeasType::AC:
	case MeasLab::MeasType::DC:
		return true;
		//dataReady = currentStatus.HasFlag(STB_4081::DataAvaliable);
		break;
	case MeasLab::MeasType::AC_DCSampling:
		return hasVLFComplete;
		//dataReady = currentStatus.HasFlag(STB_4081::ReadyFor);
		break;
	}

	return dataReady;
}

void NIPXI4081::CheckError()
{
	hasError = false;
	return;
	//ReadStatus();
	//currentStatus = (STB_4081)STBByte;
	//hasError = currentStatus.HasFlag(STB_4081::Error);
}

bool NIPXI4081::ReadError()
{
	ErrorStr = "";
	String^ errStr = "";
	return true;

	//ReadStatus();
	//currentStatus = (STB_4081)STBByte;
	//if (currentStatus.HasFlag(STB_4081::DataAvaliable))
	//{
	//	SendCommand("", errStr);
	//}
	//errStr = "";

	//while (currentStatus.HasFlag(STB_4081::Error))
	//{
	//	SendCommand("ERRSTR?", errStr);
	//	if (errStr == "")
	//	{
	//		SendCommand("*RST");
	//		return false;
	//	}
	//	ErrorStr += errStr + Environment::NewLine;
	//	ReadStatus();
	//	currentStatus = (STB_4081)STBByte;
	//}
	//hasError = false;
	//return true;
}

String^ NIPXI4081::ReturnSTB() {
	return "";
	//ReadStatus();
	//currentStatus = (STB_4081)STBByte;
	//String^ txt = "3458A" + Environment::NewLine;;
	//txt += "DataAvaliable:" + (currentStatus.HasFlag(STB_4081::DataAvaliable) ? "1" : "0") + Environment::NewLine;
	//txt += "Error:" + (currentStatus.HasFlag(STB_4081::Error) ? "1" : "0") + Environment::NewLine;
	//txt += "HiLoLimitExeeced:" + (currentStatus.HasFlag(STB_4081::HiLoLimitExeeced) ? "1" : "0") + Environment::NewLine;
	//txt += "PowerOn:" + (currentStatus.HasFlag(STB_4081::PowerOn) ? "1" : "0") + Environment::NewLine;
	//txt += "ReadyFor:" + (currentStatus.HasFlag(STB_4081::ReadyFor) ? "1" : "0") + Environment::NewLine;
	//txt += "ReadyOn:" + (currentStatus.HasFlag(STB_4081::ReadyOn) ? "1" : "0") + Environment::NewLine;
	//txt += "ServiceRequest:" + (currentStatus.HasFlag(STB_4081::ServiceRequest) ? "1" : "0") + Environment::NewLine;
	//txt += "SRQCmndExecuted:" + (currentStatus.HasFlag(STB_4081::SRQCmndExecuted) ? "1" : "0") + Environment::NewLine;
	//txt += "SubProgramExecuteComplete:" + (currentStatus.HasFlag(STB_4081::SubProgramExecuteComplete) ? "1" : "0") + Environment::NewLine;
	//return txt;

}
