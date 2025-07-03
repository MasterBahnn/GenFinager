#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <stdio.h>
using namespace std;

// struct and function declarations
template <typename before, typename after> after conversion_tool(before isbfr);
void conversion_tool(string isstr, char * ischarArr);
string error_message(int type, int errornumber);
bool value_detection(string isstr, int mode);
string inclusion_indicator(bool active);
template <typename data_type> void swap_values(data_type *val1, data_type *val2);
string print_datetime(int mode);
bool warning();
bool inspect_input(string str_input);
bool is_account_exist(string accont_file);


// setting structure members
struct settings{
    // decalration with default values
    int precision_point = 2;
    string currency_sign = "$ ";
    int list_size = 10;
    int elements_size = 20;

    bool exclude_date = false; // hides date
    bool exclude_time = false; // hides time
    bool exclude_name = false; // hides name (NULL is displayed in file if excluded)
    bool exclude_credit_values = false; // exclude credit values (said values cannot be saved in data when enabled in the account)
    bool exclude_list_datetime = false; // hides date and time
    bool exclude_condition_ctr = false; // hides condition counter

    const string currency_signs[5] = {"$", "PHP", "GBP", "YEN", "EURO"};
    const int max_precision_point = 5;
    const int min_list_size = 5;
    const int max_list_size = 15;
    const int min_element_size = 10;
    const int max_element_size = 100;

    // ------------------------------------------- settings functions -------------------------------------------------

    // currency editor function
    void currency_editor(){
        int input_cs = 0;
        system("cls");
        while (input_cs != 10){
            cout << fixed << setprecision(precision_point);

            cout << "Current: " + currency_sign << "\t Example: " + currency_sign << 100.00 << endl;
            cout << "---------------------------------------" << endl;
            cout << "Available currency signs:" << endl;

            for (int sub = 0; sub < 5 ; sub++){
                cout << sub+1 << ":  " + currency_signs[sub] << endl;
            } cout << endl;

            cout << "10 > go back to settings" << endl;
            cout << "Which currency sign you want to use?: "; cin >> input_cs;

            if(input_cs == 10) continue;

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                system("cls");
                cout << "Error: " + error_message(1, 4) << endl;
                continue;
            }

            input_cs -= 1;
            if (input_cs >= 0 || input_cs <= 4) {
                system("cls");
                currency_sign = currency_signs[input_cs];
                continue;
            } else{
                system("cls");
                cout << "Error: " + error_message(1, 2) << endl;
            }

        }

        cout << "a";
    }

    // precision editor function
    void precision_point_editor(){
        string response_adjuster;
        system("cls");
        do{
            cout << fixed << setprecision(precision_point);

            cout << "Current: " + currency_sign << 100.00 << endl;
            cout << "Precision Value: " << precision_point << endl;
            cout << "----------------------------------------" << endl << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "| Enter \"<\" << [-] " << precision_point << " [+] >> Enter \">\" |" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Min: " << 0 << "   Max: " << max_precision_point << endl << endl;

            cout << "\"c\" : go back to settings" << endl;
            cout << "[</>] : "; cin >> response_adjuster;

            if (response_adjuster == ">"){
                if(precision_point == max_precision_point){
                    system("cls");
                    cout << "Error: " + error_message(1, 3) << endl;
                    continue;
                }
                system("cls");
                precision_point += 1;
                continue;
            }

            else if (response_adjuster == "<"){
                if(precision_point == 0){
                    system("cls");
                    cout << "Error: " + error_message(1, 3) << endl;
                    continue;
                }
                system("cls");
                precision_point -= 1;
                continue;
            }

            if (response_adjuster != "c") { system("cls"); cout << "Error: " + error_message(1, 4) << endl;}
        } while(response_adjuster != "c");
        system("cls");
    }

    // list size editor function
    void list_size_editor(){
        string list_adjuster;
        system("cls");
        while(list_adjuster != "c"){
            cout << "Current list size:  " << list_size << endl;
            cout << "Min: " << min_list_size << "   Max: " << max_list_size << endl;
            cout << "----------------------------------------------" << endl;
            cout << "\"c\" : go back to settings" << endl;
            cout << "Enter your desired list size: "; cin >> list_adjuster;

            if(value_detection(list_adjuster, 1)){
                int checker = conversion_tool<string, int>(list_adjuster);

                if(checker < min_list_size || checker > max_list_size){
                    system("cls"); cout << "Error: " + error_message(1, 3);
                    continue;
                }
                else list_size = checker;

                system("cls");
                continue;
            }

            system("cls");
            if (list_adjuster != "c") { system("cls"); cout << "Error: " + error_message(1, 4);}
        } system("cls");
    }

    // element size editor function
    void element_size_editor(){
        string element_adjuster;
        system("cls");
        while(element_adjuster != "c"){
            cout << "Current element size:  " << elements_size << endl;
            cout << "Min: " << min_element_size << "   Max: " << max_element_size << endl;
            cout << "----------------------------------------------" << endl;
            cout << "\"c\" : go back to settings" << endl;
            cout << "Enter your desired element size: "; cin >> element_adjuster;

            if(value_detection(element_adjuster, 1)){
                int checker = conversion_tool<string, int>(element_adjuster);
                if(checker < min_element_size || checker > max_element_size){
                    system("cls"); cout << "Error: " + error_message(1, 3);
                    continue;
                }
                else elements_size = checker;

                system("cls");
                continue;
            }

            system("cls");
            if (element_adjuster != "c") { system("cls"); cout << "Error: " + error_message(1, 4);}
        } system("cls");
    }

    // list and element exclusions function
    void element_exclusion_modifier(){
        int exclude_resp;
        system("cls");
        while(exclude_resp != 7){

            cout << "----------------------------------------------" << endl;
            cout << "[o] > Excluded     [x] > Included" << endl << endl;
            cout << "Element exclusions: " << endl;
            cout << "1: " << inclusion_indicator(exclude_date) << " - Element date" << endl;
            cout << "2: " << inclusion_indicator(exclude_time) << " - Element time" << endl;
            cout << "3: " << inclusion_indicator(exclude_name) << " - Element name" << endl;
            cout << "4: " << inclusion_indicator(exclude_credit_values) << " - List credit values" << endl;
            cout << "5: " << inclusion_indicator(exclude_list_datetime) << " - List Date and time" << endl;
            cout << "6: " << inclusion_indicator(exclude_condition_ctr) << " - Condition counter" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "7: Go back to settings" << endl;
            cout << "Enter the number you want to switch: "; cin >> exclude_resp;

            if (exclude_resp > 1 || exclude_resp < 7) {
                switch(exclude_resp){
                    case 1: exclude_date = (exclude_date) ? false : true; break;
                    case 2: exclude_time = (exclude_time) ? false : true; break;
                    case 3: exclude_name = (exclude_name) ? false : true; break;
                    case 4: exclude_credit_values = (exclude_credit_values) ? false : true; break;
                    case 5: exclude_list_datetime = (exclude_list_datetime) ? false : true; break;
                    case 6: exclude_condition_ctr = (exclude_condition_ctr) ? false : true; break;
                } system("cls");
            } else {
                system("cls");
                cout << "Error: " + error_message(1, 2) << endl;
            }
        }
        system("cls");
    }

    // defaulting seeting changes
    void setting_defaulter(struct settings default_values){
        precision_point = default_values.precision_point;
        currency_sign = default_values.currency_sign;
        list_size = default_values.list_size;
        elements_size = default_values.elements_size;
        exclude_date = default_values.exclude_date;
        exclude_time = default_values.exclude_time;
        exclude_name = default_values.exclude_name;
        exclude_credit_values = default_values.exclude_credit_values;
        exclude_list_datetime = default_values.exclude_list_datetime;
        exclude_condition_ctr = default_values.exclude_condition_ctr;
    }

} default_settings, current_settings;

// ------------------------------------------------------------------------------------------------------------------------------------

struct statistics{
    // declaration of values
    double allowance = 0;
    double savings = 0;
    double expenses = 0;
    double loan = 0;

    // declaration of condition counters
    const string conditions[6] = {"expense_type", "income_type", "savings_deposit", "savings_withdraw", "borrow_loan", "pay_loan"};
    const string interest_type[2] = {"percentage", "return_type"};
    int condition_size = (current_settings.exclude_credit_values) ? 4 : 6;

    // declaration of condition counters
    int expense_type_count = 0;
    int income_type_count = 0;
    int deposit_type_count = 0;
    int withdraw_type_count = 0;
    int borrow_type_count = 0;
    int payloan_type_count = 0;

    // function to print Computations
    void print_values(){
        cout << fixed << setprecision(current_settings.precision_point);

        cout << " ---- Computations: -----\n";
        cout << "Expenses: " + current_settings.currency_sign << expenses;
        if(!current_settings.exclude_credit_values) cout << "   Loans: " + current_settings.currency_sign << loan;
        cout << "   Savings: " + current_settings.currency_sign << savings << endl;

        cout << "Allowance: " + current_settings.currency_sign << allowance << endl;

        if(!current_settings.exclude_condition_ctr){
            cout << "- - Condition Counter - -" << endl;
            cout << "EX: " << expense_type_count << "\t\tIN: " << income_type_count;
            if(!current_settings.exclude_credit_values) cout << "\t\t(C)BR: " << borrow_type_count;
            cout << endl;
            cout << "DP: " << deposit_type_count << "\t\tWD: " << withdraw_type_count;
            if(!current_settings.exclude_credit_values) cout << "\t\t(C)PL: " << payloan_type_count << endl;
        }

    }

    // function to compute return value
    double compute_interest(double value, double interest_percent){
        double value_percentage = value * (interest_percent * 0.01);
        value_percentage += value;
        loan += value_percentage;
        return value_percentage;
    }

    // function to compute interest percent
    double compute_precentage(double value, double return_value){
        double simple_interest = return_value - value;
        loan += return_value;
        return (simple_interest * 100) / value;
    }

