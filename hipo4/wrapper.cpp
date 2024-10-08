#include <iostream>
#include "event.h"
#include "fusion.h"
#include "reader.h"

hipo::reader hipo_FORT_Reader;
hipo::event hipo_FORT_Event;
hipo::dictionary hipo_FORT_Dictionary;

std::map<std::string, hipo::bank*> eventStore;

hipo::fusion hFusion;

extern "C" {

void hipo_file_open_(const char* filename, int length) {
    char* buffer = (char*)malloc(length + 1);
    memcpy(buffer, filename, length);
    buffer[length] = '\0';
    printf("[FORTRAN] opening file : %s\n", buffer);
    hipo_FORT_Reader.open(buffer);
    hipo_FORT_Reader.readDictionary(hipo_FORT_Dictionary);
    free(buffer);
}

void hipo_file_open(const char* filename) {
    hipo_FORT_Reader.open(filename);
    hipo_FORT_Reader.readDictionary(hipo_FORT_Dictionary);
}

int hipo_file_next_(int* fstatus) {
    bool status = hipo_FORT_Reader.next();
    if (status == false) {
        *fstatus = 12;
        return 12;
    }
    hipo_FORT_Reader.read(hipo_FORT_Event);
    std::map<std::string, hipo::bank*>::iterator it;
    for (it = eventStore.begin(); it != eventStore.end(); it++) {
        it->second->reset();  // string's value
    }
    *fstatus = 0;
    return 0;
}

void hipo_read_bank_(const char* bankname, int* bankRows, int banknameLength) {
    char* buffer = (char*)malloc(banknameLength + 1);
    memcpy(buffer, bankname, banknameLength);
    buffer[banknameLength] = '\0';
    if (eventStore.count(std::string(buffer)) == 0) {
        if (hipo_FORT_Dictionary.hasSchema(buffer) == true) {
            hipo::bank* bank_ptr = new hipo::bank(hipo_FORT_Dictionary.getSchema(buffer));
            eventStore[buffer] = bank_ptr;
            printf("---> map : initializing bank \"%24s\" (%6d, %5d) to the store\n",
                   buffer, hipo_FORT_Dictionary.getSchema(buffer).getGroup(),
                   hipo_FORT_Dictionary.getSchema(buffer).getItem());
        } else {
            *bankRows = 0;
            free(buffer);
            return;
        }
    }

    hipo_FORT_Event.getStructure(*eventStore[buffer]);
    *bankRows = eventStore[buffer]->getRows();
    free(buffer);
}

/*
  void hipo_read_bank_byid_(int *group, int *item){
    int igroup = *group;
    int iitem = *item;

    if(eventStore.count(igroup)==0){
        printf("********* bank does not exist %d\n",igroup);
        std::vector<std::string> schemaList = hipo_FORT_Dictionary.getSchemaList();
        for(int i = 0; i < schemaList.size(); i++){
            int schGroup = hipo_FORT_Dictionary.getSchema(schemaList[i].c_str()).getGroup();
            if(schGroup==igroup){
              printf(" found group = %d\n",schGroup);
               printf("---> map : initializing bank \"%24s\" (%6d) to the store\n",
                 schemaList[i].c_str(),schGroup);
                 hipo::bank *bank_ptr = new hipo::bank(hipo_FORT_Dictionary.getSchema(schemaList[i].c_str()));
                 eventStore[schGroup] = bank_ptr;
            }
        }
    }
  }*/

void get_bank_rows_(int* group, int* bankRows) {
    /*int igroup = *group;
      if(eventStore.count(igroup)==0) *bankRows = 0;
      *bankRows = eventStore[igroup]->getRows();*/
}

void hipo_read_float_(const char* group, const char* item, int* nread, float* buffer, int* maxRows,
                      int length_group, int length_item) {

    char* buffer_group = (char*)malloc(length_group + 1);
    memcpy(buffer_group, group, length_group);
    buffer_group[length_group] = '\0';

    char* buffer_item = (char*)malloc(length_item + 1);
    memcpy(buffer_item, item, length_item);
    buffer_item[length_item] = '\0';

    //printf("---->>>>> reading float (%s) (%s)\n",buffer_group,buffer_item);
    /*int id_g = *group;
      int id_i = ;
      int max  = *maxRows;
      //printf("READIN FLOAT %d %d \n",*group,*item);
      //std::vector<float> vec = hipo_FORT_Reader.getEvent()->getFloat(id_g,id_i);
      //printf("RESULT SIZE = %d \n",vec.size());
      for(int i = 0; i < vec.size(); i++){
	       if(i<max) buffer[i] = vec[i];
      }
      *nread = vec.size();*/
    if (eventStore.count(buffer_group) == 0) {
        *nread = 0;
        free(buffer_group);
        free(buffer_item);
        return;
    }

    hipo::bank* bank = eventStore[buffer_group];
    int nrows = bank->getRows();
    if (nrows > (*maxRows))
        nrows = *(maxRows);
    //printf("---->>>>> reading float (%s) (%s) (%d)\n",buffer_group,buffer_item,nrows);
    for (int i = 0; i < nrows; i++) {
        buffer[i] = bank->getFloat(buffer_item, i);
    }
    *nread = nrows;

    free(buffer_group);
    free(buffer_item);
}

void hipo_read_double_(const char* group, const char* item, int* nread, double* buffer, int* maxRows,
                       int length_group, int length_item) {

    char* buffer_group = (char*)malloc(length_group + 1);
    memcpy(buffer_group, group, length_group);
    buffer_group[length_group] = '\0';

    char* buffer_item = (char*)malloc(length_item + 1);
    memcpy(buffer_item, item, length_item);
    buffer_item[length_item] = '\0';

    if (eventStore.count(buffer_group) == 0) {
        *nread = 0;
        free(buffer_group);
        free(buffer_item);
        return;
    }

    hipo::bank* bank = eventStore[buffer_group];
    int nrows = bank->getRows();
    if (nrows > (*maxRows))
        nrows = *(maxRows);
    //printf("---->>>>> reading float (%s) (%s) (%d)\n",buffer_group,buffer_item,nrows);
    for (int i = 0; i < nrows; i++) {
        buffer[i] = bank->getDouble(buffer_item, i);
    }
    *nread = nrows;

    free(buffer_group);
    free(buffer_item);
}

void hipo_read_int_(const char* group, const char* item, int* nread, int* buffer, int* maxRows,
                    int length_group, int length_item) {

    char* buffer_group = (char*)malloc(length_group + 1);
    memcpy(buffer_group, group, length_group);
    buffer_group[length_group] = '\0';

    char* buffer_item = (char*)malloc(length_item + 1);
    memcpy(buffer_item, item, length_item);
    buffer_item[length_item] = '\0';

    if (eventStore.count(buffer_group) == 0) {
        *nread = 0;
        free(buffer_group);
        free(buffer_item);
        return;
    }

    hipo::bank* bank = eventStore[buffer_group];
    int nrows = bank->getRows();
    if (nrows > (*maxRows))
        nrows = *(maxRows);
    //printf("---->>>>> reading float (%s) (%s) (%d)\n",buffer_group,buffer_item,nrows);
    for (int i = 0; i < nrows; i++) {
        buffer[i] = bank->getInt(buffer_item, i);
    }
    *nread = nrows;
    free(buffer_group);
    free(buffer_item);
}

void hipo_read_long_(const char* group, const char* item, int* nread, int64_t* buffer, int* maxRows,
                     int length_group, int length_item) {

    char* buffer_group = (char*)malloc(length_group + 1);
    memcpy(buffer_group, group, length_group);
    buffer_group[length_group] = '\0';

    char* buffer_item = (char*)malloc(length_item + 1);
    memcpy(buffer_item, item, length_item);
    buffer_item[length_item] = '\0';

    if (eventStore.count(buffer_group) == 0) {
        *nread = 0;
        free(buffer_group);
        free(buffer_item);
        return;
    }

    hipo::bank* bank = eventStore[buffer_group];
    int nrows = bank->getRows();
    if (nrows > (*maxRows))
        nrows = *(maxRows);
    //printf("---->>>>> reading float (%s) (%s) (%d)\n",buffer_group,buffer_item,nrows);
    for (int i = 0; i < nrows; i++) {
        buffer[i] = bank->getLong(buffer_item, i);
    }
    *nread = nrows;
    free(buffer_group);
    free(buffer_item);
}

/*void hipo_read_int_(int *group, int *item, int *nread, int *buffer, int *maxRows){

    }*/

int fusion_open(const char* filename) {
    int handle = hFusion.open(filename);
    return handle;
}

int fusion_next(int handle) {
    return hFusion.next(handle) == true ? 1 : 0;
}

int fusion_schema_length(int handle, const char* bank) {
    std::string schema = hFusion.schema(handle, bank);
    return (int)schema.length();
}

void fusion_schema_string(int handle, const char* bank, char* format) {
    std::string schema = hFusion.schema(handle, bank);
    std::strcpy(format, schema.c_str());
}

void fusion_define(int handle, const char* bank) {
    hFusion.define(handle, bank);
}

void fusion_describe(int handle, const char* bank) {
    hFusion.describe(handle, bank);
}

int fusion_bankSize(int handle, const char* bank) {
    return hFusion.getSize(handle, bank);
}

int fusion_get_int(int handle, const char* bank, const char* entry, int row) {
    return hFusion.getInt(handle, bank, entry, row);
}

void fusion_get_byte_array(int handle, const char* bank, int entry, int8_t* ptr, int rows) {
    hFusion.getByteArray(handle, bank, entry, ptr, rows);
}

void fusion_get_short_array(int handle, const char* bank, int entry, int16_t* ptr, int rows) {
    hFusion.getShortArray(handle, bank, entry, ptr, rows);
}

void fusion_get_int_array(int handle, const char* bank, int entry, int32_t* ptr, int rows) {
    hFusion.getIntArray(handle, bank, entry, ptr, rows);
}

void fusion_get_float_array(int handle, const char* bank, int entry, float* ptr, int rows) {
    hFusion.getFloatArray(handle, bank, entry, ptr, rows);
}

int64_t fusion_get_long(int handle, const char* bank, const char* entry, int row) {
    return hFusion.getLong(handle, bank, entry, row);
}

float fusion_get_float(int handle, const char* bank, const char* entry, int row) {
    float value = hFusion.getFloat(handle, bank, entry, row);
    //printf(" result from wrapper = %f\n",value);
    return value;
}

float fusion_get_double(int handle, const char* bank, const char* entry, int row) {
    float value = (float)hFusion.getDouble(handle, bank, entry, row);
    //printf(" result from wrapper = %f\n",value);
    return value;
}

int fusion_entry_type(int handle, const char* bank, const char* entry) {
    return hFusion.getType(handle, bank, entry);
}

float* fusion_create_array(int size) {
    float* array = new float[size];
    for (int i = 0; i < size; i++)
        array[i] = (i + 1) * 2;
    return array;
}
}
