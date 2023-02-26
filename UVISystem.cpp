#include <iostream>
#include <iomanip> 
#include <string>
#include <fstream>
#include <sstream> // std::stringstream
#include <ctime> 

using namespace std;

int allstaffid = 1;
int main();
void  salespersonmainmenu();
void  managermainmenu();
string pubrole;

struct Vehicle
{
    int vehicleID;
    string title;
    double price;
    int reg_date;
    int mileage;
    string fuel_type;
    string transmission;
    double engine_size;
    int doors;
    string colour;
    string body_type;
    string url;
    string sale_date;
    string reserved;

    Vehicle* prev;
    Vehicle* next;

} *head, * tail, * current, * newNode;

struct staff
{
    int staffID;
    string name;
    string role;
    string password;
    staff* prev;
    staff* next;
}*staffhead, * stafftail, * staffcurrent, * staffnewNode;

struct Client
{
    int client_ID;
    string client_name;
    string client_bd;
    string client_pnum;
    Client* prev;
    Client* next;
}*clienthead, * clienttail, * clientcurrent, * clientnewNode;

struct Invoice
{
    int invoiceID;
    int carID;
    int clientID;
    string title;
    string invoiceDate;
    int salePrice;
    int  Discount;
    string clientname;
    Invoice* prev;
    Invoice* next;

}*invoicehead, * invoicetail, * invoicecurrent, * invoicenewNode;

