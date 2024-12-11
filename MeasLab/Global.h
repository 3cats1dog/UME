#pragma once

#ifndef _GLOBAL_H_
#define _GLOBAL_H_



#include "Settings.h" ;
#include "XMLFinder.h";
#include "Envanter.h";

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO::Ports;
using namespace System::IO;
using namespace MeasLab;
//using namespace Ivi;


namespace MeasLab {

	public ref  class G
	{
	public:
		static System::String^ ProductTitle = L"High Voltage Measurements";
		static System::String^ ProductVersion = "1.2.1";

		
		static System::String^ SETFILENAME = "UME_DMM.xml";
		static System::String^ ENVFILENAME = "Envanter.xml";
		static Settings^ mySet;
		static Generic::List<Envanter^>^ EnvanterList;
		static bool isFake;	// = true;
		static System::String^ DELIMETER;	// = ";";
		static System::Globalization::CultureInfo^ trcul() { return	System::Globalization::CultureInfo::CreateSpecificCulture("tr"); }
		static System::Globalization::CultureInfo^ invcul() { return System::Globalization::CultureInfo::InvariantCulture; }
		static System::Globalization::CultureInfo^ activecul() { return System::Globalization::CultureInfo::CurrentUICulture; }
		static Generic::List<String^>^ connectedGBIP;
		//static Ivi::Visa::Interop::ResourceManager^ rsc = gcnew Ivi::Visa::Interop::ResourceManagerClass();
		static double MAXLIMIT = 10E+10;
		 
		static bool Log_First1000 = false;
		static bool Log_Init = false;
		static System::String^ SaveLog;
		static System::String^ SaveLog_First1000;
		static System::String^ SaveLog_Init;
		G()
		{
			isFake = true;
			DELIMETER = ";";
		}

		~G()
		{

		}

		static void ReadSettings()
		{
			//XMLFinder^ xx = gcnew XMLFinder();
			//System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::CommonApplicationData) + "/UME";
			System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData) + "/HV_MEASLAB";
			System::String^ path = directory + "/" + G::SETFILENAME;
			if (File::Exists(path))
			{
				try
				{
					mySet = MeasLab::XMLFinder::DeserializeObject(path);
				}
				catch (Exception^ ex)
				{
					mySet = gcnew Settings();
				}
			}
			if (mySet == nullptr) mySet = gcnew Settings();
			//Attach to G;
			DELIMETER = mySet->Delimeter;
		}
		static bool SaveSettings()
		{
			//XMLFinder^ xx = gcnew XMLFinder();
			try
			{
				DELIMETER = mySet->Delimeter;
				//System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::CommonApplicationData) + "/UME";
				System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData) + "/HV_MEASLAB";
				if (!Directory::Exists(directory))
				{
					Directory::CreateDirectory(directory);
				}
				String^ path = directory + "/" + SETFILENAME;
				return MeasLab::XMLFinder::Serialize(path, mySet);
				return true;
			}
			catch (Exception^ ex)
			{
				return false;
			}
		}

		static void ReadEnvanter()
		{
			//System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::CommonApplicationData) + "/UME";
			System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData) + "/HV_MEASLAB";
			System::String^ path = directory + "/" + G::ENVFILENAME;
			if (File::Exists(path))
			{
				try
				{
					EnvanterList = MeasLab::XMLFinder::DeserializeEnv(path);
				}
				catch (Exception^ ex)
				{
					EnvanterList = gcnew Generic::List<Envanter^>();
				}
			}
			if (EnvanterList == nullptr) {
				EnvanterList = Envanter::getSampleList();	// gcnew Generic::List<Envanter^>();
			}
		}
		static bool SaveEnvanter()
		{
			try
			{
				//String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::CommonApplicationData) + "/UME";
				System::String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData) + "/HV_MEASLAB";
				if (!Directory::Exists(directory))
				{
					Directory::CreateDirectory(directory);
				}
				String^ path = directory + "/" + ENVFILENAME;
				return MeasLab::XMLFinder::SerializeEnv(path, EnvanterList);
				return true;
			}
			catch (Exception^ ex)
			{
				return false;
			}
		}

	};

};

#endif // !_GLOBAL_H_
