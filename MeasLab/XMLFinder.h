#pragma once

#ifndef _XMLFINDER_H_
#define _XMLFINDER_H_


//#include "Global.h"
#include "Settings.h";
#include "Envanter.h";

using namespace System::Xml;
using namespace System::Xml::Serialization;
using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::IO;
using namespace MeasLab;

namespace MeasLab {

	public ref class XMLFinder
	{
	public:
		XMLFinder();
		static bool Serialize(System::String^ path, Settings^ set);
		static Settings^ DeserializeObject(System::String^ path);

		static bool SerializeEnv(System::String^ path, Generic::List<Envanter^>^ envList);
		static Generic::List<Envanter^>^ DeserializeEnv(System::String^ path);

	};
}

#endif // !_XMLFINDER_H_
