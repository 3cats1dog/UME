#include "EquipList.h"
#include "Global.h";
#include "GenericDMM.h";

#include "Agilent3458.h";
#include "Agilent34410.h";
#include "Agilent34470.h";
#include "GenericDMM.h";

using namespace System;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace MeasLab;

System::Void EquipList::EquipList_Load(System::Object^ sender, System::EventArgs^ e) {


	DMMList->Clear();
	DividerList->Clear();

	for each (Envanter ^ enb  in G::EnvanterList)
	{
		if (enb->ID > MaxID) { MaxID = enb->ID; }
		switch (enb->tip)
		{
		case EnvanterType::Divider: DividerList->Add(enb); break;
		case EnvanterType::DMM: DMMList->Add(enb); break;
		}
	}

	FillDMM();
	FillDivider();
	cmbNewDMMType->SelectedIndex = 0;

	//Get All GPIB Resource;
	FindDeviceList();

	cmbAddress->Items->Clear();
	for each (String^ addr  in G::connectedGBIP)
	{
		cmbAddress->Items->Add(addr);
	}
	ClearForm();
}

Void EquipList::btnGPIBFind_Click(System::Object^ sender, System::EventArgs^ e)
{
	try
	{
		//Ivi::Visa::Interop::ResourceManager^ rsc = gcnew Ivi::Visa::Interop::ResourceManagerClass();
		//for each (String^ str in  rsc->FindRsrc("?*INSTR"))	
		//{
		//	G::connectedGBIP->Add(str);
		//} 

		for each (String ^ str in  IDMM::findRrsc())	//G::rsc->FindRsrc("?*INSTR")
		{
			if (str->Contains("GP"))
			{
				G::connectedGBIP->Add(str);
			}
		}

	}
	catch (Exception^ ex)
	{

	}
	cmbAddress->Items->Clear();
	for each (String ^ addr  in G::connectedGBIP)
	{
		cmbAddress->Items->Add(addr);
	}
}

Void EquipList::FindDeviceList() {

	G::connectedGBIP = gcnew Generic::List<String^>();
	return;
	try
	{

		//Ivi::Visa::Interop::ResourceManager^ rsc = gcnew Ivi::Visa::Interop::ResourceManagerClass();
		//for each (String^ str in  rsc->FindRsrc("?*INSTR"))	
		//{
		//	G::connectedGBIP->Add(str);
		//} 

		for each (String ^ str in  IDMM::findRrsc())	//G::rsc->FindRsrc("?*INSTR")
		{
			if (str->Contains("GP"))
			{
				G::connectedGBIP->Add(str);
			}
		}

	}
	catch (Exception^ ex)
	{

	}
}

Void EquipList::FillDMM() {
	dgw_DMM->DataSource = DMMList->ToArray();
	for each (DataGridViewColumn ^ col in dgw_DMM->Columns)
	{
		if (col->DataPropertyName == "Marka") { col->DisplayIndex = 0; }
		if (col->DataPropertyName == "Model") { col->DisplayIndex = 1; }
		if (col->DataPropertyName == "SeriNo") { col->DisplayIndex = 2; }
		if (col->DataPropertyName == "StrConnType") { col->DisplayIndex = 3; }
	}

	dgw_DMM->Refresh();
	dgw_DMM->Update();
}
Void EquipList::FillDivider() {
	dgw_Divider->DataSource = DividerList->ToArray();
	for each (DataGridViewColumn ^ col in dgw_Divider->Columns)
	{
		if (col->DataPropertyName == "Marka") { col->DisplayIndex = 0; }
		if (col->DataPropertyName == "Model") { col->DisplayIndex = 1; }
		if (col->DataPropertyName == "SeriNo") { col->DisplayIndex = 2; }
		if (col->DataPropertyName == "sfVrms") { col->DisplayIndex = 3; }
		if (col->DataPropertyName == "sfVpeak") { col->DisplayIndex = 4; }
		if (col->DataPropertyName == "sfVdc") { col->DisplayIndex = 5; }
	}

	dgw_Divider->Refresh();
	dgw_Divider->Update();
}

Void EquipList::ClearForm() {
	txtMarka->Text = "";
	txtModel->Text = "";
	txtSeriNo->Text = "";
	txtsfVpeak->Text = "";
	txtsfVrms->Text = "";
	txtsfVdc->Text = "";
	pnlDividersf->Visible = false;
	pnlDMMConnection->Visible = false;

	txtMarka->Enabled = false;
	txtModel->Enabled = false;
	txtSeriNo->Enabled = false;

	btnDelete->Visible = false;
	btnSave->Visible = false;
	btnTestConnection->Visible = false;
}

