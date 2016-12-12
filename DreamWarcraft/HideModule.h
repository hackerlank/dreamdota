#include <Windows.h>
#include <VMP.h>

void HideModule(HMODULE module_handle)
{
	DWORD p_peb_ldr_data = 0;
	__asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h];			// PEB
		mov eax, [eax+0Ch];			// PEB->ProcessModuleInfo
		mov p_peb_ldr_data, eax;	// Save ProcessModuleInfo

//in_load_order_module_list:
		mov esi, [eax+0Ch];			// ProcessModuleInfo->in_load_order_module_list[FORWARD]
		mov edx, [eax+10h];			//  ProcessModuleInfo->in_load_order_module_list[BACKWARD]

loop_in_load_order_module_list: 
		lodsd;						//  Load First Module
		mov esi, eax;		    	//  ESI points to Next Module
		mov ecx, [eax+18h];			//  LDR_MODULE->BaseAddress
		cmp ecx, module_handle;		//  Is it Our Module ?
		jne skip_a;		    		//  If Not, Next Please (@f jumps to nearest Unamed Lable @@:)
		mov ebx, [eax];				//  [FORWARD] Module 
		mov ecx, [eax+4];    		//  [BACKWARD] Module
		mov [ecx], ebx;				//  Previous Module's [FORWARD] Notation, Points to us, Replace it with, Module++
		mov [ebx+4], ecx;			//  Next Modules, [BACKWARD] Notation, Points to us, Replace it with, Module--
		jmp in_memory_order_module_list;		//  Hidden, so Move onto Next Set
skip_a:
		cmp edx, esi;							//  Reached End of Modules ?
		jne loop_in_load_order_module_list;		//  If Not, Re Loop

in_memory_order_module_list:
		mov eax, p_peb_ldr_data;	  //  PEB->ProcessModuleInfo
		mov esi, [eax+14h];			  //  ProcessModuleInfo->in_memory_order_module_list[START]
		mov edx, [eax+18h];			  //  ProcessModuleInfo->in_memory_order_module_list[FINISH]

loop_in_memory_order_module_list: 
		lodsd;
		mov esi, eax;
		mov ecx, [eax+10h];
		cmp ecx, module_handle;
		jne skip_b;
		mov ebx, [eax]; 
		mov ecx, [eax+4];
		mov [ecx], ebx;
		mov [ebx+4], ecx;
		jmp in_initialization_order_module_list;
skip_b:
		cmp edx, esi;
		jne loop_in_memory_order_module_list;

in_initialization_order_module_list:
		mov eax, p_peb_ldr_data;		//  PEB->ProcessModuleInfo
		mov esi, [eax+1Ch];				//  ProcessModuleInfo->in_initialization_order_module_list[START]
		mov edx, [eax+20h];				//  ProcessModuleInfo->in_initialization_order_module_list[FINISH]

loop_in_initialization_order_module_list: 
		lodsd;
		mov esi, eax;		
		mov ecx, [eax+08h];
		cmp ecx, module_handle;		
		jne skip_c;
		mov ebx, [eax]; 
		mov ecx, [eax+4];
		mov [ecx], ebx;
		mov [ebx+4], ecx;
		jmp Finished;
skip_c:
		cmp edx, esi;
		jne loop_in_initialization_order_module_list;

Finished:
		popfd;
		popad;
	}
}