    // for computations from elements to the declared statistic and counter variables
    void conditional_values(string type, double value, double return_value){
        if (type == conditions[0]){
            expenses += value;
            allowance -= value;
            expense_type_count += 1;
        } else if (type == conditions[1]){
            allowance += value;
            income_type_count += 1;
        } else if (type == conditions[2]){
            savings += value;
            allowance -= value;
            deposit_type_count += 1;
        } else if (type == conditions[3]){
            savings -= value;
            allowance += value;
            withdraw_type_count += 1;
        } else if (type == conditions[4]){
            loan += return_value;
            allowance += value;
            borrow_type_count += 1;
        } else if (type == conditions[5]){
            loan -= value;
            allowance -= value;
            payloan_type_count += 1;
        }
    }

};

// list of elements handling structure body
struct element{
    // decalration of member elements
    bool sub_lock = false;
    int sub_pos;
    string date;
    string time;
    string type;
    string name = "NULL";
    double value = 0;

    // order of ofstream: type sub_lock date time value name
    // two values should be

    // declaration of member credit elements
    double credit_percent = 0;
    double return_value = 0;
    // function to check conditions for preventing miscalculations and invalidations
    bool element_identifier(struct statistics show){
        if (type == show.conditions[3] && value > show.savings){
            system("cls"); cout << "Error: " + error_message(2, 2) << endl;
            return false;
        } else if (type == show.conditions[0] && show.allowance - value < 0){
            system("cls"); cout << "Error: " + error_message(2, 3) << endl;
            return false;
        } else if(type == show.conditions[6] && show.loan == 0){
            system("cls"); cout << "Error: " + error_message(2, 7) << endl;
            return false;
        }

        return true;
    }

    // function to print element data
    void print_subscript_element(int sub, struct statistics show){
        cout << fixed << setprecision(current_settings.precision_point);

        cout << sub+1 << ") ";

        if(!current_settings.exclude_date && !current_settings.exclude_time) cout << date << " " << time;

        else if(!current_settings.exclude_date) cout << date;
        else if(!current_settings.exclude_time) cout << time;


        cout << " |  " << type << "\t\t| ";

        if(!current_settings.exclude_name) cout << name << ": ";

        cout << current_settings.currency_sign << value;

        if(!current_settings.exclude_credit_values && type == show.conditions[4])
            cout << " (" << credit_percent << "%, RV: " + current_settings.currency_sign << return_value << ")";

        cout << endl;
    }


    // to edit/create debt values (return_value/credit_percentage)
    void credit_value_manipulator(struct statistics show){
        int input_ct = 0;
        cout << fixed << setprecision(current_settings.precision_point);
        show.print_values();
        cout << "--------------------------------------------------" << endl;

        for(int a = 0; a < 2; a++){
            cout << "(" <<  a+1 << ")" << show.interest_type[a] << "    ";
        } cout << endl;

        do{ cout << "Credit type (number only from the choices): "; cin >> input_ct;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "{Error: " + error_message(1, 4) << "} ";
            }
            else if (input_ct < 1 || input_ct > 2) cout << "{Error: " + error_message(1, 2) << "} ";
        }while(input_ct < 1 || input_ct > 2);

        if(input_ct == 1){ // if credit type was using interest percentage
            do{
                cout << "Enter the interest percentage: "; cin >> credit_percent;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "{Error: " + error_message(1, 4) << "} ";
                } else if (credit_percent < 0 || credit_percent > 100) cout << "{Error: Credit percentage should not pass above 100%, or go below 0%." << "} ";
            }while(credit_percent < 0 || credit_percent > 100);

            return_value = show.compute_interest(value, credit_percent);

        } else if(input_ct == 2){ // if credit type was using return value
            do{
                cout << "Enter the return value (when you pay back your credit): $"; cin >> return_value;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "{Error: " + error_message(1, 4) << "} ";
                } else if(return_value <= 0) cout << "{Error: " + error_message(2, 5) << "} ";
            }while(return_value <= 0);
            credit_percent = show.compute_precentage(value, return_value);
        }

    }

    // function to edit element
    void element_editor(struct statistics show, int subscipt_occupy){
        int choices = 0;
        while(choices != 10){
            cout << "--------------------------------------------------" << endl;
            cout << "Edit element: ";
            print_subscript_element(subscipt_occupy, show);
            cout << endl;

            show.print_values();
            cout << "-------- Edit Choices: --------" << endl;
            cout << "1: " << inclusion_indicator(sub_lock) << " Subscript lock" << endl;
            cout << "2: Value Conditions " << endl;
            cout << "3: Element Name " << endl;
            cout << "4: Element Value " << endl;
            if(type == show.conditions[4]){
                cout << "5: Loan Values" << endl;
            } cout << "10: Exit element editor" << endl;
            cout << "---------------------------" << endl;
            cout << "> "; cin >> choices;

            system("cls");

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Error: " + error_message(1, 4) << endl;
                continue;
            }

            // statement to edit credit values
            if(type == show.conditions[4] && choices == 5 && !current_settings.exclude_credit_values){
                cout << "--------------------------------------------------------------" << endl;
                cout << "Edit element: "; print_subscript_element(subscipt_occupy, show);
                credit_value_manipulator(show);
                continue;
            }

            switch(choices){
                case 1:{ // case statement to enable/disable subscript lock
                    sub_lock = (sub_lock) ? false : true;

                    break;
                } case 2:{ // case statement to edit element condition type
                    int condition_num1 = 0;
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "Edit element: "; print_subscript_element(subscipt_occupy, show);
                    show.print_values();
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "Choices (Value condition): " << endl;
                    for (int sub = 0; sub < show.condition_size; sub++){
                        cout << sub+1 << ": " + show.conditions[sub] << endl;
                    }
                    cout << "---------------" << endl;
                    cout << "Value type (number only from the choices): " << endl;

                    do {
                        cout << "> "; cin >> condition_num1;

                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "{Error: " + error_message(1, 4) << "} ";
                        }
                        else if (condition_num1 < 1 || condition_num1 > show.condition_size) cout << "{Error: " + error_message(1, 2) << "} ";

                    } while (condition_num1 < 1 || condition_num1 > show.condition_size);

                    if(element_identifier(show)){
                        type = show.conditions[condition_num1 - 1];
                    }

                    if(type == show.conditions[4]) credit_value_manipulator(show);

                    system("cls");

                    break;
                } case 3:{ // case statement to edit element name

                    if(current_settings.exclude_name){
                        cout << "Error: " + error_message(2, 1) << endl;
                       break;
                    }

                    cin.ignore();
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "Edit element: "; print_subscript_element(subscipt_occupy, show);
                    cout << "--------------------------------------------------------------" << endl;
                    do{ cout << "Name of element: "; getline(cin, name);

                        if (name.length() == 0) cout << "{Error: " + error_message(1, 1) << "} ";

                        else if (name.length() > 20) cout << "{Error: element name should not exceed to 20 characters} ";

                    } while (name.length() == 0 || name.length() > 20);

                    system("cls");

                    break;
                } case 4:{ // case statement to edit element value
                    double value_checker = 0;
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "Edit element "; print_subscript_element(subscipt_occupy, show);
                    show.print_values();
                    cout << "--------------------------------------------------------------" << endl;
                    do { cout << "Value of element: " + current_settings.currency_sign; cin >> value_checker;

                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "{Error: " + error_message(1, 4) << "} ";
                        }
                        else if (value <= 0) cout << "{Error: " + error_message(2, 5) << "} ";
                    } while (value <= 0);

                    if(element_identifier(show)){
                        value = value_checker;
                    }

                    system("cls");
                    break;
                } default:{
                    cout << "Error: " + error_message(1, 2) << endl;
                }
            }

        }

        if(type != show.conditions[4]){
            credit_percent = 0;
            return_value = 0;
        }
    }

    // function to create or edit elements to lists
    void element_creator(struct statistics show){
        bool manip_success = true;
        while(manip_success){ cout << fixed << setprecision(current_settings.precision_point);

            show.print_values();
            cout << "--------------------------------------------------------------" << endl;
            cout << "Choices (Value condition): " << endl;
            for (int sub = 0; sub < show.condition_size; sub++){
                cout << sub+1 << ": " + show.conditions[sub] << endl;
            }
            cout << "---------------" << endl;

            // -------- element type input loop ---------
            int condition_num1 = 0;
            do {
                cout << "Value type (number only from the choices): "; cin >> condition_num1;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "{Error: " + error_message(1, 4) << "} ";
                }
                else if (condition_num1 < 1 || condition_num1 > show.condition_size) cout << "{Error: " + error_message(1, 2) << "} ";
            } while (condition_num1 < 1 || condition_num1 > show.condition_size);
            type = show.conditions[condition_num1 - 1];

            cout << endl;
            cin.ignore();

            // -------- element name input loop ---------
            do{ cout << "Name of element: "; getline(cin, name);

                if (name.length() == 0) cout << "{Error: " + error_message(1, 1) << "} ";
                else if (name.length() > 20) cout << "{Error: element name should not exceed to 20 characters} ";
            } while (name.length() == 0 || name.length() > 20);

            // -------- element value input loop ---------
            do { cout << "Value of element: " + current_settings.currency_sign; cin >> value;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "{Error: " + error_message(1, 4) << "} ";
                }
                else if (value <= 0) cout << "{Error: " + error_message(2, 5) << "} ";
            } while (value <= 0);

            // -------- credit value input loop ---------
            if(type == show.conditions[4]){
                system("cls");
                cout << "--------------------------------------------------------------" << endl;
                credit_value_manipulator(show);
            }

            // ------ conditions for preventing miscalculations and invalidations ---------
            manip_success = !element_identifier(show);
        }

        // everytime the element created/edited the time is updated
        date = print_datetime(1);
        time = print_datetime(2);
    }

};

// ------------------------------------------------------------------------------------------------------------------------------------

struct list_info{
    string list_name;
    string date_time;
    bool credit_value_included = false;
    string whitelisted[3] = {"NULL", "NULL", "NULL"};
    int wl_sub = 0;

    element* element_handle = NULL; // declaration of list of elements (using dynamically allocated array)
    int element_subsript = 0; // assigns element subscript
    int pos = 0; // assigns element position (defferent from subscript); resets when all elements are deleted


