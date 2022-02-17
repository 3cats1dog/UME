#pragma once

#ifndef _SETTING_H_
#define _SETTING_H_




#include <string>
using namespace System::Text;
using namespace System;

namespace MeasLab {

	public ref class Settings
	{
	public:
		String^ Delimeter; // { get; set; }
		String^ BaseDirectory; // { get; set; }
		bool chkRS232; //{ get; set; }
		Int32 BaudRate; //{ get; set; }
		String^ COMPort; //{ get; set; }
		String^ GBIPPort; //{ get; set; }
		String^ Etiket; //{ get; set; }
		double Kademe; //{ get; set; }
		double Ratio; //{ get; set; }
		double NPLC; //{ get; set; }
		int WaveCount; //{ get; set; }
		bool useFixedZInput;
		int BeepFreq = 523;
		int BeepDuration = 900;
		int DesiredVLFCount = 1000;
		int DesiredVLFCount2 = 200;
		bool AutoNext = false;
		bool IskV = false;
		int LastDMMID =0;
		int LastDMMDividerID = 0;
		int LastDMMRange;
		int LastUUTID = 0;
		int LastUUTDividerID = 0;
		int LastUUTRange;
		int LastTestTipi;
		int LastMeasTipi;
		double LastFreq;
		double LastFreqVLF;
		int LastSampleCount;

		Settings()
		{
			Delimeter = ";";
			chkRS232 = true;
			BaudRate = 9600;
			Etiket = "Ölçüm 1";
			Kademe = 100;
			Ratio = 1;
			NPLC = 0.02;
			WaveCount = 5;
			COMPort = "Demo";
			GBIPPort = "instr:";
		}

		~Settings()
		{
			//delete Delimeter, BaseDirectory, COMPort, GBIPPort, Etiket;
		}
	};
}

#endif // !_SETTING_H_
