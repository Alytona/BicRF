# include "stdafx.h"

# include "MainForm.h"
# include "ProgressBarForm.h"

using namespace System;

// �������� ������ �� DBF-������ � ������� SQL-�������
void BicRF::MainForm::startDBFLoading() {

	// ��������� DataGridView �� ������������
	dataGridView1->Enabled = false;
	dataGridView1->AutoGenerateColumns = false;
	dataGridView1->DataMember = nullptr;

	// ��������� ����������, ������������ ��� ������ � �� � ������ ������ �� ������������,
	// �.�. � �������� ������������ �� ��������� ����������� ������
	oleDbConnection2->Close();
	oleDbConnection2->ReleaseObjectPool();  // ����������� ���� ��� ����������
	GC::Collect();							// ���������� GarbageCollector ��������� ������ ������, 
											// � �������� ������� ����� ������� ��� ��������� ������ ����������� � ��
	Application::DoEvents();				// ����, ����� ����� ���������� ����������� ������� ���������

	Threading::Thread^ loadDBFDataThread = 	gcnew System::Threading::Thread( 
		gcnew Threading::ThreadStart( this, &BicRF::MainForm::loadDBFData ));

	// ��������� ��������� ����������� ������ ����������� �� ������� �������� ��������
	rProgressBarForm = gcnew ProgressBarForm( Point( this->Location.X + 50, this->Location.Y + 50 ) );
	rProgressBarForm->Title = "�������� �� �� DBF-������";
	rProgressBarForm->Operation = "������ ��������";

	// ������ ������ �������� ������ �� DBF-������ 
	loadDBFDataThread->Start();

	// ����� ������� ������, ���������� ��������� ���������, ������� ��������� ��� �� ��������� ��������.
	// ���� ��� ������� �������������, �� �������� ������ ��������� ����������.
	rProgressBarForm->ShowDialog();
	
	loadDBFDataThread->Abort();
	delete loadDBFDataThread;

	// �������� ����� ������ �� ������ SQL-�������
	loadDBFromSQLServer();
	dataGridView1->Enabled = true;
}
// ------------------------------------------------------------------

// �������� ������� SQL-������� �� ���������� ������������
void BicRF::MainForm::createBicRFTable( String^ tablename, String^ specification) {
	try {
		oleDbCommand1->CommandText = "create table " + tablename + " " + specification + ";";
		oleDbCommand1->ExecuteNonQuery();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message,
			"�� ������� ������� ������� " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
		throw gcnew String( "�� ������� ������� ������� " + tablename );
	}
}
// ------------------------------------------------------------------

