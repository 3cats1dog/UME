#pragma once

#ifndef _GPIB
#define _GPIB
#pragma unmanaged

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visa.h"
#include "visatype.h"


public class GPIB
{

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
    /* Functions like strcpy are technically not secure because they do */
    /* not contain a 'length'. But we disable this warning for the VISA */
    /* examples since we never copy more than the actual buffer size.   */
#define _CRT_SECURE_NO_DEPRECATE
#endif



    ViSession inst;
    ViSession defaultRM;
    const ViUInt32 WaitTimeout = 300; /* Timeout in milliseconds */
    ViEvent ehandle;
    ViEventType etype;
    ViStatus status;
    ViUInt32 rcount;
    ViUInt16 statusByte;
    ViPSession inst1;
    unsigned char data[3000];
    ViBoolean TERM_EN = VI_TRUE;
    ViChar TERM_CHAR = 0x0A;
    const unsigned int MAXBUFF = 30000;
   
    const int DataAvaliable = 16;
    const int HasError = 4;
    char stringinput[512], nextstringinput[512];

    char instrDescriptor[VI_FIND_BUFLEN];
    ViUInt32 numInstrs;
    ViFindList findList;
    //ViSession  instr;



    int main1(void)
    {
        /*
         *  First we open a session to the VISA resource manager.  We are
         *  returned a handle to the resource manager session that we must
         *  use to open sessions to specific instruments.
         */

        status = viOpenDefaultRM(&defaultRM);
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the VISA Resource Manager!\n");
            exit(EXIT_FAILURE);
        }

