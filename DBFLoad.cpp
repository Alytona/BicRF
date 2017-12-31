# include "stdafx.h"

# include "MainForm.h"
# include "ProgressBarForm.h"

using namespace System;

// Загрузка данных из DBF-файлов в таблицы SQL-сервера
void BicRF::MainForm::startDBFLoading() {

	// Отключаем DataGridView со справочником
	dataGridView1->Enabled = false;
	dataGridView1->AutoGenerateColumns = false;
	dataGridView1->DataMember = nullptr;

	// Закрываем соединение, используемое для работы с БД в режиме работы со справочником,
	// т.к. в процессе пересоздания БД требуется монопольный доступ
	oleDbConnection2->Close();
	oleDbConnection2->ReleaseObjectPool();  // Освобождаем весь пул соединений
	GC::Collect();							// Заставляем GarbageCollector выполнить сборку мусора, 
											// в процессе которой будут закрыты все созданные неявно подключения к БД
	Application::DoEvents();				// Ждем, когда будет обработана накопленная очередь сообщений

	Threading::Thread^ loadDBFDataThread = 	gcnew System::Threading::Thread( 
		gcnew Threading::ThreadStart( this, &BicRF::MainForm::loadDBFData ));

	// Индикатор прогресса обязательно должен создаваться до запуска процесса загрузки
	rProgressBarForm = gcnew ProgressBarForm( Point( this->Location.X + 50, this->Location.Y + 50 ) );
	rProgressBarForm->Title = "Загрузка БД из DBF-файлов";
	rProgressBarForm->Operation = "Начало загрузки";

	// Запуск потока загрузки данных из DBF-файлов 
	loadDBFDataThread->Start();

	// После запуска потока, показываем индикатор прогресса, который закроется сам по окончании загрузки.
	// Если его закрыть принудительно, то загрузка должна корректно прерваться.
	rProgressBarForm->ShowDialog();
	
	loadDBFDataThread->Abort();
	delete loadDBFDataThread;

	// Загрузка новых данных из таблиц SQL-сервера
	loadDBFromSQLServer();
	dataGridView1->Enabled = true;
}
// ------------------------------------------------------------------

// Создание таблицы SQL-сервера по переданной спецификации
void BicRF::MainForm::createBicRFTable( String^ tablename, String^ specification) {
	try {
		oleDbCommand1->CommandText = "create table " + tablename + " " + specification + ";";
		oleDbCommand1->ExecuteNonQuery();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message,
			"Не удалось создать таблицу " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
		throw gcnew String( "Не удалось создать таблицу " + tablename );
	}
}
// ------------------------------------------------------------------

