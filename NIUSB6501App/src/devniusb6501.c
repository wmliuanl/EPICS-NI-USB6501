#include <stdio.h>

#include <dbDefs.h>
#include <registryFunction.h>
#include <biRecord.h>
#include <boRecord.h>
#include <epicsExport.h>

void SetBVal(int ChIndx,long val);
long GetBVal(int ChIndx);


long write_niusbbo();
long read_niusbbi();


struct {
    long        number;
    DEVSUPFUN   report;
    DEVSUPFUN   init;
    DEVSUPFUN   init_record;
    DEVSUPFUN   get_ioint_info;
    DEVSUPFUN   read_xxx;
    }devNIUSB6501bi={
    5,
    NULL,
    NULL,
    NULL,
    NULL,
    read_niusbbi,
};

struct {
    long        number;
    DEVSUPFUN   report;
    DEVSUPFUN   init;
    DEVSUPFUN   init_record;
    DEVSUPFUN   get_ioint_info;
    DEVSUPFUN   write_bo;
}devNIUSB6501bo = {
    5,
    NULL,
    NULL,
    NULL,
    NULL,
    write_niusbbo,
};





epicsExportAddress(dset,devNIUSB6501bi);
epicsExportAddress(dset,devNIUSB6501bo);


long write_niusbbo(prec)
struct boRecord* prec;
{
    int chindx;
    prec->pact=TRUE;
    if (prec->out.type == INST_IO) {
		if(sscanf(prec->out.value.instio.string,"Ch:%d",&chindx)==1) {
            SetBVal(chindx, prec->val);
        }
    }
    prec->pact = FALSE;
    return(0);
}



long read_niusbbi(prec)
struct biRecord* prec;
{
    prec->pact=TRUE;
    long status;
    int chindx;
    if (prec->inp.type == INST_IO) {
		if(sscanf(prec->inp.value.instio.string,"Ch:%d",&chindx)==1) {
            status=GetBVal(chindx);
            prec->rval= (status!=0);
        }
       else prec->rval=0;
    }
    prec->pact = FALSE;
    return(0);
}


