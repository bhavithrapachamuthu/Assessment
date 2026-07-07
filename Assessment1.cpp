#include<bits/stdc++.h>
using namespace std;
class Employee{
    public:
    int employeeId;
    string empName;
    float salary;
    Employee*left;
    Employee*right;
    Employee(int id,string n,float s){
        employeeId=id;
        empName=n;
        salary=s;
        left=NULL;
        right=NULL;
    }
};
class Customer{
    public:
    int customerId;
    string cusName;
    string address;
    Customer*left;
    Customer*right;
    Customer(int id,string n,string a){
        customerId=id;
        cusName=n;
        address=a;
        left=NULL;
        right=NULL;
    }
};
class Sale{
    public:
    int saleId;
    Employee*employee;
    Customer*customer;
    float amount;
    string date;
    Sale*left;
    Sale*right;
    Sale(int id,Employee*e,Customer*c,float a,string d){
        saleId=id;
        employee=e;
        customer=c;
        amount=a;
        date=d;
        left=NULL;
        right=NULL;
    }
};
//Insert employee into BST using EmpId
Employee*insertEmployee(Employee*root,Employee*newEmployee){
    if(root==NULL){
        return newEmployee;
    }
    if(newEmployee->employeeId < root->employeeId){
        root->left=insertEmployee(root->left,newEmployee);
    }
    else{
        root->right=insertEmployee(root->right,newEmployee);
    }
    return root;
}
//Insert employee into BST using CusId
Customer*insertCustomer(Customer*root,Customer*newcustomer){
    if(root==NULL){
        return newcustomer;
    }
    if(newcustomer->customerId < root->customerId){
        root->left=insertCustomer(root->left,newcustomer);
    }
    else{
        root->right=insertCustomer(root->right,newcustomer);
    }
    return root;
} 
//Insert employee into BST using SaleId 
Sale*insertSale(Sale*root,Sale*newsale){
    if(root==NULL){
        return newsale;
    }
    if(newsale->saleId < root->saleId){
        root->left=insertSale(root->left,newsale);
    }
    else{
        root->right=insertSale(root->right,newsale);
    }
    return root;
}
Employee*searchemployeebyId(Employee*root,int employeeId){
    while(root!=NULL){
        if(employeeId==root->employeeId){
            return root;
        }
        else if(employeeId < root->employeeId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
Customer*searchcustomer(Customer*root,int customerId){
    while(root!=NULL){
        if(customerId==root->customerId){
            return root;
        }
        else if(customerId < root->customerId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
Sale*searchsale(Sale*root,int saleId){
    while(root!=NULL){
        if(saleId==root->saleId){
            return root;
        }
        else if(saleId < root->saleId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
void addEmployee(Employee*&eroot){
    int id;
    string name;
    float salary;
    cout<<"\n----Employee Detials----"<<endl;
    cout<<"Enter Employee ID: ";
    cin>>id;
    while(searchemployeebyId(eroot,id)!=NULL){
        cout<<"ID already exists. Enter a different ID: ";
        cin>>id;
    }
    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter salary: ";
    cin>>salary;
    Employee*newemployee=new Employee(id,name,salary);
    eroot=insertEmployee(eroot,newemployee);
    cout<<"Employee added successfully"<<endl;
}
void addCustomer(Customer*&croot){
    int id;
    string name,address;
    cout<<"\n----Customer Detials----"<<endl;
    cout<<"Enter Customer ID: ";
    cin>>id;
    while(searchcustomer(croot,id)!=NULL){
        cout<<"ID already exists. Enter a different ID: ";
        cin>>id;
    }
    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter Address: ";
    getline(cin,address);
    Customer*newcustomer=new Customer(id,name,address);
    croot=insertCustomer(croot,newcustomer);
    cout<<"Customer added successfully"<<endl;
}
//Add sale and link Employee and customer
void addSale(Employee*eroot,Customer*croot,Sale*&sroot){
    int saleId,employeeId,customerId;
    float amount;
    string date;
    cout<<"\n----Sales Detials----"<<endl;
    cout<<"Enter Sales ID: ";
    cin>>saleId;
    while(searchsale(sroot,saleId)!=NULL){
        cout<<"ID already exists. Enter a different ID: ";
        cin>>saleId;
    }
    Employee*e;
    while(true){
        cout<<"Enter Employee ID: ";
        cin>>employeeId;
        e=eroot;
        while(e!=NULL){
            if(employeeId==e->employeeId){
                break;
            }
            else if(employeeId < e->employeeId){
                e=e->left;
            }
            else
            e=e->right;
        }
        if(e==NULL){
            cout<<"Employee not found.Enter a valid ID."<<endl;
        }
        else{
            break;
        }
    }
    Customer*c;
    while(true){
        cout<<"Enter Customer ID: ";
        cin>>customerId;
        c=croot;
        while(c!=NULL)
        { 
            if(customerId==c->customerId){
            break;
            }
            else if(customerId < c->customerId){
                c=c->left;
            }
            else
            c=c->right;
        }
        if(c==NULL){
            cout<<"Customer not found.Enter a valid ID."<<endl;
        }
        else{
            break;
        }
    }
    cout<<"Enter amount: ";
    cin>>amount;
    cout<<"Enter date: ";
    cin.ignore();
    getline(cin,date);
    Sale*newsale=new Sale(saleId,e,c,amount,date);
    sroot=insertSale(sroot,newsale);
    cout<<"Sales added successfully"<<endl;
}
Employee*searchemployeebyName(Employee*root,string empName){
    if(root==NULL){
        return NULL;
    }
    if(root->empName==empName){
        return root;
    }
    Employee*left=searchemployeebyName(root->left,empName);
    Employee*right=searchemployeebyName(root->right,empName);
    if(left!=NULL){
        return left;
    }
    else{
        return right;
    }
}
//displays all sales by a particular employee.                                                                                                                                                                                                                                               
void searchSalesReport(Sale*root,int employeeId){
    if(root==NULL){
        return;
    }
    searchSalesReport(root->left,employeeId);
    if(root->employee->employeeId==employeeId){
        cout<<"Sale ID: "<<root->saleId;
        cout<<"\nCustomer ID: "<<root->customer->customerId;
        cout<<"\nAmount: "<<root->amount;
        cout<<"\nCustomer Name: "<<root->customer->cusName<<endl;
    }
    searchSalesReport(root->right,employeeId);
}
//calculates employee sales count and total amount
void employeesummary(Sale*root,int employeeId,int&count,float&totalamount){
    if(root==NULL){
        return;
    }
    employeesummary(root->left,employeeId,count,totalamount);
        if(root->employee->employeeId==employeeId){
            count++;
            totalamount+=root->amount;
    }
    employeesummary(root->right,employeeId,count,totalamount);
}
//calculates sales count and amount for a specific employee-customer pair using Inorder traversal.
void customersalesummary(Sale*root,int employeeId,int customerId,int&count,float&amount){ 
    if(root==NULL){
        return;
    }
    customersalesummary(root->left,employeeId,customerId,count,amount); 
    if(root->employee->employeeId==employeeId && root->customer->customerId==customerId){
        count++; 
        amount+=root->amount;
    }
    customersalesummary(root->right,employeeId,customerId,count,amount);
}
void customergrouping(Customer*root,Sale*sroot,int employeeId){
    if(root==NULL){
        return;
    }
    customergrouping(root->left,sroot,employeeId);
    int count=0;
    float amount=0;
    customersalesummary(sroot,employeeId,root->customerId,count,amount);
    if(count>0){
        cout<<"\nCustomer Name: "<<root->cusName;
        cout<<"\nNo.Of.Sales: "<<count;
        cout<<"\nTotal Amount: "<<amount<<endl;
    }
    customergrouping(root->right,sroot,employeeId);
}
int countEmp(Employee*root){
    if(root==NULL){
        return 0;
    }
    return 1+countEmp(root->left)+countEmp(root->right);
}
int countCust(Customer*root){
    if(root==NULL){
        return 0;
    }
    return 1+countCust(root->left)+countCust(root->right);
}
int countSale(Sale*root){
    if(root==NULL){
        return 0;
    }
    return 1+countSale(root->left)+countSale(root->right);
}

void serializeEmp(Employee*root,vector<char>&bytes){
    if(root==NULL){
        return;
    }
    char*
    p=(char*)&root->employeeId;
    for(int i=0;i<sizeof(root->employeeId);i++){
        bytes.push_back(p[i]);
    }
    int len=root->empName.length();
    p=(char*)&len;
    for(int i=0;i<sizeof(len);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<len;i++){
        bytes.push_back(root->empName[i]);
    }
    p=(char*)&root->salary;
    for(int i=0;i<sizeof(root->salary);i++){
        bytes.push_back(p[i]);
    }
    serializeEmp(root->left,bytes);
    serializeEmp(root->right,bytes);
}
void serializeCust(Customer*root,vector<char>&bytes){
    if(root==NULL){
        return;
    }
    char*
    p=(char*)&root->customerId;
    for(int i=0;i<sizeof(root->customerId);i++){
        bytes.push_back(p[i]);
    }
    int len=root->cusName.length();
    p=(char*)&len;
    for(int i=0;i<sizeof(len);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<len;i++){
        bytes.push_back(root->cusName[i]);
    }
    len=root->address.length();
    p=(char*)&len;
    for(int i=0;i<sizeof(len);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<len;i++){
        bytes.push_back(root->address[i]);
    }
    serializeCust(root->left,bytes);
    serializeCust(root->right,bytes);
}
void serializeSale(Sale*root,vector<char>&bytes){
    if(root==NULL){
        return;
    }
        char*
        p=(char*)&root->saleId;
        for(int i=0;i<sizeof(root->saleId);i++){
            bytes.push_back(p[i]);
        }
        p=(char*)&root->employee->employeeId;
        for(int i=0;i<sizeof(root->employee->employeeId);i++){
            bytes.push_back(p[i]);
        }
        p=(char*)&root->customer->customerId;
        for(int i=0;i<sizeof(root->customer->customerId);i++){
            bytes.push_back(p[i]);
        }
        p=(char*)&root->amount;
        for(int i=0;i<sizeof(root->amount);i++){
            bytes.push_back(p[i]);
        }
        int len=root->date.length();
        p=(char*)&len;
        for(int i=0;i<sizeof(len);i++){
            bytes.push_back(p[i]);
        }
        for(int i=0;i<len;i++){
            bytes.push_back(root->date[i]);
        }
        serializeSale(root->left,bytes);
        serializeSale(root->right,bytes);
    }
/*Creates a byte vector to store data
count total emp and store count as bytes
serialize all emp records and append them to byte vector
same logic repeats to customer and sale then return as byte streams*/
void serialize(Employee*eroot,Customer*croot,Sale*sroot,vector<char>&bytes){
    int ecount=countEmp(eroot);
    char* p=(char*)&ecount;
    for(int i=0;i<sizeof(ecount);i++){
        bytes.push_back(p[i]);
    }
    serializeEmp(eroot,bytes);
    int ccount=countCust(croot);
    p=(char*)&ccount;
    for(int i=0;i<sizeof(ccount);i++){
        bytes.push_back(p[i]);
    }
    serializeCust(croot,bytes);
    int scount=countSale(sroot);
    p=(char*)&scount;
    for(int i=0;i<sizeof(scount);i++){
        bytes.push_back(p[i]);
    }
    serializeSale(sroot,bytes);
}
/*open the binary file.Then store employee,customer and sales counts. 
After that serialize each BST and write all node data into the file.*/
void writefile(Employee*eroot,Customer*croot,Sale*sroot){
    vector<char> bytes;
    serialize(eroot,croot,sroot,bytes);
    ofstream file("data.bin",ios::binary);
    if(!file){
        cout<<"File error";
        return;
    }
    file.write(bytes.data(),bytes.size());
    file.close();
    cout<<"Data saved successfully"<<endl;
}
/*Set a index value for the position in byte array
reads emp count
creates emp obj using reconstructed data
insert emp into emp tree
repeats logic to cus and sale*/
void deseralization(vector<char>&bytes,Employee*&eroot,Customer*&croot,Sale*&sroot){
    int index=0;
    int countEmp;
    char* p=(char*)&countEmp;
    for(int i=0;i<sizeof(countEmp);i++){
        p[i]=bytes[index++];
    }
    for(int i=0;i<countEmp;i++){
        int employeeId,len;
        string empName;
        float salary;
        p=(char*)&employeeId;
        for(int j=0;j<sizeof(employeeId);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        vector<char>buffer(len+1);
        for(int j=0;j<len;j++){
            buffer[j]=bytes[index++];
        }
        buffer[len]=0;
        empName=buffer.data();
        p=(char*)&salary;
        for(int j=0;j<sizeof(salary);j++){
            p[j]=bytes[index++];
        }
        Employee*employee=new Employee(employeeId,empName,salary);
        eroot=insertEmployee(eroot,employee);
    }
    int countCust;
    p=(char*)&countCust;
    for(int i=0;i<sizeof(countCust);i++){
        p[i]=bytes[index++];
    }
    for(int i=0;i<countCust;i++){
        int customerId,len;
        string cusName,address;
        p=(char*)&customerId;
        for(int j=0;j<sizeof(customerId);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        vector<char>buffer(len+1);
        for(int j=0;j<len;j++){
            buffer[j]=bytes[index++];
        }
        buffer[len]=0;
        cusName=buffer.data();
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        buffer.resize(len+1);
        for(int j=0;j<len;j++){
            buffer[j]=bytes[index++];
        }
        buffer[len]=0;
        address=buffer.data();
        Customer*customer=new Customer(customerId,cusName,address);
        croot=insertCustomer(croot,customer);
    }
    int countSale;
    p=(char*)&countSale;
    for(int i=0;i<sizeof(countSale);i++){   
        p[i]=bytes[index++];
    }
    for(int i=0;i<countSale;i++){
        int saleId,employeeId,customerId,len;
        float amount;
        string date;
        p=(char*)&saleId;
        for(int j=0;j<sizeof(saleId);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&employeeId;
        for(int j=0;j<sizeof(employeeId);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&customerId;
        for(int j=0;j<sizeof(customerId);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&amount;
        for(int j=0;j<sizeof(amount);j++){
            p[j]=bytes[index++];
        }
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        vector<char>buffer(len+1);
        for(int j=0;j<len;j++){
            buffer[j]=bytes[index++];
        }
        buffer[len]=0;
        date=buffer.data();
        Employee*employee=searchemployeebyId(eroot,employeeId);
        Customer*customer=searchcustomer(croot,customerId);
        Sale*sale=new Sale(saleId,employee,customer,amount,date);
        sroot=insertSale(sroot,sale);
    }
}
/*create a byte vector to store file data
read all bytes from the file and store in vector
deserialize the byte data and rebuild emp,cus and sale tree*/
void readfile(Employee*&eroot,Customer*&croot,Sale*&sroot){
    ifstream file("data.bin",ios::binary);
    if(!file){
        cout<<"File error";
        return;
    }
    vector<char> bytes;
    char c;
    while(file.get(c)){
        bytes.push_back(c);
    }
    deseralization(bytes,eroot,croot,sroot);
    file.close();
    cout<<"Data loaded successfully"<<endl;
}
int main(){
    Employee*eroot=NULL;
    Customer*croot=NULL;
    Sale*sroot=NULL;
    readfile(eroot,croot,sroot);
    int n;
    cout<<"Enter no.of Employees: ";
    cin>>n;
    for(int i=0;i<n;i++){
        addEmployee(eroot);
    }
    cout<<"\nEnter no.of Cutomers: ";
    cin>>n;
    for(int i=0;i<n;i++){
        addCustomer(croot);
    }
    cout<<"\nEnter no.of Sales: ";
    cin>>n;
    for(int i=0;i<n;i++){
        addSale(eroot,croot,sroot);
    }
    char choice;
    do{
    string empName;
    cout<<"\nEnter Employee Name to search: ";
    getline(cin>>ws,empName);
    Employee*employee=searchemployeebyName(eroot,empName);
    if(employee!=NULL){
        cout<<"----Employee Report----"<<endl;
        cout<<"Employee ID: "<<employee->employeeId<<endl;
        cout<<"Employee Name: "<<employee->empName<<endl;
        cout<<"Salary: "<<employee->salary<<endl;
        cout<<"\n----Sales Detials----"<<endl;
        searchSalesReport(sroot,employee->employeeId);
        int count=0;
        float totalamount=0;
        employeesummary(sroot,employee->employeeId,count,totalamount);
        cout<<"\n----Summary Report----"<<endl;
        cout<<"Total Sales Count: "<<count<<endl;
        cout<<"Total Sales Amount: "<<totalamount<<endl;
        cout<<"\n----Customer Wise Summary----";
        customergrouping(croot,sroot,employee->employeeId);
    }
    else{
        cout<<"Employee Not Found"<<endl;
    }
    cout<<"Search another employee?(y/n): ";
    cin>>choice;
}while(choice=='y'||choice=='Y');
    writefile(eroot,croot,sroot);
    return 0;
}
