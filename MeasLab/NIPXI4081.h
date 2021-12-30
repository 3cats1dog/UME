#pragma once
#include "WaveFormMeasurement.h";
#include "GenericDMM.h";

//using namespace Ivi::Visa::FormattedIO;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;
using namespace NationalInstruments::ModularInstruments::NIDmm;
using namespace NationalInstruments::ModularInstruments::SystemServices::DeviceServices;

namespace NIDMM {


	[System::Flags]
	public enum class STB_4081 : int
	{
		SubProgramExecuteComplete = 1,
		HiLoLimitExeeced = 2,
		SRQCmndExecuted = 4,
		PowerOn = 8,
		ReadyFor = 16,
		Error = 32,
		ServiceRequest = 64,
		DataAvaliable = 128,
		ReadyOn = PowerOn | ReadyFor
	};

	ref class NIPXI4081 : public IDMM
	{

	public:
		static double MOHM10 = 10E+6;
		static double GOHM10 = 10E+9;

		NIDmm^ DmmSession;
		DmmMeasurementFunction measurementMode;
		String^ _rawDataBuffer;
		bool hasVLFComplete;

		STB_4081 currentStatus;
		double ScaleCoeff = 1.0;
		List<int>^ VLFData;
		property double APER { double get() { return 0.02 * NPLC; }  void set(double value) { NPLC = value / 0.02; }}
		double rate;
		NIPXI4081() {
			Name = "4081";
			type = DMMType::DMM;
			canReadPeak = false;
			connType = EnvanterConnection::PXI;
		}
		~NIPXI4081() {
			delete cmdtxt, answertxt, sp1, instr, DmmSession;		//session1,,  instr1;
		}
		//Must implement;
		virtual void SetInitConfig() override;
		virtual	bool ZInput() override;
		virtual void CalculateParam() override;
		virtual	bool ChangeNPLC(double nplc) override;
		virtual	bool SendIDN(String^% _anwser) override;
		virtual bool ChangeVoltageRange(VoltageRange range) override;
		virtual bool GetTerminalSide() override;
		virtual bool GetLineFreq() override;
		virtual bool PrepareLiveData() override;
		virtual bool PrepareNextLiveData() override;
		virtual bool ReadLiveData(String^% _rawdata) override;
		virtual String^ CreateFakeWaveFormRawData(int adet) override;
		virtual void CheckError() override;
		virtual bool ReadError() override;
		virtual bool CheckDataReady() override;
		virtual String^ ReturnSTB() override;

		//NI Async Read;
		void WaveformAcquisition_ReadWaveformCompleted(Object^ sender, NationalInstruments::ModularInstruments::NIDmm::DmmMeasurementEventArgs<NationalInstruments::AnalogWaveform<double>^>^ e);

		//Override from IDMM
		void Connect_PXI(String^ cnnstr);			//Generic fol all type DMM
		void DisConnect();							//Generic fol all type DMM
	};
}

