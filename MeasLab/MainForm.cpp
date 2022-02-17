#include "MainForm.h"
#include "Agilent3458.h";
#include "Agilent34410.h";
#include "Agilent34470.h";
#include "GenericDMM.h";
#include "NIPXI4081.h";
#include  "Extensions.h";

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::IO::Ports;
using namespace MeasLab;

[STAThread]
void main(array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(true);
	MeasLab::MainForm form;
	Application::Run(% form);
}


#pragma region  "Init"
System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	G::ReadSettings();
	G::ReadEnvanter();
	
	panelLog->Visible = false;
	LoadSetting();
	CheckDemoMode();
	LoadCombo();

	//Clear Form
	txtLivePeakRoot2->Text = "-";
	txtLiveRMS->Text = "-";
	txtLiveDC->Text = "-";

	txtLivePeakRoot2_UUT->Text = "-";
	txtLiveRMS_UUT->Text = "-";
	txtLiveDC_UUT->Text = "-";

	lblRemainData->Text = "-- / --";
	lblPassTime->Text = "--:--";

	txtTerminal_DMM->Text = "-";
	txtTerminal_UUT->Text = "-";
	txtZInput_DMM->Text = "-";
	txtZInput_UUT->Text = "-";
	txtsfVrms_DMM->Text = "-";
	txtsfVrms_UUT->Text = "-";
	txtsfVpeak_DMM->Text = "-";
	txtsfVpeak_UUT->Text = "-";
	txtsfVdc_DMM->Text = "-";
	txtsfVdc_UUT->Text = "-";


	//Prepare test param;
	ReadFormParam();
}
System::Void MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	delete instrument, instrumentUUT;
	if (thRead != nullptr) { thRead->Abort(); }
	if (thd1 != nullptr) { thd1->Abort(); }
	if (thd2 != nullptr) { thd2->Abort(); }

	if (timer != nullptr)
		timer->Dispose(nofity);
}

void MainForm::LoadCombo()
{
	//Clear labels
	toolStripProgressBar1->Visible = false; // instrument->type == DMMType::DMM;
	toolStripProgressBar2->Visible = false; // instrumentUUT->type == DMMType::DMM;

	txtLiveRMS->Text = "-";
	txtLivePeakRoot2->Text = "-";
	txtLiveDC->Text = "-";

	txtLiveRMS_UUT->Text = "-";
	txtLivePeakRoot2_UUT->Text = "-";
	txtLiveDC_UUT->Text = "-";

	lblTestInfo_DMM->Text = "";
	lblTestInfo_UUT->Text = "";


	cmbAddress_DMM->Items->Clear();
	cmbAddress_UUT->Items->Clear();
	cmbDivider_DMM->Items->Clear();
	cmbDivider_UUT->Items->Clear();

	cmbAddress_DMM->ValueMember = "ID";
	cmbAddress_UUT->ValueMember = "ID";
	cmbDivider_DMM->ValueMember = "ID";
	cmbDivider_UUT->ValueMember = "ID";

	cmbAddress_DMM->DisplayMember = "Name";
	cmbAddress_UUT->DisplayMember = "Name";
	cmbDivider_DMM->DisplayMember = "Name";
	cmbDivider_UUT->DisplayMember = "Name";

	//cmbAddress_UUT->Items->Add("Yok");
	//cmbAddress_UUT->Items->Add("El tipi");

	for each (Envanter^ env in G::EnvanterList)
	{
		if (env->tip == EnvanterType::DMM)
		{
			if (!(env->device == DMMDevice::HandType || env->device == DMMDevice::NoneDevice))
				cmbAddress_DMM->Items->Add(env);
			cmbAddress_UUT->Items->Add(env);
		}
		else {
			cmbDivider_DMM->Items->Add(env);
			cmbDivider_UUT->Items->Add(env);
		}
	}

	cmbAddress_DMM->SelectedIndex = 0;
	cmbAddress_UUT->SelectedIndex = 0;
	cmbVoltageRange_DMM->SelectedIndex = 0;
	cmbVoltageRange_UUT->SelectedIndex = 0;
	cmbDivider_DMM->SelectedIndex = 0;
	cmbDivider_UUT->SelectedIndex = 0;

	cmbPeakType->SelectedIndex = 0;


	//Fill Last Selected;
	isInit = true;
	for each (Envanter ^ env in G::EnvanterList)
	{
		if (env->ID == G::mySet->LastDMMID) { cmbAddress_DMM->SelectedItem = env; }
		if (env->ID == G::mySet->LastUUTID) { cmbAddress_UUT->SelectedItem = env; }
		if (env->ID == G::mySet->LastDMMDividerID) { cmbDivider_DMM->SelectedItem = env; }
		if (env->ID == G::mySet->LastUUTDividerID) { cmbDivider_UUT->SelectedItem = env; }


	}
	if (G::mySet->LastDMMRange ==(int) VoltageRange::AUTO)
	{
		chkRangeAuto_DMM->Checked = true;
		cmbVoltageRange_DMM->SelectedIndex = 0;
	}
	else
	{
		cmbVoltageRange_DMM->SelectedIndex = G::mySet->LastDMMRange;
	}

	if (G::mySet->LastUUTRange == (int)VoltageRange::AUTO)
	{

		chkRangeAuto_UUT->Checked = true;
		cmbVoltageRange_UUT->SelectedIndex =0;
	}
	else
	{
		cmbVoltageRange_UUT->SelectedIndex = G::mySet->LastUUTRange;

	}


	//txtFreq->Text = G::mySet->LastFreq.ToString();
	cmbMeasType->SelectedIndex = G::mySet->LastMeasTipi;
	cmbPeakType->SelectedIndex = G::mySet->LastTestTipi;

}

void MainForm::CheckDemoMode()
{
	bool hasDemoMode = false;

	if (UUT != nullptr)
	{
		if (UUT->device == DMMDevice::HandType || UUT->device == DMMDevice::NoneDevice)
		{

		}
		else
		{
			if (UUT->Address->Contains("Demo")) hasDemoMode = true;
		}
	}
	if (DMM != nullptr)
	{
		if (DMM->Address->Contains("Demo")) hasDemoMode = true;
	}
	lblDemoMode->Visible = hasDemoMode;
	if (hasDemoMode)
		lblFooter->Text = "!!Demo Mode!!";
}

void MainForm::LoadSetting()
{
	txtBarcode->Text = G::mySet->Etiket;
	//txtRatio->Text = G::mySet->Ratio.ToString("F2", G::trcul());
	cmbSampleAdet->Text = G::mySet->WaveCount.ToString();
}
#pragma endregion

#pragma region "Test Param"

System::Void  MainForm::txtAppliedVoltage_DMM_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	if (instrument == nullptr) return;
	if (DMM == nullptr) return;
	if (chkRange_DMM->Checked) { AutoCalcVoltageRange_DMM(); }
}
System::Void  MainForm::txtAppliedVoltage_UUT_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	if (instrumentUUT == nullptr) return;
	if (UUT == nullptr) return;
	if (chkRange_UUT->Checked) { AutoCalcVoltageRange_DMM(); }
}

System::Void MainForm::chkRangeAuto_DMM_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	AutoCalcVoltageRange_DMM();
}
System::Void MainForm::chkRangeAuto_UUT_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	AutoCalcVoltageRange_UUT();
}

System::Void MainForm::chkRange_UUT_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	AutoCalcVoltageRange_UUT();
}
System::Void MainForm::chkRange_DMM_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	AutoCalcVoltageRange_DMM();
}

System::Void  MainForm::cmbSampleAdet_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	if (instrument == nullptr) return;
	int SampleCount = 10;
	int::TryParse(cmbSampleAdet->Text, SampleCount);
	instrument->totalSampleCount = SampleCount;
	instrumentUUT->totalSampleCount = SampleCount;
}
System::Void MainForm::txtFreq_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	ReadFormParam();
}
System::Void MainForm::cmbMeasType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	switch (cmbMeasType->SelectedIndex)
	{
	case 0: 
		txtFreq->Enabled = true;
		lblFreqRange->Text = "20 - 300 Hz"; 
		txtFreq->Text = G::mySet->LastFreq.ToString();
		cmbPeakType->Items[0] = "Vrms";
		cmbPeakType->Enabled = true;
		//cmbPeakType->Items[2] = "Vrms & Vpeak";
		break;
	case 1:
		txtFreq->Enabled = false;
		lblFreqRange->Text = "-";
		txtFreq->Text = "0";
		cmbPeakType->Items[0] = "Vdc";
		cmbPeakType->Enabled = true;
		//cmbPeakType->Items[2] = "Vdc & Vpeak";
		break;
	case 2: 
		txtFreq->Enabled = true;
		lblFreqRange->Text = "0.01 - 200 Hz";
		txtFreq->Text = G::mySet->LastFreqVLF.ToString();
		cmbPeakType->Items[0] = "Vrms & Vpeak";
		cmbPeakType->Enabled = false;
		cmbPeakType->SelectedIndex = 0;
		//cmbPeakType->Items[2] = "Vrms & Vpeak";
		break;
	default:
		break;
	}
	ReadFormParam();
}

System::Void MainForm::cmbAddress_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	ReadFormParam();
}
System::Void MainForm::cmbAddress_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	ReadFormParam();
}

System::Void MainForm::cmbDivider_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	ReadFormParam();

	//DMM_Divider = (Envanter^)(cmbDivider_DMM->SelectedItem);
	//txtsfVrms_DMM->Text = DMM_Divider->sfVrms.ToString("F3", G::trcul());
	//txtsfVpeak_DMM->Text = DMM_Divider->sfVpeak.ToString("F3", G::trcul());
}
System::Void MainForm::cmbDivider_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!isInit) return;
	ReadFormParam();

	//UUT_Divider = (Envanter^)(cmbDivider_UUT->SelectedItem);
	//txtsfVrms_UUT->Text = UUT_Divider->sfVrms.ToString("F3", G::trcul());
	//txtsfVpeak_UUT->Text = UUT_Divider->sfVpeak.ToString("F3", G::trcul());
}

