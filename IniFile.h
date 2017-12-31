#pragma once

using namespace System;

typedef Collections::Generic::Dictionary <String^, String^>  CIniDictionary;

// typedef Collections::Generic::KeyValuePair <String^, String^> CIniDictionary;

ref class CIniFile {

		CIniDictionary IniDictionary;
		String^ FileName;

		int Save(); 
		int Load(); 

	public:

		CIniFile( String^ _FileName ) { 
			FileName = _FileName; 
			Load();
		}

		String^  getValue( String ^parameter );

		void setValue( String ^parameter, String^ value );
};
// ------------------------------------------------------------------------------