// Пересоздание БД BicRF, требует обработки exception String^
void BicRF::MainForm::createBicRFTables() {

	rProgressBarForm->Progress = 1;

	try {

		// Пытаемся соединиться с SQL-сервером
		oleDbConnection1->ConnectionString = ConnectionStringTemplate + "master";
		oleDbConnection1->Open();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message + "\n Возможно, отсутствует доступ к SQL-серверу или его служба не запущена." 
			+ "\n Возможно, следует изменить имя SQL-сервера в настройках программы.",
			"Не удалось подключиться к SQL-серверу " + DBServerName,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );

		throw gcnew String( "Не удалось подключиться к SQL-серверу" );
	}
	rProgressBarForm->Progress = 2;

	if (oleDbConnection1->State ==  ConnectionState::Open)
	{
		// Удаление базы данных BicRF перед пересозданием
		try {
			oleDbCommand1->CommandText = "use master;";
			oleDbCommand1->ExecuteNonQuery();
			oleDbCommand1->CommandText = "drop database " + BicRF_DBName + ";";
			oleDbCommand1->ExecuteNonQuery();

		} catch (...) {
			// Исключения игнорируются, т.к. БД может не существовать
		}
		rProgressBarForm->Progress = 3;

		// Создание БД BicRF
		try {
			oleDbCommand1->CommandText = "create database " + BicRF_DBName + ";";
			oleDbCommand1->ExecuteNonQuery();

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( 
				e->Source + " > " + e->Message + "\n Возможно, не удалось удалить старую БД " + BicRF_DBName + 
				" и следует закрыть все подключения к ней",
				"Не удалось создать БД " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

			throw gcnew String( "Не удалось создать БД" + BicRF_DBName );
		}
		rProgressBarForm->Progress = 4;

		// Подключение к БД BicRF
		try {
			oleDbConnection1->ChangeDatabase( BicRF_DBName );

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( 
				e->Source + " > " + e->Message,
				"Не удалось подключиться к БД " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

			throw gcnew String( "Не удалось подключиться к созданной БД " + BicRF_DBName );
		}
		rProgressBarForm->Progress = 5;

		// Создаем таблицы
		createBicRFTable( "PZN", 
			"(VKEY char(2) not null, PZN char(2), IMY char(4), NAME varchar(40), CB_DATE datetime, CE_DATE datetime, primary key(VKEY))" );
		rProgressBarForm->Progress = 6;

		createBicRFTable( "TNP", 
			"(VKEY char(2) not null, TNP char(2), FULLNAME varchar(25), SHORTNAME varchar(5), primary key(VKEY))" );
		rProgressBarForm->Progress = 7;

		createBicRFTable( "UER", 
			"(VKEY char(2) not null, UER char(2), UERNAME varchar(70), primary key(VKEY))" );
		rProgressBarForm->Progress = 8;

		createBicRFTable( "REG", 
			"(VKEY char(2) not null, RGN char(2), NAME varchar(40), CENTER varchar(30), NAMET varchar(40), primary key(VKEY))" );
		rProgressBarForm->Progress = 9;

		createBicRFTable( "BNKSEEK", 
			"(REAL char(4), PZN char(2), UER char(2) not null, RGN char(2) not null, IND char(6), " + 
			"TNP char(2), NNP varchar(25), ADR varchar(30), RKC char(9), NAMEP varchar(45), " +
			"NEWNUM char(9) not null, TELEF varchar(25), REGN varchar(9), OKPO char(8), " +
			"DT_IZM datetime not null, KSNP char(20), DATE_IN datetime not null, " + 
			"DATE_CH datetime, primary key(NEWNUM))" );
		rProgressBarForm->Progress = 10;
	}
}
// ------------------------------------------------------------------

// Загрузка данных в таблицу
// Передается имя таблицы, начальное положение индикатора прогресса и конечное (в процентах)
void BicRF::MainForm::loadDBFFile( String^ tablename, int progress_0, int progress_1 ) {

	try {
		odbcDataAdapter1->Fill( dataSet1, tablename );

		DataTable^ tblPZN = dataSet1->Tables[ tablename ];

		// Подсчет пропорций для индикатора прогресса
		int quantity = tblPZN->Rows->Count+1, count = 0;
		float progress_step = (safe_cast<float>(progress_1-progress_0))/quantity, 
			progress_0f = safe_cast<float>(progress_0);
 
		for each (DataRow^ row in tblPZN->Rows) {
			
			bool bFirstElement = true;
			String^ values = "", ^value = "";

			for each( DataColumn^ column in tblPZN->Columns) {
				if (bFirstElement) 
					bFirstElement = false;
				else
					values += ", ";

				switch (Type::GetTypeCode( column->DataType )) {
					case TypeCode::String :
						values += (row->IsNull( column->ColumnName ))? "null" : ("'" + safe_cast<String ^>( row->default[ column->ColumnName ] ) + "'");
						break;

					case TypeCode::DateTime :
//						values += (row->IsNull( column->ColumnName ))? "null" : ("'01.01.2001 00:00:00.000'");
						values += (row->IsNull( column->ColumnName ))? "null" : ("'" + (safe_cast<DateTime ^>( row->default[ column->ColumnName ] ))->ToShortDateString() + " 00:00:00.000'");
						break;
				}
			}

			oleDbCommand1->CommandText = "insert into " + tablename + " values (" + values + ");"; 
			oleDbCommand1->ExecuteNonQuery();

			count++;

			// Новое значение для индикатора прогресса
			progress_0f += progress_step;
			rProgressBarForm->Progress = safe_cast<int>(progress_0f+0.5);  // По идее должно работать как математическое округление
		}

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message,
			"Не удалось заполнить таблицу " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );

		throw gcnew String( "Не удалось заполнить таблицу " ) + tablename;

	} catch (Exception ^e) {
		MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message, 
			"Не удалось заполнить таблицу " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
		throw gcnew String( "Не удалось заполнить таблицу " ) + tablename;
	}
}
// ------------------------------------------------------------------