void MainForm::ReadFormParam() {

	DMM = (Envanter^)(cmbAddress_DMM->SelectedItem);
	DMM_Divider = (Envanter^)(cmbDivider_DMM->SelectedItem);
	switch (DMM->device)
	{
	case DMMDevice::Agilent3458A: instrument = gcnew AgilentDMM::Agilent3458(); break;
	case DMMDevice::Agilent34410: instrument = gcnew AgilentDMM::Agilent3441x(AgilentDMM::DMMModel::Model_34410); break;
	case DMMDevice::Agilent34470: instrument = gcnew AgilentDMM::Agilent34470(); break;
	case DMMDevice::Agilent34411: instrument = gcnew AgilentDMM::Agilent3441x(AgilentDMM::DMMModel::Model_34411); break;
	case DMMDevice::NIPXI4081: instrument = gcnew NIDMM::NIPXI4081(); break;
	case DMMDevice::Generic232: instrument = gcnew MeasLab::IDMM(); break;
	}


	UUT = (Envanter^)(cmbAddress_UUT->SelectedItem);
	UUT_Divider = (Envanter^)(cmbDivider_UUT->SelectedItem);

	lblMaxVUnit_DMM->Text = DMM_Divider->sfVrms < 5 ? "V" : "kV";
	lblMeasUnit_DMM->Text = DMM_Divider->sfVrms < 5 ? "V" : "kV";

	lblMaxVUnit_UUT->Text = UUT_Divider->sfVrms < 5 ? "V" : "kV";
	lblMeasUnit_UUT->Text = UUT_Divider->sfVrms < 5 ? "V" : "kV";

	switch (UUT->device)
	{
	case DMMDevice::Agilent3458A: instrumentUUT = gcnew AgilentDMM::Agilent3458(); break;
	case DMMDevice::Agilent34410: instrumentUUT = gcnew AgilentDMM::Agilent3441x(AgilentDMM::DMMModel::Model_34410); break;
	case DMMDevice::Agilent34411: instrumentUUT = gcnew AgilentDMM::Agilent3441x(AgilentDMM::DMMModel::Model_34411); break;
	case DMMDevice::Agilent34470: instrumentUUT = gcnew AgilentDMM::Agilent34470(); break;
	case DMMDevice::NIPXI4081: instrumentUUT = gcnew NIDMM::NIPXI4081(); break;
	case DMMDevice::Generic232: instrumentUUT = gcnew MeasLab::IDMM(DMMType::DMM); break;
	case DMMDevice::HandType: instrumentUUT = gcnew MeasLab::IDMM(DMMType::Hand); break;
	case DMMDevice::NoneDevice: instrumentUUT = gcnew MeasLab::IDMM(DMMType::None);break;
	}

	pnlUUT_Param->Visible = !(UUT->device == DMMDevice::NoneDevice);

	double TestFreq = 0;
	double::TryParse(txtFreq->Text->Replace(",", "."), System::Globalization::NumberStyles::Any, G::invcul(), TestFreq);
	instrument->SampleFreq = TestFreq;
	instrumentUUT->SampleFreq = TestFreq;


	txtTerminal_DMM->Text = "-";
	txtTerminal_UUT->Text = "-";
	txtZInput_DMM->Text = "-";
	txtZInput_UUT->Text = "-";
	txtsfVrms_DMM->Text = DMM_Divider->sfVrms.ToString("F3", G::activecul());
	txtsfVrms_UUT->Text = UUT_Divider->sfVrms.ToString("F3", G::activecul());
	txtsfVpeak_DMM->Text = DMM_Divider->sfVpeak.ToString("F3", G::activecul());
	txtsfVpeak_UUT->Text = UUT_Divider->sfVpeak.ToString("F3", G::activecul());
	txtsfVdc_DMM->Text = DMM_Divider->sfVdc.ToString("F3", G::activecul());
	txtsfVdc_UUT->Text = UUT_Divider->sfVdc.ToString("F3", G::activecul());

	instrument->peakType = (PeakType)cmbPeakType->SelectedIndex;
	instrumentUUT->peakType = (PeakType)cmbPeakType->SelectedIndex;

	instrument->Name = "DMM";
	instrumentUUT->Name = "UUT";

	switch (cmbMeasType->SelectedIndex)
	{
	case 0:
		instrument->meastype = MeasType::AC;
		instrumentUUT->meastype = MeasType::AC;
		break;
	case 1:
		instrument->meastype = MeasType::DC;
		instrumentUUT->meastype = MeasType::DC;
		break;
	case 2:
		instrument->meastype = MeasType::AC_DCSampling;
		instrumentUUT->meastype = MeasType::AC_DCSampling;
		instrument->peakType = PeakType::Peak;
		instrumentUUT->peakType = PeakType::Peak;
		break;
	default:
		break;
	}
	CheckDemoMode();
	instrument->range = (VoltageRange)cmbVoltageRange_DMM->SelectedIndex;
	instrumentUUT->range = (VoltageRange)cmbVoltageRange_UUT->SelectedIndex;

	AutoCalcVoltageRange_UUT();
	AutoCalcVoltageRange_DMM();
	//And Last fill Zinput;
	
	UpdatePLCTiming();
	
}

void MainForm::AutoCalcVoltageRange_DMM() {
	if (!isInit) return;
	if (DMM_Divider == nullptr) return;
	if (DMM == nullptr) return;

	switch (instrument->meastype)
	{
		case MeasType::AC_DCSampling:
			chkRangeAuto_DMM->Enabled = false;
			chkRangeAuto_DMM->Checked = false;

			chkRange_DMM->Enabled = true;
			break;
		case MeasType::AC:
			chkRangeAuto_DMM->Enabled = true;
			//chkRangeAuto_DMM->Checked = true;

			chkRange_DMM->Enabled = true;
			break;
		default:
			chkRangeAuto_DMM->Enabled = true;
			chkRange_DMM->Enabled = true;
			chkRange_DMM->Enabled = !chkRangeAuto_DMM->Checked;
			cmbVoltageRange_DMM->Enabled = !chkRangeAuto_DMM->Checked;
			chkRangeAuto_DMM->Enabled = !chkRange_DMM->Checked;
			break;
	}

	txtZInput_DMM->Text = instrument->ZinSTR;

	if (chkRangeAuto_DMM->Checked && chkRangeAuto_DMM->Enabled) {
		instrument->range = VoltageRange::AUTO;
		return;
	}

	double divider = DMM_Divider->sfVrms < 5 ? 1.0 : 1000.0;
	if (!chkRange_DMM->Checked)
	{
		double MaxReading = DMM_Divider->sfVrms * Math::Pow(10, ((int)instrument->range) - 1);
		txtAppliedVoltage_DMM->Text = (MaxReading / divider).ToString("F2", G::activecul()->NumberFormat);

		txtAppliedVoltage_DMM->ReadOnly = true;
		cmbVoltageRange_DMM->Enabled = true;
		return;
	}
	cmbVoltageRange_DMM->Enabled = false;
	txtAppliedVoltage_DMM->ReadOnly = false;

	double AppliedVoltage = 0;
	double::TryParse(txtAppliedVoltage_DMM->Text->Replace(",", "."), System::Globalization::NumberStyles::Any, G::invcul()->NumberFormat, AppliedVoltage);

	double ReadingVoltage = AppliedVoltage * divider / DMM_Divider->sfVrms;

	if (ReadingVoltage <= 0.1) {
		instrument->range = MeasLab::VoltageRange::VOLT_01;
		cmbVoltageRange_DMM->SelectedIndex = 0;
	}
	else if (ReadingVoltage <= 1) {
		instrument->range = MeasLab::VoltageRange::VOLT_1;
		cmbVoltageRange_DMM->SelectedIndex = 1;
	}
	else if (ReadingVoltage <= 10) {
		instrument->range = MeasLab::VoltageRange::VOLT_10;
		cmbVoltageRange_DMM->SelectedIndex = 2;
	}
	else if (ReadingVoltage <= 100) {
		instrument->range = MeasLab::VoltageRange::VOLT_100;
		cmbVoltageRange_DMM->SelectedIndex = 3;
	}
	else {
		instrument->range = MeasLab::VoltageRange::VOLT_1000;
		cmbVoltageRange_DMM->SelectedIndex = 4;
	}

}
void MainForm::AutoCalcVoltageRange_UUT() {

	if (!isInit) return;
	if (UUT_Divider == nullptr) return;
	if (UUT == nullptr) return;

	switch (instrument->meastype)
	{
	case MeasType::AC_DCSampling:
		chkRangeAuto_UUT->Enabled = false;
		chkRangeAuto_UUT->Checked = false;

		chkRange_UUT->Enabled = true;
		break;
	case MeasType::AC:
		chkRangeAuto_UUT->Enabled = true;
		//chkRangeAuto_UUT->Checked = false;

		chkRange_UUT->Enabled = true;
		break;
	default:
		chkRangeAuto_UUT->Enabled = true;
		chkRange_UUT->Enabled = true;
		chkRange_UUT->Enabled = !chkRangeAuto_UUT->Checked;
		cmbVoltageRange_UUT->Enabled = !chkRangeAuto_UUT->Checked;
		chkRangeAuto_UUT->Enabled = !chkRange_UUT->Checked;
		break;
	}

	txtZInput_UUT->Text = instrumentUUT->ZinSTR;

	if (chkRangeAuto_UUT->Checked && chkRangeAuto_UUT->Enabled) {
		instrumentUUT->range = VoltageRange::AUTO;
		return;
	};

	double divider = UUT_Divider->sfVrms < 5 ? 1.0 : 1000.0;
	if (!chkRange_UUT->Checked)
	{
		double MaxReading = UUT_Divider->sfVrms * Math::Pow(10, ((int)instrumentUUT->range) - 1);
		txtAppliedVoltage_UUT->Text = (MaxReading / divider).ToString("F2", G::activecul()->NumberFormat);
		txtAppliedVoltage_UUT->ReadOnly = true;
		cmbVoltageRange_UUT->Enabled = true;
		return;
	}
	cmbVoltageRange_UUT->Enabled = false;
	txtAppliedVoltage_UUT->ReadOnly = false;

	double AppliedVoltage = 0;
	double::TryParse(txtAppliedVoltage_UUT->Text->Replace(",","."), System::Globalization::NumberStyles::Any, G::invcul()->NumberFormat, AppliedVoltage);

	double ReadingVoltage = AppliedVoltage * divider / UUT_Divider->sfVrms;

	if (ReadingVoltage < 0.1) {
		instrumentUUT->range = MeasLab::VoltageRange::VOLT_01;
		cmbVoltageRange_UUT->SelectedIndex = 0;
	}
	else if (ReadingVoltage < 1) {
		instrumentUUT->range = MeasLab::VoltageRange::VOLT_1;
		cmbVoltageRange_UUT->SelectedIndex = 1;
	}
	else if (ReadingVoltage < 10) {
		instrumentUUT->range = MeasLab::VoltageRange::VOLT_10;
		cmbVoltageRange_UUT->SelectedIndex = 2;
	}
	else if (ReadingVoltage < 100) {
		instrumentUUT->range = MeasLab::VoltageRange::VOLT_100;
		cmbVoltageRange_UUT->SelectedIndex = 3;
	}
	else {
		instrumentUUT->range = MeasLab::VoltageRange::VOLT_1000;
		cmbVoltageRange_UUT->SelectedIndex = 4;
	}
	
}

