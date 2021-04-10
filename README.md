# windows-locale-db

This is just a simple tool to dump certain properties of Windows' locale/region database into a HTML format somewhat resembling the now defunct [NLSWeb](https://web.archive.org/web/20170916200715/http://www.microsoft.com/resources/msdn/goglobal/default.mspx) page which used to be provided by Microsoft as part of WinAPI documentation. The version linked here is the one archived by the Web Archive, which only has entries for Windows Vista.

The main reason behind this was to allow easily looking up which setting in the mystical "Language for programs without Unicode support" dialog in the Region settings in the Control Panel corresponds to which ANSI/OEM/MAC code pages.

The output seen [here](https://github.com/xavery/windows-locale-db/releases/download/v1.0/output.html) was generated on a machine running Windows 10 20H2. Other versions can be added if need be.
