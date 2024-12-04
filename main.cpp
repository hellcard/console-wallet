#include <iostream>
#include <fstream> // work with files
#include <filesystem> // work with directories
#include <string>

bool is_login(std::string* un, std::string* pw, std::string* cash){ // These arguments are used to write pointers for further work. It doesn't matter what is stored in them.
    std::string username, password, cash_str, usrn, pwd;

    std::cout<<"\tEnter your username: "; std::cin>>username; std::cout<<std::endl;
    std::cout<<"\tEnter your password: "; std::cin>>password; std::cout<<std::endl;

    std::ifstream read("data/data_of_"+username+".txt"); // open file
    std::getline(read, usrn); std::getline(read, pwd); std::getline(read, cash_str); // read file

    if(username == usrn && password == pwd){ // check username & password
        *un=username;
        *pw=password;
        *cash=cash_str;
        return true;
    }
    else{
        return false;
    }
    // the close function is called when leaving the scope ...
}

class User{
    private:
        std::string usr_name, passwd; // username, password
        float user_cash; // cash
    public:
        // init
        User(std::string usrn, std::string pwd, float cash){
            usr_name = usrn; 
            passwd = pwd; 
            user_cash = cash;
        }

        // setters
        void change_passwd(std::string pwd){
            std::string* point = &passwd;
            *point = pwd;
        }
        void add_cash(float add){
            float* point = &user_cash;
            *point += add;
        }
        void sub_cash(float sub){
            float* point = &user_cash;
            *point -= sub;
        }

        // getters

        std::string get_username(){
            return usr_name;
        }

        std::string get_password(){
            return passwd;
        }

        float get_cash(){
            return user_cash;
        }
};
int main(){
    int choice;
    std::string username, password, cash_str;
    float cash = 0.0;
    float amount;

    std::cout<<"\t\t\tConsole-Wallet\n"<<std::endl;

    std::cout<<"\n\t\tMenu:\n\t1. Register new account\n\t2. Log in"<<std::endl;

    std::cout<<"\n\n\tYour choice: "; std::cin>>choice; std::cout<<std::endl; 
    switch(choice){
        case 1:
            {

            std::cout<<"\t\tREGISTER"<<std::endl;

            std::cout<<"\tEnter your username: "; std::cin>>username; std::cout<<std::endl;
            std::cout<<"\tEnter your password: "; std::cin>>password; std::cout<<std::endl;

            std::ofstream file;

            std::error_code e; // error code

            std::filesystem::create_directory("data",e); // create directory 

            file.open("data/data_of_"+username+".txt"); // create file on data/ "data_of_examplename.txt"

            file<<username<<std::endl<<password<<std::endl<<cash; // write data on file "data_of_examplename.txt"

            file.close();
            goto login_page;
            break;
            }
        case 2:
            login_page:

            std::cout<<"\t\tLOG IN"<<std::endl;
            if(!is_login(&username, &password, &cash_str)){
                std::cout<<"\tERROR: such user does not exist"<<std::endl;
                return 1;
            }
            else{
                std::cout<<"You was successfully log in :)"<<std::endl;
            }
            break;
        default:
            std::cout<<"\tERROR: such choice does not exist"<<std::endl;
            return 1;
    }
    cash = stof(cash_str);
    User usr(username,password,cash);

    std::cout<<"\n\t\t\tWelcome, "<<usr.get_username()<<std::endl;
    while(true){
        std::cout<<"\t\tCommands:\n\t 1. Info\n\t 2. Add cash\n\t 3. Substract cash\n\t 4. Change password\n\t 5. Exit"<<std::endl;
        std::cout<<"\n\t\tYour choice: "; std::cin>>choice; std::cout<<std::endl;
        switch(choice){
            case 1:
                {
                std::cout<<"\n\t\t\tInfo about your account:\n\n\tUsername: "<<usr.get_username()<<"\n\tPassword: "<<usr.get_password()<<"\n\tCash: "<<usr.get_cash()<<std::endl<<std::endl;
                break;
                }
            case 2:
                {
                std::cout<<"\t\tEnter amount: "; std::cin>>amount; std::cout<<std::endl;
                usr.add_cash(amount);
                std::ofstream file;
                file.open("data/data_of_"+usr.get_username()+".txt");
                file<<usr.get_username()<<std::endl<<usr.get_password()<<std::endl<<usr.get_cash();
                file.close();
                break;
                }
            case 3:
                {
                std::cout<<"\t\tEnter amount: "; std::cin>>amount; std::cout<<std::endl;
                usr.sub_cash(amount);
                std::ofstream file;
                file.open("data/data_of_"+usr.get_username()+".txt");
                file<<usr.get_username()<<std::endl<<usr.get_password()<<std::endl<<usr.get_cash();
                file.close();
                break;
                }
            case 4:
                {
                std::cout<<"\t\tEnter new password: "; std::cin>>password; std::cout<<std::endl;
                usr.change_passwd(password);
                std::ofstream file;
                file.open("data/data_of_"+usr.get_username()+".txt");
                file<<usr.get_username()<<std::endl<<usr.get_password()<<std::endl<<usr.get_cash();
                break;
                }
            case 5:
                { std::cout<<"log out"<<std::endl; break; }
            default:
                {
                std::cout<<"\tERROR: such choice does not exist"<<std::endl;
                break;
                }
        }
        if(choice == 5){
            break;
        }
    }
    return 0;
}