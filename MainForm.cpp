# include "stdafx.h"

# include "MainForm.h"

using namespace System;

// ��������� ������� ����������� � ������������ �� ���������� ������ �������
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

	// �������� �������������� ������
	try {
		dataView1->RowFilter = newfilter;

	} catch (Exception ^e) {
		MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
			"\n ������: " + newfilter + ",\n ��������, ��� �������������� ������" ,
			"������ ��������� ������� �����������",
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
	}
}
// ------------------------------------------------------------------

// �������� ������ �� ������ SQL-�������
void BicRF::MainForm::loadDBFromSQLServer() {

	IsDBLoaded = false;

	dataSet2->Reset();
	dataGridView1->Enabled = false;

	try {

		// �������� ����������� � SQL-��������
		if (oleDbConnection2->State == ConnectionState::Open)
			oleDbConnection2->Close();
		oleDbConnection2->ConnectionString = ConnectionStringTemplate + "master";
		oleDbConnection2->Open();

	} catch (OleDb::OleDbException ^e) {
		MessageBox::Show( 
			e->Source + " > " + e->Message + "\n ��������, ����������� ������ � SQL-������� ��� ��� ������ �� ��������." 
			+ "\n ��������, ������� �������� ��� SQL-������� � ���������� ���������.",
			"�� ������� ������������ � SQL-������� " + DBServerName,
			MessageBoxButtons::OK, MessageBoxIcon::Stop,
			MessageBoxDefaultButton::Button1 );
	}

	if (oleDbConnection2->State == ConnectionState::Open)
	{
		try {

			// ����� ��������� ���������� � SQL-�������� �������� ���������� �� BicRF 
			oleDbConnection2->Close();
			oleDbConnection2->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
			oleDbConnection2->Open();

		} catch (OleDb::OleDbException ^e) {
			MessageBox::Show( e->Source + " > " + e->Message + "\n ��������, ������� ��������� �������� �� �� DBF-������. ",
				"�� ������� ��������� ���������� � �� " + BicRF_DBName + " (SQL-������ " + DBServerName + ").",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}
	}

	if (oleDbConnection2->State ==  ConnectionState::Open)
	{
		try {
			// �������� ����������� ���������� �� ��
			oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
			oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

			// ���������� ���������� �����
			array<System::Data::DataColumn ^, 1> ^keys = gcnew array<System::Data::DataColumn ^, 1> ( 1 );
			keys[0] = dataSet2->Tables[ "BNKSEEK" ]->Columns[ "NEWNUM" ];
			dataSet2->Tables[ "BNKSEEK" ]->PrimaryKey = keys;

			oleDbDataAdapter1->SelectCommand = oleSelectTypesCommand;

			// �������� ������������ �� �� ��� ���������� �������
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
				"�� ������� ��������� �� �� " + DBServerName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
				"\n ��������, ������ �� ������� � ������� ��������� �������� �� DBF-������",
				"������ �������� ������ �� �� " + BicRF_DBName,
				MessageBoxButtons::OK, MessageBoxIcon::Stop,
				MessageBoxDefaultButton::Button1 );
		}

		if (IsDBLoaded)
		{
			// ���������� DataView, ����� ����� ����������� ����������� ����������
			dataView1->Table = dataSet2->Tables[ "BNKSEEK" ];

			// ���������� DataGridView
			dataGridView1->AutoGenerateColumns = true;
			dataGridView1->DataSource = dataView1;

			try {

				// ��������� ���������� �������� �������
				DataGridViewColumn^ column;

				column = dataGridView1->Columns[ "REAL" ];
				column->HeaderText = "������������";
				column->ToolTipText = "��� �������� ������������ ����������  ��������� ��������";

				column = dataGridView1->Columns[ "IND" ];
				column->HeaderText = "������";
				column->ToolTipText = "�������� ������";

				column = dataGridView1->Columns[ "NPNAME" ];
				column->HeaderText = "���������� �����";
				column->ToolTipText = "������������ ����������� ������, � ������� �������� ��������";

				column = dataGridView1->Columns[ "ADR" ];
				column->HeaderText = "�����";
				column->ToolTipText = "����� ��������� ��������";

				column = dataGridView1->Columns[ "RKC" ];
				column->HeaderText = "��� ���";
				column->ToolTipText = "��� ��� ��� ����";

				column = dataGridView1->Columns[ "KSNP" ];
				column->HeaderText = "����� �����";
				column->ToolTipText = "����� ������������������ ����� ��������� ��������";

				column = dataGridView1->Columns[ "REGN" ];
				column->HeaderText = "���. �����";
				column->ToolTipText = "��������������� �����";

				column = dataGridView1->Columns[ "OKPO" ];
				column->HeaderText = "����";
				column->ToolTipText = "��� ����";

				column = dataGridView1->Columns[ "DATE_IN" ];
				column->HeaderText = "���� ���������";
				column->ToolTipText = "���� ��������� ���������� �� ��������� �������� � ���";

				column = dataGridView1->Columns[ "DATE_CH" ];
				column->HeaderText = "���� ��������";
				column->ToolTipText = "";

				column = dataGridView1->Columns[ "DT_IZM" ];
				column->HeaderText = "���� ���������";
				column->ToolTipText = "���� ���������� ��������� ������";

				column = dataGridView1->Columns[ "UERNAME" ];
				column->HeaderText = "��� ��������� ��";
				column->ToolTipText = "��� ��������� (������������) ������� ����������� ��������";

				column = dataGridView1->Columns[ "NAMEP" ];
				column->HeaderText = "������������";
				column->ToolTipText = "������������ ��������� ��������";

				column = dataGridView1->Columns[ "TELEF" ];
				column->HeaderText = "��������";
				column->ToolTipText = "������ ���������";

				column = dataGridView1->Columns[ "NEWNUM" ];
				column->HeaderText = "���";
				column->ToolTipText = "���������� ����������������� ��� ���������";

				column = dataGridView1->Columns[ "IMY" ];
				column->HeaderText = "���";
				column->ToolTipText = "��� ���������";

				column = dataGridView1->Columns[ "REGNAME" ];
				column->HeaderText = "������";
				column->ToolTipText = "������ ��, � ������� �������� ��������";

				// �������� ������� � �������� �������
				dataGridView1->Columns[ "NNP" ]->Visible = false;
				dataGridView1->Columns[ "PZN" ]->Visible = false;
				dataGridView1->Columns[ "TNP" ]->Visible = false;
				dataGridView1->Columns[ "RGN" ]->Visible = false;
				dataGridView1->Columns[ "UER" ]->Visible = false;

			} catch (Exception ^e) {
				MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
					"\n ��������, ������ �� ������� � ������� ��������� �������� �� DBF-������",
					"������ ��������� ������� �����������",
					MessageBoxButtons::OK, MessageBoxIcon::Stop,
					MessageBoxDefaultButton::Button1 );
			}

			// ���������� ����������� ������ ����� � ������ �������
			try {
				TypeComboBox->DataSource = dataSet2->Tables[ "PZN" ];
				TypeComboBox->DisplayMember = "PZNAME";
				TypeComboBox->ValueMember = "PZN";
			} catch (Exception ^e) {
				MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
					"\n ��������, ������ �� ������� � ������� ��������� �������� �� DBF-������",
					"������ ��������� ������� �����������",
					MessageBoxButtons::OK, MessageBoxIcon::Stop,
					MessageBoxDefaultButton::Button1 );
			}
		}
	}

	dataGridView1->Enabled = true;
}
// ------------------------------------------------------------------

