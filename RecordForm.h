#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace BicRF {

	/// <summary>
	/// Сводка для RecordForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class RecordForm : public System::Windows::Forms::Form
	{
		DataSet^ NotebooksDataSet;	// DataSet, содержащий таблицы базы данных
		String ^SQLCommand,			// SQL-оператор для добавления/изменения записи
			^NEWNUM;				// БИК, передается в конструкторе, если пустой, 
									//		то форма будет в режиме добавления
		bool	IsInsertMode;		// Признак режима формы

	public:
		RecordForm( DataSet^ _NotebooksDataSet, String^ _newnum )
		{
			NotebooksDataSet = _NotebooksDataSet;
			NEWNUM = _newnum;
			IsInsertMode = (NEWNUM->Length == 0);

			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		String^ getSQLCommand() { return SQLCommand; };
		String^ getNEWNUM() { return NEWNUM; };

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~RecordForm()
		{
			if (components)
			{
				delete components;
			}
		}
	protected: 
		void check_NAME();
		void check_NEWNUM();

	private: System::Windows::Forms::Label^  NEWNUM_Label;
	private: System::Windows::Forms::Label^  NAME_Label;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox3;

	private: System::Windows::Forms::TextBox^  NAME_TextBox;
	private: System::Windows::Forms::TextBox^  REAL_TextBox;
	private: System::Windows::Forms::TextBox^  TELEF_TextBox;
	private: System::Windows::Forms::TextBox^  ADR_TextBox;
	private: System::Windows::Forms::TextBox^  NNP_TextBox;
	private: System::Windows::Forms::TextBox^  REGN_TextBox;

	private: System::Windows::Forms::MaskedTextBox^  NEWNUM_MaskedTextBox;
	private: System::Windows::Forms::MaskedTextBox^  KSNP_MaskedTextBox;
	private: System::Windows::Forms::MaskedTextBox^  RKC_MaskedTextBox;
	private: System::Windows::Forms::MaskedTextBox^  IND_MaskedTextBox;
	private: System::Windows::Forms::MaskedTextBox^  OKPO_MaskedTextBox;

	private: System::Windows::Forms::ComboBox^  PZN_ComboBox;
	private: System::Windows::Forms::ComboBox^  TNP_ComboBox;
	private: System::Windows::Forms::ComboBox^  RGN_ComboBox;
	private: System::Windows::Forms::ComboBox^  UER_ComboBox;

	private: System::Windows::Forms::DateTimePicker^  DATE_IN_DateTimePicker;
	private: System::Windows::Forms::DateTimePicker^  DT_IZM_DateTimePicker;
	private: System::Windows::Forms::DateTimePicker^  DATE_CH_DateTimePicker;

	private: System::Windows::Forms::Button^  OkButton;
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::CheckBox^  DATE_CH_CheckBox;



	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->UER_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->NEWNUM_Label = (gcnew System::Windows::Forms::Label());
			this->NAME_Label = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->IND_MaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TELEF_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->ADR_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->NNP_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->TNP_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->RGN_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->KSNP_MaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->RKC_MaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->NEWNUM_MaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->NAME_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->REAL_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->PZN_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->REGN_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->DATE_IN_DateTimePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->DT_IZM_DateTimePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->DATE_CH_DateTimePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->OkButton = (gcnew System::Windows::Forms::Button());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->DATE_CH_CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->OKPO_MaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->groupBox1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// UER_ComboBox
			// 
			this->UER_ComboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->UER_ComboBox->FormattingEnabled = true;
			this->UER_ComboBox->Location = System::Drawing::Point(210, 55);
			this->UER_ComboBox->Name = L"UER_ComboBox";
			this->UER_ComboBox->Size = System::Drawing::Size(483, 21);
			this->UER_ComboBox->TabIndex = 2;
			// 
			// NEWNUM_Label
			// 
			this->NEWNUM_Label->AutoSize = true;
			this->NEWNUM_Label->Location = System::Drawing::Point(20, 21);
			this->NEWNUM_Label->Name = L"NEWNUM_Label";
			this->NEWNUM_Label->Size = System::Drawing::Size(29, 13);
			this->NEWNUM_Label->TabIndex = 0;
			this->NEWNUM_Label->Text = L"БИК";
			// 
			// NAME_Label
			// 
			this->NAME_Label->AutoSize = true;
			this->NAME_Label->Location = System::Drawing::Point(11, 10);
			this->NAME_Label->Name = L"NAME_Label";
			this->NAME_Label->Size = System::Drawing::Size(83, 13);
			this->NAME_Label->TabIndex = 1;
			this->NAME_Label->Text = L"Наименование";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(146, 21);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(54, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"БИК РКЦ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 34);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(129, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Тип участника расчетов";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 82);
			this->label5->Name = L"label5";
			this->label5->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label5->Size = System::Drawing::Size(150, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Код контроля допустимости";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(20, 21);
			this->label7->Name = L"label7";
			this->label7->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label7->Size = System::Drawing::Size(64, 13);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Регион РФ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(20, 69);
			this->label8->Name = L"label8";
			this->label8->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label8->Size = System::Drawing::Size(45, 13);
			this->label8->TabIndex = 7;
			this->label8->Text = L"Индекс";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(20, 45);
			this->label9->Name = L"label9";
			this->label9->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label9->Size = System::Drawing::Size(217, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Тип и наименование населенного пункта";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(146, 69);
			this->label11->Name = L"label11";
			this->label11->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label11->Size = System::Drawing::Size(38, 13);
			this->label11->TabIndex = 10;
			this->label11->Text = L"Адрес";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(20, 93);
			this->label12->Name = L"label12";
			this->label12->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label12->Size = System::Drawing::Size(105, 13);
			this->label12->TabIndex = 11;
			this->label12->Text = L"Номера телефонов";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(225, 283);
			this->label13->Name = L"label13";
			this->label13->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label13->Size = System::Drawing::Size(133, 13);
			this->label13->TabIndex = 12;
			this->label13->Text = L"Регистрационный номер";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(13, 283);
			this->label14->Name = L"label14";
			this->label14->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label14->Size = System::Drawing::Size(60, 13);
			this->label14->TabIndex = 13;
			this->label14->Text = L"Код ОКПО";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(297, 21);
			this->label15->Name = L"label15";
			this->label15->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label15->Size = System::Drawing::Size(72, 13);
			this->label15->TabIndex = 14;
			this->label15->Text = L"Номер счета";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->IND_MaskedTextBox);
			this->groupBox1->Controls->Add(this->TELEF_TextBox);
			this->groupBox1->Controls->Add(this->ADR_TextBox);
			this->groupBox1->Controls->Add(this->NNP_TextBox);
			this->groupBox1->Controls->Add(this->TNP_ComboBox);
			this->groupBox1->Controls->Add(this->RGN_ComboBox);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Location = System::Drawing::Point(4, 156);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(696, 120);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Расположение участника расчетов ";
			// 
			// IND_MaskedTextBox
			// 
			this->IND_MaskedTextBox->Location = System::Drawing::Point(71, 66);
			this->IND_MaskedTextBox->Mask = L"000000000";
			this->IND_MaskedTextBox->Name = L"IND_MaskedTextBox";
			this->IND_MaskedTextBox->PromptChar = ' ';
			this->IND_MaskedTextBox->Size = System::Drawing::Size(70, 20);
			this->IND_MaskedTextBox->TabIndex = 12;
			// 
			// TELEF_TextBox
			// 
			this->TELEF_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->TELEF_TextBox->Location = System::Drawing::Point(131, 90);
			this->TELEF_TextBox->Name = L"TELEF_TextBox";
			this->TELEF_TextBox->Size = System::Drawing::Size(230, 20);
			this->TELEF_TextBox->TabIndex = 14;
			// 
			// ADR_TextBox
			// 
			this->ADR_TextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ADR_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->ADR_TextBox->Location = System::Drawing::Point(190, 66);
			this->ADR_TextBox->Name = L"ADR_TextBox";
			this->ADR_TextBox->Size = System::Drawing::Size(499, 20);
			this->ADR_TextBox->TabIndex = 13;
			// 
			// NNP_TextBox
			// 
			this->NNP_TextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->NNP_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->NNP_TextBox->Location = System::Drawing::Point(313, 42);
			this->NNP_TextBox->Name = L"NNP_TextBox";
			this->NNP_TextBox->Size = System::Drawing::Size(376, 20);
			this->NNP_TextBox->TabIndex = 11;
			// 
			// TNP_ComboBox
			// 
			this->TNP_ComboBox->FormattingEnabled = true;
			this->TNP_ComboBox->Location = System::Drawing::Point(243, 42);
			this->TNP_ComboBox->Name = L"TNP_ComboBox";
			this->TNP_ComboBox->Size = System::Drawing::Size(64, 21);
			this->TNP_ComboBox->TabIndex = 10;
			// 
			// RGN_ComboBox
			// 
			this->RGN_ComboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->RGN_ComboBox->FormattingEnabled = true;
			this->RGN_ComboBox->Location = System::Drawing::Point(90, 18);
			this->RGN_ComboBox->Name = L"RGN_ComboBox";
			this->RGN_ComboBox->Size = System::Drawing::Size(599, 21);
			this->RGN_ComboBox->TabIndex = 9;
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox3->Controls->Add(this->KSNP_MaskedTextBox);
			this->groupBox3->Controls->Add(this->RKC_MaskedTextBox);
			this->groupBox3->Controls->Add(this->NEWNUM_MaskedTextBox);
			this->groupBox3->Controls->Add(this->NEWNUM_Label);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->label15);
			this->groupBox3->Location = System::Drawing::Point(4, 106);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(696, 48);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Расчетные реквизиты ";
			// 
			// KSNP_MaskedTextBox
			// 
			this->KSNP_MaskedTextBox->CutCopyMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
			this->KSNP_MaskedTextBox->Location = System::Drawing::Point(375, 18);
			this->KSNP_MaskedTextBox->Mask = L"00000 000 0 000000 00000";
			this->KSNP_MaskedTextBox->Name = L"KSNP_MaskedTextBox";
			this->KSNP_MaskedTextBox->PromptChar = ' ';
			this->KSNP_MaskedTextBox->Size = System::Drawing::Size(150, 20);
			this->KSNP_MaskedTextBox->TabIndex = 7;
			this->KSNP_MaskedTextBox->TextMaskFormat = System::Windows::Forms::MaskFormat::ExcludePromptAndLiterals;
			// 
			// RKC_MaskedTextBox
			// 
			this->RKC_MaskedTextBox->Location = System::Drawing::Point(206, 18);
			this->RKC_MaskedTextBox->Mask = L"000000000";
			this->RKC_MaskedTextBox->Name = L"RKC_MaskedTextBox";
			this->RKC_MaskedTextBox->PromptChar = ' ';
			this->RKC_MaskedTextBox->Size = System::Drawing::Size(70, 20);
			this->RKC_MaskedTextBox->TabIndex = 6;
			// 
			// NEWNUM_MaskedTextBox
			// 
			this->NEWNUM_MaskedTextBox->HidePromptOnLeave = true;
			this->NEWNUM_MaskedTextBox->InsertKeyMode = System::Windows::Forms::InsertKeyMode::Overwrite;
			this->NEWNUM_MaskedTextBox->Location = System::Drawing::Point(56, 18);
			this->NEWNUM_MaskedTextBox->Mask = L"000000000";
			this->NEWNUM_MaskedTextBox->Name = L"NEWNUM_MaskedTextBox";
			this->NEWNUM_MaskedTextBox->PromptChar = ' ';
			this->NEWNUM_MaskedTextBox->Size = System::Drawing::Size(70, 20);
			this->NEWNUM_MaskedTextBox->TabIndex = 5;
			this->NEWNUM_MaskedTextBox->Leave += gcnew System::EventHandler(this, &RecordForm::NEWNUM_MaskedTextBox_Leave);
			// 
			// NAME_TextBox
			// 
			this->NAME_TextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->NAME_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->NAME_TextBox->Location = System::Drawing::Point(210, 7);
			this->NAME_TextBox->Name = L"NAME_TextBox";
			this->NAME_TextBox->Size = System::Drawing::Size(483, 20);
			this->NAME_TextBox->TabIndex = 0;
			this->NAME_TextBox->Leave += gcnew System::EventHandler(this, &RecordForm::NAME_TextBox_Leave);
			// 
			// REAL_TextBox
			// 
			this->REAL_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->REAL_TextBox->Location = System::Drawing::Point(210, 79);
			this->REAL_TextBox->Name = L"REAL_TextBox";
			this->REAL_TextBox->Size = System::Drawing::Size(59, 20);
			this->REAL_TextBox->TabIndex = 3;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 58);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(194, 13);
			this->label6->TabIndex = 24;
			this->label6->Text = L"Тип участия в электронных расчетах";
			// 
			// PZN_ComboBox
			// 
			this->PZN_ComboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->PZN_ComboBox->FormattingEnabled = true;
			this->PZN_ComboBox->Location = System::Drawing::Point(210, 31);
			this->PZN_ComboBox->Name = L"PZN_ComboBox";
			this->PZN_ComboBox->Size = System::Drawing::Size(483, 21);
			this->PZN_ComboBox->TabIndex = 1;
			// 
			// REGN_TextBox
			// 
			this->REGN_TextBox->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->REGN_TextBox->Location = System::Drawing::Point(364, 280);
			this->REGN_TextBox->Name = L"REGN_TextBox";
			this->REGN_TextBox->Size = System::Drawing::Size(125, 20);
			this->REGN_TextBox->TabIndex = 16;
			// 
			// DATE_IN_DateTimePicker
			// 
			this->DATE_IN_DateTimePicker->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->DATE_IN_DateTimePicker->Location = System::Drawing::Point(173, 304);
			this->DATE_IN_DateTimePicker->Name = L"DATE_IN_DateTimePicker";
			this->DATE_IN_DateTimePicker->Size = System::Drawing::Size(96, 20);
			this->DATE_IN_DateTimePicker->TabIndex = 17;
			this->DATE_IN_DateTimePicker->Value = System::DateTime(2017, 12, 24, 22, 39, 38, 0);
			// 
			// DT_IZM_DateTimePicker
			// 
			this->DT_IZM_DateTimePicker->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->DT_IZM_DateTimePicker->Location = System::Drawing::Point(173, 328);
			this->DT_IZM_DateTimePicker->Name = L"DT_IZM_DateTimePicker";
			this->DT_IZM_DateTimePicker->Size = System::Drawing::Size(96, 20);
			this->DT_IZM_DateTimePicker->TabIndex = 18;
			// 
			// DATE_CH_DateTimePicker
			// 
			this->DATE_CH_DateTimePicker->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->DATE_CH_DateTimePicker->Location = System::Drawing::Point(173, 352);
			this->DATE_CH_DateTimePicker->Name = L"DATE_CH_DateTimePicker";
			this->DATE_CH_DateTimePicker->Size = System::Drawing::Size(96, 20);
			this->DATE_CH_DateTimePicker->TabIndex = 20;
			this->DATE_CH_DateTimePicker->Visible = false;
			// 
			// OkButton
			// 
			this->OkButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->OkButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OkButton->Location = System::Drawing::Point(537, 385);
			this->OkButton->Name = L"OkButton";
			this->OkButton->Size = System::Drawing::Size(75, 23);
			this->OkButton->TabIndex = 21;
			this->OkButton->Text = L"Добавить";
			this->OkButton->UseVisualStyleBackColor = true;
			this->OkButton->Click += gcnew System::EventHandler(this, &RecordForm::OkButton_Click);
			// 
			// CancelButton
			// 
			this->CancelButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(618, 385);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 22;
			this->CancelButton->Text = L"Отмена";
			this->CancelButton->UseVisualStyleBackColor = true;
			// 
			// DATE_CH_CheckBox
			// 
			this->DATE_CH_CheckBox->Location = System::Drawing::Point(13, 354);
			this->DATE_CH_CheckBox->Name = L"DATE_CH_CheckBox";
			this->DATE_CH_CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DATE_CH_CheckBox->Size = System::Drawing::Size(154, 18);
			this->DATE_CH_CheckBox->TabIndex = 19;
			this->DATE_CH_CheckBox->Text = L"Дата контроля";
			this->DATE_CH_CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->DATE_CH_CheckBox->UseVisualStyleBackColor = true;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(13, 307);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(119, 13);
			this->label10->TabIndex = 37;
			this->label10->Text = L"Дата включения в БД";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(13, 331);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(154, 13);
			this->label16->TabIndex = 38;
			this->label16->Text = L"Дата последнего изменения";
			// 
			// OKPO_MaskedTextBox
			// 
			this->OKPO_MaskedTextBox->Location = System::Drawing::Point(79, 280);
			this->OKPO_MaskedTextBox->Mask = L"00000000";
			this->OKPO_MaskedTextBox->Name = L"OKPO_MaskedTextBox";
			this->OKPO_MaskedTextBox->PromptChar = ' ';
			this->OKPO_MaskedTextBox->Size = System::Drawing::Size(125, 20);
			this->OKPO_MaskedTextBox->TabIndex = 15;
			// 
			// RecordForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(705, 420);
			this->Controls->Add(this->OKPO_MaskedTextBox);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->DATE_CH_CheckBox);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OkButton);
			this->Controls->Add(this->DATE_CH_DateTimePicker);
			this->Controls->Add(this->DT_IZM_DateTimePicker);
			this->Controls->Add(this->DATE_IN_DateTimePicker);
			this->Controls->Add(this->REGN_TextBox);
			this->Controls->Add(this->UER_ComboBox);
			this->Controls->Add(this->PZN_ComboBox);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->REAL_TextBox);
			this->Controls->Add(this->NAME_TextBox);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->NAME_Label);
			this->Controls->Add(this->groupBox1);
			this->MinimumSize = System::Drawing::Size(530, 380);
			this->Name = L"RecordForm";
			this->Text = L"Добавление записи участника расчетов";
			this->Load += gcnew System::EventHandler(this, &RecordForm::RecordForm_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &RecordForm::RecordForm_FormClosing);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void RecordForm_Load(System::Object^  sender, System::EventArgs^  e) {

				// Заполнение выпадающих списков
				RGN_ComboBox->DataSource = NotebooksDataSet->Tables[ "REG" ];
				RGN_ComboBox->DisplayMember = "NAME";
				RGN_ComboBox->ValueMember = "RGN";

				PZN_ComboBox->DataSource = NotebooksDataSet->Tables[ "PZN" ];
				PZN_ComboBox->DisplayMember = "PZNAME";
				PZN_ComboBox->ValueMember = "PZN";

				TNP_ComboBox->DataSource = NotebooksDataSet->Tables[ "TNP" ];
				TNP_ComboBox->DisplayMember = "SHORTNAME";
				TNP_ComboBox->ValueMember = "TNP";

				UER_ComboBox->DataSource = NotebooksDataSet->Tables[ "UER" ];
				UER_ComboBox->DisplayMember = "UERNAME";
				UER_ComboBox->ValueMember = "UER";

				// В режиме редактирования заполняем форму данными
				if (!IsInsertMode) {
					this->Text = "Редактирование записи справочника участников расчетов";
					OkButton->Text = "Сохранить";

					DataTable^ table = NotebooksDataSet->Tables[ "BNKSEEK" ];
					DataRow^ foundrow = table->Rows->Find( NEWNUM );
					
					if (foundrow == nullptr) {

						MessageBox::Show( 
							"Не удалось загрузить данные из справочника",
							"Ошибка заполнения формы",
							MessageBoxButtons::OK,
							MessageBoxIcon::Exclamation,
							MessageBoxDefaultButton::Button1 ); 
						this->DialogResult = ::DialogResult::Cancel;
					} 
					else {
						NAME_TextBox->Text = 
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "NAMEP" ) ] );

						PZN_ComboBox->SelectedValue = foundrow->IsNull( "PZN" )? "NULL" : 
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "PZN" ) ] );

						UER_ComboBox->SelectedValue = 
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "UER" ) ] );

						REAL_TextBox->Text = foundrow->IsNull( "REAL" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "REAL" ) ] );

						NEWNUM_MaskedTextBox->Text = 
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "NEWNUM" ) ] );
						NEWNUM_MaskedTextBox->Enabled = false;

						RKC_MaskedTextBox->Text =  foundrow->IsNull( "RKC" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "RKC" ) ] );

						KSNP_MaskedTextBox->Text =  foundrow->IsNull( "KSNP" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "KSNP" ) ] );

						RGN_ComboBox->SelectedValue = 
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "RGN" ) ] );

						TNP_ComboBox->SelectedValue =  foundrow->IsNull( "TNP" )? "00" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "TNP" ) ] );

						NNP_TextBox->Text =  foundrow->IsNull( "NNP" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "NNP" ) ] );

						IND_MaskedTextBox->Text =  foundrow->IsNull( "IND" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "IND" ) ] );

						ADR_TextBox->Text =  foundrow->IsNull( "ADR" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "ADR" ) ] );

						TELEF_TextBox->Text =  foundrow->IsNull( "TELEF" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "TELEF" ) ] );

						OKPO_MaskedTextBox->Text =  foundrow->IsNull( "OKPO" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "OKPO" ) ] );

						REGN_TextBox->Text =  foundrow->IsNull( "REGN" )? "" :
							safe_cast<String ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "REGN" ) ] );

						DATE_IN_DateTimePicker->Value = DateTime(  
							safe_cast<DateTime ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "DATE_IN" ) ] ) );

						DT_IZM_DateTimePicker->Value = DateTime(  
							safe_cast<DateTime ^>( 
								foundrow->ItemArray[ table->Columns->IndexOf( "DT_IZM" ) ] ) );

						if ( foundrow->IsNull( "DATE_CH" ) ) {
							DATE_CH_CheckBox->Checked = false;
							DATE_CH_DateTimePicker->Visible = false;
						}
						else {
							DATE_CH_CheckBox->Checked = true;
							DATE_CH_DateTimePicker->Visible = true;
							DATE_CH_DateTimePicker->Value = DateTime(  
								safe_cast<DateTime ^>( 
									foundrow->ItemArray[ table->Columns->IndexOf( "DATE_CH" ) ] ) );
						}
					}
				}
			 }
	private: System::Void NAME_TextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
			check_NAME();
		}

	private: System::Void NEWNUM_MaskedTextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
			check_NEWNUM();
		 }

	private: System::Void OkButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

	private: System::Void RecordForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

			 if (this->DialogResult == ::DialogResult::OK) {

				if (NAME_TextBox->Text->Length == 0) {

					MessageBox::Show( 
						"Поле 'Наименование' не может быть пустым.", 
						"Некорректно заполнено поле формы",
						MessageBoxButtons::OK,
						MessageBoxIcon::Exclamation,
						MessageBoxDefaultButton::Button1 );

					e->Cancel = true;
					return;
				}

				if (NEWNUM_MaskedTextBox->Text->Trim()->Length != 9) {

					MessageBox::Show( 
						"Поле 'БИК' должно содержать значение ровно из 9 цифр.", 
						"Некорректно заполнено поле формы",
						MessageBoxButtons::OK,
						MessageBoxIcon::Exclamation,
						MessageBoxDefaultButton::Button1 ); 

					e->Cancel = true;
					return;
				}

				if (IsInsertMode) {
					DataRow^ foundrow = NotebooksDataSet->Tables[ "BNKSEEK" ]->Rows->Find( 
						NEWNUM_MaskedTextBox->Text );
					if (foundrow != nullptr) {

						MessageBox::Show( 
							"В справочнике уже есть запись с таким БИК", 
							"Некорректно заполнено поле формы",
							MessageBoxButtons::OK,
							MessageBoxIcon::Exclamation,
							MessageBoxDefaultButton::Button1 );

						e->Cancel = true;
						return;
					}

					// Выгрузка значений из управляющих элементов
					SQLCommand = "insert into BNKSEEK values ('";
					SQLCommand += REAL_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += PZN_ComboBox->SelectedValue + "', '";
					SQLCommand += UER_ComboBox->SelectedValue + "', '";
					SQLCommand += RGN_ComboBox->SelectedValue + "', '";
					SQLCommand += IND_MaskedTextBox->Text->Trim() + "', '";
					SQLCommand += TNP_ComboBox->SelectedValue + "', '";
					SQLCommand += NNP_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += ADR_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += RKC_MaskedTextBox->Text->Trim() + "', '";
					SQLCommand += NAME_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += NEWNUM_MaskedTextBox->Text->Trim() + "', '";
					SQLCommand += TELEF_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += REGN_TextBox->Text->Replace( "'", "''" )->Trim() + "', '";
					SQLCommand += OKPO_MaskedTextBox->Text->Trim() + "', '";
					SQLCommand += DT_IZM_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000', '";
					SQLCommand += KSNP_MaskedTextBox->Text->Trim() + "', '";
					SQLCommand += DATE_IN_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000', ";
					if (DATE_CH_CheckBox->Checked)
						SQLCommand += "'" + DATE_CH_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000'";
					else
						SQLCommand += "null";
					SQLCommand += ");";

					NEWNUM = NEWNUM_MaskedTextBox->Text->Trim();
				}
				else {
					SQLCommand = "update BNKSEEK set ";
					SQLCommand += "REAL = '" + REAL_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "PZN = '" + PZN_ComboBox->SelectedValue + "', ";
					SQLCommand += "UER = '" + UER_ComboBox->SelectedValue + "', ";
					SQLCommand += "RGN = '" + RGN_ComboBox->SelectedValue + "', ";
					SQLCommand += "IND = '" + IND_MaskedTextBox->Text->Trim() + "', ";
					SQLCommand += "TNP = '" + TNP_ComboBox->SelectedValue + "', ";
					SQLCommand += "NNP = '" + NNP_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "ADR = '" + ADR_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "RKC = '" + RKC_MaskedTextBox->Text->Trim() + "', ";
					SQLCommand += "NAMEP = '" + NAME_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "TELEF = '" + TELEF_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "REGN = '" + REGN_TextBox->Text->Replace( "'", "''" )->Trim() + "', ";
					SQLCommand += "OKPO = '" + OKPO_MaskedTextBox->Text->Trim() + "', ";
					SQLCommand += "DT_IZM = '" + DT_IZM_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000', ";
					SQLCommand += "KSNP = '" + KSNP_MaskedTextBox->Text->Trim() + "', ";
					SQLCommand += "DATE_IN = '" + DATE_IN_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000', ";
					SQLCommand += "DATE_CH = ";
					if (DATE_CH_CheckBox->Checked)
						SQLCommand += "'" + DATE_CH_DateTimePicker->Value.ToShortDateString() + " 00:00:00.000'";
					else
						SQLCommand += "null";
					SQLCommand += " where NEWNUM = '" + NEWNUM_MaskedTextBox->Text + "';";
				}
			}


		 }
};
}

