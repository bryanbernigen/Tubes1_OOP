#include <fstream>
#ifndef _EXEC_HPP__
#define _EXEC_HPP__
using namespace std;

class InvalidCommand : public exception
{
public:
    const char* what() const throw()
    {
        return "We dont know what are you saying?! Please try it again.\n";
    }
};

class InvalidSlotAmount : public exception
{
public:
    const char *what() const throw()
    {
        return "You input an invalid slot amount! Please try it again.\n";
    }
};

class QuantityNotMetException : public exception
{
public:
    const char *what() const throw()
    {
        return "Quantity Not Met\n";
    }
};

class SlotEmptyException : public exception
{
public:
    const char *what() const throw()
    {
        return "Slot is Empty\n";
    }
};

class SlotFilledException : public exception
{
public:
    const char *what() const throw()
    {
        return "Slot is Filled with other item\n";
    }
};

class SlotFullException : public exception 
{
public:
    const char* what() const throw(){
        return "Inventory is Full!\n";
    }
};

class SlotStorageInsufficient : public exception 
{
public:
    const char* what() const throw(){
        return "Storage of inventory with slot ID specified is insufficient!\n";
    }
};

class ItemNotMatch : public exception 
{
public:
    const char* what() const throw(){
        return "Item not match!\n";
    }
};

class SlotInitiallyNotEmpty : public exception 
{
public:
    const char* what() const throw(){
        return "Slot is initially not empty!\n";
    }
};

class ItemNotFound : public exception 
{
public:
    const char* what() const throw(){
        return "There's no such item with respective quantity in inventory!\n";
    }
};

class ItemQtInsufficient : public exception
{
public:
    const char* what() const throw(){
        return "Quantity of available items in inventory is insufficient!";
    }
};

class ItemNotExist : public exception
{
public:
    const char* what() const throw(){
        return "Item Not Exists!\n";
    }
};

class ToolNotMatchExc : public exception
{
public:
    const char *what() const throw()
    {
        return "Tool doesn't match!.\n";
    }
};


class InvalidUseCommand: public exception
{
    protected:
    /** Error message.
     */
    string msg_;
    public:
        /* Constructor (C strings).
        *  @param message C-style string error message.
        *                 The string contents are copied upon construction.
        *                 Hence, responsibility for deleting the char* lies
        *                 with the caller. 
        */
        explicit InvalidUseCommand() : msg_("Cannot use command USE, check item type first !!!\n") {;}

        virtual const char* what() const noexcept 
        {
            return msg_.c_str();
        }
};

#endif