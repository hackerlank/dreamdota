#include "stdafx.h"
#include <sddl.h>

//
//   FUNCTION: CreatePipeSecurity(PSECURITY_ATTRIBUTES *)
//
//   PURPOSE: The CreatePipeSecurity function creates and initializes a new 
//   SECURITY_ATTRIBUTES structure to allow Authenticated Users read and 
//   write access to a pipe, and to allow the Administrators group full 
//   access to the pipe.
//
//   PARAMETERS:
//   * ppSa - output a pointer to a SECURITY_ATTRIBUTES structure that allows 
//     Authenticated Users read and write access to a pipe, and allows the 
//     Administrators group full access to the pipe. The structure must be 
//     freed by calling FreePipeSecurity.
//
//   RETURN VALUE: Returns TRUE if the function succeeds.
//
//   EXAMPLE CALL:
//
//     PSECURITY_ATTRIBUTES pSa = NULL;
//     if (CreatePipeSecurity(&pSa))
//     {
//         // Use the security attributes
//         // ...
//
//         FreePipeSecurity(pSa);
//     }
//
BOOL CreatePipeSecurity(PSECURITY_ATTRIBUTES *ppSa)
{
    BOOL fSucceeded = TRUE;
    DWORD dwError = ERROR_SUCCESS;

    PSECURITY_DESCRIPTOR pSd = NULL;
    PSECURITY_ATTRIBUTES pSa = NULL;

    // Define the SDDL for the security descriptor.
    PCWSTR szSDDL = L"D:"       // Discretionary ACL
        L"(A;OICI;GRGW;;;AU)"   // Allow read/write to authenticated users
        L"(A;OICI;GA;;;BA)";    // Allow full control to administrators

    if (!ConvertStringSecurityDescriptorToSecurityDescriptor(szSDDL, 
        SDDL_REVISION_1, &pSd, NULL))
    {
        fSucceeded = FALSE;
        dwError = GetLastError();
        goto Cleanup;
    }
    
    // Allocate the memory of SECURITY_ATTRIBUTES.
    pSa = (PSECURITY_ATTRIBUTES)LocalAlloc(LPTR, sizeof(*pSa));
    if (pSa == NULL)
    {
        fSucceeded = FALSE;
        dwError = GetLastError();
        goto Cleanup;
    }

    pSa->nLength = sizeof(*pSa);
    pSa->lpSecurityDescriptor = pSd;
    pSa->bInheritHandle = FALSE;

    *ppSa = pSa;

Cleanup:
    // Clean up the allocated resources if something is wrong.
    if (!fSucceeded)
    {
        if (pSd)
        {
            LocalFree(pSd);
            pSd = NULL;
        }
        if (pSa)
        {
            LocalFree(pSa);
            pSa = NULL;
        }

        SetLastError(dwError);
    }
    
    return fSucceeded;
}

//
//   FUNCTION: FreePipeSecurity(PSECURITY_ATTRIBUTES)
//
//   PURPOSE: The FreePipeSecurity function frees a SECURITY_ATTRIBUTES 
//   structure that was created by the CreatePipeSecurity function. 
//
//   PARAMETERS:
//   * pSa - pointer to a SECURITY_ATTRIBUTES structure that was created by 
//     the CreatePipeSecurity function. 
//
void FreePipeSecurity(PSECURITY_ATTRIBUTES pSa)
{
    if (pSa)
    {
        if (pSa->lpSecurityDescriptor)
        {
            LocalFree(pSa->lpSecurityDescriptor);
        }
        LocalFree(pSa);
    }
}