        /*
         *  Next we use the resource manager handle to open a session to a
         *  GPIB instrument at address 2.  A handle to this session is
         *  returned in the handle inst.
         */
        status = viOpen(defaultRM, "GPIB2::5::INSTR", VI_NULL, VI_NULL, &inst);
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the device simulator");
            goto Close;
        }


        /*  Now we must enable the service request event so that VISA
         *  will receive the events.  Note: one of the parameters is
         *  VI_QUEUE indicating that we want the events to be handled by
         *  a synchronous event queue.  The alternate mechanism for handling
         *  events is to set up an asynchronous event handling function using
         *  the VI_HNDLR option.  The events go into a queue which by default
         *  can hold 50 events.  This maximum queue size can be changed with
         *  an attribute but it must be called before the events are enabled.
         */
        status = viEnableEvent(inst, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
        if (status < VI_SUCCESS)
        {
            printf("The SRQ event could not be enabled");
            goto Close;
        }

        /*
         *  Now the VISA write command is used to send a request to the
         *  instrument to generate a sine wave and assert the SRQ line
         *  when it is finished.  Notice that this is specific to one
         *  particular instrument.
         */
        strcpy(stringinput, "SYST:PRES\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        if (status < VI_SUCCESS)
        {
            printf("Error writing to the instrument\n");
            goto Close;
        }

        strcpy(stringinput, "CONF:VOLT:DC 1\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        if (status < VI_SUCCESS)
        {
            printf("Error writing to the instrument\n");
            goto Close;
        }

        viReadSTB(inst, &statusByte);
        if (statusByte || 4 > 0)
        {
            strcpy(stringinput, "SYST:ERR?\n");
            status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
            status = viRead(inst, data, 3000, &rcount);

        }

        strcpy(stringinput, "VOLT:DC:APER 1E-3\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        strcpy(stringinput, "FORMAT:DATA REAL\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        strcpy(stringinput, "SAMP:COUN 1000\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        strcpy(stringinput, "INIT; *WAI; READ?\n");
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);

        if (status < VI_SUCCESS)
        {
            printf("Error writing to the instrument\n");
            goto Close;
        }
        viReadSTB(inst, &statusByte);

        /*
         *  Now we wait for an SRQ event to be received by the event queue.
         *  The timeout is in milliseconds and is set to 30000 or 30 seconds.
         *  Notice that a handle to the event is returned by the viWaitOnEvent
         *  call.  This event handle can be used to obtain various
         *  attributes of the event.  Finally, the event handle should be closed
         *  to free system resources.
         */
         //printf("\nWaiting for an SRQ Event\n\n");
         //status = viWaitOnEvent(inst, VI_EVENT_SERVICE_REQ, WaitTimeout, &etype, &ehandle);

         /*
          *  If an SRQ event was received we first read the status byte with
          *  the viReadSTB function.  This should always be called after
          *  receiving a GPIB SRQ event, or subsequent events will not be
          *  received properly.  Then the data is read and the event is closed
          *  and the data is displayed.  Otherwise sessions are closed and the
          *  program terminates.
          */

        while (true)
        {
            status = viReadSTB(inst, &statusByte);
            if (status < VI_SUCCESS)
            {
                printf("There was an error reading the status byte");
                goto Close;
            }

            if (statusByte || DataAvaliable > 0)
            {
                break;
            }
        }


        if (status >= VI_SUCCESS || 3 > 2)
        {
            status = viReadSTB(inst, &statusByte);
            if (status < VI_SUCCESS)
            {
                printf("There was an error reading the status byte");
                goto Close;
            }

            /*strcpy(nextstringinput, "MEAS:VOLT:DC?\n");
            status = viWrite(inst, (ViBuf)nextstringinput, (ViUInt32)strlen(nextstringinput), &rcount);
            if (status < VI_SUCCESS)
            {
                printf("There was an error writing the command to get the data");
                goto Close;
            }*/

            status = viRead(inst, Fulldata, 16000, &rcount);
            if (status < VI_SUCCESS)
            {
                printf("There was an error reading the data");
                goto Close;
            }

            status = viClose(ehandle);
            if (status < VI_SUCCESS)
            {
                printf("There was an error closing the event handle");
                goto Close;
            }

            printf("Here is the data: %*s\n", rcount, Fulldata);
        }

        /*
         *  Now we must close the session to the instrument and the session
         *  to the resource manager.
         */
    Close:
        status = viClose(inst);
        status = viClose(defaultRM);
        printf("Hit enter to continue.");
        fflush(stdin);
        getchar();

        return 0;
    }

public:
    GPIB() {}
    ~GPIB() {}
    unsigned char Fulldata[30000];
    bool isConnected;

    char* getRscr() { 
        int chrIndex = 0;
        char findingResource[VI_FIND_BUFLEN * 50];
        findingResource[chrIndex] = 0;

        status = viOpenDefaultRM(&defaultRM);
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the VISA Resource Manager!\n");
            return findingResource;
        }

        status = viFindRsrc(defaultRM, "?*INSTR", &findList, &numInstrs, instrDescriptor);
        if (status < VI_SUCCESS)
        {
            printf("An error occurred while finding resources.\nHit enter to continue.");
            viClose(defaultRM);
            return findingResource;
        }

        printf("%d instruments, serial ports, and other resources found:\n\n", numInstrs);
        printf("%s \n", instrDescriptor);
        for (int i = 0; i < strlen(instrDescriptor); i++)
        {
            findingResource[chrIndex++] = instrDescriptor[i];
        } 
        findingResource[chrIndex++] = ';';
        findingResource[chrIndex] = 0;

        while (--numInstrs)
        {
            /* stay in this loop until we find all instruments */
            status = viFindNext(findList, instrDescriptor);  /* find next desriptor */
            if (status < VI_SUCCESS)
            {   /* did we find the next resource? */
                printf("An error occurred finding the next resource.\nHit enter to continue.");
                viClose(defaultRM);
                return findingResource;
            }
            printf("%s \n", instrDescriptor);
            for (int i = 0; i < strlen(instrDescriptor); i++)
            {
                findingResource[chrIndex++] = instrDescriptor[i];
            }
            findingResource[chrIndex++] = ';';
            findingResource[chrIndex] = 0;
        }
        viClose(defaultRM);
        return &findingResource[0];
    }

    bool Close()
    {
        status = viClose(inst);
        status = viClose(defaultRM);
        isConnected = false;
        return true;
    }
    bool Open(char* rsc)
    {
        status = viOpenDefaultRM(&defaultRM);
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the VISA Resource Manager!\n");
            return false;
        }

        status = viOpen(defaultRM, rsc , VI_NULL, WaitTimeout, &inst);      //"GPIB2::5::INSTR"    VI_NULL
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the device simulator");
            Close();
            return false;
        }

        ViUInt32 timeOut = 0;
        ViUInt8 Prot  =1;
        status = viSetAttribute(inst, VI_ATTR_TMO_VALUE, WaitTimeout);

        status = viGetAttribute(inst, VI_ATTR_TERMCHAR, &TERM_CHAR);
        status = viGetAttribute(inst, VI_ATTR_TERMCHAR_EN, &TERM_EN);
        status = viGetAttribute(inst, VI_ATTR_TMO_VALUE, &timeOut);               
        status = viGetAttribute(inst, VI_ATTR_IO_PROT, &Prot);
        /*   
             VI_PROT_NORMAL              (1)
             VI_PROT_FDC                 (2)
             VI_PROT_HS488               (3)
             VI_PROT_4882_STRS           (4)
             VI_PROT_USBTMC_VENDOR       (5)
        */
        

        //status = viSetAttribute(instr, VI_ATTR_ASRL_BAUD, 2400);
        //status = viSetAttribute(instr, VI_ATTR_ASRL_DATA_BITS, 7);
        ViUInt32 baud =0;
        ViUInt32 dbits = 0;
        ViUInt32 tmo = 0;
        void _VI_PTR attrValue = &baud;
        char* eptySpace;
        eptySpace = new char[2000];


        status = viReadSTB(inst, &statusByte);
        status = viGetAttribute(defaultRM, VI_ATTR_USER_DATA_64, eptySpace);        //0
        status = viGetAttribute(defaultRM, VI_ATTR_RSRC_NAME, eptySpace);           //0
        status = viGetAttribute(defaultRM, VI_ATTR_RSRC_SPEC_VERSION, eptySpace);   //0
        status = viGetAttribute(defaultRM, VI_ATTR_RM_SESSION, eptySpace);          //0
        status = viGetAttribute(defaultRM, VI_ATTR_MAX_QUEUE_LENGTH, eptySpace);    //VI_ERROR_INV_OBJECT


       
        // VI_ERROR_NSUP_ATTR = -1073807331
        // VI_ERROR_INV_OBJECT =-1073807346
        //status = viEnableEvent(inst, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
        //if (status < VI_SUCCESS)
        //{
        //    printf("The SRQ event could not be enabled");
        //    Close();
        //    return false;
        //}
        isConnected = true;
        return true;
    }
    int ReadSTB()
    {
       /* Fulldata[0] = 0;
        char* cmd = "STB?\n";
        strcpy(stringinput, cmd);   
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        status = viRead(inst, Fulldata, 250, &rcount);*/
        status = viReadSTB(inst, &statusByte);
        return statusByte;
    }
    bool SendCommand(char* cmd)
    {   
        strcpy(stringinput, cmd);            //"CONF:VOLT:DC 1\n"
        status = viWrite(inst, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &rcount);
        if (status < VI_SUCCESS)
        {
            printf("Error writing to the instrument\n");
            //Close();
            return false;
        }
        return true;
    }
    int ReadAnswerBinary()
    {
        rcount = 0;
        status = viRead(inst, Fulldata, 30000, &rcount);

        if (status < VI_SUCCESS)
        {
            printf("There was an error reading the data");
        }
        return rcount;
    }

    char* ReadAnswerWithOneByte()
    {
        unsigned char OneByte[1];
        Fulldata[0] = 0;
        unsigned int fIndex = 0;
        bool devam = true;
        while (devam)
        {
            status = viRead(inst, OneByte, 1, &rcount);
            if (status < VI_SUCCESS)        //VI_ERROR_TMO  = -1073807339
            {
                devam = false;
            }
            else
            {
                Fulldata[fIndex++] = OneByte[0];
                if (OneByte[0] == '\n')
                {
                    devam = false;
                }
            }
        }
        Fulldata[fIndex++] = 0;
        return (char*)&Fulldata;
    }
    char* ReadAnswer()
    {
        unsigned char OneByte[1];

        Fulldata[0] = 0;
        status = viRead(inst, Fulldata, 250, &rcount);
        //status = viBufRead(inst, Fulldata, 250, &rcount);

        if (status < VI_SUCCESS)
        {
            printf("There was an error reading the data");
            //Close();
            if (rcount < 0 || rcount>250)
            {
                Fulldata[0] = 0;
            }
            else
            {
                Fulldata[rcount] = 0;
            }
            return (char*)&Fulldata;
        }
        else
        {
            Fulldata[rcount] = 0;
            return (char*)&Fulldata;
        }
    }
    char* ReadAnswerBig()
    {
        Fulldata[0] = 0;
        status = viRead(inst, Fulldata, 30000, &rcount);

        if (status < VI_SUCCESS)
        {
            printf("There was an error reading the data");
            //Close();
            if (rcount < 0 || rcount>290000)
            {
                Fulldata[0] = 0;
            }
            else
            {
                Fulldata[rcount] = 0;
            }
            return (char*)&Fulldata;
        }
        else
        {
            Fulldata[rcount] = 0;
            return (char*)&Fulldata;
        }
    }
};
#endif