    bool is_player_whitelisted(string username_target){
        for(int a = 0; a < 3; a++){
            if(username_target == whitelisted[a]){
                return true;
            }
        } return false;
    }


    // -------------------- Element Handling ------------------

    void activate_elements(){
        element_handle = new element[current_settings.elements_size];
    }

    void deactivate_elements(){
        delete[] element_handle;
        element_subsript = 0;
    }


    // compute elements
    void compute_elements(struct statistics * compute){
        for(int sub = 0; sub < element_subsript; sub++){
            compute->conditional_values(element_handle[sub].type, element_handle[sub].value, element_handle[sub].return_value);
        } if(compute->borrow_type_count > 0 || compute->payloan_type_count > 0) credit_value_included = true;
        else credit_value_included = false;
    }


    // print elements in console
    void print_elements(struct statistics show){
        for(int sub = 0; sub < element_subsript; sub++){
            element_handle[sub].print_subscript_element(sub, show);
        }
    }


    // function to delete specific element from list
    void delete_element(int sub_delete){
        for (int sub = sub_delete - 1; sub < element_subsript; sub++){
            if (sub < element_subsript-1){
                element_handle[sub] = element_handle[sub+1];
            } else if (sub == element_subsript-1) {
                element_handle[sub].date = "";
                element_handle[sub].time = "";
                element_handle[sub].type = "";
                element_handle[sub].name = "";
                element_handle[sub].value = 0.0;
                element_handle[sub].credit_percent = 0.0;
                element_handle[sub].return_value = 0.0;
            }
        } element_subsript -= 1;
    }

    // function to delete all elements from lists
    void delete_element(){
        delete[] element_handle;
        element_handle = new element[current_settings.elements_size];
        element_subsript = 0;
        pos = 0;
    }

    // function to sort elements

    /*  Sort Modes:
        1: Date
        2: Time
        3: Name
        4: Value

        income elements should go first!!!
    */

    void sort_elements(int mode){
        for(int a = 0; a < element_subsript  - 1; a++){
            for(int b = 0; b < element_subsript - a - 1; b++){
                if(element_handle[b].date > element_handle[b+1].date && mode == 1){
                    swap_values(element_handle + b, element_handle + b + 1);
                } else if(element_handle[b].time > element_handle[b+1].time && mode == 2){
                    swap_values(element_handle + b, element_handle + b + 1);
                } else if(element_handle[b].name > element_handle[b+1].name && mode == 3){
                    swap_values(element_handle + b, element_handle + b + 1);
                } else if(element_handle[b].value > element_handle[b+1].value && mode == 4){
                    swap_values(element_handle + b, element_handle + b + 1);
                }
            }
        }

    }

    // reverts element ny number position
    void sort_elements(){
        for(int a = 0; a < element_subsript  - 1; a++){
            for(int b = 0; b < element_subsript - a - 1; b++){
                if(element_handle[b].sub_pos > element_handle[b+1].sub_pos){
                    swap_values(element_handle + b, element_handle + b + 1);
                }
            }
        }
    }

    // founction to search elements
    // searching by conditions is not applicable due to repetition
    // found by first instance of target
    int search_element(struct statistics show, string str_target){
        double dbl_target;

        bool if_dbl = value_detection(str_target, 2);

        if(if_dbl){
            dbl_target = conversion_tool<string, double>(str_target);
        }

        for(int sub = 0; sub < element_subsript; sub++){

            if(if_dbl){
                if(element_handle[sub].value == dbl_target || (element_handle[sub].type == show.conditions[4] && (element_handle[sub].credit_percent == dbl_target || element_handle[sub].return_value == dbl_target))){
                    return sub;
                }
            } else{
                if(element_handle[sub].date == str_target || element_handle[sub].time == str_target || element_handle[sub].name == str_target){
                    return sub;
                }
            }
        }

        return -1;
    }

    /* Logic tracing for move element function

        arr size = 3
        arr[0] = 3; arr[1] = 2; arr[2] = 9;

        move element
        sub: 0; to: 2; key = arr[0]; a = sub;

        0 > 2 false

        0 < 2 true
        0 < 2 == true arr[0] = arr[1]; a + 1 = 1
        1 < 2 == true arr[1] = arr[2]; a + 1 = 2
        2 < 2 = false arr[2] = key

        move element
        sub: 2; to: 0; key = arr[2]; a = sub;

        2 > 0 true arr[2] = arr[1]; a - 1 = 1;
        1 > 0 true arr[1] = arr[0]; a - 1 = 0;
        0 > 0 false

        0 < 0 false arr[0] = key
    */

    // member function to move element
    void move_element(int sub, int position){
        element key = element_handle[sub]; // element wants to move
        int a = sub;

        while(a > position){
            element_handle[a] = element_handle[a-1];
            a--;
        }

        while(a < position){
            element_handle[a] = element_handle[a+1];
            a++;
        }

        element_handle[a] = key;
    }


    // -------------------- File Handling ------------------

    // function to print out lists (reused for viewing lists in editing and deletion of specific element)
    void save_list_txt(struct statistics view){
        ofstream list_printer;
        string filename;
        filename = list_name + ".txt";
        list_printer.open(filename, ios::out);
        list_printer << fixed << setprecision(current_settings.precision_point);

        list_printer << "-------------------------------------------------------------------------------------\n";
        list_printer << "List Name: " + list_name << "\n";
        list_printer << "Created: " + date_time << "\n";
        list_printer << "     ----- Expenses -----     \n";

        cout << fixed << setprecision(current_settings.precision_point);

        for (int sub = 0; sub < element_subsript; sub++){
            list_printer << sub+1 << ") ";

            if(!current_settings.exclude_date) list_printer << element_handle[sub].date;
            else if(!current_settings.exclude_time) list_printer << element_handle[sub].time;

            else if(!current_settings.exclude_date == !current_settings.exclude_time)
                list_printer << element_handle[sub].date << " " << element_handle[sub].time;

            list_printer << " |  " << element_handle[sub].type << "\t\t| ";

            if(!current_settings.exclude_name) list_printer << element_handle[sub].name << ": ";

            list_printer << current_settings.currency_sign << element_handle[sub].value;

            if(!current_settings.exclude_credit_values && element_handle[sub].type == view.conditions[4])
                list_printer << " (" << element_handle[sub].credit_percent << "%, RV: " + current_settings.currency_sign << element_handle[sub].return_value << ")";

            list_printer << "\n";
        }
        list_printer << "------------------------------------------------------------\n";
        list_printer << "Expenses: " + current_settings.currency_sign << view.expenses << "\n";
        list_printer << "Savings: " + current_settings.currency_sign << view.savings << "\n";
        list_printer << "Loan: " + current_settings.currency_sign << view.loan << "\n";
        list_printer << "\n";
        list_printer << "Allowance: " + current_settings.currency_sign << view.allowance << "\n";
        list_printer << "-------------------------------------------------------------------------------------\n";

        list_printer.close();

        cout << "The contents of " + list_name + " has been saved as \"" + filename << "\".\n";
    }

    void export_list(){
        ofstream list_exporter;
        string filename;
        filename = list_name + ".lstll";
        list_exporter.open(filename, ios::out);

        list_exporter << list_name << "\n";
        list_exporter << date_time << "\n";
        list_exporter << element_subsript << "\n";
        list_exporter << "--------------------------------------------\n";
        for(int a = 0; a < element_subsript; a++){
            if(a == current_settings.elements_size) break;
            list_exporter << element_handle[a].date << " " << element_handle[a].time << " " << element_handle[a].type << " " << element_handle[a].value <<
            " " << element_handle[a].credit_percent << " "  << element_handle[a].return_value << " ";
            list_exporter << element_handle[a].name << "\n";
        }

        list_exporter.close();
        cout << "Exported list has been saved as \"" << filename << "\"." << endl;
    }

    // member function to import file
    bool import_list(string file_naming){
        ifstream list_importer;
        string filename, temp;
        filename = file_naming + ".lstll";
        list_importer.open(filename);
        if(!list_importer.is_open()){
            cout << "Error: " + error_message(4, 3) << endl;
            return false;
        }

        getline(list_importer, list_name);
        getline(list_importer, date_time);
        list_importer >> element_subsript;
        list_importer.ignore();
        getline(list_importer, temp);

        if(list_importer.fail()){
            cout << "Error: " + error_message(4, 4) << endl;
            return false;
        }

        for(int a = 0; a < element_subsript; a++){
            if(a == current_settings.elements_size) break;

            list_importer >> element_handle[a].date >> element_handle[a].time >> element_handle[a].type >> element_handle[a].value >> element_handle[a].credit_percent >> element_handle[a].return_value;
            list_importer.ignore();
            getline(list_importer, element_handle[a].name);

            if(list_importer.fail()){
                cout << "Error: " + error_message(4, 4) << endl;
                return false;
            }
        }

        list_importer.close();
        return true;
    }


    // deletes imported file after importing
    void delete_imported_file(){
        string filename = list_name + ".lstll";
        const char *delete_file = filename.c_str();

        int result = remove(delete_file);
        if(result == 0){
            cout << "Account file deleted successfully!" << endl;
        } else cout << "The file still exist you idiot" << endl;
    }


};

// ------------------------------------------------------------------------------------------------------------------------------------

/*
// function declaration for handling data
void handle_data(int *account_subscript, bool* login_status, string *username);
void save_data(int account_subscript, bool login_status, string username);

*/

// account and list file handling structure body
struct account{
    // declaration of values
    string username;
    string display_name;
    string passkey;
    list_info* list_handle; // declaration of lists of list for accounts
    int list_subscript;

    /* ------ Conditions: ------
        Username:
        > Must be at least 8 characters and limited to 20 characters
        > Do not use special characters except for these: _ @ % ? !
        > Do not have spaces

        Password:
        > Same rules applied but limited to 100 characters

        Display name:
        > Must be at least 3 characters and limited to 30 characters
        > Allowed to have spaces
        > Allowed to have special characters
    */



    // characters for username and password
    const string allowed_charcters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_@$?!"; // 64 chars

    // -------------------- Account Handling ------------------

