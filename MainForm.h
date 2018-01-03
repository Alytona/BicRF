#pragma once

# include "ProgressBarForm.h"
# include "RecordForm.h"
# include "TunesForm.h"
# include "IniFile.h"

namespace BicRF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		// Часто используемые строки
		String^ DBServerName, ^ConnectionStringTemplate, ^BicRF_DBName, ^BicRF_DSNName;

		// БИК в текущей строке
		String^ CurrentNEWNUM;
		// Смещение текущей относительно первой видимой записи в DataViewGrid
		int CurrentDGRowOffset;

		// Признак того, что БД загружена
		bool IsDBLoaded;

		CIniFile^ IniFile;


	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  insertToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::Timer^  timer1;




		// Индикатор прогресса
		ProgressBarForm^ rProgressBarForm;

		// Методы, определенные в DBFLoad.cpp
		void createBicRFTable( String^ tablename, String^ specification);
		void createBicRFTables();
		void loadDBFData();
		void loadDBFFile( String^ tablename, int progress_0, int progress_1 );
		void startDBFLoading();

		// Методы, определенные в MainForm.cpp
		void buildFilter();
		void loadDBFromSQLServer();
		void insertRecord();
		void editRecord();
		void deleteRecord();

		// Прочие методы
		String^ createConnectionStringTemplateForDBServer( String^ dbservername ) {
			return gcnew String( "Provider=SQLNCLI.1;Data Source=" + dbservername + 
				";Integrated Security=SSPI;Connect Timeout=5;General Timeout=5;Initial Catalog=" );
		}

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			// Инициализация часто используемых строк
			BicRF_DBName = "BicRF", 
			BicRF_DSNName = "BICRF";
			DBServerName = "localhost\\SQLEXPRESS";
			ConnectionStringTemplate = createConnectionStringTemplateForDBServer( DBServerName );
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Data::Odbc::OdbcCommand^  odbcSelectCommand1;
	protected: 
	private: System::Data::Odbc::OdbcConnection^  odbcConnection1;
	private: System::Data::Odbc::OdbcDataAdapter^  odbcDataAdapter1;
	private: System::Data::OleDb::OleDbCommand^  oleDbCommand1;
	private: System::Data::OleDb::OleDbConnection^  oleDbConnection1;
	private: System::Data::DataSet^  dataSet1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadFromDBFToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  помощьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem1;
	private: System::Data::OleDb::OleDbCommand^  oleDbSelectCommand1;
	private: System::Data::OleDb::OleDbDataAdapter^  oleDbDataAdapter1;
	private: System::Data::OleDb::OleDbConnection^  oleDbConnection2;
	private: System::Data::DataSet^  dataSet2;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Panel^  FilterPanel;
	private: System::Windows::Forms::TextBox^  BICTextBox;
	private: System::Windows::Forms::Label^  FilterLabel;
	private: System::Windows::Forms::CheckBox^  BICCheckBox;
	private: System::Windows::Forms::ComboBox^  TypeComboBox;
	private: System::Windows::Forms::CheckBox^  TypeCheckBox;
	private: System::Windows::Forms::CheckBox^  RegionCheckBox;
	private: System::Windows::Forms::Button^  FilterButton;
	private: System::Windows::Forms::TextBox^  RegionTextBox;
	private: System::Data::DataView^  dataView1;
	private: System::Data::OleDb::OleDbCommand^  oleSelectTypesCommand;
	private: System::Windows::Forms::ToolStripMenuItem^  servicesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  filterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tunesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  измененияToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  insertRecordToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editRecordToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteRecordToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->RegionTextBox = (gcnew System::Windows::Forms::TextBox());
			this->odbcSelectCommand1 = (gcnew System::Data::Odbc::OdbcCommand());
			this->odbcConnection1 = (gcnew System::Data::Odbc::OdbcConnection());
			this->odbcDataAdapter1 = (gcnew System::Data::Odbc::OdbcDataAdapter());
			this->oleDbCommand1 = (gcnew System::Data::OleDb::OleDbCommand());
			this->oleDbConnection1 = (gcnew System::Data::OleDb::OleDbConnection());
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadFromDBFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->измененияToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->insertRecordToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editRecordToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteRecordToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->servicesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->filterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tunesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->помощьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->оПрограммеToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oleDbSelectCommand1 = (gcnew System::Data::OleDb::OleDbCommand());
			this->oleDbConnection2 = (gcnew System::Data::OleDb::OleDbConnection());
			this->oleDbDataAdapter1 = (gcnew System::Data::OleDb::OleDbDataAdapter());
			this->dataSet2 = (gcnew System::Data::DataSet());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->insertToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FilterPanel = (gcnew System::Windows::Forms::Panel());
			this->FilterButton = (gcnew System::Windows::Forms::Button());
			this->TypeCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->RegionCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->BICCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->BICTextBox = (gcnew System::Windows::Forms::TextBox());
			this->FilterLabel = (gcnew System::Windows::Forms::Label());
			this->dataView1 = (gcnew System::Data::DataView());
			this->oleSelectTypesCommand = (gcnew System::Data::OleDb::OleDbCommand());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->contextMenuStrip1->SuspendLayout();
			this->FilterPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataView1))->BeginInit();
			this->SuspendLayout();
			// 
			// RegionTextBox
			// 
			this->RegionTextBox->Location = System::Drawing::Point(229, 25);
			this->RegionTextBox->MinimumSize = System::Drawing::Size(100, 21);
			this->RegionTextBox->Name = L"RegionTextBox";
			this->RegionTextBox->Size = System::Drawing::Size(124, 20);
			this->RegionTextBox->TabIndex = 4;
			this->RegionTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::RegionTextBox_TextChanged);
			// 
			// odbcSelectCommand1
			// 
			this->odbcSelectCommand1->CommandText = L"SELECT PZN.*\r\nFROM PZN";
			this->odbcSelectCommand1->Connection = this->odbcConnection1;
			// 
			// odbcConnection1
			// 
			this->odbcConnection1->ConnectionString = L"Dsn=BICRF";
			// 
			// odbcDataAdapter1
			// 
			this->odbcDataAdapter1->SelectCommand = this->odbcSelectCommand1;
			cli::array< System::Data::Common::DataColumnMapping^ >^ __mcTemp__1 = gcnew cli::array< System::Data::Common::DataColumnMapping^  >(6) {(gcnew System::Data::Common::DataColumnMapping(L"VKEY", 
				L"VKEY")), (gcnew System::Data::Common::DataColumnMapping(L"PZN", L"PZN")), (gcnew System::Data::Common::DataColumnMapping(L"IMY", 
				L"IMY")), (gcnew System::Data::Common::DataColumnMapping(L"NAME", L"NAME")), (gcnew System::Data::Common::DataColumnMapping(L"CB_DATE", 
				L"CB_DATE")), (gcnew System::Data::Common::DataColumnMapping(L"CE_DATE", L"CE_DATE"))};
			this->odbcDataAdapter1->TableMappings->AddRange(gcnew cli::array< System::Data::Common::DataTableMapping^  >(1) {(gcnew System::Data::Common::DataTableMapping(L"Table", 
				L"Table", __mcTemp__1))});
			// 
			// oleDbCommand1
			// 
			this->oleDbCommand1->CommandText = L"drop database BicRF; create database BicRF;";
			this->oleDbCommand1->Connection = this->oleDbConnection1;
			// 
			// oleDbConnection1
			// 
			this->oleDbConnection1->ConnectionString = L"Provider=SQLNCLI11;Data Source=STATIONARY\\SQLEXPRESS;Integrated Security=SSPI;Ini" 
				L"tial Catalog=BicRF;Connect Timeout=5;General Timeout=5";
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"NewDataSet";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->файлToolStripMenuItem, 
				this->измененияToolStripMenuItem, this->servicesToolStripMenuItem, this->справкаToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(698, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->loadFromDBFToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// loadFromDBFToolStripMenuItem
			// 
			this->loadFromDBFToolStripMenuItem->Name = L"loadFromDBFToolStripMenuItem";
			this->loadFromDBFToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->loadFromDBFToolStripMenuItem->Text = L"Загрузка из DBF";
			this->loadFromDBFToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadFromDBFToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->exitToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->exitToolStripMenuItem->Text = L"Выход";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// измененияToolStripMenuItem
			// 
			this->измененияToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->insertRecordToolStripMenuItem, 
				this->editRecordToolStripMenuItem, this->deleteRecordToolStripMenuItem});
			this->измененияToolStripMenuItem->Name = L"измененияToolStripMenuItem";
			this->измененияToolStripMenuItem->Size = System::Drawing::Size(81, 20);
			this->измененияToolStripMenuItem->Text = L"Изменения";
			// 
			// insertRecordToolStripMenuItem
			// 
			this->insertRecordToolStripMenuItem->Name = L"insertRecordToolStripMenuItem";
			this->insertRecordToolStripMenuItem->Size = System::Drawing::Size(168, 22);
			this->insertRecordToolStripMenuItem->Text = L"Добавить запись";
			this->insertRecordToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::insertRecordToolStripMenuItem_Click);
			// 
			// editRecordToolStripMenuItem
			// 
			this->editRecordToolStripMenuItem->Name = L"editRecordToolStripMenuItem";
			this->editRecordToolStripMenuItem->Size = System::Drawing::Size(168, 22);
			this->editRecordToolStripMenuItem->Text = L"Изменить запись";
			this->editRecordToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::editRecordToolStripMenuItem_Click);
			// 
			// deleteRecordToolStripMenuItem
			// 
			this->deleteRecordToolStripMenuItem->Name = L"deleteRecordToolStripMenuItem";
			this->deleteRecordToolStripMenuItem->Size = System::Drawing::Size(168, 22);
			this->deleteRecordToolStripMenuItem->Text = L"Удалить запись";
			this->deleteRecordToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteRecordToolStripMenuItem_Click);
			// 
			// servicesToolStripMenuItem
			// 
			this->servicesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->filterToolStripMenuItem, 
				this->tunesToolStripMenuItem});
			this->servicesToolStripMenuItem->Name = L"servicesToolStripMenuItem";
			this->servicesToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->servicesToolStripMenuItem->Text = L"Сервис";
			// 
			// filterToolStripMenuItem
			// 
			this->filterToolStripMenuItem->Name = L"filterToolStripMenuItem";
			this->filterToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
			this->filterToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->filterToolStripMenuItem->Text = L"Панель фильтра";
			this->filterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::filterToolStripMenuItem_Click);
			// 
			// tunesToolStripMenuItem
			// 
			this->tunesToolStripMenuItem->Name = L"tunesToolStripMenuItem";
			this->tunesToolStripMenuItem->Size = System::Drawing::Size(205, 22);
			this->tunesToolStripMenuItem->Text = L"Настройки";
			this->tunesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::tunesToolStripMenuItem_Click_1);
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->помощьToolStripMenuItem, 
				this->оПрограммеToolStripMenuItem, this->оПрограммеToolStripMenuItem1});
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->справкаToolStripMenuItem->Text = L"Справка";
			// 
			// помощьToolStripMenuItem
			// 
			this->помощьToolStripMenuItem->Name = L"помощьToolStripMenuItem";
			this->помощьToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F1;
			this->помощьToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->помощьToolStripMenuItem->Text = L"Помощь";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(146, 6);
			// 
			// оПрограммеToolStripMenuItem1
			// 
			this->оПрограммеToolStripMenuItem1->Name = L"оПрограммеToolStripMenuItem1";
			this->оПрограммеToolStripMenuItem1->Size = System::Drawing::Size(149, 22);
			this->оПрограммеToolStripMenuItem1->Text = L"О программе";
			// 
			// oleDbSelectCommand1
			// 
			this->oleDbSelectCommand1->CommandText = resources->GetString(L"oleDbSelectCommand1.CommandText");
			this->oleDbSelectCommand1->Connection = this->oleDbConnection2;
			// 
			// oleDbDataAdapter1
			// 
			this->oleDbDataAdapter1->SelectCommand = this->oleDbSelectCommand1;
			cli::array< System::Data::Common::DataColumnMapping^ >^ __mcTemp__2 = gcnew cli::array< System::Data::Common::DataColumnMapping^  >(22) {(gcnew System::Data::Common::DataColumnMapping(L"REAL", 
				L"REAL")), (gcnew System::Data::Common::DataColumnMapping(L"IND", L"IND")), (gcnew System::Data::Common::DataColumnMapping(L"NNP", 
				L"NNP")), (gcnew System::Data::Common::DataColumnMapping(L"ADR", L"ADR")), (gcnew System::Data::Common::DataColumnMapping(L"RKC", 
				L"RKC")), (gcnew System::Data::Common::DataColumnMapping(L"NAMEP", L"NAMEP")), (gcnew System::Data::Common::DataColumnMapping(L"NEWNUM", 
				L"NEWNUM")), (gcnew System::Data::Common::DataColumnMapping(L"TELEF", L"TELEF")), (gcnew System::Data::Common::DataColumnMapping(L"REGN", 
				L"REGN")), (gcnew System::Data::Common::DataColumnMapping(L"OKPO", L"OKPO")), (gcnew System::Data::Common::DataColumnMapping(L"DT_IZM", 
				L"DT_IZM")), (gcnew System::Data::Common::DataColumnMapping(L"KSNP", L"KSNP")), (gcnew System::Data::Common::DataColumnMapping(L"DATE_IN", 
				L"DATE_IN")), (gcnew System::Data::Common::DataColumnMapping(L"DATE_CH", L"DATE_CH")), (gcnew System::Data::Common::DataColumnMapping(L"NAME", 
				L"NAME")), (gcnew System::Data::Common::DataColumnMapping(L"Expr1", L"Expr1")), (gcnew System::Data::Common::DataColumnMapping(L"CENTER", 
				L"CENTER")), (gcnew System::Data::Common::DataColumnMapping(L"IMY", L"IMY")), (gcnew System::Data::Common::DataColumnMapping(L"NAMET", 
				L"NAMET")), (gcnew System::Data::Common::DataColumnMapping(L"FULLNAME", L"FULLNAME")), (gcnew System::Data::Common::DataColumnMapping(L"SHORTNAME", 
				L"SHORTNAME")), (gcnew System::Data::Common::DataColumnMapping(L"UERNAME", L"UERNAME"))};
			this->oleDbDataAdapter1->TableMappings->AddRange(gcnew cli::array< System::Data::Common::DataTableMapping^  >(1) {(gcnew System::Data::Common::DataTableMapping(L"Table", 
				L"BNKSEEK", __mcTemp__2))});
			// 
			// dataSet2
			// 
			this->dataSet2->DataSetName = L"NewDataSet";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->ContextMenuStrip = this->contextMenuStrip1;
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dataGridView1->Location = System::Drawing::Point(13, 88);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowTemplate->ReadOnly = true;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(673, 368);
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->Sorted += gcnew System::EventHandler(this, &MainForm::dataGridView1_Sorted);
			this->dataGridView1->Click += gcnew System::EventHandler(this, &MainForm::dataGridView1_Click);
			this->dataGridView1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyDown);
			this->dataGridView1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridView1_KeyUp);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->insertToolStripMenuItem, 
				this->editToolStripMenuItem, this->deleteToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(155, 70);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::contextMenuStrip1_Opening);
			// 
			// insertToolStripMenuItem
			// 
			this->insertToolStripMenuItem->Name = L"insertToolStripMenuItem";
			this->insertToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->insertToolStripMenuItem->Text = L"Добавить";
			this->insertToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::insertToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->editToolStripMenuItem->Text = L"Редактировать";
			this->editToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::editToolStripMenuItem_Click);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->deleteToolStripMenuItem->Text = L"Удалить";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteToolStripMenuItem_Click);
			// 
			// FilterPanel
			// 
			this->FilterPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->FilterPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->FilterPanel->Controls->Add(this->FilterButton);
			this->FilterPanel->Controls->Add(this->TypeCheckBox);
			this->FilterPanel->Controls->Add(this->RegionCheckBox);
			this->FilterPanel->Controls->Add(this->BICCheckBox);
			this->FilterPanel->Controls->Add(this->TypeComboBox);
			this->FilterPanel->Controls->Add(this->RegionTextBox);
			this->FilterPanel->Controls->Add(this->BICTextBox);
			this->FilterPanel->Controls->Add(this->FilterLabel);
			this->FilterPanel->Location = System::Drawing::Point(13, 28);
			this->FilterPanel->Name = L"FilterPanel";
			this->FilterPanel->Size = System::Drawing::Size(673, 54);
			this->FilterPanel->TabIndex = 3;
			this->FilterPanel->SizeChanged += gcnew System::EventHandler(this, &MainForm::FilterPanel_SizeChanged);
			// 
			// FilterButton
			// 
			this->FilterButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->FilterButton->Location = System::Drawing::Point(643, 8);
			this->FilterButton->Name = L"FilterButton";
			this->FilterButton->Size = System::Drawing::Size(25, 23);
			this->FilterButton->TabIndex = 10;
			this->FilterButton->Text = L"^";
			this->FilterButton->UseVisualStyleBackColor = true;
			this->FilterButton->Visible = false;
			// 
			// TypeCheckBox
			// 
			this->TypeCheckBox->Location = System::Drawing::Point(370, 8);
			this->TypeCheckBox->Margin = System::Windows::Forms::Padding(0);
			this->TypeCheckBox->Name = L"TypeCheckBox";
			this->TypeCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TypeCheckBox->Size = System::Drawing::Size(168, 15);
			this->TypeCheckBox->TabIndex = 9;
			this->TypeCheckBox->Text = L"Тип";
			this->TypeCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->TypeCheckBox->UseVisualStyleBackColor = true;
			this->TypeCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::TypeCheckBox_CheckedChanged);
			// 
			// RegionCheckBox
			// 
			this->RegionCheckBox->Location = System::Drawing::Point(229, 8);
			this->RegionCheckBox->Margin = System::Windows::Forms::Padding(0);
			this->RegionCheckBox->Name = L"RegionCheckBox";
			this->RegionCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->RegionCheckBox->Size = System::Drawing::Size(124, 15);
			this->RegionCheckBox->TabIndex = 8;
			this->RegionCheckBox->Text = L"Регион";
			this->RegionCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->RegionCheckBox->UseVisualStyleBackColor = true;
			this->RegionCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::RegionCheckBox_CheckedChanged);
			// 
			// BICCheckBox
			// 
			this->BICCheckBox->Location = System::Drawing::Point(89, 8);
			this->BICCheckBox->Margin = System::Windows::Forms::Padding(0);
			this->BICCheckBox->Name = L"BICCheckBox";
			this->BICCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->BICCheckBox->Size = System::Drawing::Size(124, 15);
			this->BICCheckBox->TabIndex = 7;
			this->BICCheckBox->Text = L"БИК";
			this->BICCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->BICCheckBox->UseVisualStyleBackColor = true;
			this->BICCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::BICCheckBox_CheckedChanged);
			// 
			// TypeComboBox
			// 
			this->TypeComboBox->FormattingEnabled = true;
			this->TypeComboBox->Location = System::Drawing::Point(369, 25);
			this->TypeComboBox->MinimumSize = System::Drawing::Size(100, 0);
			this->TypeComboBox->Name = L"TypeComboBox";
			this->TypeComboBox->Size = System::Drawing::Size(168, 21);
			this->TypeComboBox->Sorted = true;
			this->TypeComboBox->TabIndex = 6;
			this->TypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::TypeComboBox_SelectedIndexChanged);
			// 
			// BICTextBox
			// 
			this->BICTextBox->Location = System::Drawing::Point(89, 25);
			this->BICTextBox->MinimumSize = System::Drawing::Size(100, 20);
			this->BICTextBox->Name = L"BICTextBox";
			this->BICTextBox->Size = System::Drawing::Size(124, 20);
			this->BICTextBox->TabIndex = 2;
			this->BICTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::BICTextBox_TextChanged);
			// 
			// FilterLabel
			// 
			this->FilterLabel->AutoSize = true;
			this->FilterLabel->Location = System::Drawing::Point(8, 8);
			this->FilterLabel->Name = L"FilterLabel";
			this->FilterLabel->Size = System::Drawing::Size(65, 13);
			this->FilterLabel->TabIndex = 0;
			this->FilterLabel->Text = L"Фильтр по:";
			// 
			// oleSelectTypesCommand
			// 
			this->oleSelectTypesCommand->CommandText = L"SELECT        PZN, NAME + \' (\' + IMY + \')\' AS PZNAME\r\nFROM            PZN";
			this->oleSelectTypesCommand->Connection = this->oleDbConnection2;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(698, 468);
			this->Controls->Add(this->FilterPanel);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Справочник БИК РФ";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->contextMenuStrip1->ResumeLayout(false);
			this->FilterPanel->ResumeLayout(false);
			this->FilterPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {

			IniFile = gcnew CIniFile( ".\\BicRF.ini" );
			DBServerName = IniFile->getValue( "DBConnection:DBServerName" );
			ConnectionStringTemplate = createConnectionStringTemplateForDBServer( DBServerName );

			// По умолчанию панель фильтра прячем
			FilterPanel->Visible = false;
			dataGridView1->Bounds = Drawing::Rectangle( 
				dataGridView1->Location.X, 28, dataGridView1->Size.Width, dataGridView1->Size.Height + FilterPanel->Size.Height + 6 );
		 }
