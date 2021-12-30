#include "GenericDMM.h"

//using namespace Ivi::Visa::FormattedIO;
//using namespace Ivi::Visa::Interop;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace WaveFormMeasument;


#pragma region "Find Resources"

  List<String^>^ IDMM::findRrsc() {
	List<String^>^ dList = gcnew List<String^>();
	GPIB* f = new GPIB();
	char* liste = f->getRscr();
	int len = strlen(liste);
	if(len== 0) return dList;
	StringBuilder^ sb = gcnew StringBuilder();
	for (int i = 0; i < len; i++)
	{
		if (liste[i] == ';')
		{
			dList->Add(sb->ToString());
			sb->Clear();
		}
		else
		{
			sb->Append( Convert::ToChar(liste[i]));
		}
	}
	return dList;
}

#pragma endregion

#pragma	region "Connection"

//Generic fol all type DMM
void IDMM::Connect(String^ cnnstr, int _baudRate, bool _useGPIB)
{
	if (type != DMMType::DMM) return;
	isFake = false;
	if (cnnstr->Contains("Demo")) isFake = true;

	connType = (_useGPIB ? EnvanterConnection::GBIP : EnvanterConnection::RS232);
	//useGPIB = _useGPIB;
	if (isFake)
	{
		FakeOpen = true;
		return;
	}

	if (_useGPIB)
	{
		instr = new GPIB();
		int len = cnnstr->Length;
		char rsc[256];
		for (int i = 0; i < len; i++) { rsc[i] = cnnstr[i]; }
		rsc[len] = 0;
		instr->Open(rsc);
		//instr1 = gcnew Ivi::Visa::Interop::FormattedIO488Class();
		//instr1->InstrumentBigEndian = true;
		//instr1->IO = (IMessage^)G::rsc->Open(cnnstr, AccessMode::NO_LOCK, 0, "");	 //rsc.Open();		(IMessage)
		//instr1->IO->TerminationCharacterEnabled = true;
		//instr1->IO->TerminationCharacter = (char)0x10;
		//instr1->IO->Timeout = 300;

		//instr1 = gcnew FormattedIO488();
	}
	else
	{
		sp1 = gcnew SerialPort(cnnstr);
		sp1->BaudRate = _baudRate;
		sp1->Open();
	}
};

//Generic fol all type DMM
void IDMM::DisConnect()
{
	if (isFake)
	{
		FakeOpen = false;
		return;
	}
	if (connType == EnvanterConnection::GBIP)
	{

		//if (instr1 != nullptr)
		//{
		//	instr1->IO = nullptr;
		//}
		//delete instr1;
		if (instr != nullptr)
		{
			instr->Close();
		}
		delete instr;

	}
	else
	{
		if (sp1 != nullptr)
		{
			try
			{
				sp1->Close();
			}
			catch (Exception^ ex)
			{

			}
		}
	}
}

#pragma endregion

#pragma region "I/O"


bool IDMM::SendCommand(String^ _cmd)
{
	if (type != DMMType::DMM) return true;
	SendCmd(_cmd);
	return true;
}
bool IDMM::SendCommand(String^ _cmd, String^% _anwser)
{
	return _SendCommand(_cmd, _anwser, true);
}
void IDMM::ReadStatus()
{
	if (isFake) { return; }

	if (connType == EnvanterConnection::GBIP)
	{
		int stb1 = instr->ReadSTB();			//(int)instr1->IO->ReadSTB();	
		STBByte =  stb1;
	}
	else
	{
		SendCmd("*STB?");
		if (ReadAnswer(0))
		{
			String^ STBtext = answertxt;;	// [0] ;
			bool parseResult = Int32::TryParse(STBtext, STBByte);
		}
	}
}