    bool password_auth(){
        int attempts = 1; string verify_passkey;
        cout << "3 failed attempt == log out" << endl;
        do{
            cout << "(" << attempts << "/3) ";
            cout << "Enter your password: "; cin >> verify_passkey;
            if(passkey != verify_passkey) attempts++;
            if(attempts > 3) return false;
        }while(passkey != verify_passkey);

        return true;
    }

    void change_display_name(bool new_acc){
        string proceed_change;
        do{
            cout << "Current display name: " << display_name << endl;
            cout << "Enter your new display name (C = done changing): ";
            getline(cin, proceed_change);

            if(proceed_change.length() > 4 && proceed_change.length() < 29){
                display_name = proceed_change;
                new_acc = false;
                cout << endl;
            }
            else if (proceed_change.length() < 5 || proceed_change.length() > 28) {
                cout << endl;
                cout << "Error: " + error_message(3, 7) << endl;
            }
        }while(proceed_change != "C" && display_name.length() > 4);
    }

    void change_passkey(){
        string new_passkey1, new_passkey2;

        system("cls");
        cout << "[REMEBER YOUR NEW PASSWORD]" << endl;

        do{
            do{
                cout << "Enter your new password: "; cin >> new_passkey1;
                if (new_passkey1.length() < 8 || new_passkey1.length() > 100) cout << "{" + error_message(3, 5) << "} ";
                else if(!inspect_input(new_passkey1)) cout << "{" + error_message(3, 6) << "} ";

            }while(new_passkey1.length() < 8 || new_passkey1.length() > 100 || !inspect_input(new_passkey1));

            cout << "Enter your new password again: "; cin >> new_passkey2;
            if (new_passkey1 != new_passkey2) cout << "{" + error_message(3, 3) << "} ";
        }while(new_passkey1 != new_passkey2);

        passkey = new_passkey2;
    }


    // -------------------- List Handling ------------------


    // to create a dynamically allocated array
    void activate_lists(){
        list_handle = new list_info[current_settings.list_size];
        for(int a = 0; a < current_settings.list_size; a++){
            list_handle[a].activate_elements();
        }
    }

    // to delete a dynamically allocated array
    void deactivate_lists(){
        for(int a = 0; a < current_settings.list_size; a++){
            list_handle[a].deactivate_elements();
        }
        delete[] list_handle;
        list_subscript = 0;
    }


    void print_list(){
        for(int a = 0; a < list_subscript; a++){
            if(current_settings.exclude_credit_values && list_handle[a].credit_value_included == true) continue;

            cout << a+1 << ": ";
            if(!current_settings.exclude_list_datetime) cout << list_handle[a].date_time;
            cout << "  " << list_handle[a].list_name << " (Elements: " << list_handle[a].element_subsript << ")";
            cout << endl;
        }
    }

    // function to search list sequentially
    // it is done sequentially due to some variables are not
    // excempt variable is subsript excemption for editing list
    int search_list(string list_name_target, int excempt){
        for(int a = 0; a < list_subscript; a++){
            if(list_name_target == list_handle[a].list_name && a != excempt){
                return a;
            }
        }
        return -1;
    }

    // rename list name
    void manipulate_list_name(int manip_list){
        int distinct_ln = -1;
        do{
            cout << "Enter your list name: "; getline(cin, list_handle[manip_list].list_name);
            if(list_handle[manip_list].list_name.length() < 4 || list_handle[manip_list].list_name.length() > 30) cout << "{" + error_message(2, 6) << "} ";

            distinct_ln = search_list(list_handle[manip_list].list_name, manip_list);
            if(distinct_ln != -1) cout << "{" + error_message(3, 6) << "} ";
        }while(list_handle[manip_list].list_name.length() < 4 || list_handle[manip_list].list_name.length() > 30 || distinct_ln != -1);

    }

    // to create a new list
    void list_creation(){
        system("cls");

        int cresp = 0;
        cout << "Create a list: " << endl;
        cout << "1 > New list of element" << endl;
        cout << "2 > Import existing list" << endl;
        cout << "3 > Exit list creation" << endl;
        cout << endl;
        do{
            cout << "> "; cin >> cresp;
            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "{" + error_message(1, 4) << "} ";
            } else if(cresp < 1 || cresp > 3){
                cout << "{" + error_message(1, 2) << "} ";
            }

        }while(cresp < 1 || cresp > 3);