void MainForm::UpdatePLCTiming()
{

	switch (instrument->meastype)
	{
	case MeasType::AC:
	case MeasType::DC:
		lblTestInfo_DMM->Text = "";
		lblTestInfo_UUT->Text = "";
		break;
	case MeasType::AC_DCSampling:
		instrument->CalculateParam();

		lblTestInfo_DMM->Text = String::Format(L"Freq: {0:F2} Hz \r\n", instrument->SampleFreq);
		lblTestInfo_DMM->Text += String::Format(L"DMM => {0} örneklem (APER:{1}) ", instrument->WaveFormSampleCount, instrument->ApertureTime);
		if (instrumentUUT->type == DMMType::DMM)
		{
			instrumentUUT->CalculateParam();
			lblTestInfo_UUT->Text = String::Format(L"UUT => {0} örneklem (APER:{1})  ", instrumentUUT->WaveFormSampleCount, instrumentUUT->ApertureTime);
		}
		else
		{
			lblTestInfo_UUT->Text = "";
		}
		break;
	}
}

#pragma endregion

#pragma region "Logging"

System::Void MainForm::linkClearLog_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
	richTextBox1->Text = "";
}
void MainForm::UpdateLog(String^ msg) {

	if (richTextBox1->Text->Length > 100000)
	{
		richTextBox1->Text = "";
	}
	else
	{
		if (msg->Length > 1000)
		{
			richTextBox1->Text = msg->Substring(0,500) + richTextBox1->Text;
		}
		else
		{
			richTextBox1->Text = msg + richTextBox1->Text;
		}
	}
}

void MainForm::Instrument_LogChanged(System::Object^ sender, WaveFormMeasument::LogChangeEventArgs^ e)
{
	Invoke(gcnew Action<String^>(this, &MainForm::UpdateLog), e->Text);
}
System::Void MainForm::btnReadSTB_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
	 
	if (instrument == nullptr) return;
	if (!instrument->isConnected) return;

	richTextBox1->Text = instrument->ReturnSTB() + richTextBox1->Text;
	richTextBox1->Text = instrumentUUT->ReturnSTB() + richTextBox1->Text;
}
#pragma endregion

#pragma	region "Live Mode"
void MainForm::TimerLoop(System::Object^ state)
{
	LiveTickCount++;
	if (isbusy) return;
	isbusy = true;
	LiveReadCount++;
	if (instrument->VoltRangeChanged)
	{
		instrument->ChangeVoltageRange(instrument->range);
		instrument->VoltRangeChanged = false;
	}
	if (instrumentUUT->VoltRangeChanged)
	{
		instrumentUUT->ChangeVoltageRange(instrumentUUT->range);
		instrumentUUT->VoltRangeChanged = false;
	}
	ReadLiveData();
	LiveDataLoop();
	if (instrumentUUT->type == DMMType::DMM)
	{
		ReadLiveData_UUT();
		LiveDataLoop_UUT();
	}
	isbusy = false;
}

void MainForm::FirstLiveDataCollect()
{
	//Clear labels
	txtLiveRMS->Text = "-";
	txtLivePeakRoot2->Text = "-";

	txtLiveRMS_UUT->Text = "-";
	txtLivePeakRoot2_UUT->Text = "-";

	liveData = gcnew WaveFormMeasument::WaveFormMeasurement();
	liveDataUUT = gcnew WaveFormMeasument::WaveFormMeasurement();

	liveData->Etiket = txtBarcode->Text;
	liveData->Ratio = DMM_Divider->sfVrms;
	liveData->Ratio_Peak = DMM_Divider->sfVpeak;
	liveData->Ratio_DC = DMM_Divider->sfVdc;
	liveData->WaveCount = 1;
	liveData->Kademe = (int)instrument->range;
	liveData->sampleForEachWave = instrument->WaveFormSampleCount;
	liveData->measType = (int)instrument->meastype;
	//liveData->peakType = instrument->peakType;



	instrument->PrepareLiveData();
	//Wait for complete data;

	if (instrumentUUT->type == DMMType::DMM)
	{
		liveDataUUT->Etiket = txtBarcode->Text;
		liveDataUUT->Ratio = UUT_Divider->sfVrms;
		liveDataUUT->Ratio_Peak = UUT_Divider->sfVpeak;
		liveDataUUT->Ratio_DC = UUT_Divider->sfVdc;
		liveDataUUT->WaveCount = 1;
		liveDataUUT->Kademe = (int)instrumentUUT->range;
		liveDataUUT->sampleForEachWave = instrumentUUT->WaveFormSampleCount;
		liveDataUUT->measType = (int)instrumentUUT->meastype;
		instrumentUUT->PrepareLiveData();
	}
	else if (instrumentUUT->type == DMMType::Hand)
	{
		liveDataUUT->Etiket = txtBarcode->Text;
		liveDataUUT->Ratio = UUT_Divider->sfVrms;
		liveDataUUT->Ratio_Peak = UUT_Divider->sfVpeak;
		liveDataUUT->Ratio_DC = UUT_Divider->sfVdc;
		liveDataUUT->WaveCount = 1;
		liveDataUUT->Kademe = (int)instrumentUUT->range;
		liveDataUUT->sampleForEachWave = instrumentUUT->WaveFormSampleCount;
		liveDataUUT->measType = (int)instrumentUUT->meastype;
		//liveDataUUT->peakType = instrumentUUT->peakType;
		//User must input reading values;
	}
	else
	{
		//No device no action
	}

	//System.Threading.Thread.Sleep(liveData.toltalMsForTest);
	//Set timer to handle live loop;
	UpdateLog("Start Listening" + Environment::NewLine);

	//TimerCallback^ timerDelegate = gcnew TimerCallback(this, &MainForm::TimerLoop);
	//timer = gcnew System::Threading::Timer(timerDelegate);
	//timer->Change(1000, 1000);
	//nofity = gcnew AutoResetEvent(false);
	isPaused = false;
	ThreadStart^ ts1 = gcnew ThreadStart(this, &MainForm::ThreadRun1);
	ThreadStart^ ts2 = gcnew ThreadStart(this, &MainForm::ThreadRun2);
	ThreadStart^ ts_read = gcnew ThreadStart(this, &MainForm::ThreadRead);
	thd1 = gcnew Thread(ts1);
	thd2 = gcnew Thread(ts2);
	thRead = gcnew Thread(ts_read);
	thd1->IsBackground = true;
	thd2->IsBackground = true;
	thRead->IsBackground = true;

	instrStatus = SampleStatus::Wait;
	instrStatus_UUT = SampleStatus::Wait;
	StopReading = false;
	thd1->Start();
	thd2->Start();
	thRead->Start();
}

void MainForm::ThreadRun1() {
	while (instrument->isConnected && !StopReading)
	{
		if (!isPaused)
		{
			switch (instrStatus)
			{
			case MeasLab::SampleStatus::Wait:
				instrStatus = SampleStatus::Prepare;
				instrStatus_UUT = SampleStatus::Prepare;
				break;
			case MeasLab::SampleStatus::Prepare:
				instrument->CheckError();
				if (instrument->hasError)
				{
					instrStatus = SampleStatus::HasError;
				}
				else
				{
					if ((instrStatus_UUT == SampleStatus::Prepare && !instrumentUUT->hasError) || instrumentUUT->type != DMMType::DMM)
					{
						instrument->PrepareNextLiveData();
						instrumentUUT->PrepareNextLiveData();
						instrStatus = SampleStatus::WaitData;
						instrStatus_UUT = SampleStatus::WaitData;
					}
				//	if (instrument->meastype == MeasType::AC_DCSampling)
				//	{
				//		if (instrStatus_UUT == SampleStatus::Prepare)
				//		{
				//			instrument->PrepareNextLiveData();
				//			instrumentUUT->PrepareNextLiveData();
				//			instrStatus = SampleStatus::WaitData;
				//			instrStatus_UUT = SampleStatus::WaitData;
				//		}
				//	}
				//	else
				//	{
				//		instrument->PrepareNextLiveData();
				//		instrStatus = SampleStatus::WaitData;
				//	}
				}
				break;
			case MeasLab::SampleStatus::WaitData:
				if (instrument->CheckDataReady())
				{
					instrStatus = SampleStatus::ReadData;
				}
				else
				{
					if (instrument->hasError)
					{
						instrStatus = SampleStatus::HasError;
					}
				}
				break;
			case MeasLab::SampleStatus::ReadData:
				ReadLiveData();
				instrStatus = SampleStatus::Prepare;
				break;
			case MeasLab::SampleStatus::HasError:
				instrument->ReadError();
				if (instrument->ErrorStr != "")
				{
					MessageBox::Show(instrument->ErrorStr);
				}
				instrStatus = SampleStatus::Prepare;
				break;
			default:
				break;
			}

		}
	}
}

void MainForm::ThreadRun2() {
	while (instrumentUUT->isConnected && instrumentUUT->type == DMMType::DMM && !StopReading)
	{
		switch (instrStatus_UUT)
		{
		case MeasLab::SampleStatus::Wait:
			instrStatus_UUT = SampleStatus::Prepare;
			break;
		case MeasLab::SampleStatus::Prepare:
			instrumentUUT->CheckError();
			if (instrumentUUT->hasError)
			{
				instrStatus_UUT = SampleStatus::HasError;
			}
			else
			{
				//if (instrument->meastype == MeasType::AC_DCSampling)
				//{
				//	//For sync this action triggered by thread 1;

				//}
				//else
				//{
				//	instrumentUUT->PrepareNextLiveData();
				//	instrStatus_UUT = SampleStatus::WaitData;
				//}
			}
			break;
		case MeasLab::SampleStatus::WaitData:
			if (instrumentUUT->CheckDataReady())
			{
				instrStatus_UUT = SampleStatus::ReadData;
			}
			else
			{
				if (instrumentUUT->hasError)
				{
					instrStatus_UUT = SampleStatus::HasError;
				}
			}
			break;
		case MeasLab::SampleStatus::ReadData:
			ReadLiveData_UUT();
			instrStatus_UUT = SampleStatus::Prepare;
			break;
		case MeasLab::SampleStatus::HasError:
			instrumentUUT->ReadError();
			if (instrumentUUT->ErrorStr != "")
			{
				MessageBox::Show(instrumentUUT->ErrorStr);
			}
			instrStatus_UUT = SampleStatus::Prepare;
			break;
		default:
			break;
		}
	}

}

