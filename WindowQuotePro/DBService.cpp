#include "DBService.h"
#include "Definitions.h"

#include <msclr/lock.h>


namespace WindowQuotePro {

	DBService::DBService(String^ dbPath) : dbPath(dbPath)
	{
		bool initDb = !File::Exists(dbPath);
		if (initDb)
		{
			SQLiteConnection::CreateFile(dbPath);
		}
		connection = gcnew SQLiteConnection("Data Source=" + dbPath + ";Version=3;");
		connection->Open();

		if (initDb)
		{
			SQLiteCommand^ command = connection->CreateCommand();
			command->CommandText = "CREATE TABLE Quotes ("
				+ "id INTEGER PRIMARY KEY,"
				+ "name TEXT," 
				+ "customer TEXT,"
				+ "material INTEGER," 
				+ "size INTEGER,"
				+ "price REAL," 
				+ "FOREIGN KEY(material) REFERENCES Materials(id), "
				+ "FOREIGN KEY(size) REFERENCES Sizes(id))";
				command->ExecuteNonQuery();

			command->CommandText = "CREATE TABLE Materials (id INTEGER PRIMARY KEY, name TEXT)";
			command->ExecuteNonQuery();

			for each (KeyValuePair<Materials, String^> material in Definitions::Instance->MaterialNames)
			{
				command->CommandText = "INSERT INTO Materials (id, name) VALUES (" 
					+ Int32(static_cast<int>(material.Key)).ToString() + ", '" + material.Value + "')";
				command->ExecuteNonQuery();
			}

			command->CommandText = "CREATE TABLE Sizes (id INTEGER PRIMARY KEY, name TEXT)";
			command->ExecuteNonQuery();

			for each (KeyValuePair<Sizes, String^> size in Definitions::Instance->SizeNames)
			{
				command->CommandText = "INSERT INTO Sizes (id, name) VALUES (" 
					+ Int32(static_cast<int>(size.Key)).ToString() + ", '" + size.Value + "')";
				command->ExecuteNonQuery();
			}
		}
	}

	DBService::~DBService()
	{
		if (connection != nullptr)
		{
			connection->Close();
			delete connection;
		}
	}

	DBService^ DBService::Instance::get()
	{
		if (instance == nullptr)
		{
			msclr::lock lockObject(lock);
			if (instance == nullptr)
			{
				instance = gcnew DBService("WindowQuotePro.sqlite3");
			}
		}
		return instance;
	}

	DataTable^ DBService::LoadData()
	{
		SQLiteCommand^ command = connection->CreateCommand();
		command->CommandText = "SELECT Quotes.id, Quotes.name, Quotes.customer, Materials.name, Materials.id, Sizes.name, Sizes.id, Quotes.price FROM Quotes "
			+ "JOIN Materials ON Quotes.material = Materials.id "
			+ "JOIN Sizes ON Quotes.size = Sizes.id";
		SQLiteDataAdapter^ adapter = gcnew SQLiteDataAdapter(command);
		DataTable^ table = gcnew DataTable();
		adapter->Fill(table);
		table->Columns[1]->ColumnName = "Name";
		table->Columns[2]->ColumnName = "Customer";
		table->Columns[3]->ColumnName = "Material";
		table->Columns[5]->ColumnName = "Size";
		table->Columns[7]->ColumnName = "Price, " + Definitions::Instance->Culture->NumberFormat->CurrencySymbol;
		return table;
	}

	void DBService::UpdateRecord(Int32 id, String^ name, String^ customer, Int32 material, Int32 size, Double price)
	{
		SQLiteCommand^ command = connection->CreateCommand();
		command->CommandText = "UPDATE Quotes SET name = @name, customer = @customer, material = @material, size = @size, price = @price WHERE id = @id";
		command->Parameters->AddWithValue("@name", name);
		command->Parameters->AddWithValue("@customer", customer);
		command->Parameters->AddWithValue("@material", material);
		command->Parameters->AddWithValue("@size", size);
		command->Parameters->AddWithValue("@price", price);
		command->Parameters->AddWithValue("@id", id);
		command->ExecuteNonQuery();
	}

	int DBService::AddRecord(String^ name, String^ customer, Int32 material, Int32 size, Double price)
	{
		SQLiteCommand^ command = connection->CreateCommand();
		command->CommandText = "INSERT INTO Quotes (name, customer, material, size, price) VALUES (@name, @customer, @material, @size, @price)";
		command->Parameters->AddWithValue("@name", name);
		command->Parameters->AddWithValue("@customer", customer);
		command->Parameters->AddWithValue("@material", material);
		command->Parameters->AddWithValue("@size", size);
		command->Parameters->AddWithValue("@price", price);
		command->ExecuteNonQuery();

		command->CommandText = "SELECT last_insert_rowid()";
		return Convert::ToInt32(command->ExecuteScalar());
	}

	void DBService::DeleteRecord(Int32 id)
	{
		SQLiteCommand^ command = connection->CreateCommand();
		command->CommandText = "DELETE FROM Quotes WHERE id = @id";
		command->Parameters->AddWithValue("@id", id);
		command->ExecuteNonQuery();
	}
}
