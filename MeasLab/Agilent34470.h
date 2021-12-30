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

	[System::Flags]
	public enum class STB_34470 : int
	{
		NotUsed = 1,
		NotUsed2 = 2,
		ErrorQueue = 4,
		QDSummary = 8,
		DataAvaliable = 16,
		ESESummary = 32,
		SRESummary = 64,
		SORSummary = 128,
	};



	public ref class Agilent34470 : public IDMM
	{

	public:
		STB_34470 currentStatus;
		double ScaleCoeff = 1.0;
		property double APER { double get() { return 0.02 * NPLC; }  void set(double value) { NPLC = value / 0.02; }}
		Agilent34470() {
			Name = "34470";
			type = DMMType::DMM;
			canReadPeak = false;
		}

		~Agilent34470() {
			delete cmdtxt, answertxt, sp1, instr;		//session1,,  instr1
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
		virtual void  CheckError() override;
		virtual  bool ReadError() override;
		virtual bool CheckDataReady() override;
		virtual String^ ReturnSTB() override;

	};
}


