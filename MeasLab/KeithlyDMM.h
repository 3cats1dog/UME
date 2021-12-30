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

namespace KeithleyDMM
{


#pragma region  "Enums"

	[System::Flags]
	public enum class _STB :int    //Status Byte 
	{
		B0 = 0,   // Measurement Summary Bit (MSB)
		B1 = 1,   // Not used
		B2 = 2,   // Error Avaliable (EAV)
		B3 = 3,   // Questionable Summary Bit (QSB)
		B4 = 4,   // Message Avaliable (MAV)
		B5 = 5,   // Event Summary Bit (ESB)
		B6 = 6,   // Request Service (RQS) / Master Summary Status (MSS)
		B7 = 7,   // Operation Summary (OSB)
	};

	[System::Flags]
	public enum class STB : int     //Status Byte 
	{
		MSB = 0,   // Measurement Summary Bit (MSB)
		EAV = 2,   // Error Avaliable (EAV)
		QSB = 3,   // Questionable Summary Bit (QSB)
		MAV = 4,   // Message Avaliable (MAV)
		ESB = 5,   // Event Summary Bit (ESB)
		RQS = 6,   // Request Service (RQS) / Master Summary Status (MSS)
		OSB = 7,   // Operation Summary (OSB)
	};

	[System::Flags]
	public enum class _ESE : int	//Standart Event Status
	{
		B0 = 0,   // Operation Complete (OPC)
		B1 = 1,   // Not used
		B2 = 2,   // Wuery Error (QYE)
		B3 = 3,   // Device-Dependent Error (DDE)
		B4 = 4,   // Execution Error (EXE)
		B5 = 5,   // Command Error (CME)
		B6 = 6,   // User Request (URQ) (LOCAL key pressed)
		B7 = 7,   // Power On (PON)
	};

	[System::Flags]
	public enum class ESE : int //Standart Event Status
	{
		OPC = 0,   // Operation Complete (OPC)
		QYE = 2,   // Query Error (QYE)
		DDE = 3,   // Device-Dependent Error (DDE)
		EXE = 4,   // Execution Error (EXE)
		CME = 5,   // Command Error (CME)
		URQ = 6,   // User Request (URQ) (LOCAL key pressed)
		PON = 7,   // Power On (PON)
	};

	[System::Flags]
	public enum  class _OPE : int //Operation Events Status
	{
		B0 = 0,   // Not used
		B1 = 1,   // Not used
		B2 = 2,   // Not used
		B3 = 3,   // Not used
		B4 = 4,   // Measuring (Meas)
		B5 = 5,   // Wait For Trigger (Trig)
		B6 = 6,   // Not used
		B7 = 7,   // Not used
		B8 = 8,   // Filter Settled (Filt)
		B9 = 9,   // Not used
		B10 = 10, // Idle State (Idle)
		B11 = 11,   // Not used
		B12 = 12,   // Not used
		B13 = 13,   // Not used
		B14 = 14,   // Not used
		B15 = 15,   // Not used
	};

	[System::Flags]
	public enum class OPE : int //Operation Events Status
	{
		Meas = 4,   // Measuring (Meas)
		Trig = 5,   // Wait For Trigger (Trig)
		Filt = 8,   // Filter Settled (Filt)
		Idle = 10, // Idle State (Idle)
	};

	[System::Flags]
	public enum class _MPE : int //Measurement Events Status
	{
		B0 = 0,   // Reading Overflow (ROF)
		B1 = 1,   // Low Limit 1 Event (LL1)
		B2 = 2,   // High Limit 1 Event (HL1)
		B3 = 3,   // Low Limit 2 Event (LL2)
		B4 = 4,   // High Limit 2 Event (HL2)
		B5 = 5,   // Reading Available (RAV)
		B6 = 6,   // Buffer Notify (BN)
		B7 = 7,   // Buffer Available (BAV)
		B8 = 8,   // Buffer Half Full (BHF)
		B9 = 9,   // Buffer Full (BF)
		B10 = 10, // Buffer Overflow (BOF)
		B11 = 11, // Hardware Limit Event( HL)
		B12 = 12, // Buffer Quarter Full (BQF)
		B13 = 13, // Buffer Three-Quarter Full (BTF)
		B14 = 14, // Master Limit (ML)
		B15 = 15, // Not used
	};

	[System::Flags]
	public enum class MPE : int //Measurement Events Status
	{
		ROF = 0,   // Reading Overflow (ROF)
		LL1 = 1,   // Low Limit 1 Event (LL1)
		HL1 = 2,   // High Limit 1 Event (HL1)
		LL2 = 3,   // Low Limit 2 Event (LL2)
		HL2 = 4,   // High Limit 2 Event (HL2)
		RAV = 5,   // Reading Available (RAV)
		BN = 6,   // Buffer Notify (BN)
		BAV = 7,   // Buffer Available (BAV)
		BHF = 8,   // Buffer Half Full (BHF)
		BF = 9,   // Buffer Full (BF)
		BOF = 10, // Buffer Overflow (BOF)
		HL = 11, // Hardware Limit Event( HL)
		BQF = 12, // Buffer Quarter Full (BQF)
		BTF = 13, // Buffer Three-Quarter Full (BTF)
		ML = 14, // Master Limit (ML)
		//B15 = 15, // Not used
	};


#pragma endregion

	public ref class Keithley2700DMM : public IDMM
	{

	public:
		STB currentStatus;
		MPE curentMeasStatus;
		property double APER { double get() { return 0.02 * NPLC; }  void set(double value) { NPLC = value / 0.02; }}

		Keithley2700DMM() {
			type = DMMType::DMM;
		}
		~Keithley2700DMM() {
			delete cmdtxt, answertxt, sp1,  instr;		//session1,,  instr1
		}

		//Must implement;
		virtual void SetInitConfig() override;
		virtual bool ChangeNPLC(double nplc)  override;
		virtual void CalculateParam() override;
		virtual bool GetTerminalSide()  override;
		virtual  bool GetLineFreq() override;

		virtual bool ZInput()  override;
		virtual bool ChangeVoltageRange(VoltageRange range)  override;
		virtual bool SendIDN(String^% _anwser)  override;
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
