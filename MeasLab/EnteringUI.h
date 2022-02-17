#pragma once

namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EnteringUI
	/// </summary>
	public ref class EnteringUI : public System::Windows::Forms::Form
	{
	public:
		EnteringUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EnteringUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnSave;
	protected:

	private: System::Windows::Forms::TextBox^ txtVrms;

	private: System::Windows::Forms::Label^ lblV;
	private: System::Windows::Forms::Label^ lblVPeak;
	private: System::Windows::Forms::TextBox^ txtVpeak;
	private: System::Windows::Forms::CheckBox^ chkIskV;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EnteringUI::typeid));
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->txtVrms = (gcnew System::Windows::Forms::TextBox());
			this->lblV = (gcnew System::Windows::Forms::Label());
			this->lblVPeak = (gcnew System::Windows::Forms::Label());
			this->txtVpeak = (gcnew System::Windows::Forms::TextBox());
			this->chkIskV = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(51, 59);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(123, 49);
			this->btnSave->TabIndex = 2;
			this->btnSave->Text = L"Kaydet";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &EnteringUI::btnSave_Click);
			// 
			// txtVrms
			// 
			this->txtVrms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtVrms->Location = System::Drawing::Point(56, 26);
			this->txtVrms->Name = L"txtVrms";
			this->txtVrms->Size = System::Drawing::Size(118, 29);
			this->txtVrms->TabIndex = 0;
			this->txtVrms->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &EnteringUI::txtVrms_KeyPress);
			// 
			// lblV
			// 
			this->lblV->AutoSize = true;
			this->lblV->Location = System::Drawing::Point(12, 37);
			this->lblV->Name = L"lblV";
			this->lblV->Size = System::Drawing::Size(30, 13);
			this->lblV->TabIndex = 2;
			this->lblV->Text = L"Vrms";
			// 
			// lblVPeak
			// 
			this->lblVPeak->AutoSize = true;
			this->lblVPeak->Location = System::Drawing::Point(12, 111);
			this->lblVPeak->Name = L"lblVPeak";
			this->lblVPeak->Size = System::Drawing::Size(38, 13);
			this->lblVPeak->TabIndex = 4;
			this->lblVPeak->Text = L"Vpeak";
			this->lblVPeak->Visible = false;
			// 
			// txtVpeak
			// 
			this->txtVpeak->Location = System::Drawing::Point(56, 108);
			this->txtVpeak->Name = L"txtVpeak";
			this->txtVpeak->Size = System::Drawing::Size(26, 20);
			this->txtVpeak->TabIndex = 1;
			this->txtVpeak->Visible = false;
			// 
			// chkIskV
			// 
			this->chkIskV->AutoSize = true;
			this->chkIskV->Location = System::Drawing::Point(179, 36);
			this->chkIskV->Name = L"chkIskV";
			this->chkIskV->Size = System::Drawing::Size(39, 17);
			this->chkIskV->TabIndex = 5;
			this->chkIskV->Text = L"kV";
			this->chkIskV->UseVisualStyleBackColor = true;
			// 
			// EnteringUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(230, 132);
			this->ControlBox = false;
			this->Controls->Add(this->chkIskV);
			this->Controls->Add(this->lblVPeak);
			this->Controls->Add(this->txtVpeak);
			this->Controls->Add(this->lblV);
			this->Controls->Add(this->txtVrms);
			this->Controls->Add(this->btnSave);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"EnteringUI";
			this->Text = L"El Tipi Ölçü Aleti Manuel Veri Girişi";
			this->Load += gcnew System::EventHandler(this, &EnteringUI::EnteringUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		double Vrms;
		double Vpeak;
		int MeasType;
		int PeakTpye;
		bool IskV;

	private: 
		System::Void EnteringUI_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void txtVrms_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};

}
