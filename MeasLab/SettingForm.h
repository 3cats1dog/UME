#pragma once
#pragma once
#include "Global.h";

namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SettingForm
	/// </summary>
	public ref class SettingForm : public System::Windows::Forms::Form
	{
	public:
		SettingForm(void)
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
		~SettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ btnPlaySound;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::CheckBox^ chkUseFixZInput;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::NumericUpDown^ nud_Duration;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ nud_Freq;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::CheckBox^ chkAutoNextOnManualReading;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::TextBox^ txtWaveFormSampleCount;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::TextBox^ txtWaveFormSampleCount2;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::GroupBox^ groupBox6;
	private: System::Windows::Forms::CheckBox^ chkUseDC;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SettingForm::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->nud_Duration = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->nud_Freq = (gcnew System::Windows::Forms::NumericUpDown());
			this->btnPlaySound = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->chkUseFixZInput = (gcnew System::Windows::Forms::CheckBox());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->chkAutoNextOnManualReading = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->txtWaveFormSampleCount = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->txtWaveFormSampleCount2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->chkUseDC = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_Duration))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_Freq))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->nud_Duration);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->nud_Freq);
			this->groupBox1->Controls->Add(this->btnPlaySound);
			this->groupBox1->Location = System::Drawing::Point(283, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(255, 91);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ses Kontrol";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(95, 50);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(20, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"ms";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(95, 21);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(20, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Hz";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(5, 50);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Süre";
			// 
			// nud_Duration
			// 
			this->nud_Duration->Location = System::Drawing::Point(39, 48);
			this->nud_Duration->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->nud_Duration->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->nud_Duration->Name = L"nud_Duration";
			this->nud_Duration->Size = System::Drawing::Size(50, 20);
			this->nud_Duration->TabIndex = 3;
			this->nud_Duration->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(28, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Freq";
			// 
			// nud_Freq
			// 
			this->nud_Freq->Location = System::Drawing::Point(39, 19);
			this->nud_Freq->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
			this->nud_Freq->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->nud_Freq->Name = L"nud_Freq";
			this->nud_Freq->Size = System::Drawing::Size(50, 20);
			this->nud_Freq->TabIndex = 1;
			this->nud_Freq->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// btnPlaySound
			// 
			this->btnPlaySound->Location = System::Drawing::Point(157, 19);
			this->btnPlaySound->Name = L"btnPlaySound";
			this->btnPlaySound->Size = System::Drawing::Size(71, 49);
			this->btnPlaySound->TabIndex = 0;
			this->btnPlaySound->Text = L"Ses Çal";
			this->btnPlaySound->UseVisualStyleBackColor = true;
			this->btnPlaySound->Click += gcnew System::EventHandler(this, &SettingForm::btnPlaySound_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->chkUseFixZInput);
			this->groupBox2->Location = System::Drawing::Point(3, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(274, 164);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Giriş Empedansı";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::Color::Red;
			this->label1->Location = System::Drawing::Point(16, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(221, 78);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Sabit Empedans Modu\r\nTüm kademeler için sabit: 10MΩ\r\n\r\nDeğişken Empedans Modu\r\n10"
				L"0 mV / 1V ve 10 V kademeleri için >10 GΩ\r\n100V ve 1000 V kademeleri için 10 MΩ\r\n"
				L"";
			// 
			// chkUseFixZInput
			// 
			this->chkUseFixZInput->AutoSize = true;
			this->chkUseFixZInput->Location = System::Drawing::Point(19, 39);
			this->chkUseFixZInput->Name = L"chkUseFixZInput";
			this->chkUseFixZInput->Size = System::Drawing::Size(135, 17);
			this->chkUseFixZInput->TabIndex = 0;
			this->chkUseFixZInput->Text = L"Sabit Empedans Kullan";
			this->chkUseFixZInput->UseVisualStyleBackColor = true;
			this->chkUseFixZInput->CheckedChanged += gcnew System::EventHandler(this, &SettingForm::chkUseFixZInput_CheckedChanged);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(399, 264);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(139, 50);
			this->btnSave->TabIndex = 1;
			this->btnSave->Text = L"Kaydet";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &SettingForm::btnSave_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->chkAutoNextOnManualReading);
			this->groupBox3->Location = System::Drawing::Point(283, 109);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(255, 67);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"El Tipi DMM ";
			// 
			// chkAutoNextOnManualReading
			// 
			this->chkAutoNextOnManualReading->AutoSize = true;
			this->chkAutoNextOnManualReading->Location = System::Drawing::Point(39, 32);
			this->chkAutoNextOnManualReading->Name = L"chkAutoNextOnManualReading";
			this->chkAutoNextOnManualReading->Size = System::Drawing::Size(195, 17);
			this->chkAutoNextOnManualReading->TabIndex = 1;
			this->chkAutoNextOnManualReading->Text = L"Otomatik olarak sonraki ölçüme geç";
			this->chkAutoNextOnManualReading->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->txtWaveFormSampleCount);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Location = System::Drawing::Point(3, 182);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(274, 63);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"VLF Ölçümleri";
			// 
			// txtWaveFormSampleCount
			// 
			this->txtWaveFormSampleCount->Location = System::Drawing::Point(161, 24);
			this->txtWaveFormSampleCount->Name = L"txtWaveFormSampleCount";
			this->txtWaveFormSampleCount->Size = System::Drawing::Size(100, 20);
			this->txtWaveFormSampleCount->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 27);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(139, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Dalgaformu Örneklem Sayısı";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->txtWaveFormSampleCount2);
			this->groupBox5->Controls->Add(this->label7);
			this->groupBox5->Location = System::Drawing::Point(3, 251);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(274, 63);
			this->groupBox5->TabIndex = 4;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"AC Rms Ölçümleri (>40Hz)";
			// 
			// txtWaveFormSampleCount2
			// 
			this->txtWaveFormSampleCount2->Location = System::Drawing::Point(161, 24);
			this->txtWaveFormSampleCount2->Name = L"txtWaveFormSampleCount2";
			this->txtWaveFormSampleCount2->Size = System::Drawing::Size(100, 20);
			this->txtWaveFormSampleCount2->TabIndex = 1;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(9, 27);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(139, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Dalgaformu Örneklem Sayısı";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->chkUseDC);
			this->groupBox6->Location = System::Drawing::Point(283, 182);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(255, 63);
			this->groupBox6->TabIndex = 5;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"VLF Ölçümleri (3458A)";
			// 
			// chkUseDC
			// 
			this->chkUseDC->AutoSize = true;
			this->chkUseDC->Location = System::Drawing::Point(8, 26);
			this->chkUseDC->Name = L"chkUseDC";
			this->chkUseDC->Size = System::Drawing::Size(114, 17);
			this->chkUseDC->TabIndex = 1;
			this->chkUseDC->Text = L"DC Offset Hesapla";
			this->chkUseDC->UseVisualStyleBackColor = true;
			// 
			// SettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 319);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SettingForm";
			this->Text = L"Ayarlar";
			this->Load += gcnew System::EventHandler(this, &SettingForm::SettingForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_Duration))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_Freq))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void SettingForm_Load(System::Object^ sender, System::EventArgs^ e) {
		chkUseFixZInput->Checked = G::mySet->useFixedZInput;
		chkUseDC->Checked = G::mySet->useDCOffset;
		chkAutoNextOnManualReading->Checked = G::mySet->AutoNext;
		nud_Duration->Value = G::mySet->BeepDuration;
		nud_Freq->Value = G::mySet->BeepFreq;
		txtWaveFormSampleCount->Text = G::mySet->DesiredVLFCount.ToString();
		txtWaveFormSampleCount2->Text = G::mySet->DesiredVLFCount2.ToString();
	}
	private: System::Void btnPlaySound_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Console::Beep((int)nud_Freq->Value, (int)nud_Duration->Value);
	}

	private: System::Void chkUseFixZInput_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		
	}
	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		G::mySet->useFixedZInput = chkUseFixZInput->Checked;
		G::mySet->BeepDuration = (int)nud_Duration->Value;
		G::mySet->BeepFreq = (int)nud_Freq->Value;
		G::mySet->AutoNext = chkAutoNextOnManualReading->Checked;
		G::mySet->DesiredVLFCount = Convert::ToInt32(txtWaveFormSampleCount->Text);
		G::mySet->DesiredVLFCount2 = Convert::ToInt32(txtWaveFormSampleCount2->Text);
		G::mySet->useDCOffset = chkUseDC->Checked;
		String^ msg = "";
		if (G::mySet->DesiredVLFCount > 100000)
		{
			msg = "VLF Dalgaboyu örneklem sayısı 100.000'den büyük olamaz!";
			G::mySet->DesiredVLFCount = 100000;
		}
		if (G::mySet->DesiredVLFCount2 > 100000)
		{
			msg = "AC rms Dalgaboyu örneklem sayısı 100.000'den büyük olamaz!";
			G::mySet->DesiredVLFCount2 = 100000;
		}
		G::SaveSettings();
	}
};

}
