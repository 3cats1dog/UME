#include "XMLFinder.h"


using namespace System::Xml;
using namespace System::Xml::Serialization;
using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::IO;
using namespace MeasLab;

XMLFinder::XMLFinder() {
	//Nothing to do;
}

bool XMLFinder::Serialize(System::String^ path, Settings^ set)
{
	try
	{
		XmlSerializer^ xmlserializer = gcnew XmlSerializer(Settings::typeid);
		TextWriter^ tw = gcnew StreamWriter(path, false, Encoding::UTF8);
		XmlWriter^ writer = XmlWriter::Create(tw);
		xmlserializer->Serialize(writer, set);
		writer->Close();
		tw->Close();
		return true;
	}
	catch (Exception^ ex)
	{
		return false;
	}
}
Settings^ XMLFinder::DeserializeObject(System::String^ path)
{
	Settings^ newSet;
	try
	{
		XmlSerializer^ xmlSerializer = gcnew XmlSerializer(Settings::typeid);

		MemoryStream^ memoryStream = gcnew MemoryStream(File::ReadAllBytes(path));
		// No settings need modifying here
		XmlReaderSettings^ xmlReaderSettings = gcnew XmlReaderSettings();
		XmlReader^ xmlReader = XmlReader::Create(memoryStream, xmlReaderSettings);
		newSet = (Settings^)(xmlSerializer->Deserialize(xmlReader));
		memoryStream->Close();
		xmlReader->Close();
		return newSet;
	}
	catch (Exception^ ex)
	{
		return newSet;
	}
}

bool XMLFinder::SerializeEnv(System::String^ path, Generic::List<Envanter^>^ envList) {
	//return true;
	try
	{
		System::Type^ envListType = envList->GetType();
		XmlSerializer^ xmlserializer = gcnew XmlSerializer(envListType);			//	System::Collections::Generic::List<MeasLab::Envanter^>::typeid
		TextWriter^ tw = gcnew StreamWriter(path, false, Encoding::UTF8);
		XmlWriter^ writer = XmlWriter::Create(tw);
		xmlserializer->Serialize(writer, envList);
		writer->Close();
		tw->Close();
		return true;
	}
	catch (Exception^ ex)
	{
		return false;
	}
}

Generic::List<Envanter^>^ XMLFinder::DeserializeEnv(System::String^ path) {
	Generic::List<Envanter^>^ newList = gcnew	Generic::List < Envanter^>();
	try
	{
		XmlSerializer^ xmlSerializer = gcnew XmlSerializer(System::Collections::Generic::List<MeasLab::Envanter^>::typeid);

		MemoryStream^ memoryStream = gcnew MemoryStream(File::ReadAllBytes(path));
		// No settings need modifying here
		XmlReaderSettings^ xmlReaderSettings = gcnew XmlReaderSettings();
		XmlReader^ xmlReader = XmlReader::Create(memoryStream, xmlReaderSettings);
		newList = (Generic::List<Envanter^>^)(xmlSerializer->Deserialize(xmlReader));
		memoryStream->Close();
		xmlReader->Close();
		return newList;
	}
	catch (Exception^ ex)
	{
		return Envanter::getSampleList();
		return newList;
	}
}