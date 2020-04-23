Add-Type -AssemblyName System.Windows.Forms;
[System.Windows.Forms.Application]::EnableVisualStyles();

Function Get-CoD4-Directory($initialDirectory = "")
{
	$topmost = New-Object System.Windows.Forms.Form;
    $topmost.TopMost = $True;
    $topmost.MinimizeBox = $True;

	$dialog = New-Object System.Windows.Forms.FolderBrowserDialog;
	$dialog.Description = "Select CoD4 root directory.";
	$dialog.RootFolder = "MyComputer";
	$dialog.SelectedPath = $initialDirectory;
	
	if($dialog.ShowDialog($topmost) -eq "OK")
	{
		$folder = $dialog.SelectedPath;
	}
	$dialog.Dispose();
    $topmost.Dispose();
	return $folder;
}

Function Main($method = "")
{
	switch ($method)
	{
		"install"
		{
			$cod4_directory = Get-CoD4-Directory;
			Write-Output $cod4_directory;
			if (-not [string]::IsNullOrEmpty($cod4_directory))
			{
				Write-Output "Installed gsclib shared libraries to: $cod4_directory.";
				Copy-Item -Verbose -Path "./deps/dre2/libdre2.dll" -Destination (Join-Path $cod4_directory "libdre2.dll");
				Copy-Item -Verbose -Path "./deps/mysql/windows/lib/libmysql.dll" -Destination (Join-Path $cod4_directory "libmysql.dll");
				Copy-Item -Verbose -Path "./deps/curl/windows/lib/libcurl.dll" -Destination (Join-Path $cod4_directory "libcurl.dll");
			}
		}
		"uninstall"
		{
			$cod4_directory = Get-CoD4-Directory;
			if (-not [string]::IsNullOrEmpty($cod4_directory))
			{
				Write-Output "Uninstalled gsclib shared libraries to: $cod4_directory.";
				Remove-Item -Verbose -Path (Join-Path $cod4_directory "libdre2.dll");
				Remove-Item -Verbose -Path (Join-Path $cod4_directory "libmysql.dll");
				Remove-Item -Verbose -Path (Join-Path $cod4_directory "libcurl.dll");
			}
		}
	}
}
Main($args[0]);