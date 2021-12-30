#include "EnteringUI.h"
#include "Global.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO::Ports;
using namespace MeasLab;

System::Void EnteringUI::EnteringUI_Load(System::Object^ sender, System::EventArgs^ e) {

	if (PeakTpye == 1)
	{
		lblV->Text = "V peak";
	}
	else
	{
		if (MeasType == 0)
		{
			lblV->Text = "Vrms";
			lblVPeak->Text = "Vpeak";
		}
		else
		{
			lblV->Text = "V DC";
			lblVPeak->Text = "V DC peak";
		}
	}
	txtVrms->Focus();
}
System::Void EnteringUI::txtVrms_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == (char)13)
		btnSave_Click(nullptr, nullptr);
}

System::Void EnteringUI::btnSave_Click(System::Object^ sender, System::EventArgs^ e) {

	double v1;
	double v2;

	double::TryParse(txtVrms->Text->Replace(",","."), Globalization::NumberStyles::Any, MeasLab::G::invcul(), v1);
	double::TryParse(txtVpeak->Text->Replace(",", "."), Globalization::NumberStyles::Any, MeasLab::G::invcul(), v2);

	if (PeakTpye == 1)
	{
		Vrms = v2;
		Vpeak = v1;
	}
	else
	{
		Vrms = v1;
		Vpeak = v2;
	}

	this->Close();
}