bool IDMM::_SendCommand(String^ _cmd, String^% _anwser, bool waitAnser)
{
	bool sendOK = SendCmd(_cmd);
	if (!sendOK) return false;
	if (isFake) return true;
	if (waitAnser)
	{
		if (_cmd == "")
		{
			if (ReadAnswer(ReadByteCount))
			{
				_anwser = answertxt;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (ReadAnswer(0))
			{
				_anwser = answertxt;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}
bool IDMM::SendCmd(String^ _cmd)
{
	cmdtxt = _cmd;
	AddLogByTip(LogType::cmd);
	if (cmdtxt == "") return true;
	if (isFake) return true;
	try
	{
		if (connType == EnvanterConnection::GBIP)
		{
			char cmd[256];
			int len = _cmd->Length;
			for (int i = 0; i < len; i++) { cmd[i] = _cmd[i]; }
			cmd[len] = '\n';
			cmd[len + 1] = 0;
			instr->SendCommand(cmd);		//instr1->IO->WriteString(cmdtxt);		 
		}
		else
		{
			sp1->WriteLine(cmdtxt);
		}
		return true;
	}
	catch (Exception^ ex)
	{
		AddLog(ex->Message);
		return false;
	}
}
bool IDMM::ReadAnswer(int ReadCount)
{
	answerbyte->Clear();
	answertxt = "";
	int timeout = 300;
	DateTime start = DateTime::Now;
	bool waitAnswer = true;
	bool answered = false;

	if (isFake)
	{
		answered = true;
		AddLogByTip(LogType::answer);
		return answered;
	}

	if (connType == EnvanterConnection::GBIP)
	{
		if (ReadCount == 0)
		{
			char* cevap = instr->ReadAnswerWithOneByte();
			int len = strlen(cevap);
			answered = (len > 0);
			for (int i = 0; i < len; i++) { answerbyte->Add(cevap[i]); }
		}
		else {
			bool loop = true;
				switch (responseMode)
				{
				case MeasLab::CommMode::ASCII:
					while (loop)
					{
						char* cevap = instr->ReadAnswerWithOneByte();
						int len = strlen(cevap);
						answered = (len > 0);
						for (int i = 0; i < len; i++) { answerbyte->Add(cevap[i]); }

						if (ReadCount == 0) loop = false;
						else
						{
							if (answerbyte->Count >= ReadCount) loop = false;
						}
					}
					break;
				case MeasLab::CommMode::Binary:
					while (loop)
					{
						int len = instr->ReadAnswerBinary();
						answered = (len > 0);
						for (int i = 0; i < len; i++) { answerbyte->Add(instr->Fulldata[i]); }

						if (ReadCount == 0) loop = false;
						else
						{
							if (answerbyte->Count >= ReadCount) loop = false;
						}
					}
					break;
			}
		}

	 
		//while (waitAnswer)
		//{
		//	try
		//	{
		//		wchar_t readedChar = instr1->IO->Read(1)[0];
		//		answerbyte->Add(readedChar);
		//
		//		answered = true;
		//		if (readedChar == 0x0A && responseMode == CommMode::ASCII)
		//		{
		//			waitAnswer = false;
		//		}
		//	}
		//	catch (Exception^ ex)
		//	{
		//		 
		//		waitAnswer = false;
		//	}
		//	if (answered)
		//	{
		//		 
		//	}
		//	 
		//}

		switch (responseMode)
		{
		case CommMode::Binary:
			for each (wchar_t readedChar in answerbyte)
			{
				answertxt += ((char)readedChar).ToString("X2");
			}
			break;
		case CommMode::ASCII:
			for each (wchar_t readedChar in answerbyte)
			{
				answertxt += readedChar.ToString();
			}
		default:
			break;
		}
	}
	else
	{
		while (waitAnswer)
		{
			if (sp1->BytesToRead > 0)
			{
				answered = true;
				waitAnswer = false;
				while (sp1->BytesToRead > 0)
				{
					answertxt += sp1->ReadExisting();
					System::Threading::Thread::Sleep(100);
				}
			}
			waitAnswer = waitAnswer & (DateTime::Now.Subtract(start).TotalMilliseconds < timeout);
		}
	}

	AddLogByTip(LogType::answer);
	return answered;
}
#pragma endregion

#pragma region "I/O Logs"
void IDMM::OnLogChanged(LogChangeEventArgs^ e)
{
	LogChanged(this, e);
};

void IDMM::AddLogByTip(LogType tip)
{
	String^ log = "";
	switch (tip)
	{
	case LogType::answer:
		log = Name + "<-- " + answertxt->Trim() + Environment::NewLine;		//DateTime::Now.ToString("mm:ss:nnn") +
		break;
	case LogType::cmd:
		if (cmdtxt != "")
			log = Name + "--> " + cmdtxt + Environment::NewLine;			//DateTime::Now.ToString("mm:ss:nnn") +
		break;
	}
	logText += log;
	OnLogChanged(gcnew LogChangeEventArgs(log));
};

void IDMM::AddLog(String^ text)
{
	String^ log = DateTime::Now.ToString("mm:ss:nnn") + "<-- " + text + Environment::NewLine;
	logText += log;
	OnLogChanged(gcnew LogChangeEventArgs(log));
};

void IDMM::AddLogText(String^ text)  {
	String^ log = DateTime::Now.ToString("mm:ss:nnn") + "<-- " + text + Environment::NewLine;
	logText += log;
	OnLogChanged(gcnew LogChangeEventArgs(log));
}
String^ IDMM::ReturnSTB() {
	return "";
}

#pragma endregion

#pragma region "Must implement fuction"
void IDMM::SetInitConfig() { return; }
bool IDMM::ChangeNPLC(double nplc) { return true; }
bool IDMM::GetTerminalSide() { return true; }
bool IDMM::ZInput() { return true; }
bool IDMM::ChangeVoltageRange(VoltageRange range) { return true; }
bool IDMM::SendIDN(String^% _anwser) {
	_anwser = "Generic DMM";
	return true;
}
bool IDMM::PrepareLiveData() { return true; }
bool IDMM::PrepareNextLiveData() { return true; }
bool IDMM::ReadLiveData(String^% _rawdata) {
	_rawdata = "+1.23456789E-03VDC, +11.664SECS, +236RDNG, 000, 0000LIMITS";
	return true; 
}
void IDMM::CalculateParam() {
	WaveFormSampleCount = 1;
};
bool IDMM::GetLineFreq() {
	return true;
}
String^ IDMM::CreateFakeWaveFormRawData(int adet) {
	return  "+1.23456789E-03VDC, +11.664SECS, +236RDNG, 000, 0000LIMITS";
}
bool IDMM::CheckDataReady() {
	dataReady = true;
	return dataReady;
}
void IDMM::CheckError() {
	hasError = false;
}

bool IDMM::ReadError()
{
	ErrorStr = "";
	return true;
}
#pragma endregion