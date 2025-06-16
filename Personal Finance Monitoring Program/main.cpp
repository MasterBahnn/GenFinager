#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

double double_conversion(string isstr);
int integer_conversion(string isstr);
string error_message(int errornumber);
bool digit_detection(string isstr);
bool float_value_detection(string isstr);


// function to create elements to lists
void create_element(string type_element[], string name_element[], double value_element[], int subscipt_occupy, bool if_edit, string currency_sign1, int precision_val){
    double allowance = 0.0, savings = 0.0, expenses = 0.0;

    for (int sub = 0; sub < subscipt_occupy; sub++){
        if (type_element[sub] == "expense_type"){
            expenses += value_element[sub];
            allowance -= value_element[sub];
        } else if (type_element[sub] == "income_type"){
            allowance += value_element[sub];
        } else if (type_element[sub] == "savings_deposit"){
            savings += value_element[sub];
            allowance -= value_element[sub];
        } else if (type_element[sub]== "savings_withdraw"){
            savings -= value_element[sub];
            allowance += value_element[sub];
        }
    }

    string conditions[4] = {"expense_type", "income_type", "savings_deposit", "savings_withdraw"};
    int conditions_size = sizeof(conditions)/sizeof(conditions[0]);

    cout << fixed;
    cout << setprecision(precision_val);


    if (if_edit == true){
        cout << "Edit element "<< subscipt_occupy+1 << ")" << "    |  " + type_element[subscipt_occupy] << "\t\t| " << name_element[subscipt_occupy] << ": " + currency_sign1 << value_element[subscipt_occupy] << endl;
    }
    cout << "Allowance: " + currency_sign1 << allowance << "\tSavings: " + currency_sign1 << savings << "\tExpenses: " + currency_sign1 << expenses << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Choices (Value condition): " << endl;
    for (int sub = 0; sub < conditions_size; sub++){
        cout << sub+1 << ": " + conditions[sub] << endl;
    }
    cout << "---------------" << endl;

    int condition_num1 = 0;
    do {string input_num1 = " ";
        cout << "Value type (number only from the choices): ";
        cin >> input_num1;
        if (digit_detection(input_num1) == false) {cout << "Error: " + error_message(2); continue;}
        condition_num1 = integer_conversion(input_num1);
        if (condition_num1 < 1 || condition_num1 > 4) cout << "Error: " + error_message(2);
    } while (condition_num1 < 1 || condition_num1 > 4);
    type_element[subscipt_occupy] = conditions[condition_num1-1];

    cout << endl;
    cin.ignore();

    do{ cout << "Name of element: ";
    getline(cin, name_element[subscipt_occupy]);
    if (name_element[subscipt_occupy].length() == 0) cout << "Error: " + error_message(1);

    } while (name_element[subscipt_occupy].length() == 0);

    string value_input = " ";
    do { cout << "Value of element: " + currency_sign1; cin >> value_input;
        if (value_input.length() == 0) cout << "Error: " + error_message(1);
        else if (float_value_detection(value_input) == false) cout << "Error: " + error_message(5);
    } while (float_value_detection(value_input) == false);
    value_element[subscipt_occupy] = double_conversion(value_input);

    if (type_element[subscipt_occupy] == "savings_withdraw" && value_element[subscipt_occupy] > savings){
        system("cls");
        cout << "Error: " + error_message(3);
        create_element(type_element, name_element, value_element, subscipt_occupy, false, currency_sign1, precision_val);
    } else if (type_element[subscipt_occupy] == "expense_type" && allowance - value_element[subscipt_occupy] < 0){
        system("cls");
        cout << "Error: " + error_message(4);
        create_element(type_element, name_element, value_element, subscipt_occupy, false, currency_sign1, precision_val);
    }

}