        system("cls");
        if(cresp == 1){ cin.ignore();
            cout << "Generate new list......." << endl;
            cout << "-------------------------------------------------------" << endl;
            manipulate_list_name(list_subscript);
            list_handle[list_subscript].date_time = print_datetime(3);
            list_subscript++;
        } else if (cresp == 2){
            cin.ignore();
            string file_resp;
            cout << "Generate new list......." << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "NOTICE: " << endl;
            cout << "- The list file must be inside the program folder" << endl;
            cout << "- The list file is deleted once copied, make sure to save a copy" << endl;
            cout << "- The list file must be .lstll type file" << endl;
            cout << "- - - - -  - - " << endl;
            cout << "c > go back to menu" << endl;
            cout << "Enter the filename (exclude the \"lstll\"): " << endl;
            bool file_found = false;

            do{
                cout << "> "; getline(cin, file_resp);

                if (file_resp == "c") break;

                file_found = list_handle[list_subscript].import_list(file_resp);

            }while(!file_found);

            if(file_found){
                list_handle[list_subscript].delete_imported_file();
                list_handle[list_subscript].list_name += " - (IM)";
                list_subscript++;
            }

        }
    }

    // to delete one list
    void delete_list(int sub_delete){
        for(int a = sub_delete; a < list_subscript; a++){
            if(a < list_subscript - 1){
                list_handle[a] = list_handle[a+1];
            }else if(a == list_subscript-1){
                list_handle[a].list_name = "";
                list_handle[a].date_time = "";
                list_handle[a].element_subsript = 0;
                for(int sub = 0; sub < 3; sub++){
                    list_handle[a].whitelisted[sub] = "NULL";
                } list_handle[a].delete_element();
            }
        } list_subscript -= 1;
    }


    void delete_list(){
        deactivate_lists();
        activate_lists();
    }


    //function to search a list
    /* Modes:
        1: By name
        2: By Date
        3: By number of element
    */
    void sort_list(){
        system("cls"); int sort_resp = 0;
        cout << "-------------------------------------------------------" << endl;
        print_list();
        cout << "---------------------------------------" << endl;
        cout << "Sort list mode: " << endl;
        cout << "1: Name" << endl;
        cout << "2: Date" << endl;
        cout << "3: Number of Elements" << endl;
        cout << "4: Go back to menu" << endl;
        cout << endl;

        do{
            cout << "> "; cin >> sort_resp;

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                system("cls");
                cout << "{" + error_message(1, 4) << "} ";
            } else if(sort_resp < 1 || sort_resp > 4){
                system("cls");
                cout << "{" + error_message(1, 2) << "} ";
            }

        }while(sort_resp < 1 || sort_resp > 4);

        if(sort_resp != 4){
            for(int a = 0; a < list_subscript - 1; a++){
                for(int b = 0; b < list_subscript - a - 1; b++){
                    if(list_handle[b].list_name > list_handle[b+1].list_name && sort_resp == 1) {
                        swap_values<struct list_info>(&list_handle[b], &list_handle[b+1]);
                    } else if(list_handle[b].date_time > list_handle[b+1].date_time && sort_resp == 2){
                        swap_values<struct list_info>(&list_handle[b], &list_handle[b+1]);
                    } else if(list_handle[b].element_subsript > list_handle[b+1].element_subsript && sort_resp == 3){
                        swap_values<struct list_info>(&list_handle[b], &list_handle[b+1]);
                    }
                }
            }
        }
    }

    // add/remove whitelisted users
    void whitelist_players(int lsub){
        system("cls");
        string wresp = " ";
        while(wresp != "c"){
            cout << "------------------------------------" << endl;
            cout << "Whitelisted Users: " << endl;
            for(int a = 0; a < 3; a++){
                cout << a+1 << ": " << list_handle[lsub].whitelisted[a] << endl;
            }
            cout << endl;
            cout << "1-3: Enter the placement you want to manipulate" << endl;
            cout << "a: Add user" << endl;
            cout << "b: Remove all user" << endl;
            cout << "c: Go back" << endl;
            cout << endl;
            cout << "> "; cin >> wresp;

            system("cls");

            // statement to manipulate a whitelisted value
            if(value_detection(wresp, 1)){
                int manip_sub = conversion_tool<string, int>(wresp) - 1;

                if(manip_sub < 0 || manip_sub > 2) {
                    cout << "Error: " + error_message(1, 2) << endl;
                    continue;
                } else if(list_handle[lsub].whitelisted[manip_sub] == "NULL"){
                    cout << "Error: Empty Placement" << endl;
                    continue;
                }

                cout << "Manipulating "<< manip_sub+1 << ": " << list_handle[lsub].whitelisted[manip_sub] << endl;
                cout << endl;
                cout << "a: Replace user" << endl;
                cout << "b: Remove user" << endl;
                cout << "c: Go back" << endl;
                char mode = ' ';

                do{
                    cout << "> "; cin >> mode;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "{" + error_message(1, 2) << "} ";
                    } else if (mode < 'a' || mode > 'c') cout << "{" + error_message(1, 2) << "} ";
                }while(mode < 'a' || mode > 'c');

                if(mode == 'a'){ // Replace user to whitelist
                    cin.ignore(); string player_whitelist;

                    cout << "Enter the username you want to whitelist: (c: to cancel)" << endl;
                    bool isexist = false;
                    do{
                        cout << "> "; getline(cin, player_whitelist);

                        if(player_whitelist == "c") break;

                        if(player_whitelist == username){
                            cout << "{" + error_message(3, 8) << "} ";
                            continue;
                        }

                        isexist = is_account_exist(player_whitelist);
                        if(!isexist) cout << "{" + error_message(4, 2) << "} ";
                    } while(!isexist);

                    if(isexist) list_handle[lsub].whitelisted[manip_sub] = player_whitelist; // if user is found


                } else if(mode == 'b'){ // to delete partial whitelisted users
                    if(warning()){
                        for(int sub = manip_sub; sub < 3; sub++){
                            if(sub < 2){
                                list_handle[lsub].whitelisted[sub] = list_handle[lsub].whitelisted[sub+1];
                            } else if (sub == 2){
                                list_handle[lsub].whitelisted[sub] = "NULL";
                            }
                        } list_handle[lsub].wl_sub -= 1;
                    }
                } system("cls");

            // statement to add
            } else if (wresp == "a"){
                if(list_handle[lsub].wl_sub == 3){
                    cout << "Error: " + error_message(1, 3) << endl;
                    continue;
                }

                cin.ignore(); string player_whitelist;
                cout << "Enter the username you want to whitelist: (c: go back) " << endl;
                bool isexist = false;
                do{
                    cout << "> "; getline(cin, player_whitelist);


                    if(player_whitelist == username){
                        cout << "{" + error_message(3, 8) << "} ";
                        continue;
                    } else if (player_whitelist == "c"){
                        break;
                    }

                    isexist = is_account_exist(player_whitelist);
                    if(!isexist) cout << "{" + error_message(4, 1) << "} ";
                } while(!isexist);

                if(isexist){
                    list_handle[lsub].whitelisted[list_handle[lsub].wl_sub] = player_whitelist;
                    list_handle[lsub].wl_sub += 1;
                }

                system("cls");
            } else if (wresp == "b"){
                if(warning()){
                    for(int a = 0; a < 3; a++){
                        list_handle[lsub].whitelisted[a] = "NULL";
                    } list_handle[lsub].wl_sub = 0;
                } system("cls");

            } else{
                cin.ignore(1000, '\n');
                cout << "Error: " + error_message(1, 2) << endl;
            }

        }
    }

    // -------------------- File Handling ------------------


    string temp; // temporary variable for unwanted information

    // order of ofstream: type sub_lock date time value name

    string filename_account(){
        return username + ".lstacc";
    }

    // member function to generate new account file from account creation
    void create_account(){
        ofstream create;
        create.open(filename_account(), ios::out);

        create << username << " " << display_name << "\n";
        create << passkey << " " << 0 << "\n";
        create << "-------------------------\n";
        create << default_settings.precision_point << " " << default_settings.currency_sign << "\n";
        create << default_settings.list_size << " " << default_settings.elements_size << "\n";
        create << default_settings.exclude_date << " " << default_settings.exclude_time << " " << default_settings.exclude_name << " " << default_settings.exclude_credit_values << " " << current_settings.exclude_condition_ctr << "\n";
        create << "-------------------------\n";
        create << "\n";
        create.close();

        /*
        ofstream add_account;
        add_account.open("(ADMIN) program handler.lstr", ios::app);
        add_account << username << " " << passkey << " " << display_name << "\n";
        add_account.close();
        */

    }

    // member founction ro save account data to file
    void save_account_changes(){
        ofstream data_saver;
        data_saver.open(filename_account(), ios::out);

        data_saver << username << " " << display_name << "\n";
        data_saver << passkey << " " << list_subscript << "\n";
        data_saver << "-------------------------\n";
        data_saver << current_settings.precision_point << " " << current_settings.currency_sign << "\n";
        data_saver << current_settings.list_size << " " << current_settings.elements_size << "\n";
        data_saver << current_settings.exclude_date << " " << current_settings.exclude_time << " " << current_settings.exclude_name << " " << current_settings.exclude_credit_values << " " << current_settings.exclude_condition_ctr << "\n";
        data_saver << "-------------------------\n";
        data_saver << "\n";

        for(int row = 0; row < list_subscript; row++){
            if(row == current_settings.list_size) break;

            data_saver << list_handle[row].element_subsript << " " << list_handle[row].pos << " " << list_handle[row].list_name << "\n";
            data_saver << list_handle[row].credit_value_included << " " << list_handle[row].wl_sub << " " << list_handle[row].date_time << "\n";

            for(int sub = 0; sub < 3; sub++){
                data_saver << list_handle[row].whitelisted[sub] << " ";
            } data_saver << "\n";

            for(int column = 0; column < list_handle[row].element_subsript; column++){
                if(column == current_settings.elements_size) break;

                // order of ofstream: type sub_lock date time value name
                data_saver << list_handle[row].element_handle[column].type << " " << list_handle[row].element_handle[column].sub_lock << " " << list_handle[row].element_handle[column].sub_pos <<" " << list_handle[row].element_handle[column].date << " "
                << list_handle[row].element_handle[column].time << " " << list_handle[row].element_handle[column].value << " " << list_handle[row].element_handle[column].credit_percent << " "
                << list_handle[row].element_handle[column].return_value << " " << list_handle[row].element_handle[column].name << "\n";
            } data_saver << "\n";
        }

        data_saver.close();
    }


    // member function to load account data from file
    bool log_in(){
        ifstream acc_login;
        acc_login.open(filename_account());
        if(!acc_login.is_open()){
            cout << "Error: " + error_message(4, 1) << endl;
            return false;
        }

        string compare_username;
        acc_login >> compare_username;
        if(compare_username != username){
            cout << "Error: " + error_message(4, 1) << endl;
            acc_login.close();
            return false;
        }

        acc_login.ignore(); getline(acc_login, display_name);

        activate_lists();
        acc_login >> passkey >> list_subscript;

        acc_login >> temp;
        acc_login >> current_settings.precision_point >> current_settings.currency_sign;
        acc_login >> current_settings.list_size >> current_settings.elements_size;
        acc_login >> current_settings.exclude_date >> current_settings.exclude_time >> current_settings.exclude_name >> current_settings.exclude_credit_values >> current_settings.exclude_condition_ctr;
        acc_login >> temp;


        for(int a = 0; a < list_subscript; a++){
            if(a == current_settings.list_size) {
                list_subscript = a;
                break;
            }

            if(acc_login.eof()){
                list_subscript = a;
                break;
            }

            list_handle[a].activate_elements();

            acc_login >> list_handle[a].element_subsript >> list_handle[a].pos;

            if(acc_login.fail()){
                acc_login.clear();
                cout << "Error: " + error_message(4, 4) << endl;
                return false;
            }

            acc_login.ignore(); getline(acc_login, list_handle[a].list_name);
            acc_login >> list_handle[a].credit_value_included >> list_handle[a].wl_sub;
            acc_login.ignore(); getline(acc_login, list_handle[a].date_time);

            for(int sub = 0; sub < 3; sub++){
                acc_login >> list_handle[a].whitelisted[sub];
            }

            for(int b = 0; b < list_handle[a].element_subsript; b++){
                if(b == current_settings.elements_size) {
                    list_handle[a].element_subsript = b;
                    break;
                }

                acc_login >> list_handle[a].element_handle[b].type >> list_handle[a].element_handle[b].sub_lock >> list_handle[a].element_handle[b].sub_pos >> list_handle[a].element_handle[b].date >>
                list_handle[a].element_handle[b].time >> list_handle[a].element_handle[b].value >> list_handle[a].element_handle[b].credit_percent >> list_handle[a].element_handle[b].return_value;
                acc_login.ignore(); getline(acc_login, list_handle[a].element_handle[b].name);

                if(acc_login.fail()){
                    acc_login.clear();
                    cout << "Error: " + error_message(4, 4) << endl;
                    return false;
                }

            }
        }

        acc_login.close();
        return true;
    }

    // member function to log out
    void log_out(){
        save_account_changes();
        deactivate_lists();
    }

    void delete_account(){
        deactivate_lists();
        const char * remove_account = filename_account().c_str();

        int result = remove(remove_account);
        if(result == 0){
            cout << "Account file deleted successfully!" << endl;
        } else cout << "The file still exist you idiot" << endl;
    }


} current_account, external_list_access;



// function to save program status
void save_login_status(bool login_status, string username){
    ofstream account_saver;
    account_saver.open("ADMIN_loginstatus.lstr", ios::out);
    account_saver << login_status << " " << username << "\n";

    account_saver.close();
}

// function to load program status
bool check_login_status(){
    bool login_status; string username;

    ifstream account_loader;
    account_loader.open("ADMIN_loginstatus.lstr");

    if(!account_loader.is_open()) return false;

    account_loader >> login_status >> username;

    if(!login_status) return false;

    current_account.username = username;

    if(!current_account.log_in()){
        return false;
    }

    account_loader.close();
    return true;
}



void account_creation_tab(){
    account creating_user;
    string final_in;

    while(final_in != "y" && final_in != "c"){
        cout << "--------------------- Creating Account --------------------" << endl;
        cout << "Allowed characters: " << creating_user.allowed_charcters << endl;
        cin.ignore();
        do{
            cout << "Enter your username: ";
            getline(cin, creating_user.username);
            if(!inspect_input(creating_user.username)){
                cout << "{" + error_message(3,1) << "} " << endl;
            } else if(creating_user.username.length() < 8 || creating_user.username.length() > 20){
                cout << "{" + error_message(3,2) << "} " << endl;
            }else if (is_account_exist(creating_user.username)){
                cout << "{" + error_message(4,2) << "} " << endl;
            }
        } while(!inspect_input(creating_user.username) || creating_user.username.length() < 8 || creating_user.username.length() > 20 || is_account_exist(creating_user.username));

        string passkey1, passkey2;

        creating_user.change_passkey();

        cin.ignore();
        creating_user.display_name = creating_user.username;
        cout << endl;
        creating_user.change_display_name(true);

        system("cls");
        string anonymous_psk = "";
        anonymous_psk = anonymous_psk.assign(creating_user.passkey.length(), '*');
        cout << "Username: " << creating_user.username << endl;
        cout << "Display name: " << creating_user.display_name << endl;
        cout << "Password: " << anonymous_psk << endl;
        cout << "---------------------------------" << endl;
        cout << "Do you want to finalize changes? " << endl;
        cout << "c < Exit account creation" << endl;

        do{
            cout << "[y/n]: "; cin >> final_in;
            if(final_in != "y" && final_in != "n" && final_in != "c") cout << "{" + error_message(1, 2) << "} ";
        }while(final_in != "y" && final_in != "n" && final_in != "c");

        system("cls");
    }

    if(final_in == "y") creating_user.create_account();
}