void MainForm::ThreadRead() {
	//Control both thread, wait until they stop;

	Cursor->Current = Cursors::WaitCursor;
	bool th1Stop = (thd1->ThreadState == ThreadState::Stopped);
	bool th2Stop = (thd2->ThreadState == ThreadState::Stopped);

	while (!(th1Stop && th2Stop))
	{
		Thread::Sleep(10);
		//if (instrument->VoltRangeChanged)
		//{
		//	instrument->ChangeVoltageRange(instrument->range);
		//	instrument->VoltRangeChanged = false;
		//}
		//if (instrumentUUT->VoltRangeChanged)
		//{
		//	instrumentUUT->ChangeVoltageRange(instrumentUUT->range);
		//	instrumentUUT->VoltRangeChanged = false;
		//}
		if (instrument->type == DMMType::DMM) {
			Invoke(gcnew Action(this, &MainForm::LiveProgress));
		}
		if (instrumentUUT->type == DMMType::DMM)
		{
			Invoke(gcnew Action(this, &MainForm::LiveProgress_UUT));
		}

		th1Stop = (thd1->ThreadState == ThreadState::Stopped);
		th2Stop = (thd2->ThreadState == ThreadState::Stopped);
	}
	//After two thread stop; update UI;
	Invoke(gcnew Action(this, &MainForm::DisConnect));
}

void MainForm::ReadLiveData_UUT()
{
	String^ rawSTR = "";
	bool isOK = instrumentUUT->ReadLiveData(rawSTR);		//SendCommand(":TRAC:DATA?", rawSTR);
	if (!isOK)
	{
		MessageBox::Show("Hata Oluştu");
		return;
	}

	liveDataUUT->ReadResults(rawSTR);

	selectedSampleUUT = liveDataUUT->waves[0];

	//if (instrumentUUT->meastype == MeasType::AC_DCSampling)
	//	selectedSampleUUT->CalculateRMS();
	if (instrumentUUT->meastype == MeasType::AC_DCSampling)
	{
		switch (UUT->device)
		{
		case DMMDevice::Agilent3458A:
			selectedSampleUUT->CalculateRMS();
			break;
		default:
			selectedSampleUUT->ResetDecideDiff();
			selectedSampleUUT->CalculateRMSMulti(liveDataUUT->sampleForEachWave);
			break;
		}
	}



	Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));
	Invoke(gcnew Action(this, &MainForm::DrawMyChart_UUT));
}

void MainForm::ReadLiveData()
{
	String^ rawSTR = "";
	//instrument->AddLogText("Thread: ReadLive");
	bool hasData = instrument->ReadLiveData(rawSTR);		//SendCommand(":TRAC:DATA?", rawSTR);
	if (!hasData)
	{
		//MessageBox::Show(L"Read Live Data: !!!Hata Oluştu!!!");
		return;
	}

	//Datayı işle;
	//+1.23456789E-03VDC, +11.664SECS, +236RDNG, 000, 0000LIMITS
	//liveData->waves->Clear();
	liveData->ReadResults(rawSTR);

	selectedSample = liveData->waves[0];
	if (instrument->meastype == MeasType::AC_DCSampling)
	{
		switch (DMM->device)
		{
		case DMMDevice::Agilent3458A:
			selectedSample->CalculateRMS();
			break;
		default: 
			selectedSample->ResetDecideDiff();
			selectedSample->CalculateRMSMulti(liveData->sampleForEachWave);
			break;
		}
	}

	Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	Invoke(gcnew Action(this, &MainForm::DrawMyChart));

	//DrawMyChart();
	//UpdateLiveLabels();
}

void MainForm::LiveDataLoop_UUT()
{
	//liveData->Ratio = G::mySet->Ratio;
	instrumentUUT->PrepareNextLiveData();
}
void MainForm::LiveDataLoop()
{
	//liveData->Ratio = G::mySet->Ratio;
	instrument->PrepareNextLiveData();
}

void MainForm::UpdateLiveLabels_UUT()
{
	switch (instrument->meastype) 
	{
	case MeasType::DC:
		txtLiveRMS_UUT->Text = "-";
		txtLivePeakRoot2_UUT->Text = "-";
		if (selectedSampleUUT->Vrms > G::MAXLIMIT)
		{
			txtLiveDC_UUT->Text= "Over Range";
		}
		else
		{
			txtLiveDC_UUT->Text = Extensions::ToEngineeringNotation(selectedSampleUUT->Vrms, "F7", "V");	//  selectedSampleUUT->Vrms.ToString("F7", G::activecul());
		}
		break;
	default:
		if (selectedSampleUUT->Vrms > G::MAXLIMIT)
		{
			txtLiveRMS_UUT->Text = "Over Range";
			txtLivePeakRoot2_UUT->Text = "Over Range";
		}
		else
		{
			txtLiveRMS_UUT->Text = Extensions::ToEngineeringNotation(selectedSampleUUT->Vrms, "F7", "V"); ;			// selectedSampleUUT->Vrms.ToString("F7", G::activecul());	// +"kV";
			txtLivePeakRoot2_UUT->Text = Extensions::ToEngineeringNotation(selectedSampleUUT->VpeakRoot2, "F7", "V");		// selectedSampleUUT->VpeakRoot2.ToString("F7", G::activecul());	// +"kV";
		}
		break;
	}


	if (TestActive && ResultList->Count > ResultList_UUT->Count)
	{
		double passedSecond = DateTime::Now.Subtract(StartTime).TotalSeconds;
		int minute = (int)Math::Floor(passedSecond / 60);
		int second = (int)(passedSecond - (int)(passedSecond / 60) * 60.0);
		lblPassTime->Text = String::Format("{0:D2}:{1:D2}", minute, second);

		if (LiveReadCount % CollectModulus == 0 && measurementUUT->waves->Count < measurementUUT->WaveCount)
		{
			//selectedSampleUUT->Etiket = txtBarcode->Text;
			selectedSampleUUT->SampleNo = measurementUUT->waves->Count + 1;
			measurementUUT->waves->Add(selectedSampleUUT);
			ResultList_UUT->Add(selectedSampleUUT);
			//GridList->Add(gcnew GridObject(selectedSample, false));
			RefreshGrid(true);
		}
		lblRemainData->Text = String::Format("{0} / {1}", measurementUUT->waves->Count , measurementUUT->WaveCount);
		if (measurement->waves->Count == measurement->WaveCount)
		{
			TestActive = false;
			FinishTest();
		}
	}

}
void MainForm::UpdateLiveLabels()
{
	//this.UIThread(() = >
	// 	  
	//{

	switch (instrument->meastype)
	{
	case MeasType::DC:
		txtLiveRMS->Text = "-";
		txtLivePeakRoot2->Text = "-";
		if (selectedSample->Vdc > G::MAXLIMIT)
		{
			txtLiveDC->Text = "Over Range";
		}
		else
		{
			txtLiveDC->Text = Extensions::ToEngineeringNotation(selectedSample->Vdc, "F7", "V");			// (selectedSample->Vrms).ToString("F7", G::activecul()); // +"kV";
		}
		break;
	default:
		if (selectedSample->Vrms > G::MAXLIMIT)
		{
			txtLiveRMS->Text = "Over Range";
			txtLivePeakRoot2->Text = "Over Range";
		}
		else
		{
			txtLiveRMS->Text = Extensions::ToEngineeringNotation(selectedSample->Vrms, "F7", "V");			// (selectedSample->Vrms).ToString("F7", G::activecul()); // +"kV";
			txtLivePeakRoot2->Text = Extensions::ToEngineeringNotation(selectedSample->VpeakRoot2, "F7", "V");		// (selectedSample->VpeakRoot2).ToString("F7", G::activecul());	// +"kV";
		}
		break;
	}

	try
	{

	lblFooterCounter->Text = LiveTickCount.ToString() + " / " + LiveReadCount.ToString();

	if (TestActive)
	{
		lblRemainData->Text = String::Format("{0} / {1}", measurement->waves->Count, measurement->WaveCount);
		double passedSecond = DateTime::Now.Subtract(StartTime).TotalSeconds;
		int minute = (int)Math::Floor(passedSecond / 60);
		int second = (int)(passedSecond - (int)(passedSecond / 60) * 60.0);
		lblPassTime->Text = String::Format("{0:D2}:{1:D2}", minute, second);

		if (LiveReadCount % CollectModulus == 0 && measurement->waves->Count < measurement->WaveCount)
		{
			System::Console::Beep(G::mySet->BeepFreq, G::mySet->BeepDuration);		//523 hertz(C5) for 500 milliseconds
			//selectedSample->Etiket = txtBarcode->Text;
			selectedSample->SampleNo = measurement->waves->Count + 1;
			measurement->waves->Add(selectedSample);
			ResultList->Add(selectedSample);
			if (instrumentUUT->type == DMMType::Hand)
			{
				ShowManuelEnter();
				if (measurement->waves->Count == measurement->WaveCount)
				{
					TestActive = false;
					FinishTest();
				}
			}
			//GridList->Add(gcnew GridObject(selectedSample, false));
			RefreshGrid(false);

		}


	}
	}
	catch (Exception^ ex)
	{

	}

	//});
}
void MainForm::ShowManuelEnter() {
	//Stop polling first;
	isPaused = true;
	//Open UI Entering;
	EnteringUI^ mForm = gcnew EnteringUI();
	mForm->MeasType = (int)instrument->meastype;
	mForm->PeakTpye = (int)instrument->peakType;
	mForm->ShowDialog(this);

	bool ACorDC = (instrument->meastype == MeasType::DC ? false : true);
	liveDataUUT->ReadResults_Enter(mForm->Vrms.ToString() + Environment::NewLine + mForm->Vpeak.ToString(), ACorDC);
	selectedSampleUUT = liveDataUUT->waves[0];
	UpdateLiveLabels_UUT();
	if (G::mySet->AutoNext)
	{
		isPaused = false;
	}
	else
	{
		btnReEnter->Visible = true;
		btnContinue->Visible = true;
	}
}
void MainForm::btnReEnter_Click(System::Object^ sender, System::EventArgs^ e) {

	isPaused = true;
	btnReEnter->Visible = true;

	measurementUUT->waves->RemoveAt(measurementUUT->waves->Count-1);
	ResultList_UUT->RemoveAt(ResultList_UUT->Count - 1);

	//Open UI Entering;
	EnteringUI^ mForm = gcnew EnteringUI();
	mForm->MeasType = (int)instrument->meastype;
	mForm->ShowDialog(this);

	liveDataUUT->ReadResults(mForm->Vrms.ToString());
	selectedSampleUUT = liveDataUUT->waves[0];
	if (!TestActive) TestActive = true;
	UpdateLiveLabels_UUT();
}


void MainForm::LiveProgress() {
	if (instrument->ReadByteCount == 0)
	{
		toolStripProgressBar1->Value = 0;
		return;
	}
	toolStripProgressBar1->Visible = true;
	if (instrStatus == MeasLab::SampleStatus::ReadData)
	{
		toolStripProgressBar1->Value = ((float)instrument->answerbyte->Count / (float)instrument->ReadByteCount)*100;
	}
	else
	{
		toolStripProgressBar1->Value = 0;
	}
}
void MainForm::LiveProgress_UUT() {
	if (instrumentUUT->ReadByteCount == 0)
	{
		toolStripProgressBar2->Value = 0;
		return;
	}
	toolStripProgressBar2->Visible = true;
	if (instrStatus_UUT == MeasLab::SampleStatus::ReadData)
	{
		toolStripProgressBar2->Value =((float)instrumentUUT->answerbyte->Count / (float)instrumentUUT->ReadByteCount)*100;
	}
	else
	{
		toolStripProgressBar2->Value = 0;
	}
}