// ------------------------------------------------------------------

private: System::Void loadFromDBFToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			startDBFLoading();
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();

			 delete IniFile;
		 }

// Реакция на изменение ширины панели фильтра
private: System::Void FilterPanel_SizeChanged(System::Object^  sender, System::EventArgs^  e) {

			resizeFilterFields();
		 }

// Реакции на включение-выключение параметров фильтра и на изменение их значений  
private: System::Void BICTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (BICCheckBox->Checked) {
				 buildFilter();
			 }
		 }
private: System::Void BICCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			buildFilter();
		 }
private: System::Void RegionTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (RegionCheckBox->Checked) {
				 buildFilter();
			 }
		 }
private: System::Void RegionCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			buildFilter();
		 }
private: System::Void TypeComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (TypeCheckBox->Checked) {
				 buildFilter();
			 }
		 }
private: System::Void TypeCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			buildFilter();
		 }
// ------------------------------------------------------------------

private: System::Void filterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			// Управление видимостью панели фильтра
			if (filterToolStripMenuItem->Checked) {
				// Прячем панель
				FilterPanel->Visible = false;
				// Изменяем размер таблицы со справочником
				dataGridView1->Bounds = Drawing::Rectangle( 
				dataGridView1->Location.X, 28, dataGridView1->Size.Width, dataGridView1->Size.Height + FilterPanel->Size.Height + 6 );
			}
			else {
				// Изменяем размер таблицы со справочником
				dataGridView1->Size = Drawing::Size( dataGridView1->Size.Width, dataGridView1->Size.Height - FilterPanel->Size.Height - 6 );
				dataGridView1->Location = Drawing::Point( dataGridView1->Location.X, 28 + FilterPanel->Size.Height + 6 );
				// Показываем панель
				FilterPanel->Visible = true;
			}

			 // Меняем флаг на пункте меню "Фильтр"
			 filterToolStripMenuItem->Checked = !filterToolStripMenuItem->Checked;
		 }
