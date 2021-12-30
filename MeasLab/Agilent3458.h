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


namespace AgilentDMM {

	public enum class OFORMAT
	{
		ASCII,
		SINT,
		DINT,
		SREAL,
		DREAL
	};

	[System::Flags]
	public enum class STB_3458A : int
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

	public ref class Agilent3458 : public IDMM
	{

	public:
		STB_3458A currentStatus;
		OFORMAT dFormat;
		double ScaleCoeff = 1.0;
		List<int>^ VLFData;
		property double APER { double get() { return 0.02 * NPLC; }  void set(double value) { NPLC = value /0.02 ; }}
		Agilent3458() {
			type = DMMType::DMM;
			canReadPeak = false;
			Name = "3458A";
		}
		~Agilent3458() {
			delete cmdtxt, answertxt, sp1, instr;	//session1, , instr1
		}

		virtual void SetInitConfig() override;
		virtual	bool ZInput() override;
		virtual void CalculateParam() override;
		virtual  bool GetLineFreq() override;
		virtual	bool ChangeNPLC(double nplc) override;
		virtual	bool SendIDN(String^% _anwser) override;
		virtual bool ChangeVoltageRange(VoltageRange range) override;
		virtual bool GetTerminalSide() override;
		virtual bool PrepareLiveData() override;
		virtual bool PrepareNextLiveData() override;
		virtual bool ReadLiveData(String^% _rawdata) override;
		virtual String^ CreateFakeWaveFormRawData(int adet) override;
		virtual void CheckError() override;
		virtual bool ReadError() override;
		virtual bool CheckDataReady() override;
		virtual String^ ReturnSTB() override;
	};
}