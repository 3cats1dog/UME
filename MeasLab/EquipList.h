#pragma once

#include "Envanter.h";

namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EquipList
	/// </summary>
	public ref class EquipList : public System::Windows::Forms::Form
	{
	public:
		EquipList(void)
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
		~EquipList()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ gbDMM;
	private: System::Windows::Forms::DataGridView^ dgw_DMM;









	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::DataGridView^ dgw_Divider;




















	private: System::Windows::Forms::Button^ btnAddDivider;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtModel;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtMarka;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtSeriNo;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ cmbConnType;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ txtsfVpeak;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ txtsfVrms;
	private: System::Windows::Forms::Panel^ pnlDividersf;

	private: System::Windows::Forms::Panel^ pnlDMMConnection;
	private: System::Windows::Forms::Button^ btnDelete;
	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::ComboBox^ cmbAddress;
	private: System::Windows::Forms::Label^ label8;






















private: System::Windows::Forms::Button^ btnTestConnection;












private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::TextBox^ txtsfVdc;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column14;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column15;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column11;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column12;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ sfDC;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column13;
private: System::Windows::Forms::Button^ btnGPIBFind;
private: System::Windows::Forms::Button^ btnAddDMM;
private: System::Windows::Forms::ComboBox^ cmbNewDMMType;
private: System::Windows::Forms::Label^ lblDMMType;
private: System::Windows::Forms::Label^ lblTypeName;














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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EquipList::typeid));
			this->gbDMM = (gcnew System::Windows::Forms::GroupBox());
			this->dgw_DMM = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->sfDC = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->dgw_Divider = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnAddDivider = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lblDMMType = (gcnew System::Windows::Forms::Label());
			this->lblTypeName = (gcnew System::Windows::Forms::Label());
			this->btnTestConnection = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->pnlDividersf = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->txtsfVdc = (gcnew System::Windows::Forms::TextBox());
			this->txtsfVrms = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txtsfVpeak = (gcnew System::Windows::Forms::TextBox());
			this->pnlDMMConnection = (gcnew System::Windows::Forms::Panel());
			this->cmbAddress = (gcnew System::Windows::Forms::ComboBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->cmbConnType = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtSeriNo = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtModel = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtMarka = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->btnGPIBFind = (gcnew System::Windows::Forms::Button());
			this->btnAddDMM = (gcnew System::Windows::Forms::Button());
			this->cmbNewDMMType = (gcnew System::Windows::Forms::ComboBox());
			this->gbDMM->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_DMM))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_Divider))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->pnlDividersf->SuspendLayout();
			this->pnlDMMConnection->SuspendLayout();
			this->SuspendLayout();
			// 
			// gbDMM
			// 
			this->gbDMM->Controls->Add(this->dgw_DMM);
			this->gbDMM->Location = System::Drawing::Point(12, 38);
			this->gbDMM->Name = L"gbDMM";
			this->gbDMM->Size = System::Drawing::Size(639, 279);
			this->gbDMM->TabIndex = 0;
			this->gbDMM->TabStop = false;
			this->gbDMM->Text = L"DMM";
			// 
			// dgw_DMM
			// 
			this->dgw_DMM->AllowUserToAddRows = false;
			this->dgw_DMM->AllowUserToDeleteRows = false;
			this->dgw_DMM->BackgroundColor = System::Drawing::Color::White;
			this->dgw_DMM->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgw_DMM->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(12) {
				this->Column1, this->Column4,
					this->Column8, this->Column11, this->Column12, this->Column3, this->Column2, this->Column5, this->sfDC, this->Column6, this->Column7,
					this->Column13
			});
			this->dgw_DMM->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgw_DMM->Location = System::Drawing::Point(3, 16);
			this->dgw_DMM->MultiSelect = false;
			this->dgw_DMM->Name = L"dgw_DMM";
			this->dgw_DMM->ReadOnly = true;
			this->dgw_DMM->RowHeadersVisible = false;
			this->dgw_DMM->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dgw_DMM->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgw_DMM->Size = System::Drawing::Size(633, 260);
			this->dgw_DMM->TabIndex = 20;
			this->dgw_DMM->DoubleClick += gcnew System::EventHandler(this, &EquipList::dgw_DMM_DoubleClick);
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"No";
			this->Column1->HeaderText = L"No";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Visible = false;
			this->Column1->Width = 50;
			// 
			// Column4
			// 
			this->Column4->DataPropertyName = L"tipName";
			this->Column4->HeaderText = L"Type";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			this->Column4->Visible = false;
			// 
			// Column8
			// 
			this->Column8->DataPropertyName = L"Marka";
			this->Column8->HeaderText = L"Brand";
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			// 
			// Column11
			// 
			this->Column11->DataPropertyName = L"Model";
			this->Column11->HeaderText = L"Model";
			this->Column11->Name = L"Column11";
			this->Column11->ReadOnly = true;
			// 
			// Column12
			// 
			this->Column12->DataPropertyName = L"SeriNo";
			this->Column12->HeaderText = L"Seri No";
			this->Column12->Name = L"Column12";
			this->Column12->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->DataPropertyName = L"ScalaFactor";
			this->Column3->HeaderText = L"Scala Faktor";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Visible = false;
			// 
			// Column2
			// 
			this->Column2->DataPropertyName = L"sfVrms";
			this->Column2->HeaderText = L"Column2";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Visible = false;
			// 
			// Column5
			// 
			this->Column5->DataPropertyName = L"sfVpeak";
			this->Column5->HeaderText = L"s.f. Vpeak";
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			this->Column5->Visible = false;
			// 
			// sfDC
			// 
			this->sfDC->DataPropertyName = L"sfVdc";
			this->sfDC->HeaderText = L"sfDC";
			this->sfDC->Name = L"sfDC";
			this->sfDC->ReadOnly = true;
			this->sfDC->Visible = false;
			// 
			// Column6
			// 
			this->Column6->DataPropertyName = L"ID";
			this->Column6->HeaderText = L"ID";
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->Visible = false;
			// 
			// Column7
			// 
			this->Column7->DataPropertyName = L"StrConnType";
			this->Column7->HeaderText = L"Connection";
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			// 
			// Column13
			// 
			this->Column13->DataPropertyName = L"Name";
			this->Column13->HeaderText = L"Column13";
			this->Column13->Name = L"Column13";
			this->Column13->ReadOnly = true;
			this->Column13->Visible = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->dgw_Divider);
			this->groupBox1->Location = System::Drawing::Point(12, 353);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(639, 265);
			this->groupBox1->TabIndex = 21;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Voltage Dividers";
			// 
			// dgw_Divider
			// 
			this->dgw_Divider->AllowUserToAddRows = false;
			this->dgw_Divider->AllowUserToDeleteRows = false;
			this->dgw_Divider->BackgroundColor = System::Drawing::Color::White;
			this->dgw_Divider->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgw_Divider->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(13) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn5,
					this->dataGridViewTextBoxColumn6, this->dataGridViewTextBoxColumn7, this->dataGridViewTextBoxColumn8, this->Column14, this->dataGridViewTextBoxColumn9,
					this->Column9, this->Column10, this->Column15
			});
			this->dgw_Divider->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgw_Divider->Location = System::Drawing::Point(3, 16);
			this->dgw_Divider->MultiSelect = false;
			this->dgw_Divider->Name = L"dgw_Divider";
			this->dgw_Divider->ReadOnly = true;
			this->dgw_Divider->RowHeadersVisible = false;
			this->dgw_Divider->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgw_Divider->Size = System::Drawing::Size(633, 246);
			this->dgw_Divider->TabIndex = 20;
			this->dgw_Divider->DoubleClick += gcnew System::EventHandler(this, &EquipList::dgw_Divider_DoubleClick);
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->DataPropertyName = L"No";
			this->dataGridViewTextBoxColumn1->HeaderText = L"No";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->Visible = false;
			this->dataGridViewTextBoxColumn1->Width = 50;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->DataPropertyName = L"tipName";
			this->dataGridViewTextBoxColumn2->HeaderText = L"Type";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->Visible = false;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->DataPropertyName = L"Marka";
			this->dataGridViewTextBoxColumn3->HeaderText = L"Brand";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->DataPropertyName = L"Model";
			this->dataGridViewTextBoxColumn4->HeaderText = L"Model";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->DataPropertyName = L"SeriNo";
			this->dataGridViewTextBoxColumn5->HeaderText = L"Seri No";
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn6
			// 
			this->dataGridViewTextBoxColumn6->DataPropertyName = L"ScalaFactor";
			this->dataGridViewTextBoxColumn6->HeaderText = L"Scale Faktor";
			this->dataGridViewTextBoxColumn6->Name = L"dataGridViewTextBoxColumn6";
			this->dataGridViewTextBoxColumn6->ReadOnly = true;
			this->dataGridViewTextBoxColumn6->Visible = false;
			// 
			// dataGridViewTextBoxColumn7
			// 
			this->dataGridViewTextBoxColumn7->DataPropertyName = L"sfVrms";
			this->dataGridViewTextBoxColumn7->HeaderText = L"s.f. Vrms";
			this->dataGridViewTextBoxColumn7->Name = L"dataGridViewTextBoxColumn7";
			this->dataGridViewTextBoxColumn7->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn8
			// 
			this->dataGridViewTextBoxColumn8->DataPropertyName = L"sfVpeak";
			this->dataGridViewTextBoxColumn8->HeaderText = L"s.f. Vpeak";
			this->dataGridViewTextBoxColumn8->Name = L"dataGridViewTextBoxColumn8";
			this->dataGridViewTextBoxColumn8->ReadOnly = true;
			// 
			// Column14
			// 
			this->Column14->DataPropertyName = L"sfVdc";
			this->Column14->HeaderText = L"s.f. Vdc";
			this->Column14->Name = L"Column14";
			this->Column14->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn9
			// 
			this->dataGridViewTextBoxColumn9->DataPropertyName = L"ID";
			this->dataGridViewTextBoxColumn9->HeaderText = L"ID";
			this->dataGridViewTextBoxColumn9->Name = L"dataGridViewTextBoxColumn9";
			this->dataGridViewTextBoxColumn9->ReadOnly = true;
			this->dataGridViewTextBoxColumn9->Visible = false;
			// 
			// Column9
			// 
			this->Column9->DataPropertyName = L"StrConnType";
			this->Column9->HeaderText = L"Column9";
			this->Column9->Name = L"Column9";
			this->Column9->ReadOnly = true;
			this->Column9->Visible = false;
			// 
			// Column10
			// 
			this->Column10->DataPropertyName = L"Name";
			this->Column10->HeaderText = L"Column10";
			this->Column10->Name = L"Column10";
			this->Column10->ReadOnly = true;
			this->Column10->Visible = false;
			// 
			// Column15
			// 
			this->Column15->DataPropertyName = L"Address";
			this->Column15->HeaderText = L"Column15";
			this->Column15->Name = L"Column15";
			this->Column15->ReadOnly = true;
			this->Column15->Visible = false;
			// 
			// btnAddDivider
			// 
			this->btnAddDivider->Location = System::Drawing::Point(513, 624);
			this->btnAddDivider->Name = L"btnAddDivider";
			this->btnAddDivider->Size = System::Drawing::Size(132, 23);
			this->btnAddDivider->TabIndex = 22;
			this->btnAddDivider->Text = L"Add New Divider";
			this->btnAddDivider->UseVisualStyleBackColor = true;
			this->btnAddDivider->Click += gcnew System::EventHandler(this, &EquipList::btnAddDivider_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lblDMMType);
			this->groupBox2->Controls->Add(this->lblTypeName);
			this->groupBox2->Controls->Add(this->btnTestConnection);
			this->groupBox2->Controls->Add(this->btnDelete);
			this->groupBox2->Controls->Add(this->btnSave);
			this->groupBox2->Controls->Add(this->pnlDividersf);
			this->groupBox2->Controls->Add(this->pnlDMMConnection);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->txtSeriNo);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->txtModel);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->txtMarka);
			this->groupBox2->Location = System::Drawing::Point(657, 38);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(615, 279);
			this->groupBox2->TabIndex = 23;
			this->groupBox2->TabStop = false;
			// 
			// lblDMMType
			// 
			this->lblDMMType->AutoSize = true;
			this->lblDMMType->Location = System::Drawing::Point(109, 33);
			this->lblDMMType->Name = L"lblDMMType";
			this->lblDMMType->Size = System::Drawing::Size(31, 13);
			this->lblDMMType->TabIndex = 27;
			this->lblDMMType->Text = L"Type";
			// 
			// lblTypeName
			// 
			this->lblTypeName->AutoSize = true;
			this->lblTypeName->Location = System::Drawing::Point(34, 33);
			this->lblTypeName->Name = L"lblTypeName";
			this->lblTypeName->Size = System::Drawing::Size(31, 13);
			this->lblTypeName->TabIndex = 26;
			this->lblTypeName->Text = L"Type";
			// 
			// btnTestConnection
			// 
			this->btnTestConnection->Location = System::Drawing::Point(193, 228);
			this->btnTestConnection->Name = L"btnTestConnection";
			this->btnTestConnection->Size = System::Drawing::Size(132, 23);
			this->btnTestConnection->TabIndex = 25;
			this->btnTestConnection->Text = L"Test";
			this->btnTestConnection->UseVisualStyleBackColor = true;
			this->btnTestConnection->Click += gcnew System::EventHandler(this, &EquipList::btnTestConnection_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Location = System::Drawing::Point(24, 228);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(132, 23);
			this->btnDelete->TabIndex = 24;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &EquipList::btnDelete_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(437, 228);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(132, 23);
			this->btnSave->TabIndex = 23;
			this->btnSave->Text = L"Update";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &EquipList::btnSave_Click);
			// 
			// pnlDividersf
			// 
			this->pnlDividersf->Controls->Add(this->label9);
			this->pnlDividersf->Controls->Add(this->txtsfVdc);
			this->pnlDividersf->Controls->Add(this->txtsfVrms);
			this->pnlDividersf->Controls->Add(this->label6);
			this->pnlDividersf->Controls->Add(this->label5);
			this->pnlDividersf->Controls->Add(this->txtsfVpeak);
			this->pnlDividersf->Location = System::Drawing::Point(340, 40);
			this->pnlDividersf->Name = L"pnlDividersf";
			this->pnlDividersf->Size = System::Drawing::Size(226, 120);
			this->pnlDividersf->TabIndex = 13;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(27, 72);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(43, 13);
			this->label9->TabIndex = 13;
			this->label9->Text = L"s.f. Vdc";
			// 
			// txtsfVdc
			// 
			this->txtsfVdc->Location = System::Drawing::Point(97, 69);
			this->txtsfVdc->Name = L"txtsfVdc";
			this->txtsfVdc->Size = System::Drawing::Size(100, 20);
			this->txtsfVdc->TabIndex = 12;
			// 
			// txtsfVrms
			// 
			this->txtsfVrms->Location = System::Drawing::Point(97, 17);
			this->txtsfVrms->Name = L"txtsfVrms";
			this->txtsfVrms->Size = System::Drawing::Size(100, 20);
			this->txtsfVrms->TabIndex = 8;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(27, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(47, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"s.f. Vrms";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(27, 46);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(55, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"s.f. Vpeak";
			// 
			// txtsfVpeak
			// 
			this->txtsfVpeak->Location = System::Drawing::Point(97, 43);
			this->txtsfVpeak->Name = L"txtsfVpeak";
			this->txtsfVpeak->Size = System::Drawing::Size(100, 20);
			this->txtsfVpeak->TabIndex = 10;
			// 
			// pnlDMMConnection
			// 
			this->pnlDMMConnection->Controls->Add(this->cmbAddress);
			this->pnlDMMConnection->Controls->Add(this->label8);
			this->pnlDMMConnection->Controls->Add(this->cmbConnType);
			this->pnlDMMConnection->Controls->Add(this->label4);
			this->pnlDMMConnection->Location = System::Drawing::Point(24, 135);
			this->pnlDMMConnection->Name = L"pnlDMMConnection";
			this->pnlDMMConnection->Size = System::Drawing::Size(301, 87);
			this->pnlDMMConnection->TabIndex = 12;
			// 
			// cmbAddress
			// 
			this->cmbAddress->FormattingEnabled = true;
			this->cmbAddress->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Handheld", L"GBIP", L"RS232" });
			this->cmbAddress->Location = System::Drawing::Point(88, 36);
			this->cmbAddress->Name = L"cmbAddress";
			this->cmbAddress->Size = System::Drawing::Size(192, 21);
			this->cmbAddress->TabIndex = 8;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(10, 39);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(59, 13);
			this->label8->TabIndex = 9;
			this->label8->Text = L"GBIP/USB";
			// 
			// cmbConnType
			// 
			this->cmbConnType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbConnType->FormattingEnabled = true;
			this->cmbConnType->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Handheld", L"GBIP", L"RS232", L"PXI", L"USB" });
			this->cmbConnType->Location = System::Drawing::Point(88, 9);
			this->cmbConnType->Name = L"cmbConnType";
			this->cmbConnType->Size = System::Drawing::Size(192, 21);
			this->cmbConnType->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(61, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Connection";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(34, 112);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(42, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Seri No";
			// 
			// txtSeriNo
			// 
			this->txtSeriNo->Location = System::Drawing::Point(112, 109);
			this->txtSeriNo->Name = L"txtSeriNo";
			this->txtSeriNo->Size = System::Drawing::Size(192, 20);
			this->txtSeriNo->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(34, 86);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(36, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Model";
			// 
			// txtModel
			// 
			this->txtModel->Location = System::Drawing::Point(112, 83);
			this->txtModel->Name = L"txtModel";
			this->txtModel->Size = System::Drawing::Size(192, 20);
			this->txtModel->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(34, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Brand";
			// 
			// txtMarka
			// 
			this->txtMarka->Location = System::Drawing::Point(112, 57);
			this->txtMarka->Name = L"txtMarka";
			this->txtMarka->Size = System::Drawing::Size(192, 20);
			this->txtMarka->TabIndex = 0;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(14, 12);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(220, 20);
			this->label7->TabIndex = 24;
			this->label7->Text = L"Laboratory Equipment List";
			// 
			// btnGPIBFind
			// 
			this->btnGPIBFind->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnGPIBFind->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnGPIBFind.Image")));
			this->btnGPIBFind->Location = System::Drawing::Point(1141, 12);
			this->btnGPIBFind->Name = L"btnGPIBFind";
			this->btnGPIBFind->Size = System::Drawing::Size(131, 23);
			this->btnGPIBFind->TabIndex = 26;
			this->btnGPIBFind->Text = L"GBIP/USB Search";
			this->btnGPIBFind->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->btnGPIBFind->UseVisualStyleBackColor = true;
			this->btnGPIBFind->Click += gcnew System::EventHandler(this, &EquipList::btnGPIBFind_Click);
			// 
			// btnAddDMM
			// 
			this->btnAddDMM->Location = System::Drawing::Point(516, 320);
			this->btnAddDMM->Name = L"btnAddDMM";
			this->btnAddDMM->Size = System::Drawing::Size(132, 23);
			this->btnAddDMM->TabIndex = 27;
			this->btnAddDMM->Text = L"Add New DMM";
			this->btnAddDMM->UseVisualStyleBackColor = true;
			this->btnAddDMM->Click += gcnew System::EventHandler(this, &EquipList::btnAddDMM_Click);
			// 
			// cmbNewDMMType
			// 
			this->cmbNewDMMType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbNewDMMType->FormattingEnabled = true;
			this->cmbNewDMMType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Agilent 3458A", L"Agilent 34411", L"Agilent 34470",
					L"NI PXIe"
			});
			this->cmbNewDMMType->Location = System::Drawing::Point(381, 320);
			this->cmbNewDMMType->Name = L"cmbNewDMMType";
			this->cmbNewDMMType->Size = System::Drawing::Size(129, 21);
			this->cmbNewDMMType->TabIndex = 10;
			// 
			// EquipList
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1284, 662);
			this->Controls->Add(this->cmbNewDMMType);
			this->Controls->Add(this->btnAddDMM);
			this->Controls->Add(this->btnGPIBFind);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->btnAddDivider);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->gbDMM);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"EquipList";
			this->Text = L"Inventory List";
			this->Load += gcnew System::EventHandler(this, &EquipList::EquipList_Load);
			this->gbDMM->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_DMM))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_Divider))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->pnlDividersf->ResumeLayout(false);
			this->pnlDividersf->PerformLayout();
			this->pnlDMMConnection->ResumeLayout(false);
			this->pnlDMMConnection->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void EquipList_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void btnAddDivider_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void dgw_DMM_DoubleClick(System::Object^ sender, System::EventArgs^ e);
		System::Void dgw_Divider_DoubleClick(System::Object^ sender, System::EventArgs^ e);
		System::Void btnTestConnection_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGPIBFind_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnAddDMM_Click(System::Object^ sender, System::EventArgs^ e);

	public:
		System::Collections::Generic::List<Envanter^>^ DMMList = gcnew System::Collections::Generic::List<Envanter^>();
		System::Collections::Generic::List<Envanter^>^ DividerList = gcnew System::Collections::Generic::List<Envanter^>();
		Envanter^ SelectedEnv;
		int MaxID = 1;

		
		Void FillDMM();
		Void FillDivider();
		Void UpdateForm();
		Void ReadForm();
		Void ClearForm();
		Void FindDeviceList();


};
}
