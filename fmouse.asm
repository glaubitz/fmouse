;/*
;* fmouse.asm
;*
;* Virtual Device Driver that sends fake
;* mouse movements to the VMOUSE driver
;* to feign a mouse motion
;*
;* date: Nov., 28 2000
;* (C) Adrian Glaubitz
;* adi007@germanynet.de
;*/

.386p ; yes, we wanna use 386 protected mode instructions

INCLUDE Vmm.inc
INCLUDE Vmd.inc

WM_MOVEMOUSE	Equ	0FFEH
WM_SETMOUSE		Equ	0FFFH

; virtual device declaration
Declare_Virtual_Device FMOUSE, 4, 0, FMouse_Control, Undefined_Device_ID

VxD_LOCKED_DATA_SEG

	InputBfAdress	dd	0
	CurrentX		dd	0
	CurrentY		dd	0
	ButtonStatus	db	0

VxD_LOCKED_DATA_ENDS

VxD_LOCKED_CODE_SEG

    BeginProc FMouse_Control

        Control_Dispatch SYS_DYNAMIC_DEVICE_INIT, FMouse_Dynamic_Init
        Control_Dispatch SYS_DYNAMIC_DEVICE_EXIT, FMouse_Dynamic_Exit
        Control_Dispatch W32_DEVICEIOCONTROL, FMouse_DeviceIOControl
        clc
        ret

    EndProc FMouse_Control

	; W32_DEVICEIOCONTROL message handler
    
	BeginProc FMouse_DeviceIOControl
        
	; load DIOCParams.dwIoControl into EAX

		mov		eax, [esi + 12]
        
	; jump corresponding to the dwIOControl member
	
		mov		edx, [esi + 16]
		mov		[InputBfAdress], edx
		cmp		eax, DIOC_OPEN
		jz		short DeviceIOControlOpen
		cmp		eax, DIOC_CLOSEHANDLE
		jz		short DeviceIOControlCloseHandle
		cmp		eax, WM_MOVEMOUSE
		jz		short MoveMouse
		cmp		eax, WM_SETMOUSE
		jz		short SetMouse
      
	DeviceIOControlDone:
        
		clc
		ret

	DeviceIOControlOpen:
	
	; must return 0 in EAX
	
		xor		eax, eax
		jmp		short DeviceIOControlDone

	DeviceIOControlCloseHandle:

	; must return VXD_SUCCESS in EAX

		mov  eax, VXD_SUCCESS
		jmp  short DeviceIOControlDone

	; it is very likely that it's not needed to check the coordinates
	; whether they exceed a special bounding, is it ?

	MoveMouse:

		VxDcall	VMD_Get_Version ; is this the fixed version of vmouse ?
		cmp		ax, 400h
		jb		short DeviceIOControlDone

		mov		edx, [InputBfAdress]
		mov		eax, [edx] ; DWORD PTR [[esi + 16]]
		add		[CurrentX], eax

		mov		eax, [edx + 4] ; DWORD PTR [[esi + 16] + 4]
		add		[CurrentY], eax

		mov		[ButtonStatus], 0

	; prepare them for call

		mov		esi, [CurrentX]
		mov		edi, [CurrentY]
		mov		al,  [ButtonStatus]

	; post them to VMOUSE

		VxDcall VMD_Post_Absolute_Pointer_Message

		jmp		short DeviceIOControlDone

	SetMouse:

	; set values

	; sorry for the mass of mov's, but if i use
	; "mov DeltaX, [esi + 16]" i get an A2023

		VxDcall	VMD_Get_Version ; is this the fixed version of vmouse ?
		cmp		ax, 400h
		jb		short DeviceIOControlDone
		
		mov		edx, [InputBfAdress]
		mov		eax, [edx] ; DWORD PTR [[esi + 16]]
		mov		[CurrentX], eax
		mov		eax, [edx + 4] ; DWORD PTR [[esi + 16] + 4]
		mov		[CurrentY], eax
		mov		al, [edx + 8] ; BYTE PTR [[esi + 16] + 8]
		mov		[ButtonStatus], al		

	; prepare them for call

		mov		esi, [CurrentX]
		mov		edi, [CurrentY]
		mov		al,  [ButtonStatus]

	; post them to VMOUSE

	VxDcall VMD_Post_Absolute_Pointer_Message

		jmp		DeviceIOControlDone

    EndProc FMouse_DeviceIOControl

    ; SYS_DYNAMIC_DEVICE_EXIT message handler
    
    BeginProc FMouse_Dynamic_Exit

		mov		eax, 1
		clc
		ret

    EndProc FMouse_Dynamic_Exit

VxD_LOCKED_CODE_ENDS

VxD_ICODE_SEG
    
    ; SYS_DYNAMIC_DEVICE_INIT message handler
    
    BeginProc FMouse_Dynamic_Init
        mov		eax, 1
        clc
        ret
    EndProc FMouse_Dynamic_Init

VxD_ICODE_ENDS
    END