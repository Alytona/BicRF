# include "stdafx.h"

# include "IniFile.h"

String^ CIniFile::getValue( String ^parameter ) {

	String^ result = nullptr;
			
	if (IniDictionary.TryGetValue( parameter, result ))
		return result;

	return nullptr;
}
// ------------------------------------------------------------------------------

void CIniFile::setValue( String ^parameter, String^ value ) {

	String^ newvalue = nullptr;
			
	IniDictionary.Remove( parameter );
	IniDictionary.Add( parameter, value );

	Save();
}
// ------------------------------------------------------------------------------

int CIniFile::Save() {

	try {
		IO::File::Delete( FileName );
	} catch (...) {}

	IO::StreamWriter ^iniFile = IO::File::CreateText( FileName );

	String^ last_section = "";

	CIniDictionary::Enumerator IniDictionaryEnumerator = IniDictionary.GetEnumerator();
	while ( IniDictionaryEnumerator.MoveNext() ) {

		String ^key =  IniDictionaryEnumerator.Current.Key, ^section = "", ^parameter = "";
		int delimpos = key->IndexOf( ':' );
		if (delimpos != -1)
		{
			section = key->Substring( 0, delimpos );
			parameter = key->Substring( delimpos+1 );
		}
		else
			parameter = key;

		if (section != last_section)
		{
			last_section = section;
			iniFile->WriteLine( "[" + section + "]" );
		}

		iniFile->WriteLine( parameter + "=" + IniDictionaryEnumerator.Current.Value );
	}

	iniFile->Close();
	return 0;
}	
// ------------------------------------------------------------------------------

int CIniFile::Load() {

	IniDictionary.Clear();

	try {
		IO::StreamReader ^iniFile = IO::File::OpenText( FileName );

		String^ str = iniFile->ReadLine(), ^section = "";
		while (str != nullptr) {

			str = str->TrimStart();

			if (str[0] == '[')
				section = str->Substring( 1, str->IndexOf( ']', 1 )-1 );
			else {
				String ^parameter = str->Substring( 0, str->IndexOf( '=' ) ), 
					^value = str->Substring( str->IndexOf( '=' ) + 1 );

				IniDictionary.Add( section + ":" + parameter, value );
			}

			str = iniFile->ReadLine();
		}

		iniFile->Close();

	} catch (Exception ^e) {
		Windows::Forms::MessageBox::Show( e->GetType() + ": " + e->Source + " > " + e->Message + 
			"\n Будет создан новый файл",
			"Ошибка загрузки файла настроек",
			Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Exclamation,
			Windows::Forms::MessageBoxDefaultButton::Button1 );
	}

	return 0;
}
// ------------------------------------------------------------------------------