// function to print out lists (reused for viewing lists in editing and deletion of specific element)
void print_out_type(string list_name, string type_element[], string name_element[], double value_element[], int element_size, string currency_sign1, int precision_val){
    double allowance = 0.0, savings = 0.0, expenses = 0.0;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "List Name: " + list_name << endl;
    cout << "     ----- Expenses -----     " << endl;

    cout << fixed;
    cout << setprecision(precision_val);

    for (int sub = 0; sub < element_size; sub++){
        cout << sub+1 << ")" << "    |  " + type_element[sub] << "\t\t| " << name_element[sub] << ": " + currency_sign1 << value_element[sub] << endl;

        if (type_element[sub] == "expense_type"){
            expenses += value_element[sub];
            allowance -= value_element[sub];
        } else if (type_element[sub] == "income_type"){
            allowance += value_element[sub];
        } else if (type_element[sub] == "savings_deposit"){
            savings += value_element[sub];
            allowance -= value_element[sub];
        } else if (type_element[sub]== "savings_withdraw"){
            savings -= value_element[sub];
            allowance += value_element[sub];
        }
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "Allowance: " + currency_sign1 << allowance << "\tExpenses: " + currency_sign1 << expenses << "\tSavings: " + currency_sign1 << savings << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

}

// function to delete specific element from list
void delete_one_element(string type_element[], string name_element[], double value_element[], int subscript_occupied, int sub_delete){
    for (int sub = sub_delete; sub < subscript_occupied; sub++){
        if (sub > sub_delete){
            type_element[sub-1] = type_element[sub];
            name_element[sub-1] = name_element[sub];
            value_element[sub-1] = value_element[sub];
        } else if (sub == subscript_occupied-1) {
            type_element[sub] = "empty";
            name_element[sub] = "-- empty --";
            value_element[sub] = 0.0;
        }
    }
}

// function to delete all elements from lists
void clear_list(string type_element[], string name_element[], double value_element[], int element_size){
    for (int sub = 0; sub < element_size; sub++){
        type_element[sub] = "empty";
        name_element[sub] = "-- empty --";
        value_element[sub] = 0.0;
    }
}

// function to manipulate elements from a list
int list_editor(string list_name, string type_element[], string name_element[], double value_element[], int element_size, string currency_sign1, int precision_val){
    int input = 0;
    double allowance = 0.0, savings = 0.0, expenses = 0.0;


    while(input < 1 || input > 8){
        input = 0;
        cout << " << Exit List Editor (Press 8)" << "\n Rename list name (Press 7) " << "\t | New list (Press 6)" << "\t | Print View (Press 5) |" << endl;
        cout << "------------------------ List Editor ----------------------" << endl;
        cout << "List Name: " + list_name << endl;
        cout << "     ----- Expenses -----     " << endl;

        cout << fixed;
        cout << setprecision(precision_val);

        for (int sub = 0; sub < element_size; sub++){
            cout << sub+1 << ")" << "    |  " + type_element[sub] << "\t\t| " << name_element[sub] << ": " + currency_sign1 << value_element[sub] << endl;

            if (type_element[sub] == "expense_type"){
                expenses += value_element[sub];
                allowance -= value_element[sub];
            } else if (type_element[sub] == "income_type"){
                allowance += value_element[sub];
            } else if (type_element[sub] == "savings_deposit"){
                savings += value_element[sub];
                allowance -= value_element[sub];
            } else if (type_element[sub]== "savings_withdraw"){
                savings -= value_element[sub];
                allowance += value_element[sub];
            }
        }

        cout << "------------------------------------------------------------" << endl;
        cout << "Allowance: " + currency_sign1 << allowance << "\tExpenses: " + currency_sign1 << expenses << "\tSavings: " + currency_sign1 << savings << endl;
        if (allowance < 0) cout << "Warning: " + error_message(4) << endl;
        if (savings < 0) cout << "Warning: " + error_message(3) << endl;
        else cout << endl;

        cout << "Choices: (type the numbers)" << endl;
        cout << "1: Create new element" << "\n2: Edit specific element" << "\n3: Delete specific element" << "\n4: Delete all elements" << endl;
        string input_num = " ";
        cout << "Enter your answer: "; cin >> input_num;

        // error detection statements
        if (digit_detection(input_num) == false) {
            system("cls");
            cout << "Error: " + error_message(2);
            continue;
        } input = integer_conversion(input_num); // converts string to integer number
        if (input < 1 || input > 8){
            system("cls");
            cout << "Error: " + error_message(2);
        }
    }

    return input;
}

// ------------------------------------------- settings functions -------------------------------------------------


// function to change currency sign
string currency_editor(string currency_sign){
    string default_cs = currency_sign;
    string currency_signs[5] = {"$ ", "PHP ", "GBP ", "YEN ", "EURO "};
    int cs_size = sizeof(currency_signs)/sizeof(currency_signs[0]);

    string input_cs; int sub_cs;
    do{
        cout << "Current: \" " + currency_sign + "\""<< "\t Example: " + currency_sign << 100.00 << endl;
        cout << "---------------------------------------" << endl;
        cout << "Available currency signs:" << endl;

        for (int sub = 0; sub < cs_size ; sub++){
            cout << sub+1 << ": \" " + currency_signs[sub] << "\"  " << endl;
        } cout << endl;

        cout << "(Type \"Cancel\" to exit)" << endl;
        cout << "Which currency sign you want to use?: "; cin >> input_cs;

        if(input_cs == "Cancel") break;
        if(digit_detection(input_cs) == false) { system("cls"); cout << "Error: " + error_message(2);}

        sub_cs = integer_conversion(input_cs) - 1;
        if (sub_cs < 0 || sub_cs > cs_size-1) { system("cls"); cout << "Error: " + error_message(2);}
    } while (sub_cs < 0 || sub_cs > cs_size-1);

    if(input_cs == "Cancel") return "Cancel";

    return currency_signs[sub_cs];
}

// function to adjust precision points in floating values
string precision_editor(int def_precisionval, string currency_sign1){

    cout << fixed << setprecision(def_precisionval);

    string response_adjuster;
    do{
        cout << "Current: " + currency_sign1 << 100.00 << endl;
        cout << "Precision Value: " << def_precisionval << endl;
        cout << "----------------------------------------" << endl << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "| Type \"Decrease\" << [-] " << def_precisionval << " [+] >> Type \"Increase\" |" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Min: 0 \t Max: 4" << endl << endl;

        cout << "(Type \"Cancel\" to exit)" << endl;
        cout << "[Increase/Decrease] : "; cin >> response_adjuster;

        if(response_adjuster == "Cancel") break;

        if(response_adjuster != "Increase" && response_adjuster != "Decrease") { system("cls"); cout << "Error: " + error_message(2);}
    } while(response_adjuster != "Increase" && response_adjuster != "Decrease");

    return response_adjuster;
}

// function to display help info
void help_tab(int precision_val, string currency_sign1){
    string sample_list_name = "Daily Expense";
    string sample_type_element[6] = {"income_type", "expense_type", "expense_type", "savings_deposit", "savings_withdraw"};
    string sample_name_element[6] = {"allowance", "meal", "gasoline refill", "for emergency funds", "withdraw for car repair"};
    double sample_value_element[6] = {10000.00, 59.99 ,250.00, 400.00, 399.29};
    int sample_occupied_subscript = 5;
    int sample_size = sizeof(sample_type_element)/sizeof(sample_type_element[0]);

    string conditions[4] = {"expense_type", "income_type", "savings_deposit", "savings_withdraw"};

    cin.ignore();

    cout << "----------- Welcome to Personal Finance Monitoring Program! ---------------" << endl;
    cout << "This allows you to monitor your expenditures, and manage your finances." << endl;
    cout << "This part of the program serves as a guide for new users on using this program." << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "= To start creating new list: " << endl;
    cout << "> Go to \" StartList\" to create a new list" << endl;
    cout << "> Name a list of your desire. Then enter." << endl;
    cout << "\t Example: \"" + sample_list_name + "\" " << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[1/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "= Here's the list editor. (Note that if you first prompt to the list will be empty)" << endl;
    cout << endl;
    cout << " << Exit List Editor (Press 8)" << "\n Rename list name (Press 7) " << "\t | New list (Press 6)" << "\t | Print View (Press 5) |" << endl;
    cout << "------------------------ List Editor ----------------------" << endl;
    print_out_type(sample_list_name, sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, currency_sign1, precision_val);
    cout << endl;
    cout << "There are choices provided: " << endl;
    cout << "1: Create new element" << "\n2: Edit specific element" << "\n3: Delete specific element" << "\n4: Delete all elements" << endl;
    cout << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[2/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");


    cout << "= To create a new element (Press 1)" << endl << endl;
    cout << " > First you choose what value type you want." << endl;
    cout << " > Then write the name of the element and its price: " << endl << endl;
    sample_type_element[5] = conditions[0];
    sample_name_element[5] = "Car repair";
    sample_value_element[5] = 259.99;
    sample_occupied_subscript++;
    cout << "Example:   " << sample_type_element[5] << "\t\t| " << sample_name_element[5] << ": " + currency_sign1 << sample_value_element[5] << endl;
    cout << endl << "After adding an element: " << endl;
    print_out_type(sample_list_name, sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, currency_sign1, precision_val);
    cout << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[3/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "= To edit a specific element (Press 2)" << endl << endl;
    cout << "  > First you choose what element number you want to edit." << endl;
    cout << "  > In this case: 2" << endl;
    cout << "  > Then write the value type, name of the element and its price: " << endl << endl;
    sample_type_element[1] = conditions[0];
    sample_name_element[1] = "Overall Meal";
    sample_value_element[1] = 107.34;
    cout << "Example:   " << sample_type_element[4] << "\t\t| " << sample_name_element[4] << ": " + currency_sign1 << sample_value_element[4] << endl;
    cout << endl << "After editing an element: " << endl;
    print_out_type(sample_list_name, sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, currency_sign1, precision_val);
    cout << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[4/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "= To delete a specific element (Press 3)" << endl << endl;
    cout << "  >  First you choose what element number you want to delete." << endl;
    cout << "  >  In this case: 3" << endl;
    delete_one_element(sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, 3);
    sample_occupied_subscript--;
    cout << endl << "After deleting a specific element: " << endl;
    print_out_type(sample_list_name, sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, currency_sign1, precision_val);
    cout << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[5/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "= To delete all elements (Press 4)" << endl << endl;
    cout << "  > The program will delete all elements automatically" << endl;
    clear_list(sample_type_element, sample_name_element, sample_value_element, sample_size);
    sample_occupied_subscript = 0;
    cout << endl << "After deleting all elements: " << endl;
    print_out_type(sample_list_name, sample_type_element, sample_name_element, sample_value_element, sample_occupied_subscript, currency_sign1, precision_val);
    cout << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "[6/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "= To change the view of elements (Press 5)" << endl;
    cout << "  > This part show you the viewer mode of the list without any choices." << endl;
    cout << endl;
    cout << "= To create new set elements (Press 6)" << endl;
    cout << "  > This part let you create new element, and a new list name" << endl;
    cout << "  > Take note that once created, the data of previous elements are deleted" << endl;
    cout << endl;
    cout << "= To rename a list (Press 7)" << endl;
    cout << "  > This part let you rename the list name, without deleting the data in the elements" << endl;
    cout << endl;
    cout << "= To exit a list editor (Press 8)" << endl;
    cout << "  > This part let you exit the list editor " << endl;
    cout << "  > Take note that once exited, the data of previous elements are deleted" << endl;
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << "[7/8]  Enter to proceed to next page" << endl;
    cin.ignore();
    system("cls");

    cout << "To change currency signs and precision point values, go to Settings" << endl;
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "Thank you for reading and hope for the best!" << endl;
    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "[8/8]  Enter to exit" << endl;
}

// function to display credits
void credits_tab(){
    cout << "-------------------------------------------" << endl;
    cout << "Personal Finance Monitoring Program" << endl;
    cout << "Version: 1.0" << endl;
    cout << endl;
    cout << "Project created by: Matthew Gonzales" << endl;
    cout << "For subject Computer Programming 1" << endl << endl;

    cout << "Project Proposal: " << endl;
    cout << "https://docs.google.com/document/d/1MJc78-F3eDQR1sJcAQWmvoh1V2M9rrRn/edit?usp=sharing&ouid=103368984060361228294&rtpof=true&sd=true" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "\n\n";
    cout << "[Enter to exit]" << endl;

}

void menu_tab(){
    cout << "Personal Finance Monitoring Program" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "----- Main Menu -----" << endl;
    cout << ": StartList" << "\n: Settings" << "\n: Credits" << "\n: Help" << "\n: Exit" << endl;
    cout << "---------------------" << endl;
}





int main(){ // ------------------------- main function -------------------

    int expense_size = 20; // elements size of list

    // lists of elements to list
    string type_element[expense_size];
    string name_element[expense_size];
    double value_element[expense_size];



    // settings vaiables
    int precision_point = 2;
    string currency_sign = "$ ";

    cout << fixed << setprecision(precision_point);

    // code operations starts here
    string menu_tabs;
    while(menu_tabs != "Exit"){

        // menu loop to display and executes tabs
        while(menu_tabs != "StartList" && menu_tabs != "Exit"){

            menu_tab();

            cout << "Type the choices from above " << endl;
            cout << "> "; cin >> menu_tabs;

            // initiates settings tab
            int settings_choices = 0;
            while(settings_choices != 3 && menu_tabs == "Settings"){
                string input_settings;
                system("cls");
                cout << "----- Settings -----" << endl;
                cout << "1 > Precision Editor" << "\n2 > Currency Editor" << "\n3 > Exit" << endl;
                cout << "--------------------" << endl;
                cout << "Enter the choices above (Number only): "; cin >> input_settings;
                if (digit_detection(input_settings) == false){
                    system("cls");
                    cout << "Error: " + error_message(2);
                    continue;
                } settings_choices = integer_conversion(input_settings);

                switch(settings_choices){
                    case 1: { // initiates precision editor
                        string response_point;
                        system("cls");

                        do{
                            response_point = precision_editor(precision_point, currency_sign);
                            if (response_point == "Increase") {system("cls");
                                if (precision_point < 4) precision_point++;
                                else cout << "Error: Precision Point Number is within limits." << endl;
                            } else if (response_point == "Decrease") {system("cls");
                                if (precision_point > 0) precision_point--;
                                else cout << "Error: Precision Point Number is within limits." << endl;
                            }
                        } while(response_point != "Cancel");

                        break;
                    } case 2: { // initiates currency editor
                        string response_cs;
                        system("cls");
                        do{
                            response_cs = currency_editor(currency_sign);
                            if (response_cs != "Cancel") {system("cls"); currency_sign = response_cs;}
                        } while(response_cs != "Cancel");
                        break;
                    } default: cout << "Error: " + error_message(2);

                } system("cls");
            }
            // initiates settings tab
            if (menu_tabs == "Help"){
                system("cls");
                help_tab(precision_point, currency_sign);
                cin.ignore();
                system("cls");

            // initiates settings tab
            } else if (menu_tabs == "Credits"){
                system("cls");
                credits_tab();
                cin.ignore();
                cin.ignore();
            // error checker
            } else if (menu_tabs != "StartList" && menu_tabs != "Settings" && menu_tabs != "Help" && menu_tabs != "Credits" && menu_tabs != "Exit"){
                system("cls");
                cout << "Error: " + error_message(2);
            } else if (menu_tabs.length() == 0) {
                system("cls");
                cout << "Error: " + error_message(1);
            }
        }

        int input_num = 0;
        // while loop to initiate list editor
        while (input_num != 8 && menu_tabs == "StartList"){

            // part where you create a list
            string list_name;
            int subscipt_occupied = 0;

            cin.ignore();
            system("cls");
            cout << "Generate new list......." << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Enter your list name: "; getline(cin, list_name);
            clear_list(type_element, name_element, value_element, expense_size); // function to clear list
            system("cls");

            input_num = 0;

            // list loop part to edit list editor
            while(input_num != 6 && input_num != 8){


                // function for player choice in list editor
                input_num = list_editor(list_name, type_element, name_element, value_element, subscipt_occupied, currency_sign, precision_point);

                switch (input_num){
                    case 1: { // case statement to initiate create element
                        system("cls");

                        if (subscipt_occupied < expense_size){ // if the elements is below maximum element size
                            create_element(type_element, name_element, value_element, subscipt_occupied, false, currency_sign, precision_point); // function to create elements to lists
                            subscipt_occupied++;
                            system("cls");

                        } else { // if the elements reached to maximum element size
                            system("cls");
                            cout << "Error: Saved elements within limits (Limit is " << expense_size << ") " << endl;
                            continue;
                        } break;

                    } case 2: { // case statement to initiate edit element
                        int sub_edit = -1; string input_num;

                        system("cls");
                        do{ print_out_type(list_name, type_element, name_element, value_element, subscipt_occupied, currency_sign, precision_point); // reused function to view elements to edit

                            cout << "(Type \"Cancel\" to cancel deletion)" << endl;
                            cout << "Which element do you want to edit?: "; cin >> input_num;

                            if(input_num == "Cancel") break;

                            if(digit_detection(input_num) == false) {
                                system("cls");
                                cout << "Error: " + error_message(2);
                                continue;
                            } sub_edit = integer_conversion(input_num) - 1;

                            if (sub_edit < 0 || sub_edit > subscipt_occupied-1) { system("cls"); cout << "Error: " + error_message(2);}
                        } while (sub_edit < 0 || sub_edit > subscipt_occupied-1);

                        if(input_num == "Cancel") break;
                        system("cls");
                        create_element(type_element, name_element, value_element, sub_edit, true, currency_sign, precision_point); // reused function to edit elements to lists
                        system("cls");

                        break;
                    } case 3: { // case statement to initiate delete specified element
                        int sub_delete = -1; string input_deletion;
                        system("cls");

                        do{ print_out_type(list_name, type_element, name_element, value_element, subscipt_occupied, currency_sign, precision_point); // reused function to view elements from deletion
                            cout << "(Type \"Cancel\" to cancel deletion)" << endl;
                            cout << "Which element do you want to delete?: "; cin >> input_deletion;

                            if(input_deletion == "Cancel") break;
                            if(digit_detection(input_deletion) == false) {
                                system("cls");
                                cout << "Error: " + error_message(2);
                                continue;
                            } sub_delete = integer_conversion(input_deletion) - 1;

                            if (sub_delete < 0 || sub_delete > subscipt_occupied-1) { system("cls"); cout << "Error: " + error_message(2);}
                        } while (sub_delete < 0 || sub_delete > subscipt_occupied-1);

                        if(input_deletion == "Cancel") break;

                        delete_one_element(type_element, name_element, value_element, subscipt_occupied, sub_delete); // function to delete specific element
                        subscipt_occupied--;
                        system("cls");
                        break;

                    } case 4: { // case statement to initiate deletion of all elements
                        clear_list(type_element, name_element, value_element, expense_size);
                        subscipt_occupied = 0;
                        system("cls");
                        break;

                    } case 5: { // case statement to initiates print out mode

                        system("cls");
                        print_out_type(list_name, type_element, name_element, value_element, subscipt_occupied, currency_sign, precision_point);
                        cout << "You can copy the text printed above. [ENTER WHEN DONE]" << endl;
                        cin.ignore();
                        cin.ignore();
                        system("cls");
                        break;

                    } case 6: { // case statement to create a new list

                        string words_aftermath1;

                        cout << "-------------------------------------------------------" << endl;
                        cout << "Are you sure you want to create new list? Data is deleted upon creating." << endl;
                        do{ cout << "[Yes/No]: "; cin >> words_aftermath1;
                            if (words_aftermath1 != "Yes" && words_aftermath1 != "No") cout << "Error: " + error_message(2);
                        } while(words_aftermath1 != "Yes" && words_aftermath1 != "No");

                        if (words_aftermath1 == "No") input_num = 0;

                        break;
                    } case 7: {

                        cout << "-------------------------------------------------------" << endl;
                        cin.ignore();
                        cout << "Enter your list name: "; getline(cin, list_name);

                        break;
                    } case 8:{ // case statement to initiate exit list
                        string words_aftermath;

                        cout << "-------------------------------------------------------" << endl;
                        cout << "Are you sure you want to exit? Data is deleted upon exiting." << endl;
                        do{ cout << "[Yes/No]: "; cin >> words_aftermath;
                            if (words_aftermath != "Yes" && words_aftermath != "No") cout << "Error: " + error_message(2);
                        } while(words_aftermath != "Yes" && words_aftermath != "No");

                        if (words_aftermath == "No") input_num = 0;
                        else if (words_aftermath == "Yes") menu_tabs = " ";

                        break;
                    }

                }
                system("cls");
            }
        }
        system("cls");
        cin.ignore();
    }

    cout << "Thank you and have a nice day!" << endl;
    return 0;
}

// function to convert string to double variable
double double_conversion(string isstr){
    stringstream string;
    string << isstr;
    double isdbl;
    string >> isdbl;
    return isdbl;
}
// function to convert string to integer variable
int integer_conversion(string isstr){
    stringstream string;
    string << isstr;
    int isint;
    string >> isint;
    return isint;
}

// function to display error messages
string error_message(int errornumber){
    string display_error;

    switch(errornumber){
        case 1: display_error = "Input should not be empty.\n"; break;
        case 2: display_error = "Input not in the choices\n"; break;
        case 3: display_error = "Withdrawal exceeds savings deposit value. The expense should be below the deposit value.\n"; break;
        case 4: display_error = "Expenses exceeds allowance. Please check the values properly.\n"; break;
        case 5: display_error = "Input is invalid. Write numerical values properly.\n"; break;
    } return display_error;
}

// function to identify if the string is all digits
bool digit_detection(string isstr){
    for (int a = 0; a < isstr.length(); a++){
        if (!isdigit(isstr[a])) return false;
    } return true;
}

// function to identify if the string is all digits (2)
// but for floating values
bool float_value_detection(string isstr){
    for (int a = 0; a < isstr.length(); a++){
        if (isstr[a] == '.') {
            continue;
        }
        if (!isdigit(isstr[a])) {
            return false;
        }
    } return true;
}
