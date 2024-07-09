# WindowsQuotePro

A simple CRUD application for software for [quotations](https://www.salesforce.com/sales/cpq/what-is-cpq/).

## Prerequisites

- Visual Studio 2022 Community Edition
    - .NET Desktop Development
        - Defaults
    - Desktop development with C++
        - Defaults
        - C++/CLI support for v143 build tools

## Build and run

Application uses local SQLite database.
For this purpose SQLite client library installed within Visual Studio 2022 Community is used. It requires two libraries:
- `System.Data.Sqlite.dll`
- `SQLite.Interop.dll`

For running the application from Visual Studio  `WindowsQuotePro` project must be additionally configured:
- Navigate `properties` -> `Debugging` -> `Environment`.
- Add the following line:

    ```PATH=%PATH%;$(VSInstallDir)Common7\IDE\PrivateAssemblies;$(VSInstallDir)Common7\IDE\PrivateAssemblies\x64```
- Project should be ready to run from the Visual Studio debugger.

## Functionality

The application consist of:
- Main window:
    - Grid Data View which has two columns editable:
        - Name
        - Customer
    - "Create" button, invokes another window for creating a new quote.
    - "Update" button, invokes the same windows as "Create" button does. Active only if one or more rows are selected. Can open multiple windows for editing if multiple rows are selected.
    - "Delete" button. Active only if one or more rows are selected. Deletes selected rows from the database.
- Create / Update quote window:
    - Text field for quote name.
    - Text field for customer name.
    - Combo box with material name.
    - Combo box with size name.
    - Text field with price. Not editable. Content is calculated depending on material and size.