// Поток загрузки данных из DBF-файлов
void BicRF::MainForm::loadDBFData() {

	rProgressBarForm->Progress = 0;

	try {
		rProgressBarForm->Operation = "Создание таблиц";
		createBicRFTables();

		// Открываем ODBC-источник 
		try {
			odbcConnection1->ConnectionString = "DSN=" + BicRF_DSNName;
			odbcConnection1->Open();

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message, 
				"Не удалось открыть каталог с DBF-файлами",
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );
			throw gcnew String( "Не удалось открыть каталог с DBF-файлами" );
		}

		dataSet1->Reset();

		rProgressBarForm->Operation = "Загрузка данных в таблицу PZN";
		// Загрузка данных в таблицу PZN
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, PZN, IMY, NAME, CB_DATE, CE_DATE from PZN";
		loadDBFFile( "PZN", 11, 15 );
	
		rProgressBarForm->Operation = "Загрузка данных в таблицу TNP";
		// Загрузка данных в таблицу TNP
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, TNP, FULLNAME, SHORTNAME from TNP";
		loadDBFFile( "TNP", 16, 20 );
		rProgressBarForm->Progress = 15;
	
		rProgressBarForm->Operation = "Загрузка данных в таблицу UER";
		// Загрузка данных в таблицу UER
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, UER, UERNAME from UER";
		loadDBFFile( "UER", 21, 25 );
	
		rProgressBarForm->Operation = "Загрузка данных в таблицу REG";
		// Загрузка данных в таблицу REG
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, RGN, NAME, CENTER, NAMET from REG";
		loadDBFFile( "REG", 26, 30 );
	
		rProgressBarForm->Operation = "Загрузка данных в таблицу BNKSEEK";
		// Загрузка данных в таблицу BNKSEEK
		odbcDataAdapter1->SelectCommand->CommandText = "select REAL, PZN, UER, RGN, IND, " + 
			"TNP, NNP, ADR, RKC, NAMEP, NEWNUM, TELEF, REGN, OKPO, DT_IZM, KSNP, DATE_IN, " + 
			"DATE_CH from BNKSEEK";
		loadDBFFile( "BNKSEEK", 31, 99 );
	
	} catch (String^ e) {
		MessageBox::Show( 
			e, "При загрузке данных из DBF-файлов произошла ошибка" );
	} catch (Exception^ e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message, "При загрузке данных из DBF-файлов произошла ошибка" );
	} catch (...) {
		MessageBox::Show( 
			"При загрузке данных из DBF-файлов произошла неизвестная ошибка",
			"При загрузке данных из DBF-файлов произошла ошибка" );
	}

	// Закрываем соединение с SQL-сервером
	if (oleDbConnection1->State == ConnectionState::Open)
	{
		oleDbConnection1->ChangeDatabase( "master" );
		oleDbConnection1->Close();
	}

	// Закрываем соединение с ODBC-источником
	if (odbcConnection1->State == ConnectionState::Open)
		odbcConnection1->Close();

	// Сигналим индикатору прогресса, что можно уже закрыться
	rProgressBarForm->Progress = 100;
	Threading::Thread::Sleep( 1000 );
}
// ------------------------------------------------------------------