// ------------------------------------------------------------------------------------------------------------------------------------

// function to
void settings_tab(bool *login_status){
    int settings_choices;
    system("cls");
    while(settings_choices != 10){
        settings_choices = 0;
        cout << "------------------- Settings ---------------------" << endl;
        cout << "Username: " << current_account.username << endl;
        cout << "Display name: " << current_account.display_name << endl;
        cout << endl;
        cout << "- - - - - - - - - - - " << endl;
        cout << "1 > Precision Editor\n";
        cout << "2 > Currency Editor\n";
        cout << endl;
        cout << "3 > List size Editor\n";
        cout << "4 > Element size Editor\n";
        cout << "5 > Element exclusion modifier\n";
        cout << "6 > Reset changes to default\n";
        cout << endl;
        cout << "7 > Change display name\n";
        cout << "8 > Change password\n";
        cout << "9 > Delete account\n";
        cout << endl;
        cout << "10 > Exit Settings\n";
        cout << "--------------------" << endl;
        cout << "Enter the choices above (Number only): "; cin >> settings_choices;

        if(cin.fail()){
            cin.clear(); cin.ignore(1000, '\n');
            system("cls"); cout << "Error: " + error_message(1, 4) << endl;
            continue;
        }

        if(settings_choices == 1){ // initiates precision editor
            current_settings.precision_point_editor();
        } else if (settings_choices == 2){ // initiates currency editor
            current_settings.currency_editor();
        } else if(settings_choices == 3){ // initiates max lists editor
            if(warning()){
                current_settings.list_size_editor();
            }
        } else if(settings_choices == 4){ // initiates max elements editor
            if(warning()){
                current_settings.element_size_editor();
            }
        } else if(settings_choices == 5){ // initiates element exclusions modifier
            current_settings.element_exclusion_modifier();
        } else if(settings_choices == 6){ // initiates reset values editor
            if(warning()){
                system("cls");
                current_settings.setting_defaulter(default_settings);
            }
        } else if(settings_choices == 7){ // initiates display name manipulator
            cin.ignore();
            system("cls");
            current_account.change_display_name(false);
        } else if(settings_choices == 8){ // initiates password manipulator
            if(warning()){
                system("cls");

                if(!current_account.password_auth()){
                    system("cls");
                    current_account.log_out();
                    *login_status = false;
                    break;
                }

                current_account.change_passkey();
                system("cls");
                cout << "Account password changed!" << endl;
                continue;
            }
        } else if(settings_choices == 9){ // initiates deletion of account
            if(warning()){
                current_account.delete_account();
                current_settings.setting_defaulter(default_settings);
                *login_status = false;
                break;
            }
        }

        system("cls");
        if(settings_choices < 1 || settings_choices > 10) {
            cout << "Error: " + error_message(1, 2) << endl;
        }
    }

}

// list editor UI w/ list of elements
int list_editor(struct list_info current, struct statistics compute){
    int input_num = 0;
    while(input_num < 1 || input_num > 10){

        cout << "<< (10) Exit List Editor" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "(5) Sort Element           (6) Search Element      (7) Move Element" << endl;
        cout << "(8) Print as .txt file     (9) Export List" << endl;
        cout << "------------------------ List Editor ----------------------" << endl;
        cout << "List Name: " + current.list_name << endl;
        if(!current_settings.exclude_list_datetime)
            cout << "Updated: " + current.date_time << endl;
        cout << "Whitelisted users: ";
        for(int sub = 0; sub < 3; sub++){
            cout << current.whitelisted[sub];
            if(sub != 2) cout << ", ";
        } cout << endl << endl;

        cout << "     ----- Expenditure and Income Records -----     " << endl;

        cout << fixed << setprecision(current_settings.precision_point);
        current.print_elements(compute);
        if(current.element_subsript == 0) cout << "1) -    -    -    -   -" << endl;
        cout << endl;
        cout << "------------------------------------------------------------" << endl;
        compute.print_values();
        cout << endl;
        if (compute.allowance < 0) cout << "Warning: " + error_message(2, 3) << endl;
        if (compute.savings < 0) cout << "Warning: " + error_message(2, 2) << endl;
        if (compute.loan < 0) cout << "Warning: " + error_message(2, 7) << endl;
        else cout << endl;

        cout << "----------------------- List Input ------------------------"  << endl;
        cout << "1: Create new element               2: Edit specific element" << endl;
        cout << "3: Delete specific element          4: Delete all elements" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Enter only numbers....." << endl;
        cout << endl;
        cout << "> "; cin >> input_num;

        // error detection statements
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            cout << "Error: " + error_message(1, 4) << endl;
        } else if(input_num < 1 || input_num > 9){
            system("cls");
            cout << "Error: " + error_message(1, 2) << endl;
        }
    }

    return input_num;
}

// this is where you initiate the list editor
void startlist_tab(struct list_info * manip_list){
    int list_input = 0;
    while(list_input != 10){
        statistics current_computer; // struct declaration

        // function for element computations
        manip_list->compute_elements(&current_computer);

        // function for player choice in list editor
        list_input = list_editor(*manip_list, current_computer);

        system("cls");
        switch(list_input){
            case 1: { // case statement to initiate create element

                if (manip_list->element_subsript < current_settings.elements_size){ // if the elements is below maximum element size
                    manip_list->element_handle[manip_list->element_subsript].element_creator(current_computer);
                    manip_list->element_handle[manip_list->element_subsript].sub_pos = manip_list->pos;
                    manip_list->element_subsript += 1;
                    manip_list->pos += 1;
                    system("cls");

                } else { // if the elements reached to maximum element size
                    system("cls");
                    cout << "Error: " + error_message(1, 3) << endl;
                    continue;
                }

                break;
            } case 2: { // case statement to initiate edit element
                string e_resp; int edit_sub = -1;

                if(manip_list->element_subsript == 0){
                    cout << "Error: " + error_message(2, 8) << endl;
                    break;
                }

                do{
                    cout << "------------------------------------------------------------" << endl;
                    cout << fixed << setprecision(current_settings.precision_point);
                    manip_list->print_elements(current_computer);
                    cout << "------------------------------------------------------------" << endl;
                    current_computer.print_values();
                    cout << endl;
                    cout << "(Type \"c\" to cancel edit)" << endl;
                    cout << "Which element do you want to edit?: " << endl;
                    cout << "> "; cin >> e_resp;

                    if(e_resp == "c") break;
                    if(!value_detection(e_resp, 1)){
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 4) << endl;
                        continue;
                    }

                    edit_sub = conversion_tool<string, int>(e_resp);
                    if(edit_sub < 1 || edit_sub > manip_list->element_subsript) {
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    }
                }while(edit_sub < 1 || edit_sub > manip_list->element_subsript);

                system("cls");
                if(e_resp != "c") manip_list->element_handle[edit_sub - 1].element_editor(current_computer, edit_sub-1);

                system("cls");
                break;
            } case 3: { // case statement to initiate delete specified element
                system("cls"); string del_resp; int del_sub = -1;

                if(manip_list->element_subsript == 0){
                    cout << "Error: " + error_message(2, 8) << endl;
                    break;
                }

                do{
                    cout << "------------------------------------------------------------" << endl;
                    cout << fixed << setprecision(current_settings.precision_point);
                    manip_list->print_elements(current_computer);
                    cout << "------------------------------------------------------------" << endl;
                    current_computer.print_values();
                    cout << endl;
                    cout << "(Type \"c\" to cancel deletion)" << endl;
                    cout << "Which element do you want to delete?: " << endl;
                    cout << "> "; cin >> del_resp;

                    if(del_resp == "c") break;
                    if(!value_detection(del_resp, 1)){
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 4) << endl;
                        continue;
                    }

                    del_sub = conversion_tool<string, int>(del_resp);
                    if(del_sub < 1 || del_sub > manip_list->element_subsript) {
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    }
                }while(del_sub < 1 || del_sub > manip_list->element_subsript);

                if(del_resp != "c") manip_list->delete_element(del_sub);

                system("cls");
                break;
            } case 4: { // case statement to delete all elements
                cout << "You are going to delete all elements in " << manip_list->list_name << " list." << endl;
                if(warning()){
                    manip_list->delete_element();
                } system("cls");
                cout << "Elements in " << manip_list->list_name << " has been deleted." << endl;
                break;
            } case 5: { // case statement to initiate sort element
                int sort_mode = 0;

                if(manip_list->element_subsript == 0){
                    cout << "Error: " + error_message(2, 8) << endl;
                    break;
                }

                do{
                    cout << "------------------------------------------------------------" << endl;
                    cout << fixed << setprecision(current_settings.precision_point);
                    manip_list->print_elements(current_computer);
                    cout << "---------- Sort by: ----------" << endl;
                    if(!current_settings.exclude_date) cout << "1: Date" << endl;
                    if(!current_settings.exclude_time) cout << "2: Time" << endl;
                    if(!current_settings.exclude_name) cout << "3: Name" << endl;
                    cout << "4: Value" << endl;
                    cout << "5: Reverts to original position" << endl;
                    cout << "6: Go back to list editor" << endl;
                    cout << endl;
                    cout << "> "; cin >> sort_mode;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 4) << endl;
                    } else if (sort_mode < 1 || sort_mode > 5) {
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    } else if ((current_settings.exclude_date && sort_mode == 1) || (current_settings.exclude_time && sort_mode == 2) || (current_settings.exclude_name && sort_mode == 3)){
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    }

                }while(sort_mode < 1 || sort_mode > 6);

                if(sort_mode != 6 && sort_mode != 5) manip_list->sort_elements(sort_mode);
                else if(sort_mode == 5) manip_list->sort_elements();

                system("cls");
                break;
            } case 6: { // case statement to initiate search element
                if(manip_list->element_subsript == 0){
                    cout << "Error: " + error_message(2, 8) << endl;
                    break;
                }

                string search_value;
                cin.ignore();
                cout << "------------------------------------------------------------" << endl;
                manip_list->print_elements(current_computer);
                cout << "----------------------------------------------------" << endl;
                cout << "Search: "; getline(cin, search_value);
                cout << endl;

                int search_result = manip_list->search_element(current_computer, search_value);
                if(search_result != -1){
                    cout << "Location of \"" << search_value << "\" is found at: " << search_result+1 << endl;
                    manip_list->element_handle[search_result-1].print_subscript_element(search_result, current_computer);
                } else {
                    cout << "Location of \"" << search_value << "\" is not found...." << endl;
                }

                getline(cin, search_value);
                system("cls");


                break;
            } case 7: { // case statement to move elements to any position
                string move_resp = "-"; int sub_from = -1, sub_to = -1;

                if(manip_list->element_subsript == 0){
                    cout << "Error: " + error_message(2, 8) << endl;
                    break;
                }

                do{
                    cout << "------------------------------------------------------------" << endl;
                    cout << fixed << setprecision(current_settings.precision_point);
                    manip_list->print_elements(current_computer);
                    cout << "------------------------------------------------------------" << endl;
                    current_computer.print_values();
                    cout << endl;
                    cout << "(Type \"c\" to cancel move element)" << endl;
                    cout << "Which element do you want to move?: " << endl;
                    cout << "> "; cin >> move_resp;

                    if(move_resp == "c") break;
                    if(!value_detection(move_resp, 1)){
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 4) << endl;
                        continue;
                    }

                    sub_from = conversion_tool<string, int>(move_resp);
                    if(sub_from < 1 || sub_from > manip_list->element_subsript) {
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    } else if(manip_list->element_handle[sub_from-1].sub_lock){
                        system("cls");
                        sub_from = -1;
                        cout << "Error: Locked element. Cannot proceed" << endl;
                    }
                }while(sub_from < 1 || sub_from > manip_list->element_subsript);

                system("cls");
                if(move_resp == "c") break;

                move_resp = "-";
                cout << "------------------------------------------------------------" << endl;
                cout << fixed << setprecision(current_settings.precision_point);
                manip_list->print_elements(current_computer);
                cout << endl;
                cout << "Move element: "; manip_list->element_handle[sub_from-1].print_subscript_element(sub_from - 1, current_computer);
                cout << "------------------------------------------------------------" << endl;
                cout << "Enter the position you want to place: [1/" << manip_list->element_subsript << "] " << endl;

                do{
                    cout << "> "; cin >> move_resp;

                    if(move_resp == "c") break;
                    if(!value_detection(move_resp, 1)){
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 4) << endl;
                        continue;
                    }

                    sub_to = conversion_tool<string, int>(move_resp);
                    if(manip_list->element_handle[sub_to-1].sub_lock){
                        sub_to = -1;
                        cout << "{Locked element. Cannot proceed} ";
                    } else if(sub_from == sub_to){
                        sub_to = -1;
                        cout << "{Same position, must be in a different position} ";
                    }
                }while(sub_to < 1 || sub_to > manip_list->element_subsript);

                if(move_resp != "c"){
                    manip_list->move_element(sub_from-1, sub_to-1);
                }
                system("cls");
                break;
            } case 8: { // case statement to print elements as .txt file
                manip_list->save_list_txt(current_computer);
                break;
            } case 9: { // case statement to whitelist users
                manip_list->export_list();
                break;
            }
        }

    }


}