#pragma	endregion

#pragma	region "I/O GPIB/RS232"

void MainForm::Connect()
{
	ReadFormParam();

	toolStripProgressBar1->Visible = instrument->type == DMMType::DMM;
	toolStripProgressBar2->Visible = instrumentUUT->type == DMMType::DMM;


	//Save Last Data;
	G::mySet->LastDMMID = DMM->ID;
	G::mySet->LastDMMDividerID = DMM_Divider->ID;
	G::mySet->LastDMMRange = (int)instrument->range;

	G::mySet->LastUUTID = UUT->ID;
	G::mySet->LastUUTDividerID = UUT_Divider->ID;
	G::mySet->LastUUTRange = (int)instrumentUUT->range;

	switch (instrument->meastype)
	{
	case MeasType::AC:
		G::mySet->LastFreq = instrument->SampleFreq;
	case MeasType::AC_DCSampling:
		G::mySet->LastFreqVLF = instrument->SampleFreq;
	default:
		break;
	}
	G::mySet->LastMeasTipi = cmbMeasType->SelectedIndex;
	G::mySet->LastTestTipi = cmbPeakType->SelectedIndex;
	 
	G::SaveSettings();


	//Clear Screen Values;
	txtLiveRMS->Text = "-";
	txtLivePeakRoot2->Text = "-";
	txtLiveDC->Text = "-";
	txtLiveRMS_UUT->Text = "-";
	txtLivePeakRoot2_UUT->Text = "-";
	txtLiveDC_UUT->Text = "-";

	selectedSample = nullptr;
	DrawMyChart();


	instrument->connType = DMM->connType;
	switch (DMM->connType)
	{
	case EnvanterConnection::GBIP:
		instrument->Connect(DMM->Address, 0, true);
		break;
	case EnvanterConnection::RS232:
		instrument->Connect(DMM->Address, G::mySet->BaudRate, false);
		break;
	case EnvanterConnection::PXI:
		((NIDMM::NIPXI4081^)instrument)->Connect_PXI(DMM->Address);
		break;
	case EnvanterConnection::None:
		//El ile veri alınacak;
		break;
	}


	switch (UUT->connType)
	{
	case EnvanterConnection::GBIP:
		instrumentUUT->Connect(UUT->Address, 0, true);
		break;
	case EnvanterConnection::RS232:
		instrumentUUT->Connect(UUT->Address, G::mySet->BaudRate, false);
		break;
	case EnvanterConnection::PXI:
		((NIDMM::NIPXI4081^)instrumentUUT)->Connect_PXI(DMM->Address);
		break;
	case EnvanterConnection::None:
		//El ile veri alınacak;
		break;
	}

	//First look any data avaliable;
	bool readOK_DMM = instrument->ReadError();
	bool readOK_UUT = instrumentUUT->ReadError();

	if (!readOK_DMM || !readOK_UUT) {

		if (!readOK_DMM) {
			MessageBox::Show(L"Ref. DMM cihazı ile iletişim sorunu oluştu!!!\n");
		}
		if (!readOK_UUT) {
			MessageBox::Show(L"UUT cihazı ile iletişim sorunu oluştu!!!\n");
		}

		instrument->DisConnect();
		instrumentUUT->DisConnect();
		return;

	}

	System::Threading::Thread::Sleep(1);
	String^ deviceSTR = "";
	bool readOK = instrument->SendIDN(deviceSTR);		// instrument->SendCommand("*IDN?", deviceSTR);
	if (!readOK && 12<2)
	{
		MessageBox::Show(L"Ref. DMM bağlantısında sorun oluştu!!!");
		instrument->DisConnect();
		return;
	}
	String^ deviceSTR_UUT = "";
	if (UUT->connType != EnvanterConnection::None)
	{
		
		readOK = instrumentUUT->SendIDN(deviceSTR_UUT);
		if (!readOK)
		{
			MessageBox::Show(L"UUT bağlantısında sorun oluştu!!!");
			instrument->DisConnect();
			instrumentUUT->DisConnect();
			return;
		}
	}

	instrument->LogChanged += gcnew WaveFormMeasument::LogChangeEventHandler(this, &MainForm::Instrument_LogChanged);
	instrumentUUT->LogChanged += gcnew WaveFormMeasument::LogChangeEventHandler(this, &MainForm::Instrument_LogChanged);

	lblFooter->Text = deviceSTR->Trim();
	if (UUT->connType != EnvanterConnection::None) lblFooter->Text += "/ " + deviceSTR_UUT->Trim();




	//Collect Front-Rear information;
	instrument->GetTerminalSide();
	instrumentUUT->GetTerminalSide();
	instrument->CalculateParam();
	instrumentUUT->CalculateParam();

	//Fill Front info;
	txtTerminal_DMM->Text = instrument->TerminalSide ? "FRONT" : "REAR";
	txtTerminal_UUT->Text = instrumentUUT->TerminalSide ? "FRONT" : "REAR";

	UpdatePLCTiming();

	FirstLiveDataCollect();
}

 System::Void MainForm::btnConnect_Click(System::Object^ sender, System::EventArgs^ e) {
	 //first check VLF and Handtype multimeter combination;
	 //if (instrument->meastype == MeasType::AC_DCSampling && UUT->device == DMMDevice::HandType)
	 //{
		// MessageBox::Show(L"El tipi bir cihaz ile VLF ölçümü yapılamaz!!!");
		// return;
	 //}
	 ReadFormParam();

	 if (instrument->peakType == PeakType::Peak && instrument->meastype == MeasType::AC )
	 {
		 if (!instrument->canReadPeak)
		 {
			 MessageBox::Show(L"Peak ölçümü sadece Agilent(Keysight) 34511A modelinde bulunmaktadır!!!");
			 return;
		 }
		 if (instrumentUUT->type == DMMType::DMM && !instrumentUUT->canReadPeak)
		 {
			 MessageBox::Show(L"Peak ölçümü sadece Agilent(Keysight) 34511A modelinde bulunmatadır!!!");
			 return;
		 }
	 }

	 if (DMM->ID == UUT->ID)
	 {
		 MessageBox::Show(L"Aynı cihaz hem DMM hem de UUT olarak seçilemez!!!");
		 return;
	 }

	 try
	 {
		 Connect();
		 btnStart->Enabled = true;
		 btnConnect->Visible = false;
		 btnDisconnect->Visible = true;
		 cmbAddress_DMM->Enabled = false;
		 cmbAddress_UUT->Enabled = false;
		 cmbDivider_DMM->Enabled = false;
		 cmbDivider_UUT->Enabled = false;
		 pnlTestConfig->Enabled = false;
		 tsbtnDeviceList->Enabled = false;
		 chkRange_DMM->Enabled = false;
		 chkRange_UUT->Enabled = false;
		 cmbVoltageRange_DMM->Enabled = false;
		 cmbVoltageRange_UUT->Enabled = false;
		 btnSettings->Enabled = false;
		 //cmbMeasType->Enabled = false;
		 //txtFreq->Enabled = false;
		 //FirstLiveDataCollect();
	 }
	 catch (Exception^ ex)
	 {
		 MessageBox::Show(ex->Message);
	 }
}

 System::Void MainForm::btnDisconnect_Click(System::Object^ sender, System::EventArgs^ e) {
	 StopReading = true;
}
 void MainForm::DisConnect() {
	 delete instrument, instrumentUUT;

	 btnStart->Enabled = false;
	 if (timer != nullptr)
		 timer->Dispose(nofity);
	 instrument->DisConnect();
	 instrumentUUT->DisConnect();

	 btnConnect->Visible = true;
	 btnDisconnect->Visible = false;

	 cmbAddress_DMM->Enabled = true;
	 cmbAddress_UUT->Enabled = true;
	 cmbDivider_DMM->Enabled = true;
	 cmbDivider_UUT->Enabled = true;
	 pnlTestConfig->Enabled = true;
	 tsbtnDeviceList->Enabled = true;
	 chkRange_DMM->Enabled = true;
	 chkRange_UUT->Enabled = true;
	 cmbVoltageRange_DMM->Enabled = true;
	 cmbVoltageRange_UUT->Enabled = true;
	 btnSettings->Enabled = true;

	 //cmbMeasType->Enabled = true;
	 //txtFreq->Enabled = true;

	 //btnConnect->Text = "Bağlan";
 }

 System::Void MainForm::cmbVoltageRange_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	 //if DMM not connect just return;
	 if (!isInit) return;
	 if (!instrument) return;
	 VoltageRange rangeDMM = (VoltageRange)cmbVoltageRange_DMM->SelectedIndex;
	 instrument->range = rangeDMM;
	 AutoCalcVoltageRange_DMM();

	 if (!instrument->isConnected) return;
	 instrument->VoltRangeChanged = true;
	 //instrument->ChagneVoltageRange(rangeDMM);
 }

 System::Void MainForm::cmbVoltageRange_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	 //if UUT not connect or hand type just return;
	 if (!isInit) return;
	 if (!instrumentUUT) return;
	 if ( UUT->device == DMMDevice::NoneDevice) return;
	 VoltageRange rangeUUT = (VoltageRange)cmbVoltageRange_UUT->SelectedIndex;
	 instrumentUUT->range = rangeUUT;
	 AutoCalcVoltageRange_UUT();

	 if (!instrumentUUT->isConnected) return;
	 instrumentUUT->VoltRangeChanged = true;
	 //instrumentUUT->ChagneVoltageRange(rangeUUT);
 }

#pragma endregion

