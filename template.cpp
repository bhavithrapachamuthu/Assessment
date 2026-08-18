#include<iostream>
#include<vector>
using namespace std;
template<class T>
class Tree{
    public:
    T data;
    Tree<T>*left;
    Tree<T>*right;
    Tree(){
        left=NULL;
        right=NULL;
    }
};
class Data{
    public:
    int id;
};
class Employee:public Data{
    public:
    char empName[50];
    float salary;
};
class Customer:public Data{
    public: 
    char cusName[50];
    char address[100];
};
class Sale:public Data{
    public:
    Employee*emp;
    Customer*cus;
    float amount;
    char date[20];
};
template<typename T>
Tree<T>* insert(Tree<T>*root,Tree<T>*newnode){
    if(root==NULL){
        return newnode;
    }
    if(newnode->data.id<root->data.id){
        root->left=insert(root->left,newnode);
    }
    else if(newnode->data.id>root->data.id){
        root->right=insert(root->right,newnode);
    }
    return root;
}
template<typename T>
Tree<T>*searchbyId(Tree<T>*root,int id){
    while(root!=NULL){
        if(id==root->data.id){
            return root;
        }
        else if(id<root->data.id){
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
        cout<<"Invalid Id.Enter only numbers: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>id;
    }
    return id;
}
void addEmp(Tree<Employee>*&eroot){
    Tree<Employee>*e=new Tree<Employee>;
    cout<<"\n---Employee Details---"<<endl;
    cout<<"Enter Employee Id: ";
    e->data.id=validation();
    while(searchbyId(eroot,e->data.id)!=NULL){
        cout<<"ID already exist.Enter different Id: ";
        e->data.id=validation();
    }
    cout<<"Enter Employee Name: ";
    cin.ignore();
    cin.getline(e->data.empName,50);
    cout<<"Enter Salary: ";
    cin>>e->data.salary;
    while(cin.fail()){
        cout<<"Enter only numbers: ";
        cin.clear();
        cin.ignore(500000,'\n');
        cin>>e->data.salary;
    }
    e->left=NULL;
    e->right=NULL;
    eroot=insert(eroot,e);
    cout<<"Employee added successfully"<<endl;
}
void addCus(Tree<Customer>*&croot){
    Tree<Customer>*c=new Tree<Customer>;
    cout<<"\n---Customer Details---"<<endl;
    cout<<"Enter Customer ID: ";
    c->data.id=validation();
    while(searchbyId(croot,c->data.id)!=NULL){
        cout<<"ID already exist.Enter different Id: ";
        c->data.id=validation();
    }
    cout<<"Enter Customer Name: ";
    cin.ignore();
    cin.getline(c->data.cusName,50);
    cout<<"Enter address: ";
    cin.getline(c->data.address,100);
    c->left=NULL;
    c->right=NULL;
    croot=insert(croot,c);
}
void addSale(Tree<Sale>*&sroot,Tree<Employee>*&eroot,Tree<Customer>*&croot){
    int empId,cusId;
    Tree<Sale>*s=new Tree<Sale>;
    cout<<"\n---Sale Details---"<<endl;
    cout<<"Enter Sale Id: ";
    s->data.id=validation();
    while(searchbyId(sroot,s->data.id)!=NULL){
        cout<<"ID already exists.Enter different Id: ";
        s->data.id=validation();
    }
    cout<<"Enter Employee Id: ";
    empId=validation();
    while(searchbyId(eroot,empId)==NULL){
        cout<<"Employee not Found.Enter valid Id: ";
        empId=validation();
    }
    cout<<"Enter Customer Id: ";
    cusId=validation();
    while(searchbyId(croot,cusId)==NULL){
        cout<<"Customer not Found.Enter valid Id: ";
        cusId=validation();
    }
    cout<<"Enter amount: ";
    cin>>s->data.amount;
    while(cin.fail()){
        cout<<"Enter only digits";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>s->data.amount;
    }
    cout<<"Enter Date: ";
    cin.ignore();
    cin.getline(s->data.date,20);
    s->data.emp=&(searchbyId(eroot,empId)->data);
    s->data.cus=&(searchbyId(croot,cusId)->data);
    sroot=insert(sroot,s);
    cout<<"Sale added successfully"<<endl;
}
void empReport(Tree<Sale>*root,int empId,int &count,float &total){
    if(root==NULL){
        return;
    }
    empReport(root->left,empId,count,total);
    if(root->data.emp!=NULL && root->data.cus!=NULL && root->data.emp->id==empId){
        cout<<"Sale Id: "<<root->data.id<<endl;
        cout<<"Customer Id: "<<root->data.cus->id<<endl;
        cout<<"Customer Name: "<<root->data.cus->cusName<<endl;
        cout<<"Sales Amount: "<<root->data.amount<<endl;
        count++;
        total=total+root->data.amount;
    }
    empReport(root->right,empId,count,total);
}
void cusReport(Tree<Sale>*root,int empId,int cusId,int &count,float&amount){
    if(root==NULL){
        return;
    }
    cusReport(root->left,empId,cusId,count,amount);
        if(root->data.emp!=NULL &&root->data.cus!=NULL){
            if(root->data.emp->id==empId && root->data.cus->id==cusId){
                count++;
                amount=amount+root->data.amount;
            }
        }
        cusReport(root->right,empId,cusId,count,amount);
}
//Customer grouping for particular employee
void cusGrouping(Tree<Customer>*root,Tree<Sale>*sroot,int empId){
    if(root==NULL){
        return;
    }
    cusGrouping(root->left,sroot,empId);
    int count=0;
    float amount=0;
    cusReport(sroot,empId,root->data.id,count,amount);
    if(count>0){
        cout<<"Customer Name: "<<root->data.cusName<<endl;
        cout<<"No.of sales: "<<count<<endl;
        cout<<"Total amount: "<<amount<<endl;
    }
    cusGrouping(root->right,sroot,empId);
}
Tree<Employee>*searchbyName(Tree<Employee>*root,char name[]){
    if(root==NULL){
        return NULL;
    }
    int found=1;
    int i=0;
    while(root->data.empName[i]!=0 && name[i]!=0){
        if(root->data.empName[i]!=name[i]){
            found=0;
            break;
        }
        i++;
    }
    if(found==1 && root->data.empName[i]==0 && name[i]==0){
        return root;
    }
    Tree<Employee>*left=searchbyName(root->left,name);
    if(left!=NULL){
        return left;
    }
    Tree<Employee>*right=searchbyName(root->right,name);
    return right;
}
template<typename T>
void serializevalue(T value,vector<char>&bytes){
    char*p=(char*)&value;
    for(int i=0;i<sizeof(T);i++){
        bytes.push_back(p[i]);
    }
}
void serializeEmp(Tree<Employee>*root,vector<char>&bytes){
    if(root==NULL){
        serializevalue(-1,bytes);
        return;
    }
    serializevalue(root->data.id,bytes);
    for(int i=0;i<50;i++){
        bytes.push_back(root->data.empName[i]);
    }
    serializevalue(root->data.salary,bytes);
    serializeEmp(root->left,bytes);
    serializeEmp(root->right,bytes);
}
void serializeCus(Tree<Customer>*root,vector<char>&bytes){
    if(root==NULL){
        serializevalue(-1,bytes);
        return;
    }
    serializevalue(root->data.id,bytes);
    for(int i=0;i<50;i++){
        bytes.push_back(root->data.cusName[i]);
    }
    for(int i=0;i<100;i++){
        bytes.push_back(root->data.address[i]);
    }
    serializeCus(root->left,bytes);
    serializeCus(root->right,bytes);
}
void serializeSale(Tree<Sale>*root,vector<char>&bytes){
    if(root==NULL){
        serializevalue(-1,bytes);
        return;
    }
    serializevalue(root->data.id,bytes);
    int empId=-1;
    if(root->data.emp!=NULL){
        empId=root->data.emp->id;
    }
    serializevalue(empId,bytes);
    int cusId=-1;
    if(root->data.cus!=NULL){
        cusId=root->data.cus->id;
    }
    serializevalue(cusId,bytes);
    serializevalue(root->data.amount,bytes);
    for(int i=0;i<20;i++){
        bytes.push_back(root->data.date[i]);
    }
    serializeSale(root->left,bytes);
    serializeSale(root->right,bytes);
}
void savefile(Tree<Employee>*eroot,Tree<Customer>*croot,Tree<Sale>*sroot){
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
template<typename T>
T deserializationValue(vector<char>&bytes,int&index){
    T value;
    char*p=(char*)&value;
    for(int i=0;i<sizeof(T);i++){
        p[i]=bytes[index++];
    }
    return value;
}
Tree<Employee>*deserializeEmp(vector<char>&bytes,int&index){
    int id=deserializationValue<int>(bytes,index);
    if(id==-1){
        return NULL;
    }
    Tree<Employee>*e=new Tree<Employee>;
    e->data.id=id;
    for(int i=0;i<50;i++){
        e->data.empName[i]=bytes[index++];
    }
    e->data.salary=deserializationValue<float>(bytes,index);
    e->left=deserializeEmp(bytes,index);
    e->right=deserializeEmp(bytes,index);
    return e;
}
Tree<Customer>*deserializeCus(vector<char>&bytes,int&index){
    int id=deserializationValue<int>(bytes,index);
    if(id==-1){
        return NULL;
    }
    Tree<Customer>*c=new Tree<Customer>;
    c->data.id=id;
    for(int i=0;i<50;i++){
        c->data.cusName[i]=bytes[index++];
    }
    for(int i=0;i<100;i++){
        c->data.address[i]=bytes[index++];
    }
    c->left=deserializeCus(bytes,index);
    c->right=deserializeCus(bytes,index);
    return c;
}
Tree<Sale>*deserializeSale(vector<char>&bytes,int&index,Tree<Employee>*eroot,Tree<Customer>*croot){
    int id=deserializationValue<int>(bytes,index);
    if(id==-1){
        return NULL;
    }
    Tree<Sale>*s=new Tree<Sale>;
    s->data.id=id;
    int empId=deserializationValue<int>(bytes,index);
    int cusId=deserializationValue<int>(bytes,index);
    s->data.amount=deserializationValue<float>(bytes,index);
    for(int i=0;i<20;i++){
        s->data.date[i]=bytes[index++];
    }
    //emp pointer reconnect
    if(empId!=-1){
        Tree<Employee>*e=searchbyId(eroot,empId);
        if(e!=NULL){
            s->data.emp=&e->data;
        }
        else{
            s->data.emp=NULL;
        }
    }
        //cus pointer reconnect
        if(cusId!=-1){
            Tree<Customer>*c=searchbyId(croot,cusId);
            if(c!=NULL){
                s->data.cus=&c->data;
            }
            else{
                s->data.cus=NULL;
            }
        }
        s->left=deserializeSale(bytes,index,eroot,croot);
        s->right=deserializeSale(bytes,index,eroot,croot);
        return s;
}
void loadfile(Tree<Employee>*&eroot,Tree<Customer>*&croot,Tree<Sale>*&sroot){
    FILE*f=fopen("data.bin","rb");
    if(f==NULL){
        cout<<"Previous data Not Found"<<endl;
        return;
    }
    vector<char>bytes;
    char c;
    while(fread(&c,sizeof(char),1,f)==1){
        bytes.push_back(c);
    }
    fclose(f);
    int index=0;
    eroot=deserializeEmp(bytes,index);
    croot=deserializeCus(bytes,index);
    sroot=deserializeSale(bytes,index,eroot,croot);
    cout<<"Data loaded successfully"<<endl;
}
template<typename T>
Tree<T>*deleteNode(Tree<T>*root,int id){
    if(root==NULL){
        return NULL;
    }
    if(id< root->data.id){
        root->left=deleteNode(root->left,id);
    }
    else if(id>root->data.id){
        root->right=deleteNode(root->right,id);
    }
    else{
        if(root->left==NULL && root->right==NULL){
            delete root;
            return NULL;
        }
        else if(root->left==NULL){
            Tree<T>*temp=root->right;
            delete root;
            return temp;
        }
        else if(root->right==NULL){
            Tree<T>*temp=root->left;
            delete root;
            return temp;
        }
        else{
            Tree<T>*temp=root->right;
            while(temp->left!=NULL){
               temp=temp->left; 
            }
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data.id);    
        }
    }
    return root;
}
int main(){
    Tree<Employee>*eroot=NULL;
    Tree<Customer>*croot=NULL;
    Tree<Sale>*sroot=NULL;
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
        addCus(croot);
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
        Tree<Employee>*e=searchbyName(eroot,empName);
        if(e!=NULL){
            cout<<"----Employee report----"<<endl;
            cout<<"Employee Id: "<<e->data.id<<endl;
            cout<<"Employee Name: "<<e->data.empName<<endl;
            cout<<"Salary: "<<e->data.salary<<endl;
            cout<<"\n----Sales Detials----"<<endl;
            int count=0;
            float total=0;
            empReport(sroot,e->data.id,count,total);
            cout<<"\n----Summary report----"<<endl;
            cout<<"Total sales count: "<<count<<endl;
            cout<<"Totat sales amount: "<<total<<endl;
            cout<<"\n----Customer wise summary----"<<endl;
            cusGrouping(croot,sroot,eroot->data.id);
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
        eroot=deleteNode(eroot,id);
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
    else if(searchbyId(croot,id)==NULL){
        cout<<"Customer not found"<<endl;
    }
    else{
        croot=deleteNode(croot,id);
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
    else if(searchbyId(sroot,id)==NULL){
        cout<<"Sale not found"<<endl;
    }
    else{
        sroot=deleteNode(sroot,id);
        cout<<"Sale Deleted Successfully"<<endl;
    }
    savefile(eroot,croot,sroot);
    return 0;
}
