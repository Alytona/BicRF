#include "StdAfx.h"
#include "RecordForm.h"

	// Проверка корректности заполнения поля 'Наименование'
void BicRF::RecordForm::check_NAME() {
	NAME_TextBox->Text = NAME_TextBox->Text->Trim()->ToUpper();
	if (NAME_TextBox->Text->Length == 0)
		NAME_Label->ForeColor = Drawing::Color::Red;
	else
		NAME_Label->ForeColor = SystemColors::ControlText;
}

	// Проверка корректности заполнения поля 'БИК'
void BicRF::RecordForm::check_NEWNUM() {
	DataRow^ foundrow = NotebooksDataSet->Tables[ "BNKSEEK" ]->Rows->Find( 
		NEWNUM_MaskedTextBox->Text );
	if (foundrow == nullptr) {
		NEWNUM_Label->ForeColor = SystemColors::ControlText;
	}
	else {
		NEWNUM_Label->ForeColor = Drawing::Color::Red;
	}
}