#pragma  region "Test"

 void MainForm::btnStart_Click(System::Object^ sender, EventArgs^ e)
 {
	 if (TestActive)
	 {
		 TestActive = false;
		 FinishTest();
		 return;
	 }
	 
	 
	 pnlTestLive->BackColor = Color::FromArgb(255, 128, 128);
	 pnlTestLive->Visible = true;

	 /*ResultList->Clear();
	 ResultList_UUT->Clear();*/
	 RefreshGrid(true);
	 isPaused = false;
	 //Change grid column text;
	 switch (instrument->meastype)
	 {
	 case MeasType::AC:
	 case MeasType::AC_DCSampling:
		 for each (DataGridViewColumn ^ col in dgw_Sample->Columns)
		 {
			 if (col->DataPropertyName == "VpeakRoot2")
			 {
				 col->Name = L"Vpeak/√2";
				 col->HeaderText = L"Vpeak/√2";
				 col->Visible = true;
				 col->DisplayIndex = 2;
			 }
			 if (col->DataPropertyName == "Vrms")
			 {
				 col->Name = L"Vrms";
				 col->HeaderText = L"Vrms";
				 col->Visible = true;
				 col->DisplayIndex = 1;
			 }
			 if (col->DataPropertyName == "SampleNo")
			 {
				 col->Name = L"No";
				 col->HeaderText = L"No";
				 col->Visible = true;
				 col->DisplayIndex = 0;
			 }
		 }
		 //for each (DataGridViewColumn ^ col in dgw_Sample_UUT->Columns)
		 //{
			// if (col->DataPropertyName == "VpeakRoot2")
			// {
			//	 col->Name = L"Vpeak/√2 (UUT)";
			//	 col->HeaderText = L"Vpeak/√2 (UUT)";
			//	 col->Visible = true;
			//	 col->DisplayIndex = 2;
			// }
			// if (col->DataPropertyName == "Vrms")
			// {
			//	 col->Name = L"Vrms  (UUT)";
			//	 col->HeaderText = L"Vrms  (UUT)";
			//	 col->Visible = true;
			//	 col->DisplayIndex = 1;
			// }
			// if (col->DataPropertyName == "SampleNo")
			// {
			//	 col->Name = L"No";
			//	 col->HeaderText = L"No";
			//	 col->Visible = true;
			//	 col->DisplayIndex = 0;
			// }
		 //}
		 break;
	 case MeasType::DC:
		 for each (DataGridViewColumn ^ col in dgw_Sample->Columns)
		 {
			 if (col->DataPropertyName == "VpeakRoot2")
			 {
				 col->Name = L"Vpeak/√2";
				 col->HeaderText = L"Vpeak/√2";
				 col->Visible = false;
				 col->DisplayIndex = 2;
			 }
			 if (col->DataPropertyName == "Vrms")
			 {
				 col->Name = L"V ";
				 col->HeaderText = L"V ";
				 col->Visible = true;
				 col->DisplayIndex = 1;
			 }
			 if (col->DataPropertyName == "SampleNo")
			 {
				 col->Name = L"No";
				 col->HeaderText = L"No";
				 col->Visible = true;
				 col->DisplayIndex = 0;
			 }
		 }
		 //for each (DataGridViewColumn ^ col in dgw_Sample_UUT->Columns)
		 //{
			// if (col->DataPropertyName == "VpeakRoot2")
			// {
			//	 col->Name = L"Vpeak/√2 (UUT)";
			//	 col->HeaderText = L"Vpeak/√2 (UUT)";
			//	 col->Visible = false;
			//	 col->DisplayIndex = 2;
			// }
			// if (col->DataPropertyName == "Vrms")
			// {
			//	 col->Name = L"V (UUT)";
			//	 col->HeaderText = L"V (UUT)";
			//	 col->Visible = true;
			//	 col->DisplayIndex = 1;
			// }
			// if (col->DataPropertyName == "SampleNo")
			// {
			//	 col->Name = L"No";
			//	 col->HeaderText = L"No";
			//	 col->Visible = true;
			//	 col->DisplayIndex = 0;
			// }
		 //}


		 break;
	 }


	 measurement = gcnew WaveFormMeasument::WaveFormMeasurement();

	 measurement->Etiket = txtBarcode->Text;
	 measurement->Ratio = UUT->sfVrms;	// Convert::ToDouble(txtRatio->Text, G::trcul());
	 measurement->WaveCount = Convert::ToInt16(cmbSampleAdet->Text);
	 measurement->Kademe = (int)instrument->range;
	 measurement->NPLC = instrument->NPLC;

	 if (UUT->device != DMMDevice::NoneDevice)
	 {

		 measurementUUT = gcnew WaveFormMeasument::WaveFormMeasurement();

		 measurementUUT->Etiket = txtBarcode->Text;
		 measurementUUT->Ratio = UUT->sfVrms;	// Convert::ToDouble(txtRatio->Text, G::trcul());
		 measurementUUT->WaveCount = Convert::ToInt16(cmbSampleAdet->Text);
		 measurementUUT->Kademe = (int)instrumentUUT->range;
		 measurementUUT->NPLC = instrumentUUT->NPLC;
	 }

	 //Save Last options;
	 G::mySet->Etiket = measurement->Etiket;
	 G::mySet->Ratio = measurement->Ratio;
	 G::mySet->WaveCount = measurement->WaveCount;
	 G::SaveSettings();

	 TestDuration = measurement->WaveCount+5;	// *Convert::ToDouble(txtTestDuration->Text, G::trcul());

	 cmbSampleAdet->Enabled = false;
	 txtBarcode->Enabled = false;
	 cmbVoltageRange_DMM->Enabled = false;
	 cmbVoltageRange_UUT->Enabled = false;
	 //txtRatio->Enabled = false;
	 //txtTestDuration->Enabled = false;
	 btnStart->Enabled = true;
	 btnStart->Text = L"İptal";

	 CollectModulus = 1;	// (int)(TestDuration - 30) / measurement->WaveCount;
	 StartTime = DateTime::Now;

	 TestNo++;
	 TestActive = true;
 }

 System::Void MainForm::btnContinue_Click(System::Object^ sender, System::EventArgs^ e) {
	 if (isPaused)
	 {
		 isPaused = false;
		 btnReEnter->Visible = false;
		 btnContinue->Visible = false;
		 return;
	 }
 }

 void MainForm::FinishTest()
 {
	 pnlTestLive->BackColor = Color::FromArgb(128, 255, 128); // testFinishColor;
	 cmbSampleAdet->Enabled = true;
	 txtBarcode->Enabled = true;
	 //txtRatio->Enabled = true;
	 //txtTestDuration->Enabled = true;
	 btnStart->Enabled = true;
	 cmbVoltageRange_DMM->Enabled = true;
	 cmbVoltageRange_UUT->Enabled = true;
	 btnContinue->Visible = false;
	 btnStart->Text = L"Örneklem Al";
 }

#pragma endregion

#pragma region "Graph"

 void MainForm::dgw_Sample_CellClick(System::Object^ sender, DataGridViewCellEventArgs^ e)
 {
	 if (dgw_Sample->SelectedCells->Count == 0) return;

	 //try
	 //{

		// DataGridViewRow^ selectedRow = dgw_Sample->Rows[dgw_Sample->SelectedCells[0]->RowIndex];
		// selectedSample = (WaveFormMeasument::WaveFormSample^)(selectedRow->DataBoundItem);
		// if (selectedSample == nullptr) return;
		// DrawMyChart();
	 //}
	 //catch (Exception^ ex)
	 //{
		// MessageBox::Show(ex->Message);
	 //}
 }

 void MainForm::DrawMyChart()
 {
	 //this.UIThread(() = >
	 //{

	 //dgw_Data->DataSource = selectedSample->Data;
	 //dgw_Data->Refresh();
	 try
	 {

		 chart1->Series[0]->Points->Clear();
		 if (selectedSample == nullptr) return;
		 if (instrument->meastype != MeasType::AC_DCSampling) return;
		 double minY = 100;	// = selectedSample->Data.Min(z = > z.V);
		 double maxY = 0;	// selectedSample->Data.Max(x = > x.V);
		 bool SmoothWaveForm = false;
		 
		 if (SmoothWaveForm)
		 {

			 //Find closest zero value;
			 int StartIndex = 0;
			 double closeValue = 99999;
			 for (int i = 0; i < selectedSample->Data->Length; i++)
			 {
				 if (Math::Abs(selectedSample->Data[i]->V) < closeValue)
				 {
					 bool takeThis = false;
					 if (i == 0)
					 {
						 takeThis = (selectedSample->Data[i]->V < selectedSample->Data[i + 1]->V);
					 }
					 else
					 {
						 takeThis = (selectedSample->Data[i - 1]->V < selectedSample->Data[i]->V);
					 }
					 if (takeThis)
					 {
						 closeValue = Math::Abs(selectedSample->Data[i]->V);
						 StartIndex = i;
					 }
				 }
			 }

			 int cnt = 0;
			 for (int i = StartIndex; i < selectedSample->Data->Length; i++)
			 {
				 chart1->Series[0]->Points->AddXY(cnt++, selectedSample->Data[i]->V);
			 }
			 for (int i = 0; i < StartIndex; i++)
			 {
				 chart1->Series[0]->Points->AddXY(cnt++, selectedSample->Data[i]->V);
			 }
		 }
		 else
		 {
			 for each (WaveFormMeasument::WaveFormData ^ vdata in selectedSample->Data)
			 {
				 if (Math::Abs(vdata->V) < G::MAXLIMIT)
				 {
					 chart1->Series[0]->Points->AddXY(vdata->No, vdata->V);
				 }
				 else
				 {
					 chart1->Series[0]->Points->AddXY(vdata->No, 0);
				 }
			 }
		 }
	 }
	 catch (Exception^ ex)
	 {
		 MessageBox::Show(ex->ToString());
	 }

	 //chart1->ChartAreas[0]->AxisY.Minimum = minY;
	 //chart1->ChartAreas[0]->AxisY.Maximum = maxY;
	 //chart1->ChartAreas[0]->AxisX.Minimum = 0;*/
 //});
 }

 void MainForm::DrawMyChart_UUT() {
	 try
	 {
		 bool SmoothWaveForm = false;
		 chart1->Series[1]->Points->Clear();
		 if (selectedSampleUUT == nullptr) return;
		 if (instrument->meastype != MeasType::AC_DCSampling) return;

		 if (instrumentUUT->type != DMMType::None)
		 {
			 if (selectedSampleUUT == nullptr) return;
			 if (SmoothWaveForm)
			 {

				 //Find closest zero value;
				 int StartIndex = 0;
				 double closeValue = 99999;
				 for (int i = 0; i < selectedSampleUUT->Data->Length; i++)
				 {
					 if (Math::Abs(selectedSampleUUT->Data[i]->V) < closeValue)
					 {
						 bool takeThis = false;
						 if (i == 0)
						 {
							 takeThis = (selectedSampleUUT->Data[i]->V < selectedSampleUUT->Data[i + 1]->V);
						 }
						 else
						 {
							 takeThis = (selectedSampleUUT->Data[i - 1]->V < selectedSampleUUT->Data[i]->V);
						 }
						 if (takeThis)
						 {
							 closeValue = Math::Abs(selectedSampleUUT->Data[i]->V);
							 StartIndex = i;
						 }
					 }
				 }

				 int cnt = 0;
				 for (int i = StartIndex; i < selectedSampleUUT->Data->Length; i++)
				 {
					 chart1->Series[1]->Points->AddXY(cnt++, selectedSampleUUT->Data[i]->V);
				 }
				 for (int i = 0; i < StartIndex; i++)
				 {
					 chart1->Series[1]->Points->AddXY(cnt++, selectedSampleUUT->Data[i]->V);
				 }
			 }
			 else
			 {
				 for each (WaveFormMeasument::WaveFormData ^ vdata in selectedSampleUUT->Data)
				 {
					 if (Math::Abs(vdata->V) < G::MAXLIMIT)
					 {
						 chart1->Series[1]->Points->AddXY(vdata->No, vdata->V);
					 }
					 else
					 {
						 chart1->Series[1]->Points->AddXY(vdata->No, 0);
					 }
				 }
			 }
		 }

	 }
	 catch (Exception^ ex)
	 {
		 MessageBox::Show(ex->ToString());
	 }

 }

