#include<iostream>
#include<vector>
using namespace std;
class Employee{
    public:
    int empId;
    char empName[50];
    float salary;
    Employee*left;
    Employee*right;
};
class Customer{
    public:
    int cusId;
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
    char date[20];
    Sale*left;
    Sale*right;
};
Employee*insertEmployee(Employee*root,Employee*newnode){
    if(root==NULL){
        return newnode;
    }
    if(newnode->empId < root->empId){
        root->left=insertEmployee(root->left,newnode);
    }
    else if(newnode->empId > root->empId){
        root->right=insertEmployee(root->right,newnode);
    }
    return root;
}
Customer*insertCustomer(Customer*root,Customer*newnode){
    if(root==NULL){
        return newnode;
    }
    if(newnode->cusId < root->cusId){
        root->left=insertCustomer(root->left,newnode);
    }
    else if(newnode->cusId > root->cusId){
        root->right=insertCustomer(root->right,newnode);
    }
    return root;
}
Sale*insertSale(Sale*root,Sale*newnode){
    if(root==NULL){
        return newnode;
    }
    if(newnode->saleId < root->saleId){
        root->left=insertSale(root->left,newnode);
    }
    else if(newnode->saleId > root->saleId){
        root->right=insertSale(root->right,newnode);
    }
    return root;
}
Employee*searchbyId(Employee*root,int id){
    while(root!=NULL){
        if(id==root->empId){
            return root;
        }
        else if(id < root->empId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
Customer*searchcus(Customer*root,int id){
    while(root!=NULL){
        if(id==root->cusId){
            return root;
        }
        else if(id < root->cusId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
Sale*searchsale(Sale*root,int id){
    while(root!=NULL){
        if(id==root->saleId){
            return root;
        }
        else if(id < root->saleId){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return NULL;
}
int validation(){
    int id;
    cin>>id;
    while(cin.fail()){
        cout<<"Invalid ID.Enter only numbers: ";
        cin.clear();
        cin.ignore(100000,'\n');
        cin>>id;
    }
    return id;
}
void addEmp(Employee*&eroot){
    cout<<"\n---Employee Details---"<<endl;
    Employee*e=new Employee;
    cout<<"Enter Employee Id: ";
    e->empId=validation();
    while(searchbyId(eroot,e->empId)!=NULL){
        cout<<"Id already exits.Enter different Id: ";
        e->empId=validation();
    }
    cout<<"Enter Name: ";
    cin.ignore();
    cin.getline(e->empName,50);
    cout<<"Enter Salary: ";
    cin>>e->salary;
    //validations
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(500000,'\n');
        cin>>e->salary;
    }
    e->left=NULL;
    e->right=NULL;
    eroot=insertEmployee(eroot,e);
    cout<<"Employee added successfully"<<endl;
}
void addcus(Customer*&croot){
    cout<<"\n---Customer Details---"<<endl;
    Customer*c=new Customer;
    cout<<"Enter Customer Id: ";
    c->cusId=validation();
    while(searchcus(croot,c->cusId)!=NULL){
    cout<<"Id already exits.Enter different Id: ";
    c->cusId=validation();
    }
    cout<<"Enter Name: ";
    cin.ignore();
    cin.getline(c->cusName,50);
    cout<<"Enter Address: ";
    cin.getline(c->address,100);
    c->left=NULL;
    c->right=NULL;
    croot=insertCustomer(croot,c);
    cout<<"Customer added succesfully"<<endl;
}
void addSale(Sale*&sroot,Employee*eroot,Customer*croot){
    int empId,cusId;
    cout<<"\n---Sale Details---"<<endl;
    Sale*s=new Sale;
    cout<<"Enter Sale Id: ";
    s->saleId=validation();
    while(searchsale(sroot,s->saleId)!=NULL){
        cout<<"Id already exits.Enter different Id: ";
        s->saleId=validation();
    }
    cout<<"Enter Employee Id: ";
    empId=validation();
    while(searchbyId(eroot,empId)==NULL){
        cout<<"Employee not Found.Enter valid Id: ";
        empId=validation();
    }
    cout<<"Enter Customer Id: ";
    cusId=validation();
    while(searchcus(croot,cusId)==NULL){
        cout<<"Customer not Found.Enter valid Id: ";
        cusId=validation();
    }
    cout<<"Enter amount: ";
    cin>>s->amount;
    while(cin.fail()){
        cout<<"Enter only digits";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>s->amount;
    }
    cout<<"Enter Date: ";
    cin.ignore();
    cin.getline(s->date,20);
    s->employee=searchbyId(eroot,empId);
    s->customer=searchcus(croot,cusId);
    s->left=NULL;
    s->right=NULL;
    sroot=insertSale(sroot,s);
    cout<<"Sale added successfully"<<endl;
}
//Generates sales report for specific emp
void empReport(Sale*root,int empId,int&count,float&total){
    if(root==NULL){ 
        return;
    }
    empReport(root->left,empId,count,total);
    if(root->employee!=NULL && root->customer!=NULL && root->employee->empId==empId){
        cout<<"Sale Id: "<<root->saleId<<endl;
        cout<<"Customer ID: "<<root->customer->cusId<<endl;
        cout<<"Customer Name: "<<root->customer->cusName<<endl;
        cout<<"Sales Amount: "<<root->amount<<endl;
        count++;
        total=total+root->amount;
    }
    empReport(root->right,empId,count,total);
} 
void cusReport(Sale*root,int empId,int cusId,int&count,float&amount){ 
    if(root==NULL){
        return;
    }
    cusReport(root->left,empId,cusId,count,amount); 
    if(root->employee!=NULL && root->customer!=NULL){
    if(root->employee->empId==empId && root->customer->cusId==cusId){
        count++; 
        amount=amount+root->amount;
    }
 }
cusReport(root->right,empId,cusId,count,amount);
}
//Emp wise cus grouping report
void cusgrouping(Customer*root,Sale*sroot,int empId){
    if(root==NULL){
        return;
    }
    cusgrouping(root->left,sroot,empId);
    int count=0;
    float amount=0;
    cusReport(sroot,empId,root->cusId,count,amount);
    if(count>0){
        cout<<"Customer Name: "<<root->cusName<<endl;
        cout<<"No.Of.Sales: "<<count<<endl;
        cout<<"Total Amount: "<<amount<<endl;
    }
    cusgrouping(root->right,sroot,empId);
}
Employee*searchbyName(Employee*root,char name[]){
    if(root==NULL){
        return NULL;
    }
    int found=1;
    int i=0;
    while(root->empName[i]!=0 && name[i]!=0){
        if(root->empName[i]!=name[i]){
            found=0;
            break;
        }
        i++;
    }
    if(found==1 && root->empName[i]==0 && name[i]==0){
        return root;
    }
    Employee*left=searchbyName(root->left,name);
    if(left!=NULL){
        return left;
    }
    Employee*right=searchbyName(root->right,name);
    return right;
}
void serializeEmp(Employee*root,vector<char >&bytes){
    if(root==NULL){
        int value=-1;
        char*p=(char*)&value;
        for(int i=0;i<sizeof(int);i++){
            bytes.push_back(p[i]);
        }
        return;
    }
    char*p;
    p=(char*)&root->empId;
    for(int i=0;i<sizeof(int);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<50;i++){
        bytes.push_back(root->empName[i]);
    }
    p=(char*)&root->salary;
    for(int i=0;i<sizeof(float);i++){
        bytes.push_back(p[i]);
    }
    serializeEmp(root->left,bytes);
    serializeEmp(root->right,bytes);
}
void serializeCus(Customer*root,vector<char>&bytes){
    if(root==NULL){
        int value=-1;
        char*p=(char*)&value;
        for(int i=0;i<sizeof(int);i++){
            bytes.push_back(p[i]);
        }
        return;
    }
    char*p=(char*)&root->cusId;
    for(int i=0;i<sizeof(int);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<50;i++){
        bytes.push_back(root->cusName[i]);
    }
    for(int i=0;i<100;i++){
        bytes.push_back(root->address[i]);
    }
    serializeCus(root->left,bytes);
    serializeCus(root->right,bytes);
}
void serializeSale(Sale*root,vector<char>&bytes){
    if(root==NULL){
        int value=-1;
        char*p=(char*)&value;
        for(int i=0;i<sizeof(int);i++){
            bytes.push_back(p[i]);
        }
        return;
    }
    char*p=(char*)&root->saleId;
    for(int i=0;i<sizeof(int);i++){
        bytes.push_back(p[i]);
    }
    int empId=-1;
    if(root->employee!=NULL){
        empId=root->employee->empId;
    }
    p=(char*)&empId;
    for(int i=0;i<sizeof(int);i++){
        bytes.push_back(p[i]);
    }
    int cusId=-1;
    if(root->customer!=NULL){
        cusId=root->customer->cusId;
    }
    p=(char*)&cusId;
    for(int i=0;i<sizeof(int);i++){
        bytes.push_back(p[i]);
    }
    p=(char*)&root->amount;
    for(int i=0;i<sizeof(float);i++){
        bytes.push_back(p[i]);
    }
    for(int i=0;i<20;i++){
        bytes.push_back(root->date[i]);
    }
    serializeSale(root->left,bytes);
    serializeSale(root->right,bytes);
}
void savefile(Employee*eroot,Customer*croot,Sale*sroot){
    vector<char>bytes;
    serializeEmp(eroot,bytes);
    serializeCus(croot,bytes);
    serializeSale(sroot,bytes);
    FILE*f=fopen("data.bin","wb");
    if(f==NULL){
        cout<<"File open failed";
        return;
    }
    fwrite(bytes.data(),sizeof(char),bytes.size(),f);
    fclose(f);
    cout<<"Data saved successfully"<<endl;
}
Employee*deserializeEmp(vector<char>&bytes,int&index){
    int id;
    char*p=(char*)&id;
    for(int i=0;i<sizeof(int);i++){
        p[i]=bytes[index++];
    }
    if(id==-1){
        return NULL;
    }
    Employee*e=new Employee;
    e->empId=id;
    for(int i=0;i<50;i++){
        e->empName[i]=bytes[index++];
    }
    float salary;
    p=(char*)&salary;
    for(int i=0;i<sizeof(float);i++){
        p[i]=bytes[index++];
    }
    e->salary=salary;
    e->left=deserializeEmp(bytes,index);
    e->right=deserializeEmp(bytes,index);
    return e;
}
Customer*deserializeCus(vector<char>&bytes,int&index){
    int id;
    char*p=(char*)&id;
    for(int i=0;i<sizeof(int);i++){
        p[i]=bytes[index++];
    }
    if(id==-1){
        return NULL;
    }
    Customer*c=new Customer;
    c->cusId=id;
    for(int i=0;i<50;i++){
        c->cusName[i]=bytes[index++];
    }
    for(int i=0;i<100;i++){
        c->address[i]=bytes[index++];
    }
    c->left=deserializeCus(bytes,index);
    c->right=deserializeCus(bytes,index);
    return c;
}
Sale*deserializeSale(vector<char>&bytes,int&index,Employee*eroot,Customer*croot){
    int id;
    char*p=(char*)&id;
    for(int i=0;i<sizeof(int);i++){
        p[i]=bytes[index++];
    }
    if(id==-1){
        return NULL;
    }
    Sale*s=new Sale;
    s->saleId=id;
    int empId,cusId;
    p=(char*)&empId;
    for(int i=0;i<sizeof(int);i++){
        p[i]=bytes[index++];
    }
    if(empId==-1){
        s->employee=NULL;
    }
    else{
    s->employee=searchbyId(eroot,empId);
    }
    p=(char*)&cusId;
    for(int i=0;i<sizeof(int);i++){
        p[i]=bytes[index++];
    }
    if(cusId==-1){
        s->customer=NULL;
    }
    else{
    s->customer=searchcus(croot,cusId);
    }
    float amount;
    p=(char*)&amount;
    for(int i=0;i<sizeof(float);i++){
        p[i]=bytes[index++];
    }
    s->amount=amount;
    for(int i=0;i<20;i++){
        s->date[i]=bytes[index++];
    }
    s->left=deserializeSale(bytes,index,eroot,croot);
    s->right=deserializeSale(bytes,index,eroot,croot);
    return s;
}
void loadfile(Employee*&eroot,Customer*&croot,Sale*&sroot){
    FILE*f=fopen("data.bin","rb");
    if(f==NULL){
        cout<<"No previous Data found"<<endl;
        return;
    }
    vector<char> bytes;
    char c;
    while(fread(&c,sizeof(char),1,f)){
        bytes.push_back(c);
    }
    fclose(f);
    int index=0;
    eroot=deserializeEmp(bytes,index);
    croot=deserializeCus(bytes,index);
    sroot=deserializeSale(bytes,index,eroot,croot);    
    cout<<"Data loaded successfully"<<endl;
}
Employee*deleteEmp(Employee*root,int id){
    if(root==NULL){
        return NULL;
    }
    if(id<root->empId){
        root->left=deleteEmp(root->left,id);
    }
    else if(id>root->empId){
        root->right=deleteEmp(root->right,id);
    }
    else{
        //leaf node
        if(root->left==NULL && root->right==NULL){
            delete root;
            return NULL;
        }
        //1 child in left
        if(root->left==NULL){
            Employee*temp=root->right;
            delete root;
            return temp;
        }
        //1 child in right
        if(root->right==NULL){
            Employee*temp=root->left;
            delete root;
            return temp;
        }
        //2 child
        Employee*temp=root->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        root->empId=temp->empId;
        for(int i=0;i<50;i++){
            root->empName[i]=temp->empName[i];
        }
        root->salary=temp->salary;
        root->right=deleteEmp(root->right,temp->empId);
    }
    return root;
}
Customer*deleteCus(Customer*root,int id){
    if(root==NULL){
        return NULL;
    }
    if(id<root->cusId){
        root->left=deleteCus(root->left,id);
    }
    else if(id>root->cusId){
        root->right=deleteCus(root->right,id);
    }
    else{
        //leaf node
        if(root->left==NULL && root->right==NULL){
            delete root;
            return NULL;
        }
        //1 child in left
        if(root->left==NULL){
            Customer*temp=root->right;
            delete root;
            return temp;
        }
        //1 child in right
        if(root->right==NULL){
            Customer*temp=root->left;
            delete root;
            return temp;
        }
        //2 child
        Customer*temp=root->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        root->cusId=temp->cusId;
        for(int i=0;i<50;i++){
            root->cusName[i]=temp->cusName[i];
        }
        for(int i=0;i<100;i++){
            root->address[i]=temp->address[i];
        }
        root->right=deleteCus(root->right,temp->cusId);
    }
    return root;
}
Sale*deleteSale(Sale*root,int id){
    if(root==NULL){
        return NULL;
    }
    if(id<root->saleId){
        root->left=deleteSale(root->left,id);
    }
    else if(id>root->saleId){
        root->right=deleteSale(root->right,id);
    }
    else{
        //leaf node
        if(root->left==NULL && root->right==NULL){
            delete root;
            return NULL;
        }
        //1 child in right
        if(root->left==NULL){
            Sale*temp=root->right;
            delete root;
            return temp;
        }
        //1 child in left
        if(root->right==NULL){
            Sale*temp=root->left;
            delete root;
            return temp;
        }
        //2 child
        Sale*temp=root->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        root->saleId=temp->saleId;
        root->employee=temp->employee;
        root->customer=temp->customer;
        root->amount=temp->amount;
        for(int i=0;i<20;i++){
            root->date[i]=temp->date[i];
        }
        root->right=deleteSale(root->right,temp->saleId);
    }
    return root;
}
int main(){
    Employee*eroot=NULL;
    Customer*croot=NULL;
    Sale*sroot=NULL;
    loadfile(eroot,croot,sroot);
    int n;
    cout<<"No.of Employees: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addEmp(eroot);
    }
    cout<<"No.of Customers: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addcus(croot);
    }
    cout<<"No.of Sales: ";
    cin>>n;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>n;
    }
    for(int i=0;i<n;i++){
        addSale(sroot,eroot,croot);
    }
    char choice;
    do{
        char empName[50];
        cout<<"Enter Employee Name: ";
        cin>>ws;
        cin.getline(empName,50);
        Employee*e=searchbyName(eroot,empName);
        if(e!=NULL){
            cout<<"----Employee report----"<<endl;
            cout<<"Employee Id: "<<e->empId<<endl;
            cout<<"Employee Name: "<<e->empName<<endl;
            cout<<"Salary: "<<e->salary<<endl;
            cout<<"\n----Sales Detials----"<<endl;
            int count=0;
            float total=0;
            empReport(sroot,e->empId,count,total);
            cout<<"\n----Summary report----"<<endl;
            cout<<"Total sales count: "<<count<<endl;
            cout<<"Totat sales amount: "<<total<<endl;
            cout<<"\n----Customer wise summary----"<<endl;
            cusgrouping(croot,sroot,e->empId);
        }
        else{
            cout<<"Employee not Found"<<endl;
        }
        cout<<"Want to search another Employee?(y/n): ";
        cin>>choice;
    }while(choice=='y'||choice=='Y');
    int id;
    cout<<"Enter Employee Id to delete or(0 to cancel): ";
    cin>>id;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>id;
    }
    if(id==0){
        cout<<"Deletion cancelled"<<endl;
    }
    else if(searchbyId(eroot,id)==NULL){
        cout<<"Employee not found"<<endl;
    }
    else{
        eroot=deleteEmp(eroot,id);
        cout<<"Employee Deleted successfully"<<endl;
    }
    cout<<"Enter Customer Id to delete or(0 to cancel): ";
    cin>>id;
    while(cin.fail()){
    cout<<"Enter only numbers: ";
    cin.clear();
    cin.ignore(1000,'\n');
    cin>>id;
    }
    if(id==0){
        cout<<"Deletion Cancelled"<<endl;
    }
    else if(searchcus(croot,id)==NULL){
        cout<<"Customer not found"<<endl;
    }
    else{
        croot=deleteCus(croot,id);
        cout<<"Customer Deleted Successfully"<<endl;
    }
    cout<<"Enter Sale Id to delete or(0 to cancel): ";
    cin>>id;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin>>id;
    }
    if(id==0){
        cout<<"Deletion cancelled"<<endl;
    }
    else if(searchsale(sroot,id)==NULL){
        cout<<"Sale not found"<<endl;
    }
    else{
        sroot=deleteSale(sroot,id);
        cout<<"Sale Deleted Successfully"<<endl;
    }
    savefile(eroot,croot,sroot);
    return 0;
}