// ���������� ������
void BicRF::MainForm::insertRecord() {

	RecordForm^ rRecordForm = gcnew RecordForm( dataSet2, "" );
							
	if (rRecordForm->ShowDialog() == ::DialogResult::OK) {

		try {

			// ������������� ����������, ���� �� �������
			if (oleDbCommand1->Connection->State != ConnectionState::Open) {
				oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
				oleDbCommand1->Connection->Open();
			}

			oleDbCommand1->CommandText = rRecordForm->getSQLCommand();

			// ��������� ���������� ������ � ��
			oleDbCommand1->ExecuteNonQuery();

			// ���������� �������� ������� ������������ ������ ������� ������
			CurrentDGRowOffset = dataGridView1->CurrentRow->Index - dataGridView1->FirstDisplayedScrollingRowIndex;

			// ���������� ���������� ������
			oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
			dataSet2->Tables[ "BNKSEEK" ]->Clear();
			oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

			// ���������������� �� ���������������� ������
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
				"������ ���������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "�������� ����������� ������ ��� ���������� ������ �����������",
				"������ ���������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		}
	}

	delete rRecordForm;
}
// ------------------------------------------------------------------

// ��������� ������
void BicRF::MainForm::editRecord() {

	// ���� ���������� �� ����
	if (dataGridView1->Rows->Count > 0)
	{
		RecordForm^ rRecordForm = nullptr;

		try {
			rRecordForm = gcnew RecordForm( 
				dataSet2, 
				dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() );
							
			if (rRecordForm->ShowDialog() == ::DialogResult::OK) {

				// ���������� ��������� �������
				int currentrow_index = dataGridView1->CurrentCell->RowIndex,
					currentcol_index = dataGridView1->CurrentCell->ColumnIndex;

				// ������������� ����������, ���� �� �������
				if (oleDbCommand1->Connection->State != ConnectionState::Open) {
					oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
					oleDbCommand1->Connection->Open();
				}

				oleDbCommand1->CommandText = rRecordForm->getSQLCommand();

				// ��������� ��������� ������ � ��
				oleDbCommand1->ExecuteNonQuery();

				// ���������� ���������� ������
				oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
				dataSet2->Tables[ "BNKSEEK" ]->Clear();
				oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );

				// ��������������� �������
				dataGridView1->CurrentCell = dataGridView1[ currentcol_index, currentrow_index ];
			}

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message,
				"������ ��������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "�������� ����������� ������ ��� ��������� ������ �����������",
				"������ ��������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}

		if (rRecordForm != nullptr)
			delete rRecordForm;
	}
}
// ------------------------------------------------------------------

// �������� ������� ������ �����������
void BicRF::MainForm::deleteRecord() {

	// ���� ���������� �� ����
	if (dataGridView1->Rows->Count > 0)
	{
		// ���������� ��������� �������
		int currentrow_index = dataGridView1->CurrentCell->RowIndex,
			currentcol_index = dataGridView1->CurrentCell->ColumnIndex;

		try {

			if (MessageBox::Show( 
				"�� �������, ��� ������ ������� ������ ��������� �������� \"" +
				dataGridView1->CurrentRow->Cells[ "NAMEP" ]->Value->ToString() +
				"\" (��� - " + 
				dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() +
				")?",
				"�������� ������ �� ����������� ���������� ��������",
				MessageBoxButtons::YesNo, MessageBoxIcon::Warning,
				MessageBoxDefaultButton::Button2 ) == ::DialogResult::Yes) {

				oleDbCommand1->CommandText = 
					"delete from BNKSEEK where NEWNUM = '" +
					dataGridView1->CurrentRow->Cells[ "NEWNUM" ]->Value->ToString() + "';";

				// ������������� ����������, ���� �� �������
				if (oleDbCommand1->Connection->State != ConnectionState::Open) {
					oleDbCommand1->Connection->ConnectionString = ConnectionStringTemplate + BicRF_DBName;
					oleDbCommand1->Connection->Open();
				}

				// ��������� �������� ������ � ��
				oleDbCommand1->ExecuteNonQuery();
				
				// ���� ������� ���� �� ��������� ������, �� ��������������� �� ����������
				if (dataGridView1->Rows->Count > 1)
				{
					if (dataGridView1->CurrentRow->Index+1 == dataGridView1->Rows->Count)
						currentrow_index = dataGridView1->CurrentCell->RowIndex-1;
				}

				// ���������� ���������� ������
				oleDbDataAdapter1->SelectCommand = oleDbSelectCommand1;
				dataSet2->Tables[ "BNKSEEK" ]->Clear();
				oleDbDataAdapter1->Fill( dataSet2, "BNKSEEK" );
					
				// ������� ��������������� ������ ���� ���������� �� ����
				if (dataGridView1->Rows->Count > 1)
					dataGridView1->CurrentCell = dataGridView1[ currentcol_index, currentrow_index ];
			}

		} catch (Exception ^e) {
			MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message,
				"������ �������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );

		} catch (...) {
			MessageBox::Show( "�������� ����������� ������ ��� �������� ������ �����������",
				"������ �������� ������ �����������",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation,
				MessageBoxDefaultButton::Button1 );
		}
	}
}
// ------------------------------------------------------------------