#pragma	endregion

#pragma region "Grid Actions"
 void  MainForm::RefreshGrid(bool isUUT)
 {
	 int  MeasTypeInt = 0;	// (int)(instrument->meastype);		// == MeasType::AC_DCSampling);
		//0 rms
		//1 peak
		//2 dc
	 switch (instrument->meastype)
	 {
	 case MeasType::AC_DCSampling:
		 MeasTypeInt = 1;
		 break;
	 case MeasType::DC:
		 MeasTypeInt = 2;
		 break;
	 case MeasType::AC:
		 switch (instrument->peakType)
		 {
		 case PeakType::Peak:
			 MeasTypeInt = 1;
			 break;
		 default:
			 MeasTypeInt = 0;
			 break;
		 }
		 break;
	 }

	 if (!isUUT)
	 {
		 //if new meas on Ref side;
		 if (ResultList->Count > GridList->Count)
		 {
			 GridObject^ newMeas = gcnew GridObject(ResultList[ResultList->Count - 1], false, MeasTypeInt);			//, liveData->showAskV
			 newMeas->TestNo = TestNo;
			 GridList->Add(newMeas);
		 }
		 else
		 {
			 if (ResultList->Count > 0)
				 GridList[GridList->Count - 1]->Update(ResultList[ResultList->Count - 1], false, MeasTypeInt);		//, liveData->showAskV
		 }
	 }
	 else {
		 //if new meas on UUT side;
		 if (ResultList_UUT->Count > GridList->Count)
		 {
			 GridObject^ newMeas = gcnew GridObject(ResultList_UUT[ResultList_UUT->Count - 1], true, MeasTypeInt);	//, liveDataUUT->showAskV
			 newMeas->TestNo = TestNo;
			 GridList->Add(newMeas);
		 }
		 else
		 {
			 if (ResultList_UUT->Count >0)
				 GridList[GridList->Count - 1]->Update(ResultList_UUT[ResultList_UUT->Count - 1], true, MeasTypeInt);	//, liveDataUUT->showAskV
		 }
	 }



	 dgw_Sample->DataSource = GridList->ToArray();	// GridList->ToArray()	;// ResultList->ToArray();

	 for each (DataGridViewColumn ^ col in dgw_Sample->Columns)
	 {
		 if (col->DataPropertyName == "ScaleFactor")
		 {
			 col->DisplayIndex = 4;
		 }
		 if (col->DataPropertyName == "V_kV_UUT")
		 {
			 col->HeaderText = L"High Volt. UUT";		// +(liveDataUUT->showAskV ? L" (kV)" : L" (V)");
			 col->DisplayIndex = 3;
		 }
		 if (col->DataPropertyName == "V_kV")
		 {
			 col->HeaderText = "High Volt. REF";		//  +(liveData->showAskV ? L" (kV)" : L" (V)");
			 col->DisplayIndex = 2;
		 }
		 if (col->DataPropertyName == "SampleNo")
		 {
			 col->DisplayIndex = 1;
		 }
		 if (col->DataPropertyName == "TestNo")
		 {
			 col->DisplayIndex = 0;
		 }
	 }

	 dgw_Sample->Refresh();
	 dgw_Sample->Update();
	 CalculateSummary();

	 //dgw_Sample_UUT->DataSource = ResultList_UUT->ToArray();	// GridList->ToArray()	;// ResultList->ToArray();
	 //for each (DataGridViewColumn ^ col in dgw_Sample_UUT->Columns)
	 //{
		// if (col->DataPropertyName == "VpeakRoot2")
		// {
		//	 col->DisplayIndex = 2;
		// }
		// if (col->DataPropertyName == "Vrms")
		// {
		//	 col->DisplayIndex = 1;
		// }
		// if (col->DataPropertyName == "SampleNo")
		// {
		//	 col->DisplayIndex = 0;
		// }
	 //}

	 //dgw_Sample_UUT->Refresh();
	 //dgw_Sample_UUT->Update();
	 //CalculateSummary_UUT();
 }
 void MainForm::CalculateSummary() {
	 lblResultSumm_DMM->Text = "-";
	 double sum = 0;
	 double count = 0;
	 double minScale = 9999999;
	 chart2->Series[0]->Points->Clear();
	 if (ResultList->Count == 0) return;
	 for each (GridObject^ go  in GridList)
	 {
		 count++;
		 sum += go->ScaleFactor;
		 chart2->Series[0]->Points->AddXY(go->V_kV, go->ScaleFactor);
		 if (minScale > go->ScaleFactor) { minScale = go->ScaleFactor; }
	 }
	 if (minScale == 9999999)  minScale = 0;

	 chart2->ChartAreas[0]->AxisY->Minimum = minScale * 0.8;
	 double avgValue = sum / count;
	 double sumsqr = 0;
	 for each (GridObject^ wfs  in GridList)
	 {
		 count++;
		 sumsqr += Math::Pow(avgValue - wfs->ScaleFactor, 2);
	 }
	 double dagilganlik = Math::Sqrt(sumsqr / count);


	 lblResultSumm_DMM->Text = String::Format(L"Ort: {0:F3}   , Delta: {1:F3} ", avgValue, dagilganlik);
 }

 void MainForm::CalculateSummary_DMM() {
	 lblResultSumm_DMM->Text = "-";
	 double sum = 0;
	 double count = 0;
	 if (ResultList->Count == 0) return;
	 for each (WaveFormSample^ wfs  in ResultList)
	 {
		 count++;
		 sum += wfs->Vrms;
	 }
	 double avgValue = sum / count;
	 double sumsqr = 0;
	 for each (WaveFormSample ^ wfs  in ResultList)
	 {
		 count++;
		 sumsqr += Math::Pow(avgValue - wfs->Vrms, 2);
	 }
	 double dagilganlik = Math::Sqrt(sumsqr / count);

	 lblResultSumm_DMM->Text = String::Format(L"Ort: {0:F3} kV  , Delta: {1:F3} kV", avgValue, dagilganlik);
 }
 void MainForm::CalculateSummary_UUT() {
	 //lblResultSumm_UUT->Text = "-";
	 //double sum = 0;
	 //double count = 0;
	 //if (ResultList_UUT->Count == 0) return;
	 //for each (WaveFormSample ^ wfs  in ResultList_UUT)
	 //{
		// count++;
		// sum += wfs->Vrms;
	 //}
	 //double avgValue = sum / count;
	 //double sumsqr = 0;
	 //for each (WaveFormSample ^ wfs  in ResultList_UUT)
	 //{
		// count++;
		// sumsqr += Math::Pow(avgValue - wfs->Vrms, 2);
	 //}
	 //double dagilganlik = Math::Sqrt(sumsqr / count);

	 //lblResultSumm_UUT->Text = String::Format(L"Ort: {0:F3} kV  , Delta: {1:F3} kV", avgValue, dagilganlik);

 }

 void MainForm::llblRefreshGrid_LinkClicked(System::Object^ sender, LinkLabelLinkClickedEventArgs^ e)
 {
	 RefreshGrid(true);
 }

 void  MainForm::linkLabel1_LinkClicked(System::Object^ sender, LinkLabelLinkClickedEventArgs^ e)
 {
	 // SampleList to XML;
	 //SaveTestSettings(ResultList, txtBarcode->Text);
	 SaveTestSettings(GridList, txtBarcode->Text);
 }

