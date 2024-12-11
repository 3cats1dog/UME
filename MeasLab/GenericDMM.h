#pragma once
#include "WaveFormMeasurement.h";
#pragma managed(push, off)
#include "GPIB.h";
#pragma managed(pop)

//using namespace Ivi::Visa::FormattedIO;
//using namespace Ivi::Visa::Interop;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;

namespace MeasLab {

	public enum class  CommMode
	{ 
		ASCII,
		Binary,
	};
 

	public enum class  PeakType
	{
		Voltage,
		Peak,
		VoltagePeak,
	};


	public enum class SampleStatus {
		Wait,
		Prepare,
		WaitData,
		ReadData,
		HasError,
	};


	public enum class DMMType {
		DMM,
		Hand,
		None,
	};

	public enum class MeasType {
		AC,
		DC,
		AC_DCSampling,
	};

	public enum class ZInput {
		MOHM_1,
		MOHM_10,
		MOHM_100,
		GOHM_1,
		GOHM_10,
		GOHM_100,
	};
	public enum class VoltageRange {
		VOLT_01,
		VOLT_1,
		VOLT_10,
		VOLT_100,
		VOLT_1000,
		AUTO,
	};
	public enum class LineFreq {
		LineFreq_50Hz,
		LineFreq_60Hz,
	};

	public ref class IDMM
	{
	private:
		bool FakeOpen = false;


	public:

		EnvanterConnection connType;
		CommMode responseMode;
		PeakType peakType;
		DMMType type;
		MeasType meastype;
		bool TerminalSide;		//true for FRONT, false for REAR
		property ZInput Zin
		{	ZInput get() {
			if (G::mySet == nullptr) return ZInput::GOHM_10;
			if (G::mySet->useFixedZInput) return ZInput::MOHM_10;
			switch (range)
			{
			case MeasLab::VoltageRange::VOLT_01:
			case MeasLab::VoltageRange::VOLT_1:
			case MeasLab::VoltageRange::VOLT_10:
				return ZInput::GOHM_10;
				break;
			case MeasLab::VoltageRange::VOLT_100:
			case MeasLab::VoltageRange::VOLT_1000:
				return ZInput::MOHM_10;
				break;
			default:
				return ZInput::GOHM_10;
				break;
			}
		}
		};
		property String^ ZinSTR { String^ get() {
			switch (Zin)
			{
			case ZInput::GOHM_1 : return L"1 GΩ"; break;
			case ZInput::GOHM_10: return L">10 GΩ"; break;
			case ZInput::GOHM_100: return L">100 GΩ"; break;
			case ZInput::MOHM_1: return L">1 MΩ"; break;
			case ZInput::MOHM_10: return L"10 MΩ"; break;
			case ZInput::MOHM_100: return L"100 MΩ"; break;
			}
			
		}
		}
		property String^ peakTypeSTR { String^ get() {
			switch (peakType)
			{
			case PeakType::Voltage: return L"Voltage"; break;
			case PeakType::Peak: return L"Peak"; break;
			case PeakType::VoltagePeak: return L"Voltage&Peak"; break;
			}
		}
		}
		property String^ meastypeSTR { String^ get() {
			switch (meastype)
			{
			case MeasType::AC: return L"AC"; break;
			case MeasType::DC: return L"DC"; break;
			case MeasType::AC_DCSampling: return L"AC Peak"; break;
			}
		}
		}
		property String^ rangeSTR { String^ get() {
			switch (range)
			{
			case VoltageRange::VOLT_01: return L"100 mV"; break;
			case VoltageRange::VOLT_1: return L"1 V"; break;
			case VoltageRange::VOLT_10: return L"10 V"; break;
			case VoltageRange::VOLT_100: return L"100 V"; break;
			case VoltageRange::VOLT_1000: return L"1000 V"; break;
			}
		}
		}
		static bool isFake = false;
		String^ msgBuf1;
		bool dataReady = false;
		bool canReadPeak = false;
		bool hasError = false;
		int ReadByteCount = 0;
		property bool isConnected
		{
			bool get()
			{
				switch (connType)
				{
				case EnvanterConnection::GBIP:
				case EnvanterConnection::USB:
					if (isFake) return FakeOpen;
					//if (instr1 == nullptr) return false;
					//if (instr1->IO == nullptr) return false;
					if (instr == nullptr) return false;
					return instr->isConnected;
					return true;
				case EnvanterConnection::PXI:
					return PXI_Connected;
					break;
				case EnvanterConnection::RS232:
					if (isFake) return FakeOpen;
					if (sp1 == nullptr) return false;
					return (sp1->IsOpen);
				}
				return false;
			}
		}


		String^ Name;
		double TIMER;
		double ApertureTime;
		double NPLC;
		int totalSampleCount;
		int WaveFormSampleCount;
		bool CollectWaveForm = false;
		double SampleFreq = 50.0;
		VoltageRange range;
		bool VoltRangeChanged = false;
		LineFreq lineFreq = LineFreq::LineFreq_50Hz;
		bool PXI_Connected;
		//GPIB instruments
		//GpibSession^ session1;
		GPIB* instr;
		//Ivi::Visa::Interop::FormattedIO488^ instr1;

		//MessageBasedFormattedIO^ instr1;
		//RS232 instruments
		SerialPort^ sp1;

		Int32 STBByte;
		String^ cmdtxt;
		String^ answertxt;
		String^ ErrorStr;

		System::Collections::Generic::List<char>^ answerbyte;
		IDMM() {
			Name = "Generic";
			answerbyte = gcnew System::Collections::Generic::List<char>();
			canReadPeak = false;
		}
		IDMM(DMMType _type) {
			Name = "Generic";
			type = _type;
			canReadPeak = false;
			answerbyte = gcnew System::Collections::Generic::List<char>();
		}
		~IDMM() {
			delete cmdtxt, answertxt, sp1, instr;		//session1, , instr1
		}


		  void Connect(String^ cnnstr, int _baudRate, EnvanterConnection _connType);	//Generic fol all type DMM
		  void DisConnect();											//Generic fol all type DMM

	public:
		//Must implement;
		virtual void SetInitConfig();
		virtual void CalculateParam();
		virtual bool ChangeNPLC(double nplc);
		virtual bool GetTerminalSide();
		virtual  bool GetLineFreq();
		virtual bool ZInput();
		virtual bool ChangeVoltageRange(VoltageRange range);
		virtual bool SendIDN(String^% _anwser);
		virtual bool PrepareLiveData();
		virtual bool PrepareNextLiveData();
		virtual bool ReadLiveData(String^% _rawdata);
		virtual bool CheckDataReady();
		virtual void CheckError();
		virtual bool ReadError();
		virtual String^ CreateFakeWaveFormRawData(int adet);
		virtual String^ ReturnSTB();


		 bool SendCommand(String^ _cmd);
		 bool SendCommand(String^ _cmd, String^% _anwser);
		 void ReadStatus();
		 static List<String^>^ findRrsc();


	private:
		 bool _SendCommand(String^ _cmd, String^% _anwser, bool waitAnser);
		 bool SendCmd(String^ _cmd);
		 bool ReadAnswer(int ReadCount);

	protected:
	public:
		virtual event LogChangeEventHandler^ LogChanged;
		String^ logText = "";
		virtual void OnLogChanged(LogChangeEventArgs^ e);
		void AddLogText(String^ text);
	private:
		void AddLogByTip(LogType tip);
		void AddLog(String^ text);

	};
}