void access_list(int resp22){
    int resp3 = 0;

    cout << "-------------------------------------------" << endl;
    cout << resp22+1 << ": ";
    if(!current_settings.exclude_list_datetime) cout << current_account.list_handle[resp22].date_time;
    cout << "  " << current_account.list_handle[resp22].list_name << " (Elements: " << current_account.list_handle[resp22].element_subsript << ")" << endl;
    cout << endl;
    cout << "1 > Access list" << endl;
    cout << "2 > Rename list name" << endl;
    cout << "3 > Delete List" << endl;
    cout << "4 > Whitelist Users"  << endl;
    cout << "5 > Go back to menu" << endl;
    cout << "------------------------------" << endl;

    do{
        cout << "> "; cin >> resp3;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: " + error_message(1, 4) << endl;
        } else if(resp3 < 1 || resp3 > 4){
            cout << "Error: " + error_message(1, 2) << endl;
        }

        if(resp3 == 3){
            if(!warning()) resp3 = 0;
        }
    }while(resp3 < 1 || resp3 > 5);

    system("cls");
    switch(resp3){
        case 1:{
            startlist_tab(current_account.list_handle + resp22);
            current_account.list_handle[resp22].date_time = print_datetime(3); // updates date and time when accessing the list
            break;
        } case 2:{
            cin.ignore();
            current_account.manipulate_list_name(resp22);
            break;
        } case 3:{
            current_account.delete_list(resp22);
            break;
        } case 4:{
            current_account.whitelist_players(resp22);
            break;
        }
    }
    current_account.save_account_changes();
    system("cls");
}


void whitelist_access(){
    system("cls"); bool account_checker = false;

    while(external_list_access.username != "c"){
        cout << "---------------------------------------------" << endl;
        cout << "Enter \"c\" to go back to menu" << endl;
        cout << "Enter username of the owner of the list:" << endl;
        do{
            cout << "> "; getline(cin, external_list_access.username);
            if(external_list_access.username == "c") break;
            if(!inspect_input(external_list_access.username)){
                cout << "{" + error_message(3,1) << "} " << endl;
                continue;
            } else if(external_list_access.username.length() < 8 || external_list_access.username.length() > 20){
                cout << "{" + error_message(3,2) << "} " << endl;
                continue;
            }

            account_checker = external_list_access.log_in();
            if(!account_checker){
                cout << "{" + error_message(4, 1) + "} " << endl;
            }
        }while(!account_checker);

        cout << endl; string search_list; system("cls");
        while(account_checker && search_list != "c"){
            cout << "Enter a list name from \"" << external_list_access.username << "\": (c: Go back to username search)" << endl;
            cout << "> "; getline(cin, search_list);

            int extlistsub = external_list_access.search_list(search_list, -1);
            if(extlistsub != -1 && external_list_access.list_handle[extlistsub].is_player_whitelisted(current_account.username)){
                system("cls");
                startlist_tab(external_list_access.list_handle + extlistsub);
                external_list_access.save_account_changes();
                cin.ignore();
            } else {
                cout << endl;
                cout << "Error: " + error_message(4, 3) << " And/or user is not whitelisted." << endl;
            }
        }
    }

    external_list_access.log_out();
    current_account.log_in();
}

// ------------------------------------------------------------------------------------------------------------------------------------

void display_header(){
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "  |      ~~~~~~        |  $$$$$ $$$$$ $$  $ $$$$$ $ $$  $  $$$  $$$$$ $$$$$ $$$$        $     $        " << endl;
    cout << "  | -----------------  |  $     $     $ $ $ $     $ $ $ $ $   $ $     $     $   $     $     $     $    " << endl;
    cout << "  | ~~~~  ~~~~         |  $  $$ $$$   $ $ $ $$$   $ $ $ $ $$$$$ $  $$ $$$   $$$$       $       $       " << endl;
    cout << "  | --------------     |  $   $ $     $ $ $ $     $ $ $ $ $   $ $   $ $     $  $     $      $          " << endl;
    cout << "  | * ~~~~~~    ~~ $$  |  $$$$$ $$$$$ $  $$ $     $ $  $$ $   $ $$$$$ $$$$$ $   $        $      $      " << endl;
    cout << "  | * ~~~~~~    ~~ $$  |  -------------------------------------------------------    $     $     $     " << endl;
    cout << "  | * ~~~~~~    ~~ $$  |       General Purpose Finance Monitoring System                 $      $      " << endl;
    cout << "  | --------------     |  - - - - - - - - - - - - - - - - - - - - - - - - - - - -     $       $        " << endl;
    cout << "  | - ~~~~~  `         |       \"Manage Expenses easily and smoothly......\"             $    $     $  " << endl;
    cout << "  | - ~~~~~  `         |                                                              $         $      " << endl;
    cout << "  |                    |     Project creaated by: Matthew Kristoff B. Gonzales      ~~~~~~~~~~~~~~~    " << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;

}


void menu_tab(struct account user){
    display_header();
    cout << "Welcome, " << user.display_name << "! (" << user.username << ")" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Current list size: " << user.list_subscript << "/" << current_settings.list_size << endl;
    cout << "----- Lists: -----" << endl;
    user.print_list();
    cout << "---------------------" << endl;

    cout << "a: Create new list" << endl;
    cout << "b: Sort Lists" << endl;
    cout << "c: Delete All Lists" << endl;
    cout << "d: Access List from other accounts" << endl;
    cout << endl;
    cout << "e: Settings" << endl;
    cout << "f: Help" << endl;
    cout << "g: Credits" << endl;
    cout << "h: Log out" << endl;
    cout << "i: Exit" << endl;
}

// function to display help info
void help_tab(){
    int help_resp = 0;
    while(help_resp != 9){
        cout << "---------------------------------------------------------------" << endl;
        cout << "     How can we help you? " << endl;
        cout << endl;
        cout << "1: Introduction" << endl;
        cout << "2: List handling" << endl;
        cout << "3: List editor " << endl;
        cout << "4: List import/export" << endl;
        cout << "5: Whitelisting" << endl;
        cout << "6: Settings" << endl;
        cout << "7: Account handling" << endl;
        cout << "8: Other informations" << endl;
        cout << "9: Exit" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << endl;


        do{
            cout << "> "; cin >> help_resp;

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "{" + error_message(1,4) << "} " << endl;
            } else if(help_resp < 1 || help_resp > 8) cout << "{" + error_message(1,2) << "} " << endl;


        }while(help_resp < 1 || help_resp > 9);

        system("cls");
        if(help_resp == 9) continue;


        ifstream help_reader; string reader;
        help_reader.open("ADMIN_Help.lstr");

        while(!help_reader.eof()){
            getline(help_reader, reader);
            if(reader == to_string(help_resp)){
                while(getline(help_reader, reader) && reader != "ENDOFLINE"){
                    cout << reader << endl;
                }
            }

        }

        help_reader.close();

        cin.ignore();
        cout << "[Enter to exit]" << endl;
        getline(cin, reader);
        system("cls");
    }

}