//void MainForm::SaveTestSettings(List<WaveFormMeasument::WaveFormSample^>^ SampleList, String^ barkod)
 //{
	// SaveFileDialog^ sfd = gcnew SaveFileDialog();
	// sfd->Filter = "CSV Dosyası|*.csv";
	// sfd->FileName = barkod + ".csv";
	// String^ fileName = Path::GetFileNameWithoutExtension(sfd->FileName);
	// sfd->OverwritePrompt = true;
	// sfd->InitialDirectory = G::mySet->BaseDirectory;
	// if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	// {
	//	 String^ barcode = "barkod";
	//	 TextWriter^ tw = gcnew StreamWriter(sfd->FileName, true, Encoding::UTF8); // ;  File.CreateText())
	//	 tw->WriteLine(WaveFormMeasument::WaveFormSample::Headers());
	//	 for each (WaveFormMeasument::WaveFormSample ^ vs in SampleList)
	//	 {
	//		 barcode = vs->Etiket;
	//		 tw->WriteLine(vs->ToString());
	//	 }
	//	 //(IDisposable ^)(tw)->Dispose();
	//	 //tw->Dispose();
	//	 delete tw;
 //
	//	 String^ path = Path::GetDirectoryName(sfd->FileName);
	//	 String^ DataPath = Path::Combine(path, fileName + "_data.csv");
	//	 tw = gcnew StreamWriter(DataPath, true, Encoding::UTF8);
 //
	//	 tw->WriteLine("Etiket;SampleNo;No;T;V");
	//	 for each (WaveFormMeasument::WaveFormSample ^ vs in SampleList)
	//	 {
	//		 for each (WaveFormMeasument::WaveFormData ^ vd in vs->Data)
	//		 {
	//			 tw->WriteLine(String::Format("{1}{0}{2}{0}{3}{0}", G::DELIMETER, vs->Etiket, vs->SampleNo, vd->ToString()));
	//		 }
	//	 }
	//	 //tw->Dispose();
	//	 delete tw;
	// }


 void MainForm::SaveTestSettings(List<GridObject^>^ SampleList, String^ barkod)
 {
	 String^ filename = barkod;
	 if (chkAddDateTime->Checked)
	 {
		 filename += "_" + DateTime::Now.ToString("yyyy_MM_ddHHmm");
	 }
	 SaveFileDialog^ sfd = gcnew SaveFileDialog();
	 sfd->Filter = L"CSV Dosyası|*.csv";
	 sfd->FileName = filename + ".csv";
	 String^ fileName = Path::GetFileNameWithoutExtension(sfd->FileName);
	 sfd->OverwritePrompt = true;
	 sfd->InitialDirectory = G::mySet->BaseDirectory;
	 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

	 TextWriter^ tw = gcnew StreamWriter(sfd->FileName, false, Encoding::UTF8); // ;  File.CreateText())
	 //First Add Device Info;
	 tw->WriteLine(String::Format(L"#{0}Ref DMM{0}UUT DMM", G::DELIMETER));
	 tw->WriteLine(String::Format(L"DMM{0}{1}{0}{2}", G::DELIMETER, DMM->ToString(), UUT->ToString()));
	 if (UUT->device == DMMDevice::NoneDevice)
	 {
		 tw->WriteLine(String::Format(L"Bölücü{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->ToString(), "-"));
		 tw->WriteLine(String::Format(L"Kademe{0}{1}{0}{2}", G::DELIMETER, instrument->rangeSTR, "-"));
		 tw->WriteLine(String::Format(L"s.f Vrms{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->sfVrms, "-"));
		 tw->WriteLine(String::Format(L"s.f Vpeak{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->sfVpeak, "-"));
		 tw->WriteLine(String::Format(L"ZIn{0}{1}{0}{2}", G::DELIMETER, instrument->ZinSTR, "-"));
		 tw->WriteLine(String::Format(L"Terminal{0}{1}{0}{2}", G::DELIMETER, instrument->TerminalSide ? "FRONT" : "REAR", "-"));
	 }
	 else
	 {
		 tw->WriteLine(String::Format(L"Bölücü{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->ToString(), UUT_Divider->ToString()));
		 tw->WriteLine(String::Format(L"Kademe{0}{1}{0}{2}", G::DELIMETER, instrument->rangeSTR, instrumentUUT->rangeSTR));
		 tw->WriteLine(String::Format(L"s.f Vrms{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->sfVrms, UUT_Divider->sfVrms));
		 tw->WriteLine(String::Format(L"s.f Vpeak{0}{1}{0}{2}", G::DELIMETER, DMM_Divider->sfVpeak, UUT_Divider->sfVpeak));
		 tw->WriteLine(String::Format(L"ZIn{0}{1}{0}{2}", G::DELIMETER, instrument->ZinSTR, instrumentUUT->ZinSTR));
		 tw->WriteLine(String::Format(L"Terminal{0}{1}{0}{2}", G::DELIMETER, instrument->TerminalSide ? "FRONT" : "REAR", instrumentUUT->TerminalSide ? "FRONT" : "REAR"));
	 }

	 tw->WriteLine("");
	 tw->WriteLine("");
	 tw->WriteLine(L"Test Bilgileri;");
	 tw->WriteLine(String::Format(L"Test Tipi{0}{1}", G::DELIMETER, instrument->meastypeSTR));
	 tw->WriteLine(String::Format(L"Veri Tipi{0}{1}", G::DELIMETER, instrument->peakTypeSTR ));
	 tw->WriteLine(String::Format(L"Frekans {0}{1} Hz", G::DELIMETER, (instrument->meastype == MeasType::DC ? 0.0 : instrument->SampleFreq)));
	 tw->WriteLine(String::Format(L"Test Tarihi{0}{1}", G::DELIMETER, DateTime::Now));

	 tw->WriteLine("");
	 tw->WriteLine("");
	 tw->WriteLine(L"Ölçümler;");

	 if (instrument->peakType == PeakType::Peak)
	 {
		 tw->WriteLine(String::Format(L"Test#{0}Sıra#{0}Ref Vpeak/√2 (V){0} UUT Vpeak/√2 (V){0}Ref Vpeak/√2 (kV){0} UUT Vpeak/√2 (kV){0}", G::DELIMETER));
	 }
	 else
	 {
		 tw->WriteLine(String::Format(L"Test#{0}Sıra#{0}Ref Vrms (V){0} UUT Vrms (V){0}Ref Vrms (kV){0} UUT Vrms (kV){0}", G::DELIMETER));
	 }
	 for (int i = 0; i < SampleList->Count; i++)
	 {
		 //tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}{0}{2}{0}{3}", G::DELIMETER, i + 1, SampleList[i]->V_Raw, SampleList[i]->V_Raw_UUT, SampleList[i]->V_kV, SampleList[i]->V_kV_UUT));
		 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}{0}{4}{0}{5}{0}{6}{0}", G::DELIMETER, SampleList[i]->TestNo, i + 1, SampleList[i]->V_Raw, SampleList[i]->V_Raw_UUT, SampleList[i]->V_kV, SampleList[i]->V_kV_UUT));
	 }


	/* if (instrument->meastype == MeasType::AC_DCSampling)
	 {
		 tw->WriteLine(String::Format(L"#{0}Ref DMM{0} {0}UUT DMM{0}", G::DELIMETER));
		 tw->WriteLine(String::Format(L"#{0}Vpeak/√2{0}{0}Vpeak/√2 (UUT){0}", G::DELIMETER));
		 for (int i = 0; i < ResultList->Count; i++)
		 {
			 if (ResultList_UUT->Count > i)
			 {
				 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}{0}{2}{0}{3}", G::DELIMETER, i + 1, ResultList[i]->Vrms, ResultList[i]->VpeakRoot2, ResultList_UUT[i]->Vrms, ResultList_UUT[i]->VpeakRoot2));
			 }
			 else
			 {
				 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}{0}{4}{0}{5}", G::DELIMETER, i + 1, ResultList[i]->Vrms, ResultList[i]->VpeakRoot2, "-", "-"));
			 }
		 }
	 }
	 else
	 {
		 tw->WriteLine(String::Format(L"#{0}Ref DMM{0}UUT DMM", G::DELIMETER));
		 if (instrument->peakType == PeakType::Voltage)
		 {
			 for (int i = 0; i < ResultList->Count; i++)
			 {
				 if (ResultList_UUT->Count > i)
				 {
					 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}{0}{2}{0}{3}", G::DELIMETER, i + 1, SampleList[i]->V_Raw, SampleList[i]->V_Raw_UUT, "-", "-"));
					 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}", G::DELIMETER, i + 1, ResultList[i]->Vrms, ResultList_UUT[i]->Vrms));
				 }
				 else
				 {
					 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}", G::DELIMETER, i + 1, ResultList[i]->Vrms, "-"));
				 }
			 }
		 }
		 else
		 {
			 for (int i = 0; i < ResultList->Count; i++)
			 {
				 if (ResultList_UUT->Count > i)
				 {
					 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}", G::DELIMETER, i + 1, ResultList[i]->VpeakRoot2, ResultList_UUT[i]->VpeakRoot2));
				 }
				 else
				 {
					 tw->WriteLine(String::Format(L"{1}{0}{2}{0}{3}", G::DELIMETER, i + 1, ResultList[i]->VpeakRoot2, "-"));
				 }
			 }
		 }
	 }*/
	 delete tw;
 }

 void  MainForm::linkLabel2_LinkClicked(System::Object^ sender, LinkLabelLinkClickedEventArgs^ e)
 {
	 TestNo = 0;
	 GridList->Clear();
	 ResultList->Clear();
	 ResultList_UUT->Clear();
	 //GridList->Clear();
	 btnReEnter->Visible = false;
	 RefreshGrid(true);
 }

 void  MainForm::txtRatio_TextChanged(System::Object^ sender, EventArgs^ e)
 {
	 /*double ratio = 0;
	 bool ratioOK = double::TryParse(txtRatio->Text, System::Globalization::NumberStyles::Any, G::trcul(), ratio);
	 if (ratioOK)
	 {
		 G::mySet->Ratio = ratio;
	 }*/
 }

#pragma endregion

#pragma  region "Bar Buttons"
 void  MainForm::btnShowLog_Click(System::Object^ sender, EventArgs^ e)
 {
	 panelLog->Visible = !panelLog->Visible;
 }

 void  MainForm::helpToolStripButton_Click(System::Object^ sender, EventArgs^ e)
 {
	 if (1 > 2)
	 {

	 //Test Multi;
	 liveData = gcnew WaveFormMeasument::WaveFormMeasurement();
	 liveDataUUT = gcnew WaveFormMeasument::WaveFormMeasurement();

	 liveData->Etiket = txtBarcode->Text;
	 liveData->Ratio = DMM_Divider->sfVrms;
	 liveData->Ratio_Peak = DMM_Divider->sfVpeak;
	 liveData->Ratio_DC = DMM_Divider->sfVdc;
	 liveData->WaveCount = 1;
	 liveData->Kademe = (int)instrument->range;
	 liveData->sampleForEachWave = instrument->WaveFormSampleCount;
	 liveData->measType = (int)instrument->meastype;

	 liveDataUUT->Etiket = txtBarcode->Text;
	 liveDataUUT->Ratio = UUT_Divider->sfVrms;
	 liveDataUUT->Ratio_Peak = UUT_Divider->sfVpeak;
	 liveDataUUT->Ratio_DC = UUT_Divider->sfVdc;
	 liveDataUUT->WaveCount = 1;
	 liveDataUUT->Kademe = (int)instrumentUUT->range;
	 liveDataUUT->sampleForEachWave = instrumentUUT->WaveFormSampleCount;
	 liveDataUUT->measType = (int)instrumentUUT->meastype;


	 measurement->waves->Clear();
	 measurementUUT->waves->Clear();

	 ResultList->Clear();
	 ResultList_UUT->Clear();

	 TestActive = true;
	 selectedSample = gcnew WaveFormMeasument::WaveFormSample(1,1);
	 selectedSampleUUT = gcnew WaveFormMeasument::WaveFormSample(1,1);

	 //No:1
	 selectedSample->Vrms = 1;
	 selectedSampleUUT->Vrms = 1;
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));

	 //No:2
	 selectedSample->Vrms = 2;
	 selectedSampleUUT->Vrms = 2;
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));

	 //No:3
	 selectedSample->Vrms = 3;
	 selectedSampleUUT->Vrms = 3;
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));

	 //No:4
	 selectedSample->Vrms = 4;
	 selectedSampleUUT->Vrms = 4;
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));

	 //No:5
	 selectedSample->Vrms = 5;
	 selectedSampleUUT->Vrms = 5;
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels));
	 Invoke(gcnew Action(this, &MainForm::UpdateLiveLabels_UUT));

	 return;
	 }

	 AboutForm^ about = gcnew AboutForm();
	 about->ShowDialog(this);
	 delete about;
 }

 void  MainForm::btnExit_Click(System::Object^ sender, EventArgs^ e)
 {
	 delete instrument, timer;
	 this->Close();
 }

 void MainForm::tsbtnDeviceList_Click(System::Object^ sender, System::EventArgs^ e) {
	 EquipList^ setPage = gcnew EquipList();
	 setPage->ShowDialog(this);
	 delete setPage;
	 CheckDemoMode();
	 isInit = false;
	 LoadCombo();
	 isInit = true;
	 ReadFormParam();
 }

 void  MainForm::btnSettings_Click(System::Object^ sender, EventArgs^ e)
 {
	 SettingForm^ setForm = gcnew SettingForm();
	 setForm->ShowDialog(this);
 }

#pragma endregion