// ������������ �� BicRF, ������� ��������� exception String^
void BicRF::MainForm::createBicRFTables() {

	rProgressBarForm->Progress = 1;

	try {

		// �������� ����������� � SQL-��������
		oleDbConnection1->ConnectionString = ConnectionStringTemplate + "master";
		oleDbConnection1->Open();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message + "\n ��������, ����������� ������ � SQL-������� ��� ��� ������ �� ��������." 
			+ "\n ��������, ������� �������� ��� SQL-������� � ���������� ���������.",
			"�� ������� ������������ � SQL-������� " + DBServerName,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );

		throw gcnew String( "�� ������� ������������ � SQL-�������" );
	}
	rProgressBarForm->Progress = 2;

	if (oleDbConnection1->State ==  ConnectionState::Open)
	{
		// �������� ���� ������ BicRF ����� �������������
		try {
			oleDbCommand1->CommandText = "use master;";
			oleDbCommand1->ExecuteNonQuery();
			oleDbCommand1->CommandText = "drop database " + BicRF_DBName + ";";
			oleDbCommand1->ExecuteNonQuery();

		} catch (...) {
			// ���������� ������������, �.�. �� ����� �� ������������
		}
		rProgressBarForm->Progress = 3;

		// �������� �� BicRF
		try {
			oleDbCommand1->CommandText = "create database " + BicRF_DBName + ";";
			oleDbCommand1->ExecuteNonQuery();

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( 
				e->Source + " > " + e->Message + "\n ��������, �� ������� ������� ������ �� " + BicRF_DBName + 
				" � ������� ������� ��� ����������� � ���",
				"�� ������� ������� �� " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

			throw gcnew String( "�� ������� ������� ��" + BicRF_DBName );
		}
		rProgressBarForm->Progress = 4;

		// ����������� � �� BicRF
		try {
			oleDbConnection1->ChangeDatabase( BicRF_DBName );

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( 
				e->Source + " > " + e->Message,
				"�� ������� ������������ � �� " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

			throw gcnew String( "�� ������� ������������ � ��������� �� " + BicRF_DBName );
		}
		rProgressBarForm->Progress = 5;

		// ������� �������
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

// �������� ������ � �������
// ���������� ��� �������, ��������� ��������� ���������� ��������� � �������� (� ���������)
void BicRF::MainForm::loadDBFFile( String^ tablename, int progress_0, int progress_1 ) {

	try {
		odbcDataAdapter1->Fill( dataSet1, tablename );

		DataTable^ tblPZN = dataSet1->Tables[ tablename ];

		// ������� ��������� ��� ���������� ���������
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

			// ����� �������� ��� ���������� ���������
			progress_0f += progress_step;
			rProgressBarForm->Progress = safe_cast<int>(progress_0f+0.5);  // �� ���� ������ �������� ��� �������������� ����������
		}

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message,
			"�� ������� ��������� ������� " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );

		throw gcnew String( "�� ������� ��������� ������� " ) + tablename;

	} catch (Exception ^e) {
		MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message, 
			"�� ������� ��������� ������� " + tablename,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
		throw gcnew String( "�� ������� ��������� ������� " ) + tablename;
	}
}
// ------------------------------------------------------------------

// ����� �������� ������ �� DBF-������
void BicRF::MainForm::loadDBFData() {

	rProgressBarForm->Progress = 0;

	try {
		rProgressBarForm->Operation = "�������� ������";
		createBicRFTables();

		// ��������� ODBC-�������� 
		try {
			odbcConnection1->ConnectionString = "DSN=" + BicRF_DSNName;
			odbcConnection1->Open();

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message, 
				"�� ������� ������� ������� � DBF-�������",
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );
			throw gcnew String( "�� ������� ������� ������� � DBF-�������" );
		}

		dataSet1->Reset();

		rProgressBarForm->Operation = "�������� ������ � ������� PZN";
		// �������� ������ � ������� PZN
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, PZN, IMY, NAME, CB_DATE, CE_DATE from PZN";
		loadDBFFile( "PZN", 11, 15 );
	
		rProgressBarForm->Operation = "�������� ������ � ������� TNP";
		// �������� ������ � ������� TNP
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, TNP, FULLNAME, SHORTNAME from TNP";
		loadDBFFile( "TNP", 16, 20 );
		rProgressBarForm->Progress = 15;
	
		rProgressBarForm->Operation = "�������� ������ � ������� UER";
		// �������� ������ � ������� UER
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, UER, UERNAME from UER";
		loadDBFFile( "UER", 21, 25 );
	
		rProgressBarForm->Operation = "�������� ������ � ������� REG";
		// �������� ������ � ������� REG
		odbcDataAdapter1->SelectCommand->CommandText = "select VKEY, RGN, NAME, CENTER, NAMET from REG";
		loadDBFFile( "REG", 26, 30 );
	
		rProgressBarForm->Operation = "�������� ������ � ������� BNKSEEK";
		// �������� ������ � ������� BNKSEEK
		odbcDataAdapter1->SelectCommand->CommandText = "select REAL, PZN, UER, RGN, IND, " + 
			"TNP, NNP, ADR, RKC, NAMEP, NEWNUM, TELEF, REGN, OKPO, DT_IZM, KSNP, DATE_IN, " + 
			"DATE_CH from BNKSEEK";
		loadDBFFile( "BNKSEEK", 31, 99 );
	
	} catch (String^ e) {
		MessageBox::Show( 
			e, "��� �������� ������ �� DBF-������ ��������� ������" );
	} catch (Exception^ e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message, "��� �������� ������ �� DBF-������ ��������� ������" );
	} catch (...) {
		MessageBox::Show( 
			"��� �������� ������ �� DBF-������ ��������� ����������� ������",
			"��� �������� ������ �� DBF-������ ��������� ������" );
	}

	// ��������� ���������� � SQL-��������
	if (oleDbConnection1->State == ConnectionState::Open)
	{
		oleDbConnection1->ChangeDatabase( "master" );
		oleDbConnection1->Close();
	}

	// ��������� ���������� � ODBC-����������
	if (odbcConnection1->State == ConnectionState::Open)
		odbcConnection1->Close();

	// �������� ���������� ���������, ��� ����� ��� ���������
	rProgressBarForm->Progress = 100;
	Threading::Thread::Sleep( 1000 );
}
// ------------------------------------------------------------------