Void EquipList::UpdateForm() {
	txtMarka->Text = SelectedEnv->Marka;
	txtModel->Text = SelectedEnv->Model;
	txtSeriNo->Text = SelectedEnv->SeriNo;
	txtsfVpeak->Text = SelectedEnv->sfVpeak.ToString("F2", G::activecul());
	txtsfVrms->Text = SelectedEnv->sfVrms.ToString("F2", G::activecul());
	txtsfVdc->Text = SelectedEnv->sfVdc.ToString("F2", G::activecul());

	cmbConnType->SelectedIndex = (int)SelectedEnv->connType;
	cmbAddress->Text = SelectedEnv->Address;

	txtMarka->Enabled = true;
	txtModel->Enabled = true;
	txtSeriNo->Enabled = true;

	switch (SelectedEnv->tip)
	{
		  case EnvanterType::Divider:
			  lblTypeName->Visible = false;
			  lblDMMType->Visible = false;
			  pnlDividersf->Visible = true;
			  pnlDMMConnection->Visible = false;
			  btnDelete->Visible = SelectedEnv->ID == 0 ? false : true;
			  btnSave->Visible = true;
			  btnTestConnection->Visible = false;
			  break;
		  case EnvanterType::DMM:
			  lblTypeName->Visible = true;
			  lblDMMType->Visible = true;
			  pnlDividersf->Visible = false;
			  pnlDMMConnection->Visible = true;
			  btnDelete->Visible = false;
			  btnSave->Visible = true;
			  btnTestConnection->Visible = true;
			  if (SelectedEnv->connType == EnvanterConnection::GBIP || SelectedEnv->connType == EnvanterConnection::PXI)
			  {
				  btnDelete->Visible = true;
			  }
			  lblDMMType->Text = SelectedEnv->device.ToString();
			  break;
	}
}
Void EquipList::ReadForm() {

	SelectedEnv->Marka = txtMarka->Text;
	SelectedEnv->Model = txtModel->Text;
	SelectedEnv->SeriNo = txtSeriNo->Text;

	cmbConnType->SelectedIndex = (int)SelectedEnv->connType;

	txtMarka->Enabled = true;
	txtModel->Enabled = true;
	txtSeriNo->Enabled = true;

	double sf1, sf2, sf3;
	bool parse1 = double::TryParse(txtsfVpeak->Text->Replace(",","."), Globalization::NumberStyles::Any, G::invcul(), sf1);
	bool parse2 = double::TryParse(txtsfVrms->Text->Replace(",", "."), Globalization::NumberStyles::Any, G::invcul(), sf2);
	bool parse3 = double::TryParse(txtsfVdc->Text->Replace(",", "."), Globalization::NumberStyles::Any, G::invcul(), sf3);

	switch (SelectedEnv->tip)
	{
	case EnvanterType::Divider:

		if (parse1)SelectedEnv->sfVpeak = sf1;
		if (parse2)SelectedEnv->sfVrms = sf2;
		if (parse3)SelectedEnv->sfVdc = sf3;

		if (!(parse1 && parse2 && parse3))
		{
			MessageBox::Show(L"Lütfen geçerli bir sayı giriniz!!!");
		}

		break;
	case EnvanterType::DMM:
		break;
	}
	SelectedEnv->Address = cmbAddress->Text;
}


System::Void  EquipList::btnAddDMM_Click(System::Object^ sender, System::EventArgs^ e) {

	SelectedEnv = gcnew	Envanter();
	SelectedEnv->tip = EnvanterType::DMM;
	SelectedEnv->connType = EnvanterConnection::GBIP;
	SelectedEnv->ID = 0;
	btnSave->Text = L"Yeni Ekle";

	switch (cmbNewDMMType->SelectedIndex)
	{
	case 0:
		SelectedEnv->device = DMMDevice::Agilent3458A;
		SelectedEnv->Marka = "Agilent";
		SelectedEnv->Model = "3458A";
		break;
	case 1:
		SelectedEnv->device = DMMDevice::Agilent34411;
		SelectedEnv->Marka = "Agilent";
		SelectedEnv->Model = "34411";
		break;
	case 2:
		SelectedEnv->device = DMMDevice::Agilent34470;
		SelectedEnv->Marka = "Agilent";
		SelectedEnv->Model = "34470";
		break;
	case 3:
		SelectedEnv->device = DMMDevice::NIPXI4081;
		SelectedEnv->connType = EnvanterConnection::PXI;
		SelectedEnv->Marka = "National Instrument";
		SelectedEnv->Model = "PXI 4081";
		break;
	}
	UpdateForm();
}

