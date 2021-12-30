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
	public enum class STB_3441x : int
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

	public enum class DMMModel {
		Model_34410,
		Model_34411,
	};

	public ref class Agilent3441x : public IDMM
	{

	public:
		STB_3441x currentStatus;
		DMMModel model;
		double ScaleCoeff = 1.0;
		property double APER { double get() { return 0.02 * NPLC; }  void set(double value) { NPLC = value / 0.02; }}
		Agilent3441x() {
			Name = "34411";
			type = DMMType::DMM;
			model = DMMModel::Model_34411;
			canReadPeak = true;
		}
		Agilent3441x(DMMModel _model) {
			Name = "34411";
			type = DMMType::DMM;
			switch (_model)
			{
			case AgilentDMM::DMMModel::Model_34410:	Name = "34410"; break;
			case AgilentDMM::DMMModel::Model_34411:	Name = "34411"; break;
			}
			model = _model;
			canReadPeak = true;
		}

		~Agilent3441x() {
			delete cmdtxt, answertxt, sp1, instr;		//session1,,  instr1;
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


	};
}
 