Invoice* CreateNewInvoice(int invoiceid, int carid, int clientid, string title, string invoicedate, int saleprice, int discount, string clientname)
{
    Invoice* newnode = new Invoice;
    newnode->invoiceID = invoiceid;
    newnode->carID = carid;
    newnode->clientID = clientid;
    newnode->title = title;
    newnode->invoiceDate = invoicedate;
    newnode->salePrice = saleprice;
    newnode->Discount = discount;
    newnode->clientname = clientname;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

Vehicle* CreateNewNnode(int vehicleID, string title, double price, int reg_date, int mileage,
    string fuel_type, string transmission, double engine_size, int doors, string colour,
    string body_type, string url, string sale_date, string reserved) //create a newnode - use for any insert
{
    Vehicle* newnode = new Vehicle;
    newnode->vehicleID = vehicleID;
    newnode->title = title;
    newnode->price = price;
    newnode->reg_date = reg_date;
    newnode->mileage = mileage;
    newnode->fuel_type = fuel_type;
    newnode->transmission = transmission;
    newnode->engine_size = engine_size;
    newnode->doors = doors;
    newnode->colour = colour;
    newnode->body_type = body_type;
    newnode->url = url;
    newnode->sale_date = sale_date;
    newnode->reserved = reserved;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

Client* CreateNewClient(int client_ID, string client_name, string client_bd, string client_pnum) //create a newnode - use for any insert
{
    Client* newnode = new Client;
    newnode->client_ID = client_ID;
    newnode->client_name = client_name;
    newnode->client_bd = client_bd;
    newnode->client_pnum = client_pnum;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

staff* CreateNewStaff(int staffID, string name, string role, string password) //create a newnode - use for any insert
{
    staff* newnode = new staff;
    newnode->staffID = staffID;
    newnode->name = name;
    newnode->role = role;
    newnode->password = password;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

void insertIntotheendoflist(Vehicle* newnode) //from O(N) reduce become O(1)
{
    if (head == NULL)
    {
        head = tail = newnode;
    }
    else
    {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    }
}

void insertIntotheendoflistStaff(staff* newnode) //from O(N) reduce become O(1)
{
    if (staffhead == NULL)
    {
        staffhead = stafftail = newnode;
    }
    else
    {
        stafftail->next = newnode;
        newnode->prev = stafftail;
        stafftail = newnode;
    }
}

void insertIntotheendoflistInvoice(Invoice* newnode) //from O(N) reduce become O(1)
{
    if (invoicehead == NULL)
    {
        invoicehead = invoicetail = newnode;
    }
    else
    {
        invoicetail->next = newnode;
        newnode->prev = invoicetail;
        invoicetail = newnode;
    }
}

void clearList() {               //clear for car 
    while (head != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
}

void clearList2() {            // clear for invoice

    Invoice* invoice = invoicehead;

    while (invoicehead != nullptr) {
        invoice = invoicehead;
        invoicehead = invoicehead->next;
        delete invoice;
    }
    invoicetail = nullptr;
}


void clearList3() {               //clear for client

    Client* client = clienthead;
    while (clienthead != nullptr) {
        client = clienthead;
        clienthead = clienthead->next;
        delete client;
    }
    clienttail = nullptr;
}

int changedate(string date) {
    // Input date string
    string dateStr = date;

    // Parse the day, month, and year values from the date string
    int count = 1;
    int day, month, year;
    string monthStr;
    stringstream ss(dateStr);
    ss >> day >> monthStr >> year;

    count = count + 1;

    // Convert the month string to an integer value
    if (monthStr == "Jan") {
        month = 1;
    }
    else if (monthStr == "Feb") {
        month = 2;
    }
    else if (monthStr == "Mar") {
        month = 3;
    }
    else if (monthStr == "Apr") {
        month = 4;
    }
    else if (monthStr == "May") {
        month = 5;
    }
    else if (monthStr == "Jun") {
        month = 6;
    }
    else if (monthStr == "Jul") {
        month = 7;
    }
    else if (monthStr == "Aug") {
        month = 8;
    }
    else if (monthStr == "Sep") {
        month = 9;
    }
    else if (monthStr == "Oct") {
        month = 10;
    }
    else if (monthStr == "Nov") {
        month = 11;
    }
    else if (monthStr == "Dec") {
        month = 12;
    }
    else {
        cerr << "Error: invalid month string" << endl;
        cout << count << "flag" << endl;
    }

    // Construct an integer value from the day, month, and year values
    int dateInt = year * 10000 + month * 100 + day;

    return dateInt;
}

void insertSortedBySaleDate(Vehicle* newnode)
{
    Vehicle* current = head;
    Vehicle* prev = NULL;

    while (current != NULL && changedate(current->sale_date) > changedate(newnode->sale_date))
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        head = newnode;
    }
    else
    {
        prev->next = newnode;
    }

    newnode->prev = prev;
    newnode->next = current;

    if (current == NULL)
    {
        tail = newnode;
    }
    else
    {
        current->prev = newnode;
    }
}

void readCSVandInsert2(string filename)
{
    string vehicleID, title, price, reg_date, mileage, fuel_type, transmission, engine_size, doors, colour, body_type, url, sale_date, reserved;
    int intdoors;
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    getline(infile, line); // skip the header line

    while (infile.good())
    {

        getline(infile, vehicleID, ',');
        if (vehicleID == "")
        {
            break;
        }
        getline(infile, title, ',');
        getline(infile, price, ',');
        getline(infile, reg_date, ',');
        getline(infile, mileage, ',');
        getline(infile, fuel_type, ',');
        getline(infile, transmission, ',');
        getline(infile, engine_size, ',');
        getline(infile, doors, ',');
        getline(infile, colour, ',');
        getline(infile, body_type, ',');
        getline(infile, url, ',');
        getline(infile, sale_date, ',');
        getline(infile, reserved);

        try {
            intdoors = stoi(doors);
        }
        catch (const std::invalid_argument& e) {
            intdoors = 0;
        }
        
        Vehicle* newnode = CreateNewNnode(stoi(vehicleID), title, stod(price), stoi(reg_date), stoi(mileage), fuel_type, transmission, stod(engine_size), intdoors, colour, body_type, url, sale_date, reserved);

        insertSortedBySaleDate(newnode);
    }
    infile.close();
}

void searchcarbyfilter(double maxPrice, string transmission) {
    int count = 0; // to count the number of cars that meet the filter
    current = head;
    while (current != NULL) {
        if (current->price <= maxPrice && current->transmission == transmission) {
            cout << "\t\t**** Vehicle ID: " << current->vehicleID << " **********************************************************************" <<  endl;
            cout << "\t\t     Title: " << current->title << endl;
            cout << "\t\t     Price: " << current->price << endl;
            cout << "\t\t     Registration Date: " << current->reg_date << endl;
            cout << "\t\t     Mileage: " << current->mileage << endl;
            cout << "\t\t     Fuel Type: " << current->fuel_type << endl;
            cout << "\t\t     Transmission: " << current->transmission << endl;
            cout << "\t\t     Engine Size: " << current->engine_size << endl;
            cout << "\t\t     Doors: " << current->doors << endl;
            cout << "\t\t     Colour: " << current->colour << endl;
            cout << "\t\t     Body Type: " << current->body_type << endl;
            cout << "\t\t     URL: " << current->url << endl;
            cout << "\t\t     Sale Date: " << current->sale_date << endl;
            cout << "\t\t     Reserved: " << current->reserved << endl;
            cout << "\t\t********************************************************************************************" << current->reserved << endl;
            cout << endl;
            count++;
        }
        current = current->next;
    }
    if (count == 0) {
        cout << "No vehicles meet the filter criteria." << endl;
    }
}

void searchvehicleMenu() {
    clearList();
    readCSVandInsert2("carlist.csv");
    double maxPrice;
    string transmission;
    string choice;
    cout << "\t\t	    | What Range of Price do you want to search? : ";
    cin >> maxPrice;
    cout << "\t\t	    | What Transmission you want? " << endl;
    cout << "\t\t	    | 1. Manual                   " << endl;
    cout << "\t\t	    | 2. Semi Auto                " << endl;
    cout << "\t\t	    | 3. Auto                     " << endl;
    cout << "\t\t	    | Enter Your Choice: ";

    cin >> choice;
    cout << endl;
    if (choice == "1") {
        transmission = "Manual";
    }
    else if (choice == "2") {
        transmission = "Semi-Automatic";
    }
    else if (choice == "3") {
        transmission = "Automatic";
    }
    else {
        cout << "Invalid Input" << endl;
    }

    searchcarbyfilter(maxPrice, transmission);
}


Invoice* divide(Invoice* invoicehead, Invoice* invoicetail) {
    int pivot = stoi(invoicetail->invoiceDate);
    Invoice* index = invoicehead;
    cout << invoicehead;
    for (Invoice* i = invoicehead; i != invoicetail; i = i->next) {
        if (stoi(i->invoiceDate) < pivot) {
            int temp = stoi(i->invoiceDate);
            i->invoiceDate = index->invoiceDate;
            index->invoiceDate = to_string(temp);
            index = index->next;
        }
    }
    string temp2 = invoicetail->invoiceDate;
    invoicetail->invoiceDate = index->invoiceDate;
    index->invoiceDate = temp2;
    return index;
}

Invoice* lastNode(Invoice* root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void swap(double* a, double* b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

void swap(string* a, string* b)
{
    string t = *a;
    *a = *b;
    *b = t;
}


Invoice* partition(Invoice* l, Invoice* h)
{
    // set pivot as h element
    string pivot = h->invoiceDate;

    // similar to i = l-1 for array implementation
    Invoice* i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Invoice* j = l; j != h; j = j->next)
    {
        if (j->invoiceDate <= pivot)
        {
            // Similar to i++ for array
            i = (i == NULL) ? l : i->next;
            //i and j
            swap(&(i->invoiceID), &(j->invoiceID));
            swap(&(i->carID), &(j->carID));
            swap(&(i->clientID), &(j->clientID));
            swap(&(i->title), &(j->title));
            swap(&(i->invoiceDate), &(j->invoiceDate));
            swap(&(i->salePrice), &(j->salePrice));
            swap(&(i->Discount), &(j->Discount));
            swap(&(i->clientname), &(j->clientname));
        }
    }
    i = (i == NULL) ? l : i->next; // Similar to i++
    //i and h
    swap(&(i->invoiceID), &(h->invoiceID));
    swap(&(i->carID), &(h->carID));
    swap(&(i->clientID), &(h->clientID));
    swap(&(i->title), &(h->title));
    swap(&(i->invoiceDate), &(h->invoiceDate));
    swap(&(i->salePrice), &(h->salePrice));
    swap(&(i->Discount), &(h->Discount));
    swap(&(i->clientname), &(h->clientname));
    return i;
}

void _quickSort(Invoice* l, Invoice* h)
{
    if (h != NULL && l != h && l != h->next)
    {
        Invoice* p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

void quickSort(Invoice* head)
{
    // Find last node
    Invoice* h = lastNode(head);

    // Call the recursive QuickSort
    _quickSort(head, h);
}

//Delete after implementation is done! 
void printList(Invoice* head)
{
    while (head)
    {
        cout << head->invoiceDate << " ";
        head = head->next;
    }
    cout << endl;
}

void Quick(Invoice* invoicehead, Invoice* invoicetail) {
    if (invoicehead != nullptr && invoicetail != nullptr && invoicehead != invoicetail) {
        Invoice* d = divide(invoicehead, invoicetail);
        Quick(invoicehead, d->prev);
        Quick(d->next, invoicetail);
    }
}

void readCSVandInsert(string filename)
{
    string vehicleID, title, price, reg_date, mileage, fuel_type, transmission, engine_size, doors, colour, body_type, url, sale_date, reserved;
    int intdoors;
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    getline(infile, line); // skip the header line

    while (infile.good())
    {

        getline(infile, vehicleID, ',');
        if (vehicleID == "")
        {
            break;
        }
        getline(infile, title, ',');
        getline(infile, price, ',');
        getline(infile, reg_date, ',');
        getline(infile, mileage, ',');
        getline(infile, fuel_type, ',');
        getline(infile, transmission, ',');
        getline(infile, engine_size, ',');
        getline(infile, doors, ',');
        getline(infile, colour, ',');
        getline(infile, body_type, ',');
        getline(infile, url, ',');
        getline(infile, sale_date, ',');
        getline(infile, reserved);

        try {
            intdoors = stoi(doors);
        }
        catch (const std::invalid_argument& e) {
            intdoors = 0;
        }
        Vehicle* newnode = CreateNewNnode(stoi(vehicleID), title, stod(price), stoi(reg_date), stoi(mileage), fuel_type, transmission, stod(engine_size), intdoors, colour, body_type, url, sale_date, reserved);

        insertIntotheendoflist(newnode);
    }
    infile.close();
}

void readCSVandInsertInvoice(string filename)
{
    string invoiceID, carID, clientID, title, invoicedate, saleprice, discount, clientname;
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    getline(infile, line); // skip the header line

    while (infile.good())
    {

        getline(infile, invoiceID, ',');
        if (invoiceID == "") {
            break;
        }
        getline(infile, carID, ',');
        getline(infile, clientID, ',');
        getline(infile, title, ',');
        getline(infile, invoicedate, ',');
        getline(infile, saleprice, ',');
        getline(infile, discount, ',');
        getline(infile, clientname);

        Invoice* newnode = CreateNewInvoice(stoi(invoiceID), stoi(carID), stoi(clientID), title, invoicedate, stoi(saleprice), stoi(discount), clientname);

        insertIntotheendoflistInvoice(newnode);
    }
    infile.close();
}

void readCSVandInsertStaff(string filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    getline(infile, line); // skip the header line

    while (getline(infile, line))
    {
        stringstream ss(line);
        string staffID, name, role, password;
        getline(ss, staffID, ',');
        getline(ss, name, ',');
        getline(ss, role, ',');
        getline(ss, password);

        staff* newnode = CreateNewStaff(stoi(staffID), name, role, password);
        insertIntotheendoflistStaff(newnode);
    }

    infile.close();
}

void insertIntoEndClient(Client* newnode) //from O(N) reduce become O(1)
{
    if (clienthead == NULL)
    {
        clienthead = clienttail = newnode;
    }
    else
    {
        clienttail->next = newnode;
        newnode->prev = clienttail;
        clienttail = newnode;
    }
}

void insertIntoEndInvoice(Invoice* newnode) //from O(N) reduce become O(1)
{
    if (invoicehead == NULL)
    {
        invoicehead = invoicetail = newnode;
    }
    else
    {
        invoicetail->next = newnode;
        newnode->prev = invoicetail;
        invoicetail = newnode;
    }
}

void readCSVandInsertClient(string filename)
{
    string client_ID, client_name, client_bd, client_pnum;

    ifstream clientfile(filename);
    if (!clientfile.is_open())
    {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    getline(clientfile, line); // skip the header line

    while (clientfile.good())
    {

        getline(clientfile, client_ID, ',');
        if (client_ID == "") {
            break;
        }

        getline(clientfile, client_name, ',');
        getline(clientfile, client_bd, ',');
        getline(clientfile, client_pnum);

        Client* newnode = CreateNewClient(stoi(client_ID), client_name, client_bd, client_pnum);
        insertIntoEndClient(newnode);
    }
    clientfile.close();
}


Client* binarySearchClient(Client* head, int id) {
    Client* left = head;
    Client* right = nullptr;
    while (left != right) {
        Client* mid = left;
        int count = 0;
        while (mid->next != right && count < (right - left + 1) / 2) {
            mid = mid->next;
            count++;
        }
        if (mid->client_ID < id) {
            left = mid->next;
        }
        else {
            right = mid;
        }
    }
    if (right != nullptr && right->client_ID == id) {
        return right;
    }
    else {
        return nullptr;
    }
}

Client* binarySearchClient2(Client* head, int id) {
    Client* current = head;
    while (current != nullptr) {
        if (current->client_ID == id) {
            return current;
        }
        else if (current->client_ID < id) {
            current = current->next;
        }
        else {
            return nullptr;
        }
    }
    return nullptr;
}


void WriteIntoClient()
{
    ofstream file("Client.csv");

    file << "ClientID,Name,Birthday,PhoneNumber" << endl;
    int countID = 0;
    Client* current = clienthead;
    while (current != NULL)
    {
        countID = (countID + 1);
        file << countID << ",";
        file << current->client_name << ",";
        file << current->client_bd << ",";
        file << current->client_pnum << "\n";

        current = current->next;
    }
    file.close();
}

void WriteIntoInvoice()
{
    ofstream file("Invoice.csv");

    file << "invoiceID,CarID,ClientID,title,InvoiceDate,salePrice,discount,clientName" << endl;
    int countID = 0;
    Invoice* current = invoicehead;
    while (current != NULL)
    {
        countID = (countID + 1);
        file << countID << ",";
        file << current->carID << ",";
        file << current->clientID << ",";
        file << current->title << ",";
        file << current->invoiceDate << ",";
        file << current->salePrice << ",";
        file << current->Discount << ",";
        file << current->clientname << "\n";

        current = current->next;
    }
    file.close();
}


void AddClient()
{
    string client_name, client_bd, client_pnum;
    cout << "\n\t\t           Adding Client..." << endl << endl;
    cout << "\t\t        | Enter a Client Name: ";
    cin >> client_name;
    cout << "\n\t\t        | Enter a Client Birthday: " ;
    cin >> client_bd;
    cout << "\n\t\t        | Enter a Client Client PhoneNumber: " ;
    cin >> client_pnum;

    clearList3();
    readCSVandInsertClient("Client.csv");
    Client* newnode2 = CreateNewClient(1, client_name, client_bd, client_pnum);
    insertIntoEndClient(newnode2);
    WriteIntoClient();

}

void UpdateClient()
{
    string clientname, clientbd, clientphonenumber;
    int clientID;
    cout << "\n\t\t          Updating Client... " << endl << endl;
    cout << "\t\t        | Enter a Client ID: " ;
    cin >> clientID;
    cout << "\n\t\t        | Enter a Client Name: " ;
    cin >> clientname;
    cout << "\n\t\t        | Enter a Client Birthday: ";
    cin >> clientbd;
    cout << "\n\t\t        | Enter a Client Client PhoneNumber: ";
    cin >> clientphonenumber;

    clearList3();
    readCSVandInsertClient("Client.csv");
    Client* client = binarySearchClient(clienthead, clientID);
    client->client_name = clientname;
    client->client_bd = clientbd;
    client->client_pnum = clientphonenumber;
    WriteIntoClient();
}

void manageClient()
{
    string client_name, client_bd, client_pnum;
    int choice;
    cout << "\t\t        | Manage Client Menu" << endl;
    cout << "\t\t        | 1. Add Client" << endl;
    cout << "\t\t        | 2. Edit Client" << endl;
    cout << "\t\t        | Enter Your Choice: ";
    cin >> choice;
    if (choice == 1)
    {
        AddClient();
    }
    else if (choice == 2)
    {
        UpdateClient();
    }
    else
    {
        cout << "\n\t\t\t\t\t\t Invalid Input! Please Try Again!   \n" << endl;
    }

}

void displayList() // delete afther the program is implemented
{
    Vehicle* current = head;

    while (current != NULL)
    {
        cout << current->title << " - " << current->price << " - " << current->reg_date << " - " << current->mileage
            << " - " << current->fuel_type << " - " << current->transmission << endl;
        current = current->next;
    }
    cout << endl << "List is ended here!" << endl << endl;
}

void displayList2() // delete afther the program is implemented
{
    Invoice* invoicecurrent = invoicehead;

    while (invoicecurrent != NULL)
    {
        cout << invoicecurrent->invoiceID << " - " << invoicecurrent-> carID << " - " << invoicecurrent-> clientID << " - " << invoicecurrent->title
            << " - " << invoicecurrent->invoiceDate << " - " << invoicecurrent->salePrice << " - " << invoicecurrent->clientname << endl;
        invoicecurrent = invoicecurrent->next;
    }
    cout << endl << "List is ended here!" << endl << endl;
}


//delete after the implementation of the program is done 
void displayListStaff()
{
    staff* current = staffhead;

    while (current != NULL)
    {
        cout << to_string(current->staffID) << ". " << current->name << " - " << current->role << " - " << current->password << endl;
        current = current->next;
    }
    cout << endl << "List is ended here!" << endl << endl;
}

// irrelavant class ask before delete
string GetStaffRole(int staffID, string password)
{
    staffcurrent = staffhead;

    while (staffcurrent != NULL)
    {
        if (staffcurrent->staffID == staffID)
        {
            if (staffcurrent->password == password)
            {
                return staffcurrent->role;
            }
            else
            {
                return "Invalid password";
            }
        }
        staffcurrent = staffcurrent->next;

    }

    return "Staff member not found";
}

Vehicle* binarySearchVehicle(Vehicle* head, int id) {
    Vehicle* left = head;
    Vehicle* right = head;
    while (right->next != nullptr && right->vehicleID < id) {
        left = right;
        right = right->next;
    }
    if (right->vehicleID == id) {
        return right;
    }
    else {
        return nullptr;
    }
}

Vehicle* binarySearchVehicle2(Vehicle* head, int id) {
    Vehicle* left = head;
    Vehicle* right = nullptr;
    while (left != right) {
        Vehicle* mid = left;
        int count = 0;
        while (mid->next != right && count < (right - left + 1) / 2) {
            mid = mid->next;
            count++;
        }
        if (mid->vehicleID < id) {
            left = mid->next;
        }
        else if (mid->vehicleID > id) {
            right = mid;
        }
        else {
            return mid;
        }
    }
    return nullptr;
}

Invoice* linearSearchInvoice(Invoice* head, int id) {
    Invoice* current = head;
    while (current != nullptr) {
        if (current->invoiceID == id) {
            return current;
        }
        else if (current->invoiceID < id) {
            current = current->next;
        }
        else {
            return nullptr;
        }
    }
    return nullptr;
}

Invoice* linearSearchInvoice2(Invoice* head, int id) {
    Invoice* current = head;
    while (current != nullptr) {
        if (current->carID == id) {
            return current;
        }
        else if (current->carID < id) {
            current = current->next;
        }
        else {
            return nullptr;
        }
    }
    return nullptr;
}

staff* binarySearchStaff(staff* head, int id) {
    staff* left = head;
    staff* right = head;
    while (right->next != nullptr && right->staffID < id) {
        left = right;
        right = right->next;
    }
    if (right->staffID == id) {
        return right;
    }
    else {
        return nullptr;
    }
}

staff* binarySearchStaff2(staff* head, int id) {
    staff* current = head;
    while (current != nullptr) {
        if (current->staffID == id) {
            return current;
        }
        else if (current->staffID < id) {
            current = current->next;
        }
        else {
            return nullptr;
        }
    }
    return nullptr;
}

string findRoleByIdAndPassword(staff* head, int id, string password)
{
    staff* element = binarySearchStaff(head, id);
    if (element != nullptr && element->password == password) {
        return element->role;
    }
    else {
        return "";
    }
}

//Manager 
void WriteintoCSV()
{
    ofstream file;
    file.open("carlist.csv");

    file << "vehicleID,Title,Price,Registration Date,Mileage,Fuel Type,Transmission,Engine Size,Doors,Colour,Body Type,URL,Sale Date,Reserved" << endl;
    Vehicle* current = head;
    while (current != NULL)
    {
        file << current->vehicleID << ",";
        file << current->title << ",";
        file << current->price << ",";
        file << current->reg_date << ",";
        file << current->mileage << ",";
        file << current->fuel_type << ",";
        file << current->transmission << ",";
        file << current->engine_size << ",";
        file << current->doors << ",";
        file << current->colour << ",";
        file << current->body_type << ",";
        file << current->url << ",";
        file << current->sale_date << ",";
        file << current->reserved << endl;

        current = current->next;
    }
    file.close();
}


void bookVehicle()
{
    string clientinfo, vehicleinfo;
    int vehicleID, ClientID;
    cout << "\t\t	| What ClientID you wanted to book? " << endl;
    cout << "\t\t	| Type your ClientID:           ";
    cin >> ClientID;
    cout << "\t\t	| Which vehicleID you wanted to book? " << endl;
    cout << "\t\t	| Type your VehicleID:          ";
    cin >> vehicleID;

    clearList();
    readCSVandInsert("carlist.csv");

    Vehicle* vehicle = binarySearchVehicle2(head, vehicleID);
    vehicle->reserved = to_string(ClientID);
    WriteintoCSV();

}



void push(Vehicle** head_ref, int new_data)
{
    Vehicle* new_node = new Vehicle; /* allocate node */
    new_node->price = new_data;

    /* since we are adding at the
    beginning, prev is always NULL */
    new_node->prev = NULL;

    /* link the old list of the new node */
    new_node->next = (*head_ref);

    /* change prev of head node to new node */
    if ((*head_ref) != NULL) (*head_ref)->prev = new_node;

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}


int getCurrentDateInt() {

    std::time_t now = std::time(nullptr); // Get the current time
    std::tm tm;    // Convert the time to a struct tm using localtime_s
    localtime_s(&tm, &now);
    int year = tm.tm_year + 1900;    // Calculate the date as an integer in the format of YYYYMMDD
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int dateInt = year * 10000 + month * 100 + day;

    return dateInt;
}

void menuselector(string soul)
{
    if (soul == "manager")
    {
        managermainmenu();
    }
    else if (soul == "salesperson")
    {
        salespersonmainmenu();
    }
    else
    {
        main();
    }
}

void createInvoice()
{
    int invoiceID;
    int CarID;
    int ClientID;
    int orginalprice;
    int salePrice;
    int discount;
    cout << "\t\t	|               Enter The CarID to be Invoiced?:  ";
    cin >> CarID;
    cout << "\t\t	| Enter The ClientID to be attached to the Car?:  ";
    cin >> ClientID;
    cout << "\t\t	|                   Enter a discount price (RM):  ";
    cin >> discount;

    clearList2();
    readCSVandInsertInvoice("Invoice.csv"); //validation
    Invoice* check;
    check = NULL;
    check = linearSearchInvoice2(invoicehead, CarID);

    if (check != NULL)
    {
        cout << "\t\t	| ********************   Invoice is existed  ************** " << "\n\n\n\n";
        cin.clear();
        cin.ignore(256, '\n');
        createInvoice();
    }

    clearList3();
    readCSVandInsertClient("Client.csv");
    Client* client = binarySearchClient2(clienthead, ClientID);
    if (client == NULL)
    {
        cout << "\t\t        | *************   Client has not existed **************** " << "\n";
        cout << "\t\t	                           Please try Again!                        " << "\n\n";
        cin.clear();
        cin.ignore(256, '\n');
        createInvoice();
    }

    clearList();
    readCSVandInsert("carlist.csv");
    Vehicle* vehicle = binarySearchVehicle2(head, CarID);
    orginalprice = vehicle->price;

    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	                           INVOICE                         " << endl;
    cout << "\t\t	| Original Price:  " << orginalprice << endl;
    salePrice = orginalprice - discount;


    int currentdate = getCurrentDateInt();
    string strdate = to_string(currentdate);


    cout << "\t\t        | ClientName: " << client->client_name << endl <<
        "\t\t	| CarID: " << CarID << endl <<
        "\t\t	| ClientID: " << ClientID << endl <<
        "\t\t        | date: " << strdate << endl <<
        "\t\t	|           " << endl <<
        "\t\t        |    Car Description: " << vehicle->title << endl <<
        "\t\t        |    ****** Total Price: " << salePrice << " ******" << endl <<
        "\t\t	 __________________________________________________________" << "\n" << endl;


    Invoice* invoice = CreateNewInvoice(1, CarID, ClientID, vehicle->title, strdate, salePrice, discount, client->client_name);
    insertIntoEndInvoice(invoice);


    WriteIntoInvoice();
    menuselector(pubrole);

}



void printbill(string invoice, string carid, string staffid, string clientid, string invoicedate, string discount, string total) {
    cout << "\t\t	|----------------------------|" << endl;
    cout << "\t\t	|          RECEIPT" << "           |" << endl;
    cout << "\t\t	|----------------------------|" << endl;
    cout << "\t\t	|   InvoiceID: " << invoice << "             |" << endl;
    cout << "\t\t	|   CarID: " << carid << "                 |" << endl;
    cout << "\t\t	|   StaffID: " << staffid << "               |" << endl;
    cout << "\t\t	|   ClientID: " << invoicedate << "       |" << endl;
    cout << "\t\t	|   Invoice Date" << discount << "           |" << endl;
    cout << "\t\t	|   Discount(RM)" << discount << "           |" << endl;
    cout << "\t\t	|   Subtotal: " << total << "           |" << endl;
    cout << "\t\t	|----------------------------" << "|" << endl;
}

void createbill() {
    int invoiceid;

    cout << "\t\t	| Enter the Invoice ID to be Billed:  ";
    while (!(cin >> invoiceid)) {
        cout << "Invalid input. Please enter a valid invoice ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    clearList();
    readCSVandInsertInvoice("invoice.csv");
    Invoice* invoice = linearSearchInvoice(invoicehead, invoiceid);

    if (invoice == nullptr) {
        cout << "invoiceID Does Not Exist" << endl;
        cin.clear();
        cin.ignore();
        createbill();
    }
    if (invoice->invoiceID == 0) {
        cout << "invoiceID Does Not Exist" << endl;
        cin.clear();
        cin.ignore();
        createbill();
    }
    clearList();
    readCSVandInsert("carlist.csv");
    Vehicle* vehicle = binarySearchVehicle2(head, invoice->carID);

    if (invoice == nullptr) {
        cout << "invoiceID Does Not Exist" << endl;
        cin.clear();
        cin.ignore();
        createbill();
    }
    if (vehicle->vehicleID = NULL) {
        cout << "VehicleID Does Not Exist" << endl;
        cin.clear();
        cin.ignore();
        createbill();
    }
    else if (vehicle->reserved == "Sold") {
        cout << "\t\t	** Vehicles Has Been Sold, Please Create Bill For Another Vehicle! **" << endl;
        cin.clear();
        cin.ignore();
    }
    printbill(to_string(invoiceid), to_string(invoice->carID), to_string(allstaffid), to_string(invoice->clientID), invoice->invoiceDate, to_string(invoice->Discount), to_string(invoice->salePrice));

    vehicle->reserved = "Sold";
    WriteintoCSV();
}

void searchreportbyfilter(double maxPrice, string transmission) {
    int count = 0; // to count the number of cars that meet the filter
    current = head;
    while (current != NULL) {
        if (current->price <= maxPrice && current->transmission == transmission) {
            cout << "Vehicle ID: " << current->vehicleID << endl;
            cout << "Title: " << current->title << endl;
            cout << "Price: " << current->price << endl;
            cout << "Registration Date: " << current->reg_date << endl;
            cout << "Mileage: " << current->mileage << endl;
            cout << "Fuel Type: " << current->fuel_type << endl;
            cout << "Transmission: " << current->transmission << endl;
            cout << "Engine Size: " << current->engine_size << endl;
            cout << "Doors: " << current->doors << endl;
            cout << "Colour: " << current->colour << endl;
            cout << "Body Type: " << current->body_type << endl;
            cout << "URL: " << current->url << endl;
            cout << "Sale Date: " << current->sale_date << endl;
            cout << "Reserved: " << current->reserved << endl;
            cout << endl;
            count++;
        }
        current = current->next;
    }
    if (count == 0) {
        cout << "No vehicles meet the filter criteria." << endl;
    }
}

void salesReport()
{
    cout << "\n\n\n\t\t\t                            Sales Report                       " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	|  Date  | | CarID |  | Client Name | |Client ID| |Invoice ID| |Discount| | Price | " << endl;
    int sum = 0;
    clearList2();
    readCSVandInsertInvoice("Invoice.csv");
    quickSort(invoicehead);

    invoicecurrent = invoicehead;
    while (invoicecurrent != NULL)
    {
        cout << "\t\t         " << invoicecurrent->invoiceDate;
        cout << "      " << invoicecurrent->carID;
        cout << "\t  " << invoicecurrent->clientname;
        cout << "\t\t   " << invoicecurrent->clientID;
        cout << "\t       " << invoicecurrent->invoiceID;
        cout << "\t  " << invoicecurrent->Discount;

        sum = sum + invoicecurrent->salePrice;
        cout << "\t    " << invoicecurrent->salePrice << endl;
        invoicecurrent = invoicecurrent->next;

    }
    cout << "\t\t\t---------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t                                                          TOTAL SALES PRICE: " << sum << endl;
    cout << "\t\t\t---------------------------------------------------------------------------------------" << endl;
}

void billingReport()
{
    int tempid;
    cout << "\n\n\n                                             Billing Report                       " << endl;
    cout << "  ///////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "  |  Date  | | CarID | | ClientID | | Client Name | |              Title                                    |" << endl;
    clearList2();
    readCSVandInsertInvoice("Invoice.csv"); // to find the sold vehicle carID 
    clearList();
    readCSVandInsert("carlist.csv"); //using the cardID to find out so that no need to check one by one until 1500+ lines
    quickSort(invoicehead);
    int sum = 0;

    invoicecurrent = invoicehead;
    while (invoicecurrent != NULL)
    {
        cout << "   " << invoicecurrent->invoiceDate;
        cout << "      " << invoicecurrent->carID;
        cout << "\t  " << invoicecurrent->clientID;
        cout << "\t       " << invoicecurrent->clientname;
        cout << "\t    " << invoicecurrent->title << endl;

        tempid = invoicecurrent->carID;
        Vehicle* car = binarySearchVehicle2(head, tempid);
        if (car->reserved == "Sold") 
        {
            sum = sum + 1;

        }

        invoicecurrent = invoicecurrent->next;

    }
    cout << "  ---------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                                                       TOTAL VEHICLE SOLD: " << sum << endl;
    cout << "  ---------------------------------------------------------------------------------------------------------" << endl;
}

void clientReport()
{
    int tempid;
    cout << "\n\n\n\t\t                         Client Report                       " << endl;
    cout << "\t\t    ///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t    | Client ID | | Client Name | | Birthday | | Phone Number | " << endl;
    clearList3();
    readCSVandInsertClient("Client.csv");
    int sum = 0;

    clientcurrent = clienthead;
    while (clientcurrent != NULL)
    {
        cout << "\t\t       " << clientcurrent->client_ID;
        cout << "\t      " << clientcurrent->client_name;
        cout << "\t     " << clientcurrent->client_bd;
        cout << "\t  " << clientcurrent->client_pnum << endl;


        tempid = clientcurrent->client_ID;
        Client* client = binarySearchClient2(clienthead, tempid);
        if (client->client_ID != NULL)
        {
            sum = sum + 1;
        }

        clientcurrent = clientcurrent->next;

    }
    cout << "\t\t     ------------------------------------------------------------" << endl;
    cout << "\t\t                                     TOTAL CLIENT NUMBERS : " << sum << endl;
    cout << "\t\t     ------------------------------------------------------------" << endl;
}

void generateReport()
{
    string choice;

    cout << "\t\t        | 1. Sales Report" << endl;
    cout << "\t\t        | 2. Billing Report" << endl;
    cout << "\t\t        | 3. Client Report" << endl;
    cout << "\t\t        | Enter your choice: ";
    cin >> choice;

    if (choice == "1")
    {
        salesReport();
    }
    else if (choice == "2")
    {
        billingReport();
    }
    else if (choice == "3")
    {
        clientReport();
    }
    else 
    {
        cout << " Invalid Input! Please Try Again!";
    }
}



void salespersonmainmenu()
{
    string opt;
    cout << "\t\t\t\t\t " << endl;
    cout << "\n\n\n\t\t                   Salesperson - Main Menu Page         " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| 1- search vehicle information " << endl;
    cout << "\t\t	| 2- create sale invoice        " << endl;
    cout << "\t\t	| 3- create bill receipt        " << endl;
    cout << "\t\t	| 4- book the vehicle           " << endl;
    cout << "\t\t	| 5- manage client information  " << endl;
    cout << "\t\t	| 7- log out                    " << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t	| Select your choice:  ";
    cin >> opt;

    if (opt == "1")
    {
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t Search Vehicle Information  \n";
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        searchvehicleMenu();
        salespersonmainmenu();

    }
    else if (opt == "2")
    {
        cout << "\n\n\n\t\t                   Create Sales Invoice         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        createInvoice();
        salespersonmainmenu();
    }
    else if (opt == "3")
    {
        cout << "\n\n\n\t\t                   Create Bill Receipt         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        createbill();
        salespersonmainmenu();
    }
    else if (opt == "4")
    {
        cout << "\n\n\n\t\t                   Booking Vehicle         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        bookVehicle();
        cout << "\n\t\t\t\t\t\t Booking Successfully !   \n";
        salespersonmainmenu();
    }
    else if (opt == "5")
    {
        cout << "\n\n\n\t\t                   Manage Client Information         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        manageClient();
        cout << "\n\t\t\t\t\t\t Update Successfully !   \n";
        salespersonmainmenu();
    }
    else if (opt == "7")
    {
        cout << "\n\t\t\t\t\t\t Log Out Successfully! \n";
        main();
    }
    else
    {
        cout << "Invalid Input, Please try again" << endl;
    }
}

void managermainmenu()
{
    string opt;
    cout << "\t\t\t\t\t " << endl;
    cout << "\n\t\t                         Manager - Main Menu Page                 " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| 1- search vehicle information " << endl;
    cout << "\t\t	| 2- create sale invoice        " << endl;
    cout << "\t\t	| 3- create bill receipt        " << endl;
    cout << "\t\t	| 6- produce report             " << endl;
    cout << "\t\t	| 7- log out                    " << endl;
    cout << "\t\t	 __________________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t	| Select your choice:  ";
    cin >> opt;


    if (opt == "1")
    {
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t         Search Vehicle Information  \n";
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        searchvehicleMenu();
        managermainmenu();

    }
    else if (opt == "2")
    {
        cout << "\n\n\n\t\t                   Create Sales Invoice         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        createInvoice();
        managermainmenu();
    }
    else if (opt == "3")
    {
        cout << "\n\n\n\t\t                   Create Bill Receipt         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        createbill();
        managermainmenu();

    }
    else if (opt == "6")
    {
        cout << "\n\n\n\t\t                                Generate Report         " << endl;
        cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
        generateReport();
        managermainmenu();
    }
    else if (opt == "7")
    {
        cout << "\n\t\t\t\t\t\t Log Out Successfully! \n";
        main();
    }
    else
    {
        cout << "Invalid Input, Please try again" << endl;

    }
}


int main()
{
    clearList();
    readCSVandInsert("carlist.csv");
    int staffID;
    string password, role;
    readCSVandInsertStaff("staff.csv");

    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t     Vehicle Invoicing System \n\n";
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     LOGIN \n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tEnter username: ";
    cin >> staffID;
    allstaffid = staffID;
    cout << "\t\t\t\t\tEnter password: ";
    cin >> password;

    role = findRoleByIdAndPassword(staffhead, staffID, password);
    if (role == "manager")
    {
        pubrole = "manager";
        managermainmenu();
    }
    else if (role == "salesperson")
    {
        pubrole = "salesperson";
        salespersonmainmenu();
    }
    else
    {
        cout << " \n\n\t\t\t\t\t Invalid Input, Program Ended! " << endl; 
    }
}