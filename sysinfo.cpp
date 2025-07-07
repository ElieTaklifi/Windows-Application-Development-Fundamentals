// System Information
// Use the following functions to display information about the system and the user: 
// GetSystemInfo, GetComputerName, GetComputerNameEx, GetSystemDirectory,
// GetUserName, GetUserNameEx, GetPerformanceInfo.

#include <Windows.h>
#include <stdio.h>

void PrintGetNativeSystemInfo() {
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);

	printf("Number of Logical Processors: %u\n", si.dwNumberOfProcessors);
	printf("Processor Type: %u\n", si.dwProcessorType);
	printf("Allocation Granularity: %u\n", si.dwAllocationGranularity);
	printf("Page size: %u Bytes\n", si.dwPageSize);
	printf("Processor Mask: 0x%zX\n", si.dwActiveProcessorMask);
	printf("Minimumprocess address:0x%p\n", si.lpMinimumApplicationAddress);
	printf("Maximum process address: 0x%p\n", si.lpMaximumApplicationAddress);
	printf("Processor Level: %hu\n", si.wProcessorLevel);
	printf("Processor Revision: %hu\n", si.wProcessorRevision);
}

int main() {
	
	PrintGetNativeSystemInfo();
	
	return 0;
}
