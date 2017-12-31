# include "stdafx.h"

# include "MainForm.h"

using namespace System;

// Установка фильтра справочника в соответствии со значениями панели фильтра
void BicRF::MainForm::buildFilter() {
	String ^newfilter = "";

	if (BICCheckBox->Checked)
		 newfilter += "NEWNUM like '%" + BICTextBox->Text->Trim() + "%'";

	if (RegionCheckBox->Checked) {
		if (newfilter->Length > 0) newfilter += " and ";
		newfilter += "REGNAME like '%" + RegionTextBox->Text->Trim() + "%'";
	}

	if (TypeCheckBox->Checked) {
		if (newfilter->Length > 0) newfilter += " and ";
		newfilter += "PZN = '" + TypeComboBox->SelectedValue + "'";
	}

	// Включаем подготовленный фильтр
	try {
		dataView1->RowFilter = newfilter;

	} catch (Exception ^e) {
		MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
			"\n Фильтр: " + newfilter + ",\n возможно, это синтаксическая ошибка" ,
			"Ошибка включения фильтра справочника",
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
	}
}
// ------------------------------------------------------------------

// Загрузка данных из таблиц SQL-сервера
void BicRF::MainForm::loadDBFromSQLServer() {

	IsDBLoaded = false;

	dataSet2->Reset();
	dataGridView1->Enabled = false;

	try {

		// Пытаемся соединиться с SQL-сервером
		if (oleDbConnection2->State == ConnectionState::Open)
			oleDbConnection2->Close();
		oleDbConnection2->ConnectionString = ConnectionStringTemplate + "master";
		oleDbConnection2->Open();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message + "\n Возможно, отсутствует доступ к SQL-серверу или его служба не запущена." 
			+ "\n Возможно, следует изменить имя SQL-сервера в настройках программы.",
			"Не удалось подключиться к SQL-серверу " + DBServerName,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
	}

	if (oleDbConnection2->State == ConnectionState::Open)
	{
		try {

			// После успешного соединения с SQL-сервером пытаемся подключить БД BicRF 
			oleDbConnection2->Close();
			oleDbConnection2->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
			oleDbConnection2->Open();

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( e->Source + " > " + e->Message + "\n Возможно, следует выполнить загрузку БД из DBF-файлов. ",
				"Не удалось выполнить соединение с БД " + BicRF_DBName + " (SQL-сервер " + DBServerName + ").",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}
	}

	if (oleDbConnection2->State ==  ConnectionState::Open)
	{
		try {
			// Загрузка справочника участников из БД
			oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
			oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

			// Построение первичного ключа
			array<System::Data::DataColumn ^, 1> ^keys = gcnew array<System::Data::DataColumn ^, 1> ( 1 );
			keys[0] = dataSet2->Tables[ "BNKSEEK" ]->Columns[ "NEWNUM" ];
			dataSet2->Tables[ "BNKSEEK" ]->PrimaryKey = keys;

			oleDbDataAdapter1->SelectCommand = oleSelectTypesCommand;

			// Загрузка справочников из БД для выпадающих списков
			oleSelectTypesCommand->CommandText = 
				"select PZN, NAME + isnull( ' (' + rtrim( IMY ) + ')', '' ) as PZNAME from PZN order by 2";
			oleDbDataAdapter1->Fill( dataSet2, "PZN" );

			oleSelectTypesCommand->CommandText = "select RGN, NAME from REG";
			oleDbDataAdapter1->Fill( dataSet2, "REG" );

			oleSelectTypesCommand->CommandText = "select UER, UERNAME from UER";
			oleDbDataAdapter1->Fill( dataSet2, "UER" );

			oleSelectTypesCommand->CommandText = "select TNP, SHORTNAME from TNP";
			oleDbDataAdapter1->Fill( dataSet2, "TNP" );

			IsDBLoaded = true;

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( e->Source + " > " + e->Message,
				"Не удалось загрузить БД из " + DBServerName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
				"\n Возможно, формат БД устарел и следует выполнить загрузку из DBF-файлов",
				"Ошибка загрузки данных из БД " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );
		}

		if (IsDBLoaded)
		{
			// Подключаем DataView, чтобы иметь возможность фильтровать справочник
			dataView1->Table = dataSet2->Tables[ "BNKSEEK" ];

			// Подключаем DataGridView
			dataGridView1->AutoGenerateColumns = true;
			dataGridView1->DataSource = dataView1;

			try {

				// Настройка заголовков столбцов таблицы
				DataGridViewColumn^ column;

				column = dataGridView1->Columns[ "REAL" ];
				column->HeaderText = "Допустимость";
				column->ToolTipText = "Код контроля допустимости проведения  расчетных операций";

				column = dataGridView1->Columns[ "IND" ];
				column->HeaderText = "Индекс";
				column->ToolTipText = "Почтовый индекс";

				column = dataGridView1->Columns[ "NPNAME" ];
				column->HeaderText = "Населенный пункт";
				column->ToolTipText = "Наименование населенного пункта, в котором размещен участник";

				column = dataGridView1->Columns[ "ADR" ];
				column->HeaderText = "Адрес";
				column->ToolTipText = "Адрес участника расчетов";

				column = dataGridView1->Columns[ "RKC" ];
				column->HeaderText = "БИК РКЦ";
				column->ToolTipText = "БИК РКЦ или ГРКЦ";

				column = dataGridView1->Columns[ "KSNP" ];
				column->HeaderText = "Номер счета";
				column->ToolTipText = "Номер корреспондентского счета участника расчетов";

				column = dataGridView1->Columns[ "REGN" ];
				column->HeaderText = "Рег. номер";
				column->ToolTipText = "Регистрационный номер";

				column = dataGridView1->Columns[ "OKPO" ];
				column->HeaderText = "ОКПО";
				column->ToolTipText = "Код ОКПО";

				column = dataGridView1->Columns[ "DATE_IN" ];
				column->HeaderText = "Дата включения";
				column->ToolTipText = "Дата включения информации об участнике расчетов в ЭБД";

				column = dataGridView1->Columns[ "DATE_CH" ];
				column->HeaderText = "Дата контроля";
				column->ToolTipText = "";

				column = dataGridView1->Columns[ "DT_IZM" ];
				column->HeaderText = "Дата изменения";
				column->ToolTipText = "Дата последнего изменения записи";

				column = dataGridView1->Columns[ "UERNAME" ];
				column->HeaderText = "Тип участника ЭР";
				column->ToolTipText = "Тип участника (пользователя) системы электронных расчетов";

				column = dataGridView1->Columns[ "NAMEP" ];
				column->HeaderText = "Наименование";
				column->ToolTipText = "Наименование участника расчетов";

				column = dataGridView1->Columns[ "TELEF" ];
				column->HeaderText = "Телефоны";
				column->ToolTipText = "Номера телефонов";

				column = dataGridView1->Columns[ "NEWNUM" ];
				column->HeaderText = "БИК";
				column->ToolTipText = "Банковский идентификационный код участника";

				column = dataGridView1->Columns[ "IMY" ];
				column->HeaderText = "Тип";
				column->ToolTipText = "Тип участника";

				column = dataGridView1->Columns[ "REGNAME" ];
				column->HeaderText = "Регион";
				column->ToolTipText = "Регион РФ, в котором размещен участник";

				// Скрываем колонки с внешними ключами
				dataGridView1->Columns[ "NNP" ]->Visible = false;
				dataGridView1->Columns[ "PZN" ]->Visible = false;
				dataGridView1->Columns[ "TNP" ]->Visible = false;
				dataGridView1->Columns[ "RGN" ]->Visible = false;
				dataGridView1->Columns[ "UER" ]->Visible = false;

			} catch (Exception ^e) {
				MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
					"\n Возможно, формат БД устарел и следует выполнить загрузку из DBF-файлов",
					"Ошибка настройки колонок справочника",
					MessageBoxButtons::OK, MessageBoxIcon::Stop,
					MessageBoxDefaultButton::Button1 );
			}

			// Заполнение выпадающего списка типов в панели фильтра
			try {
				TypeComboBox->DataSource = dataSet2->Tables[ "PZN" ];
				TypeComboBox->DisplayMember = "PZNAME";
				TypeComboBox->ValueMember = "PZN";
			} catch (Exception ^e) {
				MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
					"\n Возможно, формат БД устарел и следует выполнить загрузку из DBF-файлов",
					"Ошибка настройки колонок справочника",
					MessageBoxButtons::OK, MessageBoxIcon::Stop,
					MessageBoxDefaultButton::Button1 );
			}
		}
	}

	dataGridView1->Enabled = true;
}
// ------------------------------------------------------------------

