#pragma once
#pragma once

#ifndef _ENVANTER_H_
#define _ENVANTER_H_


#include <string>
using namespace System::Text;
using namespace System;
using namespace System::Collections;
using namespace System::Xml::Serialization;

namespace MeasLab {
	public enum class  DMMDevice
	{
		Agilent34410,
		Agilent34470,
		Agilent34411,
		Agilent3458A,
		NIPXI4081,
		Generic232,
		HandType,
		DividerDevice,
		NoneDevice,
	};
	public enum class EnvanterType
	{
		DMM = 1,
		Divider = 2,
	};

	public enum class EnvanterConnection
	{
		None = 0,
		GBIP = 1,
		RS232 = 2,
		PXI = 3,
	};

	[Serializable]
	public ref class Envanter
	{
	private:
		 String^ _Marka;
		 String^ _Model;
		 String^ _SeriNo;
		 double _sfVrms;
		 double _sfVpeak;
		 double _sfVdc;
		 String^ _Address;

	public:
		Envanter();
		static Generic::List<Envanter^>^ getSampleList();

		property int ID;
		property int No;
		EnvanterConnection connType;
		DMMDevice device;
		EnvanterType tip;

		[XmlIgnore]
		property String^ Name {
			String^ get()
			{
				switch (tip)
				{
				case EnvanterType::DMM:
					return  Model + " (" + SeriNo + ")";
					break;
				case EnvanterType::Divider:
					return Marka + " (sf:" + sfVrms.ToString() + ")";
					break;
				default:
					return "-";
					break;
				}
			}
		}
		[XmlIgnore]
		property String^ tipName {
			String^ get() {
				switch (tip)
				{
				case EnvanterType::DMM: return "DMM"; break;
				case EnvanterType::Divider: return L"Bölücü"; break;
				default: return ""; break;
				}
			}
		}
		[XmlIgnore]
		property String^ ScalaFactor { String^ get() {
			switch (tip)
			{
			case EnvanterType::DMM: return "-"; break;
			case EnvanterType::Divider: return sfVrms.ToString(); break;
			default: return ""; break;
			}
		}}

		[XmlIgnore]
		property String^ StrConnType { String^ get() {
			switch (connType)
			{
			case EnvanterConnection::None: return "El tipi"; break;
			case EnvanterConnection::GBIP:return "GBIP"; break;
			case EnvanterConnection::RS232:return "RS232"; break;
			default: return ""; break;
			}
		}}

		property String^ Marka { String^ get() { return _Marka; }  void set(String^ value) { _Marka = value; } }
		property String^ Model { String^ get() { return _Model; }  void set(String^ value) { _Model = value; } }
		property String^ SeriNo { String^ get() { return _SeriNo; }  void set(String^ value) { _SeriNo = value; } }
		property String^ Address { String^ get() { return _Address; }  void set(String^ value) { _Address = value; } }
		property double sfVrms { double get() { return _sfVrms; }  void set(double value) { _sfVrms = value; } }
		property double sfVpeak { double get() { return _sfVpeak; }  void set(double value) { _sfVpeak = value; } }
		property double sfVdc { double get() { return _sfVdc; }  void set(double value) { _sfVdc = value; } }

		
		virtual String^ ToString() override
		{
			switch (tip)
			{
			case EnvanterType::DMM:
				return  Model + " (" + SeriNo + ")"; 
				break;
			case EnvanterType::Divider:
				return Marka + " (sf:" + sfVrms.ToString() + ")";
				break;
			default:
				return "-";
				break;
			}
		}

	};
}
#endif