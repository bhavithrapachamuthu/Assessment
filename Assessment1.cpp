#include<iostream>
#include<vector>
using namespace std;
class Employee{
    public:
    int employeeId;
    char empName[50];
    float salary;
    Employee*left;
    Employee*right;
};
class Customer{
    public:
    int customerId;
    char cusName[50];
    char address[100];
    Customer*left;
    Customer*right;
};
class Sale{
    public:
    int saleId;
    Employee*employee;
    Customer*customer;
    float amount;
    char date[15];
    Sale*left;
    Sale*right;
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
    char name[50];
    float salary;
    cout<<"\n----Employee Detials----"<<endl;
    cout<<"Enter Employee ID: ";
    cin>>id;
    while(cin.fail() || searchemployeebyId(eroot,id)!=NULL){
        if(cin.fail()){
            cout<<"Invalid ID.Enter Numbers only: ";
            cin.clear();
            cin.ignore(50,'\n');
        }
        else{
        cout<<"ID already exists.Enter different Id: ";
        }
        cin>>id;
    }
    cout<<"Enter Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter salary: ";
    cin>>salary;
    Employee*e=new Employee;
    e->employeeId=id;
    e->salary=salary;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(100000,'\n');
        cin>>salary;
    }
    int i=0;
    for(i=0;name[i]!=0;i++){
        e->empName[i]=name[i];
    }
    e->empName[i]=0;
    e->left=NULL;
    e->right=NULL;
    eroot=insertEmployee(eroot,e);
    cout<<"Employee added successfully"<<endl;
}
void addCustomer(Customer*&croot){
    int id;
    char name[50],address[100];
    cout<<"\n----Customer Detials----"<<endl;
    cout<<"Enter Customer ID: ";
    cin>>id;
    while(cin.fail() || searchcustomer(croot,id)!=NULL){
        if(cin.fail()){
            cout<<"Invalid ID.Enter Numbers only: ";
            cin.clear();
            cin.ignore(50,'\n');
        }
        else{
        cout<<"ID already exists.Enter different Id: ";
        }
        cin>>id;
    }
    cout<<"Enter Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter Address: ";
    cin.getline(address,100);
    Customer*c=new Customer;
    c->customerId=id;
    int i=0;
    for(i=0;name[i]!=0;i++){
        c->cusName[i]=name[i];
    }
    c->cusName[i]=0;
    int j=0;
    for(j=0;address[j]!=0;j++){
        c->address[j]=address[j];
        }
    c->address[j]=0;
    c->left=NULL;
    c->right=NULL;
    croot=insertCustomer(croot,c);
    cout<<"Customer added successfully"<<endl;
}
//Add sale and link Employee and customer
void addSale(Employee*eroot,Customer*croot,Sale*&sroot){
    int saleId,employeeId,customerId;
    float amount;
    char date[15];
    cout<<"\n----Sales Detials----"<<endl;
    cout<<"Enter Sales ID: ";
    cin>>saleId;
    while(cin.fail() || searchsale(sroot,saleId)!=NULL){
        if(cin.fail()){
            cout<<"Invalid ID.Enter Numbers only: ";
            cin.clear();
            cin.ignore(50,'\n');
        }
        else{
        cout<<"ID already exists.Enter different Id: ";
        }
        cin>>saleId;
    }
    Employee*e;
    while(true){
        cout<<"Enter Employee ID: ";
        cin>>employeeId;
        while(cin.fail()){
            cout<<"Invalid ID.Enter Numbers only: ";
            cin.clear();
            cin.ignore(50,'\n');
            cin>>employeeId;
        }
        e=searchemployeebyId(eroot,employeeId);
        if(e==NULL){
            cout<<"Employee not found.Enter a valid ID."<<endl;
        }
        else{
            break;
        }
    }
    Customer*c=NULL;
    while(true){
        cout<<"Enter Customer ID: ";
        cin>>customerId;
        while(cin.fail()){
            cout<<"Invalid ID.Enter Numbers only: ";
            cin.clear();
            cin.ignore(50,'\n');
            cin>>customerId;
        }
        c=searchcustomer(croot,customerId);
        if(e==NULL){
            cout<<"Customer not found.Enter a valid ID."<<endl; 
        }
        else{
            break;
        }
    }
    cout<<"Enter amount: ";
    cin>>amount;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(100000,'\n');
        cin>>amount;
    }
    cout<<"Enter date: ";
    cin.ignore();
    cin.getline(date,15);
    Sale*s=new Sale;
    s->saleId=saleId;
    s->employee=e;
    s->customer=c;
    s->amount=amount;
    int i=0;
    for(i=0;date[i]!=0;i++){
        s->date[i]=date[i];
    }
    s->date[i]=0;
    s->left=NULL;
    s->right=NULL;
    sroot=insertSale(sroot,s);
    cout<<"Sales added successfully"<<endl;
}
Employee*searchemployeebyName(Employee*root,char empName[]){
    if(root==NULL){
        return NULL;
    }
    int found=1;
    int i=0;
    while(root->empName[i]!=0 && empName[i]!=0){
        if(root->empName[i]!=empName[i]){
            found=0;
            break;
        }
        i++;
    }
    if(found==1 && root->empName[i]==0 && empName[i]==0){
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
    int len=0;
    while(root->empName[len]!=0){
        len++;
    }
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
    int len=0;
    while(root->cusName[len]!=0){
        len++;
    }
    p=(char*)&len;
    for(int i=0;i<sizeof(len);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<len;i++){
        bytes.push_back(root->cusName[i]);
    }
    len=0;
    while(root->address[len]!=0){
        len++;
    }
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
        int len=0;
        while(root->date[len]!=0){
            len++;
        }
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
    FILE*f=fopen("data.bin","wb");
    if(!f){
        cout<<"File error";
        return;
    }
    fwrite(bytes.data(),sizeof(char),bytes.size(),f);
    fclose(f);
    cout<<"Data saved successfully"<<endl;
}
/*Set a index value for the position in byte array
reads emp count
creates emp obj using reconstructed data
insert emp into emp tree
repeats logic to cus and sale*/
void deseralization(vector<char>&bytes,Employee*&eroot,Customer*&croot,Sale*&sroot){
    int index=0;
    //Employee
    int countEmp;
    char* p=(char*)&countEmp;
    for(int i=0;i<sizeof(countEmp);i++){
        p[i]=bytes[index++];//Outer loop, reading each record
    }
    for(int i=0;i<countEmp;i++){
        int employeeId,len;
        float salary;
        Employee*e=new Employee;
        p=(char*)&employeeId;
        for(int j=0;j<sizeof(employeeId);j++){ //inner loop, reading each bytes of a reacord
            p[j]=bytes[index++];//to move next byte
        }
        e->employeeId=employeeId;
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        for(int j=0;j<len;j++){
            e->empName[j]=bytes[index++];
        }
        e->empName[len]=0;
        p=(char*)&salary;
        for(int j=0;j<sizeof(salary);j++){
            p[j]=bytes[index++];
        }
        e->salary=salary;
        e->left=NULL;
        e->right=NULL;
        eroot=insertEmployee(eroot,e);
    }
    //Customer
    int countCust;
    p=(char*)&countCust;
    for(int i=0;i<sizeof(countCust);i++){
        p[i]=bytes[index++];
    }
    for(int i=0;i<countCust;i++){
        int customerId,len;
        Customer*c=new Customer;
        //Cus Id
        p=(char*)&customerId;
        for(int j=0;j<sizeof(customerId);j++){
            p[j]=bytes[index++];
        }
        c->customerId=customerId;
        //Cus Name
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        for(int j=0;j<len;j++){
            c->cusName[j]=bytes[index++];
        }
        c->cusName[len]=0;
        //Address
        p=(char*)&len;
        for(int j=0;j<sizeof(len);j++){
            p[j]=bytes[index++];
        }
        for(int j=0;j<len;j++){
            c->address[j]=bytes[index++];
        }
        c->address[len]=0;
        c->left=NULL;
        c->right=NULL;
        croot=insertCustomer(croot,c);
    }
    //Sale
    int countSale;
    p=(char*)&countSale;
    for(int i=0;i<sizeof(countSale);i++){   
        p[i]=bytes[index++];
    }
    for(int i=0;i<countSale;i++){
        int saleId,employeeId,customerId,len;
        float amount;
        char date[11];
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
        for(int j=0;j<len;j++){
            date[j]=bytes[index++];
        }
        date[len]=0;
        Employee*employee=searchemployeebyId(eroot,employeeId);
        Customer*customer=searchcustomer(croot,customerId);
        Sale*s=new Sale;
        s->saleId=saleId;
        s->employee=employee;
        s->customer=customer;
        s->amount=amount;
        for(int j=0;j<len;j++){
            s->date[j]=date[j];
        }
        s->date[len]=0;
        s->left=NULL;
        s->right=NULL;
        sroot=insertSale(sroot,s);
    }
}
/*create a byte vector to store file data
read all bytes from the file and store in vector
deserialize the byte data and rebuild emp,cus and sale tree*/
void readfile(Employee*&eroot,Customer*&croot,Sale*&sroot){
    FILE*f=fopen("data.bin","rb");
    if(!f){
        cout<<"File error";
        return;
    }
    vector<char> bytes;
    char c;
    while(fread(&c,1,1,f)){
        bytes.push_back(c);
    }
    deseralization(bytes,eroot,croot,sroot);
    fclose(f);
    cout<<"Data loaded successfully"<<endl; 
}
void deleteEmp(Employee*root){
    if(root==NULL){
        return;
    }
    deleteEmp(root->left);
    deleteEmp(root->right);
    delete root;
}
void deleteCus(Customer*root){
    if(root==NULL){
        return;
    }
    deleteCus(root->left);
    deleteCus(root->right);
    delete root;
}
void deleteSale(Sale*root){
    if(root==NULL){
        return;
    }
    deleteSale(root->left);
    deleteSale(root->right);
    delete root;
}
int main(){
    Employee*eroot=NULL;
    Customer*croot=NULL;
    Sale*sroot=NULL;
    readfile(eroot,croot,sroot);
    int n;
    cout<<"Enter no.of Employees: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addEmployee(eroot);
    }
    cout<<"\nEnter no.of Cutomers: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addCustomer(croot);
    }
    cout<<"\nEnter no.of Sales: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addSale(eroot,croot,sroot);
    }
    char choice;
    do{
    char empName[50];
    cout<<"\nEnter Employee Name to search: ";
    cin>>ws;
    cin.getline(empName,50);
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
    deleteEmp(eroot);
    deleteCus(croot);
    deleteSale(sroot);
    return 0;
}