// ------------------------------------------------------------------

private: System::Void deleteRecordToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			deleteRecord();
		 }
// ------------------------------------------------------------------

private: System::Void insertRecordToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			insertRecord();
		 }
// ------------------------------------------------------------------

private: System::Void editRecordToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			editRecord();
		 }
// ------------------------------------------------------------------

private: System::Void tunesToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {

			 DBServerName = IniFile->getValue( "DBConnection:DBServerName" );

			 TunesForm^ rTunesForm = gcnew TunesForm( DBServerName, Point( 
				servicesToolStripMenuItem->Bounds.Location.X + this->Location.X, 
				servicesToolStripMenuItem->Bounds.Location.Y + this->Location.Y + 50 ) );

			if (rTunesForm->ShowDialog() == ::DialogResult::OK) {
				
				// Сохранение настроек
				if (DBServerName != rTunesForm->DBServerName) {

					DBServerName = rTunesForm->DBServerName;
					IniFile->setValue( "DBConnection:DBServerName", DBServerName );

					ConnectionStringTemplate = createConnectionStringTemplateForDBServer( DBServerName );

					// Если изменяется имя SQL-сервера, нужно заново загрузить с него данные
					loadDBFromSQLServer();
				}
			}
			delete rTunesForm;
		 }
