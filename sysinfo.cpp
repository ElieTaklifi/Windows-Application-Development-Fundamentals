// System Information
// Use the following functions to display information about the system and the user: 
// GetNativeSystemInfo, GetSystemInfo, GetComputerName, GetComputerNameEx, GetSystemDirectory,
// GetUserName, GetUserNameEx, GetPerformanceInfo.

#include <Windows.h>
#include <stdio.h>
#include <Lmcons.h>
#include <Security.h>
//#define SECURITY_WIN32

void PrintGetNativeSystemInfo() {
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);

	printf("\n *** GetNativeSystemInfo *** \n\n");
	printf("Number of Logical Processors: %u\n", si.dwNumberOfProcessors);
	printf("Processor Type: %u\n", si.dwProcessorType);
	printf("Allocation Granularity: %u\n", si.dwAllocationGranularity);
	printf("Page size: %u Bytes\n", si.dwPageSize);
	printf("Processor Mask: 0x%zX\n", si.dwActiveProcessorMask);
	printf("Minimumprocess address:0x%p\n", si.lpMinimumApplicationAddress);
	printf("Maximum process address: 0x%p\n", si.lpMaximumApplicationAddress);
	printf("Processor Level: %hu\n", si.wProcessorLevel);
	printf("Processor Revision: %hu\n", si.wProcessorRevision);
	printf("----------------------------------------------------\n");
}

void PrintGetSystemInfo() {
	
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	printf("\n *** GetSystemInfo *** \n\n");
	printf("Number of Logical Processors: %u\n", si.dwNumberOfProcessors);
	printf("Processor Type: %u\n", si.dwProcessorType);
	printf("Allocation Granularity: %u\n", si.dwAllocationGranularity);
	printf("Page size: %u Bytes\n", si.dwPageSize);
	printf("Processor Mask: 0x%zX\n", si.dwActiveProcessorMask);
	printf("Minimumprocess address:0x%p\n", si.lpMinimumApplicationAddress);
	printf("Maximum process address: 0x%p\n", si.lpMaximumApplicationAddress);
	printf("Processor Level: %hu\n", si.wProcessorLevel);
	printf("Processor Revision: %hu\n", si.wProcessorRevision);
	printf("----------------------------------------------------\n");
}

void PrintGetComputerName() {  
    
	wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerName(computerName, &size)) {  
        printf("\n *** GetComputerName *** \n\n");  
        printf("Computer Name: %ls\n", computerName);  
    } else {  
        printf("Failed to retrieve computer name. Error: %lu\n", GetLastError());  
    }  
    printf("----------------------------------------------------\n");  
}

void PrintGetComputerNameEx() {

	wchar_t computerName[256];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	
	if (GetComputerNameEx(ComputerNameDnsFullyQualified, computerName, &size)) {
		printf("\n *** GetComputerNameEx *** \n\n");
		printf("Computer Name: %ls\n", computerName);
	}
	else {
		printf("Failed to retrieve computer name. Error: %lu\n", GetLastError());
	}
	printf("----------------------------------------------------\n");
}

void PrintGetSystemDirectory() {

	TCHAR systemDirectory[MAX_PATH]; // Buffer to store the path
	DWORD result; // To store the return value of GetSystemDirectory

	// Call GetSystemDirectory to get the path
	result = GetSystemDirectory(systemDirectory, MAX_PATH);

	printf("\n *** PrintGetSystemDirectory *** \n\n");
	if (result == 0) {
		// Handle error if the function fails
		printf("Error getting system directory. Error code: %lu\n", GetLastError());
	}
	else if (result > MAX_PATH) {
		// Handle case where the buffer is too small
		printf("Buffer too small. Required size: %lu\n", result);
	}
	else {
		// Print the system directory path
		printf("System Directory: %ls\n", systemDirectory);	
	}
	printf("----------------------------------------------------\n");
}

void PrintGetUserName() {

	TCHAR usernameBuffer[UNLEN + 1]; // Buffer to store the username, UNLEN is max username length
	DWORD usernameLength = UNLEN + 1; // Size of the buffer

	printf("\n *** PrintGetUserName *** \n\n");

	// Call GetUserName to retrieve the username
	if (GetUserName(usernameBuffer, &usernameLength)) {
		// Convert TCHAR array to std::string for easier handling and printing
		printf("Current username: %ls\n", usernameBuffer);
	}
	else {
		// Handle error if GetUserName fails
		printf("Failed to get username. Error code: %lu\n", GetLastError());
	}
	printf("----------------------------------------------------\n");

}