// function to display credits
void credits_tab(){
    string temp, data_gatherer;
    ifstream readerfile;
    readerfile.open("ADMIN_Credit.lstr");

    display_header();
    while(getline(readerfile, data_gatherer)){
        cout << data_gatherer << endl;
    }

    cout << endl;
    cout << "[Enter to exit]" << endl;
    getline(cin, temp);

}


// ------------------------- main function -----------------------

int main(){
    bool login_status = false;

    // code operations starts here
    login_status = check_login_status();

    bool prog_conditions = true;
    while(prog_conditions){

        // ------------------------- Menu Tab (logged in) --------------------------------
        if(login_status){
            string resp2; bool list_crdt = true;
            int resp22 = -1;
            do{
                if(!login_status) break;

                menu_tab(current_account);
                cout << "------------------------------" << endl;
                cout << "> "; cin >> resp2;

                system("cls");

                if(resp2 == "a"){ // Create new list
                    if(current_account.list_subscript == current_settings.list_size){
                        cout << "Error: " + error_message(1, 3) << endl;
                        continue;
                    }
                    current_account.list_creation();
                    current_account.save_account_changes();
                    system("cls");
                    continue;
                } else if(resp2 == "b"){ // Sort List
                    current_account.sort_list();
                    system("cls");
                } else if(resp2 == "c"){ // Delete List
                    if(warning()){
                        current_account.delete_list();
                        current_account.save_account_changes();
                    }
                    system("cls");
                } else if(resp2 == "d"){ // Access list from other users
                    cin.ignore();
                    whitelist_access();
                    system("cls");
                }


                else if(resp2 == "e"){ // Settings
                    settings_tab(&login_status);
                    if(!login_status){
                        resp2 = "h";
                        continue;
                    } else {
                        current_account.log_out();
                        current_account.log_in();
                    }
                    system("cls");
                } else if(resp2 == "f"){ // Help
                    help_tab();
                    system("cls");
                } else if(resp2 == "g"){ // Credits
                    cin.ignore();
                    credits_tab();
                    system("cls");
                } else if(resp2 == "h" || resp2 == "i"){  // Log out / exit
                    break;
                }

                else {
                    if(!value_detection(resp2, 1)){
                        cin.ignore(1000, '\n');
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                        continue;
                    }

                    resp22 = conversion_tool<string, int>(resp2);

                    if(resp22 < 1 || resp22 > current_account.list_subscript+1){
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    }

                    list_crdt = current_settings.exclude_credit_values && current_account.list_handle[resp22].credit_value_included;
                    if(list_crdt){
                        system("cls");
                        cout << "Error: " + error_message(1, 2) << endl;
                    }
                }

            }while(resp22 < 1 || resp22 > current_account.list_subscript+1 || list_crdt);

            if(resp2 == "h"){ // Log out
                if(login_status)current_account.log_out();
                login_status = false;
                save_login_status(login_status, current_account.username);
                system("cls");
                continue;
            } else if(resp2 == "i"){ // Exit the program / Remained logged
                current_account.log_out();
                save_login_status(login_status, current_account.username);
                prog_conditions = false;
                system("cls");
                continue;
            }

            if(resp22 >= 1 || resp22 <= current_account.list_subscript+1){
                if(current_account.list_subscript == 0) {
                    system("cls");
                    cout << "Error: " + error_message(1, 2) << endl;
                    continue;
                }
                system("cls");
                resp22--;

                access_list(resp22);

            } system("cls");
            continue;
        }

        // ------------------------- Menu Tab (logged out) --------------------------------
        else {
            int resp1 = -1;
            do{
                display_header();
                cout << endl;
                cout << "1 < Log in" << endl;
                cout << "2 < Create an account" << endl;
                cout << "3 < Credits" << endl;
                cout << "4 < Exit" << endl;
                cout << "----------------------------------------------------" << endl;
                cout << "> "; cin >> resp1;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("cls");
                    cout << "Error: " + error_message(1, 4) << endl;
                } else if(resp1 < 1 || resp1 > 4){
                    system("cls");
                    cout << "Error: " + error_message(1, 2) << endl;
                }

            } while(resp1 < 1 || resp1 > 4);

            system("cls");

            // ------------------------- Login tab --------------------------------
            if(resp1 == 1){
                cin.ignore();
                bool status = true;
                while(status){
                    bool account_checker = false;

                    cout << "\"c\" < Go back to menu" << endl;

                    do{
                        cout << "Enter your username: "; getline(cin, current_account.username);
                        if(current_account.username == "c") break;
                        if(!inspect_input(current_account.username)){
                            cout << "{" + error_message(3,1) << "} ";
                            continue;
                        } else if(current_account.username.length() < 8 || current_account.username.length() > 20){
                            cout << "{" + error_message(3,2) << "} " << endl;
                            continue;
                        }

                        account_checker = current_account.log_in();
                    }while(!account_checker);

                    if(current_account.username == "c") break;

                    cout << endl;
                    if(current_account.password_auth()){
                        // save_data(account_size, login_status, current_username);
                        status = false;
                        login_status = true;
                        save_login_status(login_status, current_account.username);
                        cin.ignore();
                    }

                    system("cls");
                }

            // ------------------------- Account creation --------------------------------
            } else if(resp1 == 2){
                account_creation_tab();
                // handle_data(&account_size, &login_status, &current_username);


            } else if(resp1 == 3){
                cin.ignore();
                credits_tab();
            } else if(resp1 == 4){ //  Exit program
                prog_conditions = false;
            }
            system("cls");
        }


    }

    cout << "Thank you and have a nice day!" << endl;
    return 0;
}

// ------------------------------------------------------------------------------------------------------------------------------------

// convert tools
template <typename before, typename after>
after conversion_tool(before isbfr){
    stringstream convert;
    convert << isbfr;
    after isaft;
    convert >> isaft;
    return isaft;
}


// function to display error messages
string error_message(int type, int errornumber){
    switch(type){
        case 1:{ // input related
            if(errornumber == 1) return "Input should not be empty.";
            else if(errornumber == 2) return "Input not in the choices.";
            else if(errornumber == 3) return "Operation exceeding the limits, cannot proceed.";
            else if(errornumber == 4) return "Invalid input.";
            break;
        } case 2:{ // element and list value related
            if(errornumber == 1) return "The option was excluded in the settings.";
            else if(errornumber == 2) return "Withdrawal exceeds savings deposit value. The expense should be below the deposit value.";
            else if(errornumber == 3) return "Expenses exceeds allowance. Please check the values properly.";
            else if(errornumber == 4) return "List name should be distinct form other lists";
            else if(errornumber == 5) return "Value cannot be zero or less";
            else if(errornumber == 6) return "List name should at least 4 to 30 characters only";
            else if(errornumber == 7) return "Overpaid loan value. Please check the values properly";
            else if(errornumber == 8) return "Proceeding without existing elements";
            break;
        } case 3:{ // account info related
            if(errornumber == 1) return "Invalid username.";
            else if(errornumber == 2) return "Username should be at least 8 to 20 characters.";
            else if(errornumber == 3) return "Password do not match.";
            else if(errornumber == 4) return "Incorrect password.";
            else if(errornumber == 5) return "Invalid new password.";
            else if(errornumber == 6) return "Password should be at least 8 to 30 characters.";
            else if(errornumber == 7) return "Display name should be at least 5 to 30 characters.";
            else if(errornumber == 8) return "Self-whitelisting; cannot do that";
            break;
        } case 4: { // file related
            if(errornumber == 1) return "Account not yet existed";
            else if(errornumber == 2) return "Username already existed";
            else if(errornumber == 3) return "List file not found";
            else if(errornumber == 4) return "File cannot load properly";
            break;
        }


    }

    return "Error type or number was not valid.";
}


// function to identify if the string is all digits
bool value_detection(string isstr, int mode){
    if(mode == 1){
        for (int a = 0; a < (int) isstr.length(); a++){
            if (!isdigit(isstr[a])) return false;
        }
    } else if(mode == 2){
        bool dec_point = false;
        for (int a = 0; a < (int) isstr.length(); a++){
            if (isstr[a] == '.' && !dec_point) {
                dec_point = true;
                continue;
            }
            if (!isdigit(isstr[a])) {
                return false;
            }
        }
    }

    return true;
}

template <typename data_type>
void swap_values(data_type *val1, data_type *val2){
    data_type temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

string inclusion_indicator(bool active){
    return (active) ? "[o]" : "[x]";
}

bool warning(){
    string resp;
    cout << "Do you want to proceed? (Cannot be reversed once done)" << endl;

    do{
        cout << "[y/n]: "; cin >> resp;
        if (resp != "y" && resp != "n") {
            cout << "Error: " + error_message(1, 2) << endl;
        }
    }while(resp != "y" && resp != "n");

    return resp == "y";
}

bool inspect_input(string str_input){
    string allowed_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_@$?!";
    for(int a = 0; a < (int) str_input.length(); a++){
        bool not_found = true;
        for(int b = 0; b < (int) allowed_characters.length(); b++){
            if(str_input[a] == ' ') return false;
            else if(str_input[a] == allowed_characters[b]) not_found = false;
        }

        if(not_found) return false;
    }
    return true;
}

string print_datetime(int mode){
    time_t current_time = time(0);
    tm * result = localtime(&current_time);

    string return_date, return_time;
    return_date = to_string(result->tm_mon + 1) + "/" + to_string(result->tm_mday) + "/" + to_string(result->tm_year + 1900);
    return_time = to_string(result->tm_hour) + ":" + to_string(result->tm_min);

    if(mode == 1) return return_date;
    else if(mode == 2) return return_time;
    else if(mode == 3) return return_date + " " + return_time;

    return "MODE 1-2-3";
}

bool is_account_exist(string accont_file){
    ifstream check;
    string filename = accont_file + ".lstacc";
    check.open(filename);

    if(check.is_open()){
        string compare_username;
        check >> compare_username;

        if(compare_username != accont_file){
            check.close();
            return false;
        }

        check.close();
        return true;
    }

    check.close();
    return false;
}