// ------------------------------------------------------------------

private: System::Void resizeFilterFields() {
			
			// Пропорциональное изменение ширин полей фильтра, 
			// пропорции вычисляются исходя из минимальных ширин

			// Вычисляем ширину полей фильтра - текущую (полную) и минимальную
			int w = FilterButton->Location.X - BICTextBox->Location.X - 16*3,
				w0 = (BICTextBox->MinimumSize.Width + RegionTextBox->MinimumSize.Width + TypeComboBox->MinimumSize.Width);

			//	Пропорции минимальных ширин полей фильтра (w1+w2+w3 = 1)
			float w1 = (float)(BICTextBox->MinimumSize.Width)/w0, 
				w2 = (float)(RegionTextBox->MinimumSize.Width)/w0, 
				w3 = (float)(TypeComboBox->MinimumSize.Width)/w0;

			// Ширина каждого поля фильтра рассчитывается как часть текущей полной ширины
			BICTextBox->Size = Drawing::Size( safe_cast<int>( w1*w ), BICTextBox->Size.Height );
			BICCheckBox->Size = Drawing::Size( safe_cast<int>( w1*w ), BICCheckBox->Size.Height );
			RegionTextBox->Size = Drawing::Size( safe_cast<int>( w2*w ), RegionTextBox->Size.Height );
			RegionCheckBox->Size = Drawing::Size( safe_cast<int>( w2*w ), RegionCheckBox->Size.Height );
			TypeComboBox->Size = Drawing::Size( safe_cast<int>( w3*w ), TypeComboBox->Size.Height );
			TypeCheckBox->Size = Drawing::Size( safe_cast<int>( w3*w ), TypeCheckBox->Size.Height );

			// Сдвигаем поля фильтра с учетом изменившихся ширин
			RegionTextBox->Location = Drawing::Point( BICTextBox->Location.X + BICTextBox->Size.Width + 16, RegionTextBox->Location.Y );
			RegionCheckBox->Location = Drawing::Point( RegionTextBox->Location.X, RegionCheckBox->Location.Y );
			TypeComboBox->Location = Drawing::Point( RegionTextBox->Location.X + RegionTextBox->Size.Width + 16, TypeComboBox->Location.Y );
			TypeCheckBox->Location = Drawing::Point( TypeComboBox->Location.X, TypeCheckBox->Location.Y );
		 }