void PrintGetUserNameEx() {
	GetUserNameEx
	
	// Define the desired name format
	EXTENDED_NAME_FORMAT nameFormat = NameFullyQualifiedDN; // Example: CN=Jeff Smith,OU=Users,DC=Engineering,DC=Microsoft,DC=Com

	// Initial buffer size (can be adjusted)
	DWORD bufferSize = 256;
	//std::wstring userName;
	//userName.resize(bufferSize); // Resize the string to hold the name

	// Loop to handle potential ERROR_MORE_DATA if buffer is too small
	while (!GetUserNameEx(nameFormat, &userName[0], &bufferSize))
	{
		if (GetLastError() == ERROR_MORE_DATA)
		{
			userName.resize(bufferSize); // Resize the buffer to the required size
		}
		else
		{
			std::wcerr << L"Error retrieving username: " << GetLastError() << std::endl;
			return 1;
		}
	}

	//// Resize the string to the actual length of the name (excluding null terminator)
	//userName.resize(bufferSize - 1);

	//std::wcout << L"Username (" << nameFormat << L"): " << userName << std::endl;

	//// Example of another format: NameSamCompatible (e.g., Engineering\JSmith)
	//nameFormat = NameSamCompatible;
	//bufferSize = 256;
	//userName.resize(bufferSize);

	//while (!GetUserNameEx(nameFormat, &userName[0], &bufferSize))
	//{
	//	if (GetLastError() == ERROR_MORE_DATA)
	//	{
	//		userName.resize(bufferSize);
	//	}
	//	else
	//	{
	//		std::wcerr << L"Error retrieving username: " << GetLastError() << std::endl;
	//		return 1;
	//	}
	//}
	//userName.resize(bufferSize - 1);
	//std::wcout << L"Username (" << nameFormat << L"): " << userName << std::endl;

}

void PrintGetPerformanceInfo() {

	PERFORMANCE_INFORMATION perfInfo;

	// Set the size of the structure before calling the function
	perfInfo.cb = sizeof(PERFORMANCE_INFORMATION);

	printf("\n *** PrintGetPerformanceInfo *** \n\n");
	// Call GetPerformanceInfo to retrieve system performance data
	if (GetPerformanceInfo(&perfInfo, sizeof(PERFORMANCE_INFORMATION))) {
		// Convert page-based values to bytes using PageSize
		ULONGLONG totalPhysicalMemoryBytes = (ULONGLONG)perfInfo.PhysicalTotal * perfInfo.PageSize;
		ULONGLONG availablePhysicalMemoryBytes = (ULONGLONG)perfInfo.PhysicalAvailable * perfInfo.PageSize;
		ULONGLONG systemCacheBytes = (ULONGLONG)perfInfo.SystemCache * perfInfo.PageSize;

		std::cout << "System Performance Information:" << std::endl;
		std::cout << "Total Physical Memory: " << totalPhysicalMemoryBytes / (1024 * 1024) << " MB" << std::endl;
		std::cout << "Available Physical Memory: " << availablePhysicalMemoryBytes / (1024 * 1024) << " MB" << std::endl;
		std::cout << "System Cache Size: " << systemCacheBytes / (1024 * 1024) << " MB" << std::endl;
		std::cout << "Current Processes: " << perfInfo.ProcessCount << std::endl;
		std::cout << "Current Threads: " << perfInfo.ThreadCount << std::endl;
		std::cout << "Current Handles: " << perfInfo.HandlesCount << std::endl;
		std::cout << "Commit Limit (Pages): " << perfInfo.CommitLimit << std::endl;
		std::cout << "Commit Total (Pages): " << perfInfo.CommitTotal << std::endl;
	}
	else {
		std::cerr << "Failed to retrieve performance information. Error code: " << GetLastError() << std::endl;
	}
	printf("----------------------------------------------------\n");
}

int main() {
	
	PrintGetNativeSystemInfo();
	PrintGetSystemInfo();
	PrintGetComputerName();
	PrintGetComputerNameEx();
	PrintGetSystemDirectory();
	PrintGetUserName();
	PrintGetUserNameEx();
	PrintGetPerformanceInfo();
	
	return 0;
}
