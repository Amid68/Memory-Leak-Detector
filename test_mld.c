#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mld.h"

typedef struct employee_ {
    unsigned int emp_id;
    char emp_name[32];
    float emp_salary;
} employee;

typedef struct department_ {
    char dept_name[32];
    unsigned int dept_id;
    employee *manager;
} department;

typedef struct company_ {
    char company_name[32];
    department *departments;
    unsigned int num_departments;
} company;

void test_employee_registration(struct_db_t *struct_db) {
    field_info_t emp_fields[] = {
        FIELD_INFO(employee, emp_id, UINT32, ""),
        FIELD_INFO(employee, emp_name, CHAR, ""),
        FIELD_INFO(employee, emp_salary, FLOAT, "")
    };

    REG_STRUCT(struct_db, employee, emp_fields);
}

void test_department_registration(struct_db_t *struct_db) {
    field_info_t dept_fields[] = {
        FIELD_INFO(department, dept_name, CHAR, ""),
        FIELD_INFO(department, dept_id, UINT32, ""),
        FIELD_INFO(department, manager, OBJ_PTR, "employee")  // Pass "employee" as a string
    };

    REG_STRUCT(struct_db, department, dept_fields);
}

void test_company_registration(struct_db_t *struct_db) {
    field_info_t company_fields[] = {
        FIELD_INFO(company, company_name, CHAR, ""),
        FIELD_INFO(company, departments, OBJ_PTR, "department"),  // Pass "department" as a string
        FIELD_INFO(company, num_departments, UINT32, "")
    };

    REG_STRUCT(struct_db, company, company_fields);
}

void run_all_tests() {
    struct_db_t struct_db = {NULL, 0};

    printf("=== Registering Employee Structure ===\n");
    test_employee_registration(&struct_db);
    print_structure_db(&struct_db);

    printf("\n=== Registering Department Structure ===\n");
    test_department_registration(&struct_db);
    print_structure_db(&struct_db);

    printf("\n=== Registering Company Structure ===\n");
    test_company_registration(&struct_db);
    print_structure_db(&struct_db);

    struct_db_t empty_db = {NULL, 0};
    printf("\n=== Printing Empty Structure Database ===\n");
    print_structure_db(&empty_db);
}

int main() {
    run_all_tests();
    return 0;
}