// ------------------------------------------------------------------

private: System::Void dataGridView1_Sorted(System::Object^  sender, System::EventArgs^  e) {

			 // После изменения порядка сортировки ищем в DataViewGrid строку с текущим БИК и выбираем ее.
			 for each (DataGridViewRow^ row in dataGridView1->Rows) {
				 if ( row->Cells[ "NEWNUM" ]->Value->ToString() == CurrentNEWNUM ) {

					 int fdc = dataGridView1->FirstDisplayedCell->ColumnIndex;
					 dataGridView1->FirstDisplayedCell = row->Cells[ fdc ];
					 dataGridView1->CurrentCell = row->Cells[ dataGridView1->CurrentCell->ColumnIndex ];

					 // Восстанавливаем, если возможно, смещение текущей от начала DataViewGrid
					 if (dataGridView1->CurrentCell->RowIndex - CurrentDGRowOffset >= 0)
						dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->CurrentCell->RowIndex - CurrentDGRowOffset;
					 else
						dataGridView1->FirstDisplayedScrollingRowIndex = 0;

					 break;
				 }
			 }
		 }
// ------------------------------------------------------------------

private: System::Void dataGridView1_Click(System::Object^  sender, System::EventArgs^  e) {

			// При нажатии на заголовок колонки происходит изменение сортировки, 
			// отлавливаем это нажатие и запоминаем БИК, соответствующий текущей, и положение текущей в DataViewGrid
			
			// Конвертирование координат мыши в координаты на DataViewGrid
			Point mousepoint = dataGridView1->PointToClient( Point ( MousePosition.X, MousePosition.Y ) );
			// Определение строки DataViewGrid, в которой произошло нажатие
			DataGridView::HitTestInfo^ htinfo = dataGridView1->HitTest( mousepoint.X, mousepoint.Y );

			// Если клик произошел на заголовке колонки, запоминаем положение текущей
			if (htinfo->RowIndex == -1 && htinfo->ColumnIndex != -1) {
				CurrentNEWNUM = safe_cast<String^>( dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value ); 
				CurrentDGRowOffset = dataGridView1->CurrentRow->Index - dataGridView1->FirstDisplayedScrollingRowIndex;
			}
		}
