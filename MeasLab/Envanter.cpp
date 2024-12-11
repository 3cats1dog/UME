#include "Envanter.h"

using namespace System::Text;
using namespace System;
using namespace MeasLab;

Envanter::Envanter() {

	this->ID = 0;
	this->Marka = "";
	this->Model = "";
	this->No = 0;
	this->SeriNo = "";
	this->sfVpeak = 1.0;
	this->sfVrms = 1.0;
	this->tip = EnvanterType::DMM;

	//Nothing to do;
}

Generic::List<Envanter^>^  Envanter::getSampleList()
{
	Generic::List<Envanter^>^ newList = gcnew Generic::List<Envanter^>();

	Envanter^ env6 = gcnew Envanter();
	env6->ID = 6;
	env6->No = 6;
	env6->device = DMMDevice::NoneDevice;
	env6->connType = EnvanterConnection::None;
	env6->Marka = L"None";
	env6->Model = L"None";
	env6->SeriNo = L" ";
	env6->sfVrms = 1;
	env6->sfVpeak = 1;
	env6->tip = EnvanterType::DMM;
	newList->Add(env6);


	Envanter^ env7 = gcnew Envanter();
	env7->ID = 7;
	env7->No = 7;
	env7->device = DMMDevice::HandType;
	env7->connType = EnvanterConnection::None;
	env7->Marka = L"Hand type";
	env7->Model = L"Hand type";
	env7->SeriNo = L"-";
	env7->sfVrms = 1;
	env7->sfVpeak = 1;
	env7->tip = EnvanterType::DMM;
	newList->Add(env7);

	Envanter^ env1 = gcnew Envanter();
	env1->ID = 1;
	env1->No = 1;
	env1->device = DMMDevice::Agilent3458A;
	env1->connType = EnvanterConnection::GBIP;
	env1->Marka = L"Agilent";
	env1->Model = L"3458";
	env1->SeriNo = L"12345";
	env1->tip = EnvanterType::DMM;
	env1->Address = L"Demo";
	newList->Add(env1);


	//Envanter^ env2 = gcnew Envanter();
	//env2->ID = 2;
	//env2->No = 2;
	//env2->device = DMMDevice::Agilent34410;
	//env2->connType = EnvanterConnection::GBIP;
	//env2->Marka = L"Agilent";
	//env2->Model = L"34410";
	//env2->SeriNo = L"A12345";
	//env2->Address = L"Demo";
	//env2->tip = EnvanterType::DMM;
	//newList->Add(env2);

	Envanter^ env3 = gcnew Envanter();
	env3->ID = 3;
	env3->No = 3;
	env3->device = DMMDevice::Agilent34411;
	env3->connType = EnvanterConnection::GBIP;
	env3->Marka = L"Agilent";
	env3->Model = L"34411A";
	env3->SeriNo = L"B12345";
	env3->Address = L"Demo";
	env3->tip = EnvanterType::DMM;
	newList->Add(env3);

	//Envanter^ env8 = gcnew Envanter();
	//env8->ID = 8;
	//env8->No = 8;
	//env8->device = DMMDevice::NIPXI4081;
	//env8->connType = EnvanterConnection::GBIP;
	//env8->Marka = L"NI";
	//env8->Model = L"PXI 4081";
	//env8->SeriNo = L"B12345";
	//env8->Address = L"Demo";
	//env8->tip = EnvanterType::DMM;
	//newList->Add(env8);


	Envanter^ env4 = gcnew Envanter();
	env4->ID = 4;
	env4->No = 4;
	env4->device = DMMDevice::DividerDevice;
	env4->connType = EnvanterConnection::None;
	env4->Marka = L"Germany";
	env4->Model = L"HPV";
	env4->SeriNo = L"Divider1";
	env4->sfVrms = 1000.4;
	env4->sfVpeak = env4->sfVrms * Math::Sqrt(2);
	env4->tip = EnvanterType::Divider;
	newList->Add(env4);

	Envanter^ env5= gcnew Envanter();
	env5->ID = 5;
	env5->No = 5;
	env5->device = DMMDevice::DividerDevice;
	env5->connType = EnvanterConnection::None;
	env5->Marka = L"Local";
	env5->Model = L"HPV";
	env5->SeriNo = L"Divider2";
	env5->sfVrms = 5001.6;
	env5->sfVpeak = env5->sfVrms * Math::Sqrt(2);
	env5->tip = EnvanterType::Divider;
	newList->Add(env5);

	Envanter^ env11 = gcnew Envanter();
	env11->ID = 11;
	env11->No = 11;
	env11->device = DMMDevice::DividerDevice;
	env11->connType = EnvanterConnection::None;
	env11->Marka = L"Local";
	env11->Model = L"Default";
	env11->SeriNo = L"Divider2";
	env11->sfVrms = 1000.0;
	env11->sfVpeak = 1000.0;
	env11->tip = EnvanterType::Divider;
	newList->Add(env11);


	Envanter^ env9 = gcnew Envanter();
	env9->ID = 9;
	env9->No = 9;
	env9->device = DMMDevice::Agilent3458A;
	env9->connType = EnvanterConnection::GBIP;
	env9->Marka = L"Agilent";
	env9->Model = L"3458A";
	env9->SeriNo = L"B12345";
	env9->Address = L"Demo";
	env9->tip = EnvanterType::DMM;
	newList->Add(env9);


	Envanter^ env10 = gcnew Envanter();
	env10->ID = 10;
	env10->No = 10;
	env10->device = DMMDevice::Agilent34470;
	env10->connType = EnvanterConnection::GBIP;
	env10->Marka = L"Agilent";
	env10->Model = L"34470A";
	env10->Address = L"Demo";
	env10->SeriNo = L"B12345";
	env10->tip = EnvanterType::DMM;
	newList->Add(env10);

	return (newList);
}