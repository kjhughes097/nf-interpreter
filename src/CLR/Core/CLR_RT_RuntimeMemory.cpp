//
// Copyright (c) 2017 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#include "nanoCLR_Interop.h"

//////////////////////////////////////// 
// !!! DO NOT EDIT THIS FILE !!! 

#define LINK_SIZE_BYTES              4
#define PAYLOAD_SIZE_BYTES          12
#define INTERRUPT_RECORD_SIZE_BYTES 24
#define INLINE_SIZE_BYTES           (8 * sizeof(int*) + sizeof(int))

#define ENTRY_SIZE__extrasmall          32
#define HASH_TABLE_ENTRY__extrasmall     9
#define INTERRUPT_RECORDS__extrasmall   16
#define INLINE_BUFFER__extrasmall       16

#define ENTRY_SIZE__small              128
#define HASH_TABLE_ENTRY__small         33
#define INTERRUPT_RECORDS__small        64
#define INLINE_BUFFER__small            32
 
#define ENTRY_SIZE__medium             512
#define HASH_TABLE_ENTRY__medium       129
#define INTERRUPT_RECORDS__medium      128
#define INLINE_BUFFER__medium           64

#define ENTRY_SIZE__large             2048
#define HASH_TABLE_ENTRY__large        521
#define INTERRUPT_RECORDS__large       512
#define INLINE_BUFFER__large           128

/////////////////////////////////////////////
// undefine everything and define defaults
#ifdef  PLATFORM_DEPENDENT_ENTRY_SIZE
#undef  PLATFORM_DEPENDENT_ENTRY_SIZE
#endif
#define PLATFORM_DEPENDENT_ENTRY_SIZE ENTRY_SIZE__medium

#ifdef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE
#undef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE
#endif
#define PLATFORM_DEPENDENT_HASH_TABLE_SIZE HASH_TABLE_ENTRY__medium

#ifdef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#undef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#endif
#define PLATFORM_DEPENDENT_INTERRUPT_RECORDS INTERRUPT_RECORDS__medium

#ifdef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#undef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#endif
#define PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE INLINE_BUFFER__medium

// undefine everything and define defaults
/////////////////////////////////////////////

////////////////////////////////////////////////////////
// apply user selection from platform_selector.h file
#ifdef RUNTIME_MEMORY_PROFILE__extrasmall
#undef  PLATFORM_DEPENDENT_ENTRY_SIZE
#define PLATFORM_DEPENDENT_ENTRY_SIZE ENTRY_SIZE__extrasmall
#undef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE
#define PLATFORM_DEPENDENT_HASH_TABLE_SIZE HASH_TABLE_ENTRY__extrasmall
#undef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#define PLATFORM_DEPENDENT_INTERRUPT_RECORDS INTERRUPT_RECORDS__extrasmall
#undef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#define PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE INLINE_BUFFER__extrasmall
#endif

#ifdef RUNTIME_MEMORY_PROFILE__small
#undef  PLATFORM_DEPENDENT_ENTRY_SIZE
#define PLATFORM_DEPENDENT_ENTRY_SIZE ENTRY_SIZE__small
#undef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE
#define PLATFORM_DEPENDENT_HASH_TABLE_SIZE HASH_TABLE_ENTRY__small
#undef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#define PLATFORM_DEPENDENT_INTERRUPT_RECORDS INTERRUPT_RECORDS__small
#undef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#define PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE INLINE_BUFFER__small
#endif

#ifdef RUNTIME_MEMORY_PROFILE__medium
#undef  PLATFORM_DEPENDENT_ENTRY_SIZE
#define PLATFORM_DEPENDENT_ENTRY_SIZE ENTRY_SIZE__medium
#undef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE
#define PLATFORM_DEPENDENT_HASH_TABLE_SIZE HASH_TABLE_ENTRY__medium
#undef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#define PLATFORM_DEPENDENT_INTERRUPT_RECORDS INTERRUPT_RECORDS__medium
#undef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#define PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE INLINE_BUFFER__medium
#endif

#ifdef RUNTIME_MEMORY_PROFILE__large
#undef  PLATFORM_DEPENDENT_ENTRY_SIZE
#define PLATFORM_DEPENDENT_ENTRY_SIZE ENTRY_SIZE__large 
#undef  PLATFORM_DEPENDENT_HASH_TABLE_SIZE 
#define PLATFORM_DEPENDENT_HASH_TABLE_SIZE HASH_TABLE_ENTRY__large  
#undef  PLATFORM_DEPENDENT_INTERRUPT_RECORDS
#define PLATFORM_DEPENDENT_INTERRUPT_RECORDS INTERRUPT_RECORDS__large
#undef  PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE
#define PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE INLINE_BUFFER__large
#endif
// apply user selection from platform_selector.h file
////////////////////////////////////////////////////////

//--//

size_t LinkArraySize   () { return (PLATFORM_DEPENDENT_ENTRY_SIZE  + PLATFORM_DEPENDENT_HASH_TABLE_SIZE); } 
size_t LinkMRUArraySize() { return (PLATFORM_DEPENDENT_ENTRY_SIZE  + 1                                 ); } 
size_t PayloadArraySize() { return  PLATFORM_DEPENDENT_ENTRY_SIZE;                                        } 
#ifndef CLR_NO_IL_INLINE
size_t InlineBufferCount() { return PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE; }
#endif

unsigned int g_scratchVirtualMethodTableLink   [ LINK_SIZE_BYTES    * (PLATFORM_DEPENDENT_ENTRY_SIZE  + PLATFORM_DEPENDENT_HASH_TABLE_SIZE) / sizeof(unsigned int) + 1 ];
unsigned int g_scratchVirtualMethodTableLinkMRU[ LINK_SIZE_BYTES    * (PLATFORM_DEPENDENT_ENTRY_SIZE  + 1                                 ) / sizeof(unsigned int) + 1 ];
unsigned int g_scratchVirtualMethodPayload     [ PAYLOAD_SIZE_BYTES *  PLATFORM_DEPENDENT_ENTRY_SIZE                                        / sizeof(unsigned int) + 1 ]; 

#ifndef CLR_NO_IL_INLINE
unsigned int g_scratchInlineBuffer[ INLINE_SIZE_BYTES * PLATFORM_DEPENDENT_INLINE_BUFFER_SIZE / sizeof(unsigned int) + 1 ];
#endif

//--//

size_t InterruptRecords() { return PLATFORM_DEPENDENT_INTERRUPT_RECORDS; } 

unsigned int g_scratchInterruptDispatchingStorage[ (PLATFORM_DEPENDENT_INTERRUPT_RECORDS  * INTERRUPT_RECORD_SIZE_BYTES) / sizeof(unsigned int) + 1 ];

//--//

// !!! DO NOT EDIT THIS FILE  !!! 
////////////////////////////////////////