// ------------------------------------------------------------------

private: System::Void dataGridView1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			
			if (!e->Shift && !e->Alt && !e->Control) {
			
				switch ( e->KeyCode ) {
					case Keys::Insert :
						insertRecord();
						break;

					case Keys::Delete :
						deleteRecord();
						break;

					case Keys::Enter :
						editRecord();
						break;
				}
			}
		}
// ------------------------------------------------------------------

private: System::Void dataGridView1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (!e->Shift && !e->Alt && !e->Control) {
				switch ( e->KeyCode ) {
					case Keys::Enter :		// Подавляем обработку нажатия Enter, т.к. в противном случае происходит смещение текущей на строку ниже
						e->Handled = true;
						break;
				}
			}
		}
// ------------------------------------------------------------------

private: System::Void insertToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 insertRecord();
		 }
private: System::Void editToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 editRecord();
		 }
private: System::Void deleteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 deleteRecord();
		 }
// ------------------------------------------------------------------

private: System::Void contextMenuStrip1_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

				// Конвертирование координат всплывающего меню в координаты на DataViewGrid
				Point menupoint = dataGridView1->PointToClient( Point ( contextMenuStrip1->Location.X, contextMenuStrip1->Location.Y ) );
				// Определение строки DataViewGrid, на которой произошел вызов меню
				DataGridView::HitTestInfo^ htinfo = dataGridView1->HitTest( menupoint.X, menupoint.Y );

				if (htinfo->RowIndex != -1 && htinfo->ColumnIndex != -1)
					dataGridView1->CurrentCell = dataGridView1[ htinfo->ColumnIndex, htinfo->RowIndex ];
				else
					e->Cancel = true;	// Подавление появления меню в заголовках колонок и строк
		 }
// ------------------------------------------------------------------

// Загрузка данных откладывается до момента, когда будет показана форма
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			// Загрузка данных из БД
			loadDBFromSQLServer();

			// Пересчет ширин полей фильтра
			resizeFilterFields();

			timer1->Enabled = false;
		}
// ------------------------------------------------------------------

};
}

