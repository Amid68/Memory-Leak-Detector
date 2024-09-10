#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mld.h"

void print_structure_rec(struct_db_rec_t *struct_rec) {
    if (!struct_rec) return;

    printf("Structure Name: %s\n", struct_rec->struct_name);
    printf("Size: %u\n", struct_rec->ds_size);
    printf("Number of fields: %u\n", struct_rec->n_fields);

    for (unsigned int i = 0; i < struct_rec->n_fields; i++) {
        field_info_t *field = &struct_rec->fields[i];
        printf("\tField Name: %s\n", field->fname);
        printf("\tData Type: %d\n", field->dtype);
        printf("\tSize: %u\n", field->size);
        printf("\tOffset: %u\n", field->offset);

        if (field->dtype == OBJ_PTR || field->dtype == OBJ_STRUCT) {
            printf("\tNested Structure Name: %s\n", field->nested_str_name);
        }
        printf("\n");
    }
}

void print_structure_db(struct_db_t *struct_db) {
    if (!struct_db || struct_db->count == 0) {
        printf("Structure Database is empty.\n");
        return;
    }

    struct_db_rec_t *current = struct_db->head;
    printf("Structure Database: %u structures\n", struct_db->count);
    
    while (current) {
        print_structure_rec(current);
        current = current->next;
    }
}

int add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec) {
    if (!struct_db || !struct_rec) {
        return -1;
    }

    struct_rec->next = struct_db->head;
    struct_db->head = struct_rec;
    struct_db->count++;
    return 0;
}
