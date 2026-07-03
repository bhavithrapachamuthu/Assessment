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
        if(cin.fail()){
            cout<<"Invalid Sales ID.Enter numbers only"<<endl;
            return;
        }
    }
    cout<<"Enter Employee ID: ";
    cin>>employeeId;
    Employee*e=eroot;
    while(e!=NULL)
    {
        if(employeeId==e->employeeId){
            break;
        }
        else if(employeeId < e->employeeId){
            e=e->left;
        }
        else
        e=e->right;
    }
    cout<<"Enter Customer ID: ";
    cin>>customerId;
    Customer*c=croot;
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
    if(e==NULL||c==NULL) {
        cout<<"Employee or Customer not found"<<endl;
        return;
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
void serializeEmp(Employee*root,ofstream&file){
    if(root==NULL){
        return;
    }
    file.write((char*)&root->employeeId,sizeof(root->employeeId));
    int len=root->empName.length();
    file.write((char*)&len,sizeof(len));
    file.write(root->empName.data(),len);
    file.write((char*)&root->salary,sizeof(root->salary));
    serializeEmp(root->left,file);
    serializeEmp(root->right,file);
}
void serializeCust(Customer*root,ofstream&file){
    if(root==NULL){
        return;
    }
    file.write((char*)&root->customerId,sizeof(root->customerId));
    int len=root->cusName.length();
    file.write((char*)&len,sizeof(len));
    file.write(root->cusName.data(),len);
    len=root->address.length();
    file.write((char*)&len,sizeof(len));
    file.write(root->address.data(),len);
    serializeCust(root->left,file);
    serializeCust(root->right,file);
}
void serializeSale(Sale*root,ofstream&file){
    if(root==NULL){
        return;
    }
    file.write((char*)&root->saleId,sizeof(root->saleId));
    int empId=root->employee->employeeId;
    file.write((char*)&empId,sizeof(empId));
    int cusId=root->customer->customerId;
    file.write((char*)&cusId,sizeof(cusId));
    file.write((char*)&root->amount,sizeof(root->amount));
    int len=root->date.length();
    file.write((char*)&len,sizeof(len));
    file.write(root->date.data(),len);
    serializeSale(root->left,file);
    serializeSale(root->right,file);
}
/*open the binary file.Then store employee,customer and sales counts. 
After that serialize each BST and write all node data into the file.*/
void writefile(Employee*eroot,Customer*croot,Sale*sroot){
    ofstream file("data.bin",ios::binary);
    if(!file){
        cout<<"File error";
        return;
    }
    //Employee
    int empcount=countEmp(eroot);
    file.write((char*)&empcount,sizeof(empcount));
    serializeEmp(eroot,file);
    //Customer
    int custcount=countCust(croot);
    file.write((char*)&custcount,sizeof(custcount));
    serializeCust(croot,file);
    //Sale
    int salecount=countSale(sroot);
    file.write((char*)&salecount,sizeof(salecount));
    serializeSale(sroot,file);
    file.close();
    cout<<"Data saved successfully"<<endl;
}
/*open the binary file.Then read the stored counts.
After that read all employee,customer and sales data,recreate the objects and rebuild the tree.
restore the links between sales,employees and customers and close the file.*/
void readfile(Employee*&eroot,Customer*&croot,Sale*&sroot){
    ifstream file("data.bin",ios::binary);
    if(!file){
        cout<<"File Error"<<endl;
        return;
    }
    int countEmp;
    file.read((char*)&countEmp,sizeof(countEmp));
    for(int i=0;i<countEmp;i++){
        int employeeId,len;
        float salary;
        string empName;
        file.read((char*)&employeeId,sizeof(employeeId));
        file.read((char*)&len,sizeof(len));
        vector<char>buffer(len+1);
        file.read(buffer.data(),len);
        buffer[len]=0;
        empName=buffer.data();
        file.read((char*)&salary,sizeof(salary));
        Employee*employee=new Employee(employeeId,empName,salary);
        eroot=insertEmployee(eroot,employee);
    }
    int countCust;
    file.read((char*)&countCust,sizeof(countCust));
    for(int i=0;i<countCust;i++){
        int customerId,len;
        string address,custName;
        file.read((char*)&customerId,sizeof(customerId));
        //Customer name
        file.read((char*)&len,sizeof(len));
        vector<char>buffer1(len+1);
        file.read(buffer1.data(),len);
        buffer1[len]=0;
        custName=buffer1.data();
        //Customer address
        file.read((char*)&len,sizeof(len));
        vector<char>buffer2(len+1);
        file.read(buffer2.data(),len);
        buffer2[len]=0;
        address=buffer2.data();
        Customer*customer=new Customer(customerId,custName,address);
        croot=insertCustomer(croot,customer);
    }
    int countSale;
    file.read((char*)&countSale,sizeof(countSale));
    for(int i=0;i<countSale;i++) {
        int saleId,employeeId,customerId,len;
        float amount;
        string date;
        file.read((char*)&saleId,sizeof(saleId));
        file.read((char*)&employeeId,sizeof(employeeId));
        file.read((char*)&customerId,sizeof(customerId));
        file.read((char*)&amount,sizeof(amount));
        file.read((char*)&len,sizeof(len));
        vector<char>buffer(len+1);
        file.read(buffer.data(),len);
        buffer[len]=0;
        date=buffer.data();
        Employee*employee=searchemployeebyId(eroot,employeeId);
        Customer*customer=searchcustomer(croot,customerId);
        Sale*sale=new Sale(saleId,employee,customer,amount,date);
        sroot=insertSale(sroot,sale);
    }
    file.close();
    cout<<"Data Loaded successfully"<<endl;
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
