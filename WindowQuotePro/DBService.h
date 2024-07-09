#pragma once

namespace WindowQuotePro {

	using namespace System;
	using namespace System::Data;
	using namespace System::Data::SQLite;
	using namespace System::IO;


	/// <summary>
	/// Class managing the database operations.
	/// </summary>
	
	ref class DBService
	{
	private:
		static DBService^ instance = nullptr;
		static Object^ lock = gcnew Object();

		String^ dbPath = nullptr;
		SQLiteConnection^ connection = nullptr;

		DBService(String^ dbPath);
		~DBService();
	public:

		static property DBService^ Instance
		{
			DBService^ get();
		}

		DataTable^ LoadData();
		int AddRecord(String^ name, String^ customer, Int32 material, Int32 size, Double price);
		void UpdateRecord(Int32 id, String^ name, String^ customer, Int32 material, Int32 size, Double price);
		void DeleteRecord(Int32 id);
	};
}