System::Void EquipList::btnAddDivider_Click(System::Object^ sender, System::EventArgs^ e) {
	SelectedEnv = gcnew	Envanter();
	SelectedEnv->device = DMMDevice::DividerDevice;
	SelectedEnv->tip = EnvanterType::Divider;
	SelectedEnv->ID = 0;
	btnSave->Text = L"Yeni Ekle";
	UpdateForm();
}

System::Void  EquipList::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
	switch (SelectedEnv->tip)
	{
	case EnvanterType::Divider:
		DividerList->Remove(SelectedEnv);
		G::EnvanterList->Remove(SelectedEnv);
		//Save as xml;
		G::SaveEnvanter();
		FillDivider();
		break;
	case EnvanterType::DMM:
		DMMList->Remove(SelectedEnv);
		G::EnvanterList->Remove(SelectedEnv);
		//Save as xml;
		G::SaveEnvanter();
		FillDMM();
		break;
	}
}

System::Void  EquipList::btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
	ReadForm();
	ClearForm();
	switch (SelectedEnv->tip)
	{
	case EnvanterType::Divider:
		if (SelectedEnv->ID == 0)
		{
			SelectedEnv->ID = MaxID + 1;
			MaxID++;
			//New divider;
			DividerList->Add(SelectedEnv);
			G::EnvanterList->Add(SelectedEnv);
		}
		FillDivider(); 
		break;
	case EnvanterType::DMM: 
		if (SelectedEnv->ID == 0)
		{
			SelectedEnv->ID = MaxID + 1;
			MaxID++;
			//New DMM;
			DMMList->Add(SelectedEnv);
			G::EnvanterList->Add(SelectedEnv);
		}
		FillDMM(); 
		break;
	}
	G::SaveEnvanter();
	delete SelectedEnv;
}

System::Void  EquipList::dgw_DMM_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
	if (dgw_DMM->SelectedRows->Count < 1) return;
	SelectedEnv = DMMList[dgw_DMM->SelectedRows[0]->Index];
	btnSave->Text = L"Güncelle";
	UpdateForm();
}
System::Void  EquipList::dgw_Divider_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
	if (dgw_Divider->SelectedRows->Count < 1) return;
	SelectedEnv = DividerList[dgw_Divider->SelectedRows[0]->Index];
	btnSave->Text = L"Güncelle";
	UpdateForm();
}

System::Void EquipList::btnTestConnection_Click(System::Object^ sender, System::EventArgs^ e) {
	MeasLab::IDMM^ instrument;

	switch (SelectedEnv->device)
	{
	case DMMDevice::Agilent3458A: instrument = gcnew AgilentDMM::Agilent3458(); break;
	case DMMDevice::Agilent34470: instrument = gcnew AgilentDMM::Agilent34470(); break;
	case DMMDevice::Agilent34411: instrument = gcnew AgilentDMM::Agilent3441x(AgilentDMM::DMMModel::Model_34411); break;
	default:
	case DMMDevice::Generic232: instrument = gcnew MeasLab::IDMM(); break;
	}

	SelectedEnv->Address = cmbAddress->Text;

	switch (SelectedEnv->connType)
	{
	case EnvanterConnection::GBIP:
		instrument->Connect(SelectedEnv->Address, 0, true);
		break;
	case EnvanterConnection::RS232:
		instrument->Connect(SelectedEnv->Address, G::mySet->BaudRate, false);
		break;
	case EnvanterConnection::None:
		//El ile veri alınacak;
		break;
	}
	//First look any data avaliable;
	instrument->ReadError();

	System::Threading::Thread::Sleep(1);
	String^ deviceSTR = "";
	bool readOK = instrument->SendIDN(deviceSTR);
	if (readOK)
	{
		MessageBox::Show(deviceSTR);
	}
	else
	{
		MessageBox::Show(L"Bağlantı hatası!!");
	}
	instrument->DisConnect();

	delete instrument;
}

