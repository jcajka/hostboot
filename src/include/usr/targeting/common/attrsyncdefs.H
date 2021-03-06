/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/include/usr/targeting/common/attrsyncdefs.H $             */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2012,2014              */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef __ATTRSYNC_DEFS_H__
#define __ATTRSYNC_DEFS_H__

//******************************************************************************
// Macros
//******************************************************************************
// constants for use in masking off corresponding bytes in message data words
// used for attribute synchronization mbox messages, sectoin ID and page
// number are used in the sync messages
const uint64_t SECTIONID_MASK       = 0xFFFF000000000000;
const uint64_t PAGE_NUMBER_MASK     = 0x0000FFFF00000000;

// page count mask, used in attribute sync commit message  
const uint64_t PAGE_COUNT_MASK      = 0xFFFF000000000000;

// mask to manipulate the return code field in the data returned in the
// response to an attribute sync commit message
const uint64_t RETURN_CODE_MASK     = 0xFFFF000000000000;


// used to add the section into the first data word of an attribute sync
// message - only modifies the first two bytes of the uint64_t
#define ATTR_SYNC_ADD_SECTION_ID( sectionId, data0 )  \
                            ( data0 = ( data0 & ~SECTIONID_MASK) | \
                            ( static_cast<uint64_t>(sectionId) << 48 ) )

// used to get the section from the first data word of an attribute sync
// message - only retrieves the first two bytes of the uint64_t
#define ATTR_SYNC_GET_SECTION_ID( data0 ) ( static_cast<SECTION_TYPE>( \
                            ( data0 & SECTIONID_MASK ) >> 48 ) )

// used to add the number of the current page to be sync'd. used in the
// attribute sync message code. Only modifies the second two bytes 
// of the uint64_t
#define ATTR_SYNC_ADD_PAGE_NUMBER( pageNumber, data0 )    \
                            ( data0 = ( data0 & ~PAGE_NUMBER_MASK) | \
                            ( static_cast<uint64_t>(pageNumber) << 32 ) )

// used to get the number of the current page to be sync'd. used in the
// attribute sync message code. Only retrieves the second two bytes
// of the uint64_t
#define ATTR_SYNC_GET_PAGE_NUMBER( data0 ) ( static_cast<uint16_t>( \
                            ( data0 & PAGE_NUMBER_MASK ) >> 32 ) )

// Used in the commit message sent after all the pages of the current section
// are sent, the macro will add the total page count to the first two bytes
// of the data[0] uint64_t in the mailbox message.
#define ATTR_SYNC_ADD_PAGE_COUNT( pageCount, data0 ) \
                            ( data0 = ( data0 & ~PAGE_COUNT_MASK) | \
                            ( static_cast<uint64_t>(pageCount) << 48 ) )

// Used in the commit message sent after all the pages of the current section
// are sent, the macro will extract the total page count from the first two bytes
// of the data[0] uint64_t in the mailbox message.
#define ATTR_SYNC_GET_PAGE_COUNT( data0 ) ( static_cast<uint16_t> ( \
                            ( data0 & PAGE_COUNT_MASK ) >> 48 ) )

// sets the return code in the first 2 bytes of the mailbox message
#define ATTR_SYNC_ADD_RC( rc, data0 ) \
                            ( data0 = (data0 & ~RETURN_CODE_MASK) | \
                            ( static_cast<uint64_t>(rc) << 48 ) )

// gets the return code from the uint64_t returned by the mailbox message
#define ATTR_SYNC_GET_RC( data0 ) ( static_cast<ATTR_SYNC_RC>( \
                            ( data0 & RETURN_CODE_MASK )  >> 48 ))

namespace   TARGETING
{
    /**
     * @enum TARGETING::ATTR_SYNC_MSG_TYPE
     *
     * @brief  Targeting attribute sync service message types for use in the
     *         attribute sync messages between FSP and Hostboot
     */
    enum ATTR_SYNC_MSG_TYPE
    {
        //NOTE: Types cannot overlap with types in utillidmgrdefs.H
        //  due to common FSP message queue
        ATTR_SYNC_NO_MSG          = 0,
        ATTR_SYNC_SECTION_TO_FSP  = 0x000000A1,
        ATTR_SYNC_COMPLETE_TO_FSP = 0x000000A2,
        ATTR_SYNC_REQUEST_TO_HB   = 0x000000A3,
        ATTR_SYNC_SECTION_TO_HB   = 0x000000A4,
        ATTR_SYNC_COMPLETE_TO_HB  = 0x000000A5,
    };


    /**
     * @enum TARGETING::ATTR_SYNC_RC
     *
     * @brief  Return code values for the sync complete message used by HB
     *         and the FSP when the sync has been completed.
     *
     */
    enum ATTR_SYNC_RC
    {
        ATTR_SYNC_SUCCESS = 0,
        ATTR_SYNC_FAILURE = 1
    };

}; // end namespace

#endif