// Добавление записи
void BicRF::MainForm::insertRecord() {

	RecordForm^ rRecordForm = gcnew RecordForm( dataSet2, "" );
							
	if (rRecordForm->ShowDialog() == ::DialogResult::OK) {

		try {

			// Переоткрываем соединение, если не открыто
			if (oleDbCommand1->Connection->State != ConnectionState::Open) {
				oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
				oleDbCommand1->Connection->Open();
			}

			oleDbCommand1->CommandText = rRecordForm->getSQLCommand();

			// Выполняем добавление записи в БД
			oleDbCommand1->ExecuteNonQuery();

			// Запоминаем смещение текущей относительно первой видимой записи
			CurrentDGRowOffset = dataGridView1->CurrentRow->Index - dataGridView1->FirstDisplayedScrollingRowIndex;

			// Зачитываем справочник заново
			oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
			dataSet2->Tables[ "BNKSEEK" ]->Clear();
			oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

			// Позиционирование на свежедобавленную запись
			for each (DataGridViewRow^ row in dataGridView1->Rows) {
				if ( row->Cells[ "NEWNUM" ]->Value->ToString() == rRecordForm->getNEWNUM() ) {

					int fdc = dataGridView1->FirstDisplayedCell->ColumnIndex;
					dataGridView1->FirstDisplayedCell = row->Cells[ fdc ];

					dataGridView1->CurrentCell = row->Cells[ dataGridView1->CurrentCell->ColumnIndex ];

					if (dataGridView1->CurrentCell->RowIndex - CurrentDGRowOffset >= 0)
						dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->CurrentCell->RowIndex - CurrentDGRowOffset;
					else
						dataGridView1->FirstDisplayedScrollingRowIndex = 0;

					break;
				}
			}

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message,
				"Ошибка добавления записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "Возникла неизвестная ошибка при добавлении записи справочника",
				"Ошибка добавления записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		}
	}

	delete rRecordForm;
}
// ------------------------------------------------------------------

// Изменение записи
void BicRF::MainForm::editRecord() {

	// Если справочник не пуст
	if (dataGridView1->Rows->Count > 0)
	{
		RecordForm^ rRecordForm = nullptr;

		try {
			rRecordForm = gcnew RecordForm( 
				dataSet2, 
				dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() );
							
			if (rRecordForm->ShowDialog() == ::DialogResult::OK) {

				// Запоминаем положение текущей
				int currentrow_index = dataGridView1->CurrentCell->RowIndex,
					currentcol_index = dataGridView1->CurrentCell->ColumnIndex;

				// Переоткрываем соединение, если не открыто
				if (oleDbCommand1->Connection->State != ConnectionState::Open) {
					oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
					oleDbCommand1->Connection->Open();
				}

				oleDbCommand1->CommandText = rRecordForm->getSQLCommand();

				// Выполняем изменение записи в БД
				oleDbCommand1->ExecuteNonQuery();

				// Зачитываем справочник заново
				oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
				dataSet2->Tables[ "BNKSEEK" ]->Clear();
				oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

				// Восстанавливаем текущую
				dataGridView1->CurrentCell = dataGridView1[ currentcol_index, currentrow_index ];
			}

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message,
				"Ошибка изменения записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "Возникла неизвестная ошибка при изменении записи справочника",
				"Ошибка изменения записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}

		if (rRecordForm != nullptr)
			delete rRecordForm;
	}
}
// ------------------------------------------------------------------

// Удаление текущей записи справочника
void BicRF::MainForm::deleteRecord() {

	// Если справочник не пуст
	if (dataGridView1->Rows->Count > 0)
	{
		// Запоминаем положение текущей
		int currentrow_index = dataGridView1->CurrentCell->RowIndex,
			currentcol_index = dataGridView1->CurrentCell->ColumnIndex;

		try {

			if (MessageBox::Show( 
				"Вы уверены, что хотите удалить запись участника расчетов \"" +
				dataGridView1->CurrentRow->Cells[ "NAMEP" ]->Value->ToString() +
				"\" (БИК - " + 
				dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() +
				")?",
				"Удаление записи из справочника участников расчетов",
				MessageBoxButtons::YesNo, MessageBoxIcon::Warning,
				MessageBoxDefaultButton::Button2 ) == ::DialogResult::Yes) {

				oleDbCommand1->CommandText = 
					"delete from BNKSEEK where NEWNUM = '" +
					dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() + "';";

				// Переоткрываем соединение, если не открыто
				if (oleDbCommand1->Connection->State != ConnectionState::Open) {
					oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
					oleDbCommand1->Connection->Open();
				}

				// Выполняем удаление записи в БД
				oleDbCommand1->ExecuteNonQuery();
				
				// Если текущая была на последней записи, то позиционируемся на предыдущую
				if (dataGridView1->Rows->Count > 1)
				{
					if (dataGridView1->CurrentRow->Index+1 == dataGridView1->Rows->Count)
						currentrow_index = dataGridView1->CurrentCell->RowIndex-1;
				}

				// Зачитываем справочник заново
				oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
				dataSet2->Tables[ "BNKSEEK" ]->Clear();
				oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );
					
				// Текущую восстанавливаем только если справочник не пуст
				if (dataGridView1->Rows->Count > 1)
					dataGridView1->CurrentCell = dataGridView1[ currentcol_index, currentrow_index ];
			}

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message,
				"Ошибка удаления записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "Возникла неизвестная ошибка при удалении записи справочника",
				"Ошибка удаления записи справочника",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}
	}
}
// ------------------------------------------------------------------

